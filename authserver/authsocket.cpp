#include <iostream>
#include "authsocket.h"
#include "../shared/utils/util.h"
#include "../shared/opcodes/opcodes.h"

using namespace std;

AuthSocket::AuthSocket(QTcpSocket* socket)
{
    m_socket = socket;
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));

    cout << "New incoming connection from " << m_socket->peerAddress().toString().toAscii().data() << endl;

    SendInitPacket();
}

void AuthSocket::OnRead()
{
    cout << "OnRead" << endl;
}

void AuthSocket::OnClose()
{
    cout << "Closing connection with " << m_socket->peerAddress().toString().toAscii().data() << endl;
    m_socket->deleteLater();
}

// Faire une classe WorldPacket
void AuthSocket::SendInitPacket()
{
    QByteArray packet;
    QDataStream pkt(&packet, QIODevice::WriteOnly);

    pkt << SMSG_HELLO_CONNECTION_SERVER;
    pkt << GenerateRandomString(32);
    SendPacket(packet);
    cout << "Send packet " << GetOpcodeName(SMSG_HELLO_CONNECTION_SERVER).toAscii().data() << endl;
}

void AuthSocket::SendPacket(QByteArray packet)
{
    m_socket->write(packet);
}
