#include "authsocket.h"
#include "authserver.h"
#include "utils/util.h"
#include "opcodes/opcodes.h"
#include "logs/log.h"
#include "configuration/configmgr.h"

AuthSocket::AuthSocket(QTcpSocket *socket) : SocketReader(socket)
{
    m_state = OnCheckingVersion;

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));

    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
    SendInitPacket();
}

AuthSocket::~AuthSocket() {}

void AuthSocket::OnClose()
{
    if(!m_infos.isEmpty())
        Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_STATE, 0, m_infos["account_id"].toInt());

    Log::Write(LOG_TYPE_NORMAL, "Closing connection with %s", m_socket->peerAddress().toString().toLatin1().data());
    AuthServer::Instance()->RemoveSocket(this);
    m_socket->deleteLater();
}

void AuthSocket::SendPacket(WorldPacket data)
{
    m_socket->write(data.GetPacket() + (char)0x00);
    Log::Write(LOG_TYPE_DEBUG, "Send packet %s ( Header : %s )", GetOpcodeName(data.GetOpcode()).toLatin1().data(), GetOpcodeHeader(data.GetOpcode()).toLatin1().data());
    if(data.GetPacket().length() > 0)
        Log::Write(LOG_TYPE_DEBUG, "Packet data : %s", QString(data.GetPacket()).toLatin1().data());
}

void AuthSocket::ProcessPacket(QString packet)
{
    if(packet.isEmpty())
        return;

    Log::Write(LOG_TYPE_DEBUG, "Received packet from <%s> : %s", m_socket->peerAddress().toString().toLatin1().data(), packet.toLatin1().data());

    // Phase d'authentification
    if(m_state != Logged)
    {
        if(m_state == OnCheckingVersion)
        {
            CheckVersion(packet);
        }
        else if(m_state == OnAuthentication)
        {
            // Limite de queue atteinte
            if(AuthQueue::Instance()->GetClientsCount() > ConfigMgr::Auth()->GetInt("QueueClientLimit"))
            {
                WorldPacket OutOfBounds(SMSG_QUEUE_OUT_OF_BOUNDS);
                SendPacket(OutOfBounds);
                return;
            }

            // Mauvais paquet : retour à l'étape 0 de l'authentification
            if(!packet.contains("#1"))
            {
                m_state = OnCheckingVersion;
                WorldPacket data(SMSG_LOGIN_ERROR);
                SendPacket(data);
                return;
            }

            AuthQueue::Instance()->AddClient(this);
            m_state = OnQueue;
            m_idsPacket = packet;
        }
        else if(m_state == OnQueue)
        {
            QueueManager();
        }
        return;
    }

    if(packet == "Af")
    {
        QueueManager();
        return;
    }

    if(packet == "Ax")
    {
        SendPersos();
        return;
    }

    if(packet.left(2) == "AX")
    {
        SelectServer(packet.mid(2).toUInt());
        return;
    }
}

void AuthSocket::SendInitPacket()
{
    QSqlQuery req = Database::Auth()->PQuery(AUTH_SELECT_IP_BANNED, m_socket->peerAddress().toString().toLatin1().data());
    if(req.first())
    {
        WorldPacket ban(SMSG_ACCOUNT_BANNED);
        SendPacket(ban);
        return;
    }

    WorldPacket data(SMSG_HELLO_CONNECTION_SERVER);
    m_hashKey = GenerateRandomString(32);
    data << m_hashKey;
    SendPacket(data);
}

void AuthSocket::SendPersos()
{
    WorldPacket persos(SMSG_GIVE_PERSOS);
    persos << QString::number(((ulong)m_infos["subscription_time"].toInt()) * 1000).toLatin1().data();
    QMap<int, int> serversPersos;
    QSqlQuery req = Database::Char()->PQuery(SELECT_ACCOUNT_CHARACTERS, m_infos["account_id"].toInt());
    while(req.next())
    {
        int curServerId = req.value(req.record().indexOf("server_id")).toInt();
        if(serversPersos.contains(curServerId))
            serversPersos[curServerId]++;
        else
            serversPersos.insert(curServerId, 1);
    }
    if(!serversPersos.isEmpty())
    {
        for(QMap<int, int>::Iterator i = serversPersos.begin(); i != serversPersos.end(); ++i)
        {
            persos << "|" << QString::number(i.key()) << "," << QString::number(i.value());
        }
    }

    SendPacket(persos);
}

