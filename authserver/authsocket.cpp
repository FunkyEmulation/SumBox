#include <iostream>
#include "authsocket.h"
#include "AuthConfig.h"
#include "../shared/utils/util.h"
#include "../shared/opcodes/opcodes.h"

using namespace std;

AuthSocket::AuthSocket(QTcpSocket* socket)
{
    m_packet = "";
    m_state = 0;
    m_socket = socket;
    m_DbCon = AuthModel::getInstance(NULL,NULL,NULL,NULL);

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));
    connect(this,SIGNAL(CloseConnection()),this,SLOT(OnClose()));

    cout << "New incoming connection from " << m_socket->peerAddress().toString().toAscii().data() << endl;
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
        cout << "Received packet from <" << m_socket->peerAddress().toString().toAscii().data() << "> : "
             << m_packet.toAscii().data() << endl;

        ParsePacket(m_packet);
        m_packet = "";
    }
}

void AuthSocket::ParsePacket(QString packet)
{
    if(m_state < 2) // Phase d'authentification
    {
        switch(m_state)
        {
            case 0:
                CheckVersion(packet);
                break;
            case 1:
                CheckAccount(packet);
                break;
        }

        return;
    }

    if(packet == "AP")
    {
        SendRandomName();
        return;
    }
}

void AuthSocket::SendRandomName()
{
    QString randomName = GenerateRandomPseudo(4,8);
    WorldPacket randomPseudo(SMSG_RANDOM_PSEUDO);
    randomPseudo << randomName;
    SendPacket(randomPseudo);
}


void AuthSocket::CheckVersion(QString version)
{
    QMap<QString,QString> config = AuthConfig::getInstance()->getConfig();
    if(version != config["clientVersion"]) // Mauvaise version
    {
        m_state = 0;
        WorldPacket data(SMSG_BAD_VERSION);
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

    m_infos = m_DbCon->getAccount(account);

    // Compte inexistant
    if(m_infos.isEmpty())
    {
       m_state = 0;
       WorldPacket data(SMSG_LOGIN_ERROR);
       SendPacket(data);
       return;
    }

    // Mot de passe correct
    if(cryptPassword(m_infos["password"],m_hashKey) == hashPass)
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
        SendInformations(); // On envoi les infos du compte

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
    dataPseudo << m_infos["pseudo"];
    SendPacket(dataPseudo);

    WorldPacket dataCommunauty(SMSG_GIVE_COMMUNAUTY);
    dataCommunauty << "0";
    SendPacket(dataCommunauty);

    SendServers();

    WorldPacket dataGmLevel(SMSG_GIVE_GMLEVEL);
    dataGmLevel << m_infos["gmlevel"];
    SendPacket(dataGmLevel);

    WorldPacket dataQuestion(SMSG_GIVE_QUESTION);
    dataQuestion << m_infos["secret_question"];
    SendPacket(dataQuestion);
}

void AuthSocket::SendServers()
{
    QString packetServers = "";
    QList< QMap<QString, QString> > servers = m_DbCon->getServers();

    for(int i = 0; i < servers.length(); ++i)
    {
        packetServers += servers[i]["id"] + ";";
        packetServers += servers[i]["state"] + ";";
        packetServers += servers[i]["population"] + ";";
        packetServers += servers[i]["subscription"];
        if(i < servers.length() - 1)
            packetServers += "|";
    }

    WorldPacket dataServers(SMSG_GIVE_SERVERS);
    dataServers << packetServers;
    SendPacket(dataServers);
}

void AuthSocket::OnClose()
{
    cout << "Closing connection with " << m_socket->peerAddress().toString().toAscii().data() << endl;
    m_socket->deleteLater();
}

// Faire une classe WorldPacket
void AuthSocket::SendInitPacket()
{
    WorldPacket data(SMSG_HELLO_CONNECTION_SERVER);
    m_hashKey = GenerateRandomString(32);
    data << m_hashKey;
    SendPacket(data);
}

void AuthSocket::SendPacket(WorldPacket data)
{
    m_socket->write(data.GetPacket() + (char)0x00);
    cout << "Send packet " << GetOpcodeName(data.GetOpcode()).toAscii().data() << " ( Header : " << GetOpcodeHeader(data.GetOpcode()).toAscii().data() << " )" << endl;
    if(data.GetPacket().length() > 0)
        qDebug() << "Packet data : " << data.GetPacket();
}
