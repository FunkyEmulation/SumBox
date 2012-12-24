#include "authserver.h"

AuthServer::AuthServer()
{
    m_server = new QTcpServer();
}

AuthServer::~AuthServer()
{
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

void AuthServer::DelSockObject()
{
    AuthSocket* target = qobject_cast<AuthSocket *>(sender());
    m_sockets.removeAt(m_sockets.indexOf(target));
}

void AuthServer::OnConnect()
{
    QTcpSocket* socket = m_server->nextPendingConnection();
    AuthSocket* newSockObject = new AuthSocket(socket);
    m_sockets.push_back(newSockObject);
}
