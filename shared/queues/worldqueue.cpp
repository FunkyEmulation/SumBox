#include "WorldQueue.h"

WorldQueue*  WorldQueue::m_instance = 0;

WorldQueue::WorldQueue()
{
    m_clients.clear();
    m_timer = new QTimer(this);
    m_timer->setInterval(ConfigMgr::World()->GetInt("QueueRefreshTime"));
}

WorldQueue::~WorldQueue()
{
    m_clients.clear();
}

void WorldQueue::Start()
{
    m_timer->start();
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(RefreshQueue()));
}

void WorldQueue::Stop()
{
    m_timer->stop();
}

void WorldQueue::RefreshQueue()
{
    if(m_clients.isEmpty())
    {
        Stop();
        return;
    }

    if (WorldSession* client = m_clients.takeFirst())
        client->SendCharacterList();
}

void WorldQueue::AddClient(WorldSession* socket)
{
    // Queue stoppée, on la relance :
    if(!m_timer->isActive())
        Start();

    m_clients.append(socket);
    Log::Write(LOG_TYPE_NORMAL,"Add client " + socket->GetIp() + " in queue.");
}

