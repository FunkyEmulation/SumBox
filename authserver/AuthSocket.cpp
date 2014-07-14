#include "AuthSocket.h"
#include "AuthServer.h"
#include "Utils/Util.h"
#include "Opcodes/Opcodes.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"

AuthSocket::AuthSocket(QTcpSocket *socket) : SocketHandler(socket)
{
    m_state = OnCheckingVersion;

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));

    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
    SendInitPacket();
}

AuthSocket::~AuthSocket() {}

// A mettre en virtual non ?
void AuthSocket::OnClose()
{
    if(!m_infos.isEmpty())
        Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_STATE, 0, m_infos["account_id"].toInt());

    AuthServer::Instance()->RemoveSocket(this);
    SocketHandler::OnClose();
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
                WorldPacket data(SMSG_ACCOUNT_LOGIN_ERROR);
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

    if(packet.at(0) == 'A') // Normalement le seul type de packet sur l'auth
    {
        switch(packet.at(1).toLatin1())
        {
            case 'f':
                return QueueManager();
            case 'x':
                return SendPersos();
            case 'X':
                return SelectServer(packet.mid(2).toUInt());
            case 'F':
                return SearchFriend(packet.mid(2));
            default:
                Log::Write(LOG_TYPE_DEBUG, "Unhandled header packet : %s", packet.left(2).toLatin1().data());
            break;
        }
    }
}

void AuthSocket::SearchFriend(QString pseudo)
{
    WorldPacket packet(SMSG_SEARCH_FRIEND);
    QSqlQuery req = Database::Auth()->PQuery(AUTH_SEARCH_FRIEND, pseudo.toLatin1().data());
    while(req.next())
    {
        packet << req.value(req.record().indexOf("realm_id")).toString().toLatin1().data() << "," << req.value(req.record().indexOf("num_characters")).toString().toLatin1().data() << ";";
    }

    SendPacket(packet);
}

void AuthSocket::SendInitPacket()
{
    QSqlQuery req = Database::Auth()->PQuery(AUTH_SELECT_IP_BANNED, m_socket->peerAddress().toString().toLatin1().data());
    if(req.first())
    {
        WorldPacket data(SMSG_ACCOUNT_BANNED);
        SendPacket(data);
        return;
    }

    WorldPacket data(SMSG_HELLO_CONNECTION_SERVER);
    m_hashKey = GenerateRandomString(32);
    data << m_hashKey;
    SendPacket(data);
}

void AuthSocket::SendPersos()
{
    WorldPacket data(SMSG_ACCOUNT_REALM_CHAR);
    data << (qint64)(m_infos["subscription_time"].toInt()) * 1000;

    QSqlQuery result = Database::Auth()->PQuery(AUTH_SELECT_ACCOUNT_CHARACTERS, m_infos["account_id"].toInt());
    while(result.next())
    {
        data << "|" << (quint8)result.value(result.record().indexOf("realm_id")).toUInt();
        data << "," << (quint8)result.value(result.record().indexOf("num_characters")).toUInt();
    }

    SendPacket(data);
}

void AuthSocket::QueueManager()
{
    WorldPacket queuePosition(MSG_QUEUE_POSITION);

    if(!AuthQueue::Instance()->ClientInQueue(this)) // Non das la file
    {
        queuePosition << "1|1|0|1|-1";
    }
    else
    {
        queuePosition << AuthQueue::Instance()->GetClientPosition(this) << "|"; // Position dans la file
        queuePosition << AuthQueue::Instance()->GetClientsCount() << "|"; // Nombre d'abonnés dans la file
        queuePosition << 0 << "|"; // Nombre de non abonnés
        queuePosition << (quint8)(m_infos["subscription_time"].toInt() > 0 ? 1 : 0);
        queuePosition << 1; // Queue id
    }

    SendPacket(queuePosition);
}

void AuthSocket::CheckVersion(QString version)
{
    QString acceptedClientVersion = ConfigMgr::Auth()->GetQString("AcceptClientVersion");
    if(version != acceptedClientVersion) // Mauvaise version
    {
        m_state = OnCheckingVersion;
        WorldPacket data(SMSG_ACCOUNT_BAD_CLIENT_VERSION);
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

    if (req.first())
    {
        for (quint8 i = 0; i < req.record().count(); ++i)
            m_infos.insert(req.record().fieldName(i), req.value(i));

        if (m_infos["subscription_time"].toInt() < 0)
            m_infos["subscription_time"] = QVariant(0);

        // Mot de passe correct
        if (CryptPassword(m_infos["hash_password"].toString(), m_hashKey) == hashPass)
        {
            if (m_infos["banned"] == "1")
            {
                m_state = OnCheckingVersion;

                WorldPacket data(SMSG_ACCOUNT_BANNED);
                SendPacket(data);
                return;
            }
            else if (m_infos["online"] == "1")
            {
                m_state = OnCheckingVersion;

                WorldPacket data(SMSG_ACCOUNT_ALREADY_CONNECTED);
                SendPacket(data);
                return;
            }

            // Ids OK, non banni, non logged
            Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_STATE, 1, m_infos["account_id"].toUInt());

            SendInformations();
            m_state = Logged; // Authentification terminée
            return;
        }
    }

    m_state = OnCheckingVersion;

    WorldPacket data(SMSG_ACCOUNT_LOGIN_ERROR);
    SendPacket(data);
}

void AuthSocket::SendInformations()
{
    WorldPacket dataPseudo(SMSG_ACCOUNT_PSEUDO);
    dataPseudo << m_infos["pseudo"].toString();
    SendPacket(dataPseudo);

    WorldPacket dataCommunauty(SMSG_COMMUNITY);
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

    WorldPacket dataServers(SMSG_REALMS_LIST);
    dataServers << server;
    SendPacket(dataServers);

    WorldPacket dataGmLevel(SMSG_ACCOUNT_GMLEVEL);
    dataGmLevel << m_infos["gm_level"].toString();
    SendPacket(dataGmLevel);

    WorldPacket dataQuestion(SMSG_ACCOUNT_SECRET_QUESTION);
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

    qDebug() << key;
    Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_SESSION_KEY, key.toLatin1().data(), m_infos["account_id"].toUInt());

    WorldPacket packet(SMSG_REALM_INFOS);
    packet << infos;
    SendPacket(packet);
}
