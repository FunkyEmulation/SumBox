#ifndef WORLD_H
#define WORLD_H

#include <QtCore>
#include "worldserver.h"
#include "logs/log.h"
#include "configuration/configmgr.h"
#include "utils/singleton.h"

class WorldSession;

typedef QList<WorldSession*> SessionList;

class World : public Singleton<World>
{
public:
    World();
    ~World();

    bool IsRunning() { return m_is_running; }

    void AddSession(WorldSession* session);
    void RemoveSession(WorldSession* session);

private:
    bool m_is_running;
    SessionList m_sessions;
};

#endif
