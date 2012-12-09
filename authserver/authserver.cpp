#include "authserver.h"

AuthServer::AuthServer()
{
    m_server = new QTcpServer();
}

AuthServer::~AuthServer()
{
    for(SocketList::ConstIterator itr = m_sockets.begin(); itr != m_sockets.end(); ++itr)
    {
        if((*itr))
            (*itr)->OnClose();
    }

    m_sockets.clear();
    delete m_server;
}

bool AuthServer::Start(QHostAddress address, quint16 port)
{
    if(!m_server->listen(address, port))
        return false;

    connect(m_server, SIGNAL(newConnection()), this, SLOT(OnConnect()));
    return true;
}

void AuthServer::Stop()
{
    m_server->close();
}

void AuthServer::OnConnect()
{
    QTcpSocket* socket = m_server->nextPendingConnection();
    m_sockets.push_back(new AuthSocket(socket));
}
