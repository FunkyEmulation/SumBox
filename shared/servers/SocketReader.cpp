#include "SocketReader.h"

SocketReader::SocketReader(QTcpSocket *socket)
{
    m_socket = socket;
    m_packet = "";

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
}

void SocketReader::OnRead()
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
