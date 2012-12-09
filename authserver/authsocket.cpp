#include "authsocket.h"

AuthSocket::AuthSocket(QTcpSocket* socket)
{
    m_socket = socket;
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
}

void AuthSocket::OnRead()
{

}
