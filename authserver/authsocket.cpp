#include <iostream>
#include "authsocket.h"
#include "../shared/utils/util.h"
#include "../shared/opcodes/opcodes.h"
#include "../shared/logs/log.h"
#include "../shared/configuration/configmgr.h"

using namespace std;

AuthSocket::AuthSocket(QTcpSocket* socket)
{
    m_socket = socket;
    m_packet = "";
    m_state = 0;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));

    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toAscii().data());
    SendInitPacket();
}

void AuthSocket::OnRead()
{
    QDataStream in(m_socket);

    char *curPacket = new char;

    while(in.readRawData(curPacket, 1) != -1)
    {
       if(*curPacket != 0x00) // Ce n'est pas le dernier caractère
       {
          if(*curPacket != '\n' && *curPacket != '\r')
            m_packet += *curPacket;
       }
       else
          break;
    }

    if(!m_packet.isEmpty() && *curPacket == 0x00) // Reçu en entier ?
    {
        Log::Write(LOG_TYPE_NORMAL, "Received packet from <%s> : %s", m_socket->peerAddress().toString().toAscii().data(), m_packet.toAscii().data());

        ParsePacket(m_packet);
        m_packet = "";
    }
}

void AuthSocket::OnClose()
{
    if(!m_infos.isEmpty())
        Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_STATE, 0, m_infos["id"].toInt());

    Log::Write(LOG_TYPE_NORMAL, "Closing connection with %s", m_socket->peerAddress().toString().toAscii().data());
    m_socket->deleteLater();
}

void AuthSocket::SendInitPacket()
{
    QSqlQuery req = Database::Auth()->PQuery(AUTH_SELECT_IP_BANNED, m_socket->peerAddress().toString().toAscii().data());
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

void AuthSocket::SendPacket(WorldPacket data)
{
    m_socket->write(data.GetPacket() + (char)0x00);
    Log::Write(LOG_TYPE_DEBUG, "Send packet %s ( Header : %s )", GetOpcodeName(data.GetOpcode()).toAscii().data(), GetOpcodeHeader(data.GetOpcode()).toAscii().data());
    if(data.GetPacket().length() > 0)
        Log::Write(LOG_TYPE_DEBUG, "Packet data : %s", QString(data.GetPacket()).toAscii().data());
}

void AuthSocket::ParsePacket(QString packet)
{
    // Phase d'authentification
    if(m_state < 2)
    {
        if(m_state == 0)
            CheckVersion(packet);
        else
            CheckAccount(packet);

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

    if(packet == "AP")
    {
        SendRandomName();
        return;
    }
}

void AuthSocket::SendPersos()
{
    WorldPacket persos(SMSG_GIVE_PERSOS);
    persos << m_infos["subscription_time"].toString().toAscii().data();
    // Manque |NbrePersos,surServerId|nbrePersos,surServerid2...

    SendPacket(persos);
}

void AuthSocket::QueueManager()
{
    // On envoit les infos du compte :
    SendInformations();
    return;
}

void AuthSocket::SendRandomName()
{
    QString randomName = GenerateRandomPseudo(4, 8);
    WorldPacket randomPseudo(SMSG_RANDOM_PSEUDO);
    randomPseudo << randomName;
    SendPacket(randomPseudo);
}


void AuthSocket::CheckVersion(QString version)
{
    QString acceptedClientVersion = ConfigMgr::Auth()->GetQString("AcceptClientVersion");
    if(version != acceptedClientVersion) // Mauvaise version
    {
        m_state = 0;
        WorldPacket data(SMSG_BAD_VERSION);
        data << acceptedClientVersion;
        SendPacket(data);
        return;
    }

    m_state = 1;
}

void AuthSocket::CheckAccount(QString ids)
{
    // Mauvais paquet : retour à l'étape 0 de l'authentification
    if(!ids.contains("#1"))
    {
        m_state = 0;
        WorldPacket data(SMSG_LOGIN_ERROR);
        SendPacket(data);
        return;
    }

    QStringList identifiants = ids.split("#1");
    QString account = identifiants.takeFirst();
    QString hashPass = identifiants.takeFirst();

    QSqlQuery req = Database::Auth()->PQuery(AUTH_SELECT_ACCOUNT, account.toAscii().data());

    if(!req.first())
    {
        m_state = 0;
        WorldPacket data(SMSG_LOGIN_ERROR);
        SendPacket(data);
        return;
    }

    for(quint8 i = 0; i < req.record().count(); ++i)
        m_infos.insert(req.record().fieldName(i), req.value(i));

    // Mot de passe correct
    if(cryptPassword(m_infos["password"].toString(), m_hashKey) == hashPass)
    {
        if(m_infos["banned"] == "1")
        {
            m_state = 0;
            WorldPacket data(SMSG_ACCOUNT_BANNED);
            SendPacket(data);
            return;
        }

        if(m_infos["logged"] == "1")
        {
            m_state = 0;
            WorldPacket data(SMSG_ALREADY_LOGGED);
            SendPacket(data);
            return;
        }

        // Ids OK, non banni, non logged
        m_state = 2;
        Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_STATE, 1, m_infos["id"].toUInt());

    }
    else
    {
        m_state = 0;
        WorldPacket data(SMSG_LOGIN_ERROR);
        SendPacket(data);
        return;
    }

    m_state = 2; // Authentification terminée
}

void AuthSocket::SendInformations()
{
    WorldPacket dataPseudo(SMSG_GIVE_PSEUDO);
    dataPseudo << m_infos["pseudo"].toString();
    SendPacket(dataPseudo);

    WorldPacket dataCommunauty(SMSG_GIVE_COMMUNAUTY);
    dataCommunauty << "0";
    SendPacket(dataCommunauty);

    QSqlQuery req = Database::Auth()->Query(AUTH_SELECT_ALL_SERVERS);
    QString server = "";

    while(req.next())
    {
        for(quint8 i = 0; i < req.record().count(); ++i)
        {
            server += req.value(i).toString();
            if(i != req.record().count() - 1)
                server += ";";
        }

        server += "|";
    }
    server = server.left(server.size() - 1);

    WorldPacket dataServers(SMSG_GIVE_SERVERS);
    dataServers << server;
    SendPacket(dataServers);

    WorldPacket dataGmLevel(SMSG_GIVE_GMLEVEL);
    dataGmLevel << m_infos["gmlevel"].toString();
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
    QString infos = req.value(req.record().indexOf("ip")).toString() + ":";
    infos += req.value(req.record().indexOf("port")).toString() + ";";
    infos += key;

    qDebug() << key;
    Database::Auth()->PQuery(AUTH_INSERT_LIVE_CONNECTION, 0, m_infos["id"].toUInt(), key.toAscii().data());

    WorldPacket packet(SMSG_SERVER_INFOS);
    packet << infos;
    SendPacket(packet);
}
