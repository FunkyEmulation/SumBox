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

    QString packet = "";
    char *curPacket = new char;

    while(in.readRawData(curPacket,1) != -1)
    {
       if(*curPacket != 0x00) // Ce n'est pas le dernier caractère
          packet += *curPacket;
       else
          break;
    }

    if(!packet.isEmpty())
    {
        cout << "Received packet from <" << m_socket->peerAddress().toString().toAscii().data() << "> : "
             << packet.toAscii().data() << endl;
    }

    parsePacket(packet);
    //qDebug() << in;
}

void AuthSocket::parsePacket(QString packet)
{

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
    m_socket->write(data.GetPacket() + (char)0x00);
    cout << "Send packet " << GetOpcodeName(data.GetOpcode()).toAscii().data() << " ( Header : " << GetOpcodeHeader(data.GetOpcode()).toAscii().data() << " )" << endl;
    qDebug() << "Packet data : " << data.GetPacket();
}
