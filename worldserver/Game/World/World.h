#ifndef WORLD_H
#define WORLD_H

#include <QtCore>
#include "WorldServer.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "Utils/Singleton.h"

class WorldSession;

struct sRaceStartInfos
{
    sRaceStartInfos() : mapId(0), cellId(0) {}
    quint16 mapId;
    quint16 cellId;
};

typedef QList<WorldSession*> SessionList;

class World : public Singleton<World>
{
public:
    World();
    ~World();

    bool Initialize();
    bool IsRunning() { return m_is_running; }

    void AddSession(WorldSession* session);
    void RemoveSession(WorldSession* session);

    void LoadRaceStartInfos();
    sRaceStartInfos GetRaceStartInfos(quint8 race);

private:
    bool m_is_running;
    SessionList m_sessions;
    QMap<quint8, sRaceStartInfos> m_raceStartInfos;
};

#endif
