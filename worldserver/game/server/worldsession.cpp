#include "worldsession.h"
#include "opcodes/opcodes.h"
#include "logs/log.h"
#include "configuration/configmgr.h"
#include "game/world/world.h"

WorldSession::WorldSession(QTcpSocket *socket) : SocketReader(socket)
{
    m_state = OnDetails;
    m_accountInfos.id = 0;
    m_accountInfos.username = QString();
    m_accountInfos.pseudo = QString();
    m_accountInfos.gmLevel = 0;
    m_accountInfos.secretQuestion = QString();
    m_accountInfos.secretAnswer = QString();
    m_accountInfos.subscriptionTime = 0;
    m_charsList.clear();

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));

    WorldPacket data(SMSG_HELLO_GAME_SERVER);
    SendPacket(data);

    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
}

WorldSession::~WorldSession() {}

void WorldSession::ProcessPacket(QString packet)
{
    if(packet.isEmpty())
        return;

    Log::Write(LOG_TYPE_DEBUG, "Received packet from <%s> : %s", m_socket->peerAddress().toString().toLatin1().data(), packet.toLatin1().data());

    QString header2 = packet.left(2);
    QString header3 = packet.left(3);

    OpcodeStruct opcode = GetOpcodeByHeader(header3);

    if (opcode.name == "MSG_UNKNOWN_OPCODE")
        opcode = GetOpcodeByHeader(header2);

    if (opcode.name != "MSG_UNKNOWN_OPCODE")
        (this->*opcode.handler)(packet);
    else
        Log::Write(LOG_TYPE_DEBUG, "Packet <%s> is unhandled. Content : %s", header2.toLatin1().data(), packet.toLatin1().data());
}

void WorldSession::OnClose()
{
    World::Instance()->RemoveSession(this);
    SocketReader::OnClose();
}

void WorldSession::SetAccountInfos(QSqlQuery queryResult)
{
    if (queryResult.first())
    {
        m_accountInfos.id               = queryResult.value(queryResult.record().indexOf("account_id")).toInt();
        m_accountInfos.username         = queryResult.value(queryResult.record().indexOf("username")).toString();
        m_accountInfos.pseudo           = queryResult.value(queryResult.record().indexOf("pseudo")).toString();
        m_accountInfos.gmLevel          = queryResult.value(queryResult.record().indexOf("gm_level")).toInt();
        m_accountInfos.secretQuestion   = queryResult.value(queryResult.record().indexOf("secret_question")).toString();
        m_accountInfos.secretAnswer     = queryResult.value(queryResult.record().indexOf("secret_answer")).toString();

        qint32 subscriptionTime = queryResult.value(queryResult.record().indexOf("subscription")).toLongLong() * 1000;

        if (subscriptionTime > 0)
            m_accountInfos.subscriptionTime = subscriptionTime;
    }

}