void AuthSocket::QueueManager()
{
    WorldPacket queuePosition(SMSG_QUEUE_POSITION);

    if(!AuthQueue::Instance()->ClientInQueue(this)) // Non das la file
    {
        queuePosition << "1|1|0|1|-1";
    }
    else
    {
        queuePosition << QString::number(AuthQueue::Instance()->GetClientPosition(this)).toLatin1().data() << "|"; // Position dans la file
        queuePosition << QString::number(AuthQueue::Instance()->GetClientsCount()).toLatin1().data() << "|"; // Nombre d'abonnés dans la file
        queuePosition << "0|"; // Nombre de non abonnés
        queuePosition << "1|"; // Abonné ?
        queuePosition << "1"; // Queue id
    }

    SendPacket(queuePosition);
}

void AuthSocket::CheckVersion(QString version)
{
    QString acceptedClientVersion = ConfigMgr::Auth()->GetQString("AcceptClientVersion");
    if(version != acceptedClientVersion) // Mauvaise version
    {
        m_state = OnCheckingVersion;
        WorldPacket data(SMSG_BAD_VERSION);
        data << acceptedClientVersion;
        SendPacket(data);
        return;
    }

    m_state = OnAuthentication;
}

void AuthSocket::CheckAccount()
{
    QStringList identifiants = m_idsPacket.split("#1");
    QString account = identifiants.takeFirst();
    QString hashPass = identifiants.takeFirst();

    QSqlQuery req = Database::Auth()->PQuery(AUTH_SELECT_ACCOUNT, account.toLatin1().data());

    if(!req.first())
    {
        m_state = OnCheckingVersion;
        WorldPacket data(SMSG_LOGIN_ERROR);
        SendPacket(data);
        return;
    }

    for(quint8 i = 0; i < req.record().count(); ++i)
        m_infos.insert(req.record().fieldName(i), req.value(i));

    if(m_infos["subscription_time"].toInt() < 0)
        m_infos["subscription_time"] = QVariant(0);

    // Mot de passe correct
    if(cryptPassword(m_infos["hash_password"].toString(), m_hashKey) == hashPass)
    {
        if(m_infos["banned"] == "1")
        {
            m_state = OnCheckingVersion;
            WorldPacket data(SMSG_ACCOUNT_BANNED);
            SendPacket(data);
            return;
        }

        if(m_infos["online"] == "1")
        {
            m_state = OnCheckingVersion;
            WorldPacket data(SMSG_ALREADY_LOGGED);
            SendPacket(data);
            return;
        }

        // Ids OK, non banni, non logged
        Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_STATE, 1, m_infos["account_id"].toUInt());
    }
    else
    {
        m_state = OnCheckingVersion;
        WorldPacket data(SMSG_LOGIN_ERROR);
        SendPacket(data);
        return;
    }

    SendInformations();
    m_state = Logged; // Authentification terminée
}

void AuthSocket::SendInformations()
{
    WorldPacket dataPseudo(SMSG_GIVE_PSEUDO);
    dataPseudo << m_infos["pseudo"].toString();
    SendPacket(dataPseudo);

    WorldPacket dataCommunauty(SMSG_GIVE_COMMUNAUTY);
    dataCommunauty << "0"; // 0 = Fr
    SendPacket(dataCommunauty);

    QSqlQuery req = Database::Auth()->Query(AUTH_SELECT_ALL_SERVERS);
    QString server = "";

    while(req.next())
    {
        server += req.value(req.record().indexOf("realm_id")).toString() + ";";
        server += req.value(req.record().indexOf("status")).toString() + ";";
        server += "1;"; // int Completion
        server += "1";  // bool canLog

        server += "|";
    }
    server = server.left(server.size() - 1);

    WorldPacket dataServers(SMSG_GIVE_SERVERS);
    dataServers << server;
    SendPacket(dataServers);

    WorldPacket dataGmLevel(SMSG_GIVE_GMLEVEL);
    dataGmLevel << m_infos["gm_level"].toString();
    SendPacket(dataGmLevel);

    WorldPacket dataQuestion(SMSG_GIVE_QUESTION);
    dataQuestion << m_infos["secret_question"].toString();
    SendPacket(dataQuestion);
}

void AuthSocket::SelectServer(uint id)
{
    QSqlQuery req = Database::Auth()->PQuery(AUTH_SELECT_SERVER, id);
    if(!req.first())
    {
        qDebug() << "Server not found";
        return;
    }

    QString key = GenerateRandomString(16);
    QString infos = req.value(req.record().indexOf("address")).toString() + ":";
    infos += req.value(req.record().indexOf("port")).toString() + ";";
    infos += key;

    Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_SESSION_KEY, key.toLatin1().data(), m_infos["account_id"].toUInt());

    WorldPacket packet(SMSG_SERVER_INFOS);
    packet << infos;
    SendPacket(packet);
}
