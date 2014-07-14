#include "AuthQueue.h"

template<> AuthQueue*  Singleton<AuthQueue>::m_instance = 0;

AuthQueue::AuthQueue()
{
    m_clients.clear();
    m_timer = new QTimer(this);
    m_timer->setInterval(ConfigMgr::Auth()->GetInt("QueueRefreshTime"));
}

AuthQueue::~AuthQueue()
{
    m_clients.clear();
}

void AuthQueue::Start()
{
    m_timer->start();
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(RefreshQueue()));
}

void AuthQueue::Stop()
{
    m_timer->stop();
}

void AuthQueue::RefreshQueue()
{
    if(m_clients.isEmpty())
    {
        Stop();
        return;
    }

    if (AuthSocket* client = m_clients.takeFirst())
        client->CheckAccount();
}

void AuthQueue::AddClient(AuthSocket* socket)
{
    if(!m_timer->isActive())
        Start();

    m_clients.append(socket);
    Log::Write(LOG_TYPE_NORMAL,"Add client " + socket->GetIp() + " in queue.");
}
