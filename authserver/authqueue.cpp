#include "authqueue.h"

AuthQueue*  AuthQueue::m_instance = 0;

AuthQueue* AuthQueue::Instance()
{
    if(m_instance == 0)
    {
        m_instance = new AuthQueue;
    }

    return m_instance;
}

AuthQueue::AuthQueue()
{
    m_clients = new ClientList;
    m_timer = new QTimer;
}

void AuthQueue::Start()
{
    m_timer->setInterval(10000);
    m_timer->start();

    QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(RefreshQueue()));

}

void AuthQueue::Stop()
{
    m_timer->stop();
    cout << "queue stoppee" << endl;
}

void AuthQueue::RefreshQueue()
{
    if(m_clients->isEmpty())
    {
        return;
    }

    AuthSocket* client = m_clients->takeFirst();
    client->CheckAccount();

    // Plus de client en attente : on arrête la file
    if(m_clients->isEmpty())
    {
        Stop();
    }
}

ClientList* AuthQueue::GetClients()
{
    return m_clients;
}

void AuthQueue::AddClient(AuthSocket *socket)
{
    // Queue stoppée, on la relance :
    if(!m_timer->isActive())
    {
        Start();
    }

    m_clients->append(socket);
    Log::Write(LOG_TYPE_NORMAL,"Add client " + socket->GetIp() + " in queue.");
}
