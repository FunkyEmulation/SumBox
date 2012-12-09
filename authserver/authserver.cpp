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

void AuthServer::OnConnect()
{

}

void AuthServer::OnRead()
{

}

void AuthServer::OnClose()
{

}
