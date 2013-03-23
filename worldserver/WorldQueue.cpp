#include "WorldQueue.h"

WorldQueue*  WorldQueue::m_instance = 0;

WorldQueue::WorldQueue()
{
    m_clients.clear();
    m_timer = new QTimer;
    m_timer->setInterval(ConfigMgr::World()->GetInt("TimeQueueRefresh"));
}

WorldQueue::~WorldQueue()
{
    m_clients.clear();
    delete m_timer; // normalement inutile car géré par Qt?
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
        client->SendCharacters();
}

void WorldQueue::AddClient(WorldSession* socket)
{
    // Queue stoppée, on la relance :
    if(!m_timer->isActive())
        Start();

    m_clients.append(socket);
    Log::Write(LOG_TYPE_NORMAL,"Add client " + socket->GetIp() + " in queue.");
}

