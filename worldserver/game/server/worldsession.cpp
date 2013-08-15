#include "worldsession.h"
#include "opcodes/opcodes.h"
#include "logs/log.h"
#include "configuration/configmgr.h"

WorldSession::WorldSession(QTcpSocket *socket) : SocketReader(socket)
{
    m_state = OnDetails;

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));

    WorldPacket data(SMSG_HELLO_GAME_SERVER);
    SendPacket(data);

    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toAscii().data());
}

WorldSession::~WorldSession() {}

void WorldSession::ProcessPacket(QString packet)
{
    if(packet.isEmpty())
        return;

    Log::Write(LOG_TYPE_DEBUG, "Received packet from <%s> : %s", m_socket->peerAddress().toString().toAscii().data(), packet.toAscii().data());

    QString header2 = packet.left(2);
    QString header3 = packet.left(3);

    OpcodeStruct opcode = GetOpcodeByHeader(header3);

    if (opcode.name == "MSG_UNKNOWN_OPCODE")
        opcode = GetOpcodeByHeader(header2);

    if (opcode.name != "MSG_UNKNOWN_OPCODE")
        (this->*opcode.handler)(packet);
    else
        Log::Write(LOG_TYPE_DEBUG, "Packet <%s> is unhandled. Content : %s", header2.toAscii().data(), packet.toAscii().data());

}

void WorldSession::OnClose()
{
    Log::Write(LOG_TYPE_NORMAL, "Closing connection with %s", m_socket->peerAddress().toString().toAscii().data());
    m_socket->deleteLater();
}

void WorldSession::SendPacket(WorldPacket data)
{
    m_socket->write(data.GetPacket() + (char)0x00);
    Log::Write(LOG_TYPE_DEBUG, "Send packet %s ( Header : %s )", GetOpcodeName(data.GetOpcode()).toAscii().data(), GetOpcodeHeader(data.GetOpcode()).toAscii().data());
    if(data.GetPacket().length() > 0)
        Log::Write(LOG_TYPE_DEBUG, "Packet data : %s", QString(data.GetPacket()).toAscii().data());
}
