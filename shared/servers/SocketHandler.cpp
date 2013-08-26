#include "SocketHandler.h"
#include "logs/log.h"

SocketHandler::SocketHandler(QTcpSocket *socket)
{
    m_socket = socket;
    m_packet = "";

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
}

void SocketHandler::OnRead()
{
    char *curChar = new char;
    while(m_socket->read(curChar, 1) > (qint64)0)
    {
        if(*curChar != 0x00)
        {
            if(*curChar != '\n' && *curChar != '\r')
                m_packet += *curChar;
        }
        else // Fin d'un packet détectée
        {
            ProcessPacket(m_packet);
            m_packet = "";
        }
    }
}

void SocketHandler::OnClose()
{
    Log::Write(LOG_TYPE_NORMAL, "Closing connection with %s", m_socket->peerAddress().toString().toLatin1().data());
    m_socket->deleteLater();
}

void SocketHandler::SendPacket(const WorldPacket& data) const
{
    m_socket->write(data.GetPacket().toLatin1() + (char)0x00);
    Log::Write(LOG_TYPE_DEBUG, "Send packet %s ( Header : %s )", GetOpcodeName(data.GetOpcode()).toLatin1().data(), GetOpcodeHeader(data.GetOpcode()).toLatin1().data());
    if(data.GetPacket().length() > 0)
        Log::Write(LOG_TYPE_DEBUG, "Packet data : %s", QString(data.GetPacket()).toLatin1().data());
}
