#include "AuthServer.h"

template<> AuthServer*  Singleton<AuthServer>::m_instance = 0;

AuthServer::AuthServer()
{
    m_server = new QTcpServer(this);
    m_sockets.clear();
}

AuthServer::~AuthServer()
{
    m_sockets.clear();
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
    Log::Delete();
    m_server->close();
}

void AuthServer::OnConnect()
{
    QTcpSocket* socket = m_server->nextPendingConnection();
    AuthSocket* newSockObject = new AuthSocket(socket);
    m_sockets.push_back(newSockObject);
}

void AuthServer::RemoveSocket(AuthSocket* socket)
{
    m_sockets.removeOne(socket);
}
