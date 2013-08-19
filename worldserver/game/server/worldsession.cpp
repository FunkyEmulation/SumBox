#include "worldsession.h"
#include "opcodes/opcodes.h"
#include "logs/log.h"
#include "configuration/configmgr.h"

WorldSession::WorldSession(QTcpSocket *socket)
{
    m_socket = socket;
    m_packet = "";
    m_state = OnDetails;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));

    WorldPacket data(SMSG_HELLO_GAME_SERVER);
    SendPacket(data);

    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toAscii().data());
}

WorldSession::~WorldSession() {}

void WorldSession::OnRead()
{
    QDataStream in(m_socket);

    char *curPacket = new char;

    while(in.readRawData(curPacket, 1) != -1)
    {
        if(*curPacket != 0x00)
        {
            if(*curPacket != '\n' && *curPacket != '\r')
                m_packet += *curPacket;
        }
        else
            break;
    }

    if(!m_packet.isEmpty())
    {
        Log::Write(LOG_TYPE_DEBUG, "Received packet from <%s> : %s", m_socket->peerAddress().toString().toAscii().data(), m_packet.toAscii().data());

        QString header2 = m_packet.left(2);
        QString header3 = m_packet.left(3);

        OpcodeStruct opcode = GetOpcodeByHeader(header3);

        if (opcode.name == "MSG_UNKNOWN_OPCODE")
            opcode = GetOpcodeByHeader(header2);

        if (opcode.name != "MSG_UNKNOWN_OPCODE")
            (this->*opcode.handler)(m_packet);
        else
            Log::Write(LOG_TYPE_DEBUG, "Packet <%s> is unhandled. Content : %s", header2.toAscii().data(), m_packet.toAscii().data());

        m_packet = "";
    }
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
