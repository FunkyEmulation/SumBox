#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <QtCore>
#include "configuration.h"

class ConfigMgr
{
public:
    static ConfigMgr* Instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            mutex.lock();
            m_instance = new ConfigMgr;
            mutex.unlock();
        }
        return m_instance;
    }

    static void Close()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_instance;
        mutex.unlock();
    }

    Configuration* GetAuthConfig() { Q_ASSERT(m_auth); return m_auth; }
    Configuration* GetWorldConfig() { Q_ASSERT(m_world); return m_world; }

    static Configuration* Auth() { return ConfigMgr::Instance()->GetAuthConfig(); }
    static Configuration* World() { return ConfigMgr::Instance()->GetWorldConfig(); }

    bool LoadAuthConfig(QString fileName);
    bool LoadWorldConfig(QString fileName);

private:
    ConfigMgr();
    ~ConfigMgr();

    static ConfigMgr* m_instance;

    Configuration* m_auth;
    Configuration* m_world;
};

#endif
