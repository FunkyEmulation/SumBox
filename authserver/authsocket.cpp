#include <iostream>
#include "authsocket.h"
#include "../shared/utils/util.h"
#include "../shared/opcodes/opcodes.h"

using namespace std;

AuthSocket::AuthSocket(QTcpSocket* socket)
{
    m_socket = socket;
    m_blockSize = 0;
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));

    cout << "New incoming connection from " << m_socket->peerAddress().toString().toAscii().data() << endl;

    SendInitPacket();
}

void AuthSocket::OnRead()
{
    QDataStream in(m_socket);
    qDebug() << in;
    if(m_blockSize == 0)
    {
        if(m_socket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> m_blockSize;
    }

    if(m_socket->bytesAvailable() < m_blockSize)
        return;

    m_blockSize = 0;
    cout << "Received a complete packet" << endl;
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
    data << GenerateRandomString(32);
    SendPacket(data);
}

void AuthSocket::SendPacket(WorldPacket data)
{
    data.seek(0);
    data << (quint16) (data.GetPacket().size() - sizeof(quint16));
    m_socket->write(data.GetPacket());
    cout << "Send packet " << GetOpcodeName(data.GetOpcode()).toAscii().data() << " ( Header : " << GetOpcodeHeader(data.GetOpcode()).toAscii().data() << " )" << endl;
}
