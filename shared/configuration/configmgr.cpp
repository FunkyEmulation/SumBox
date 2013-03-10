#include "configmgr.h"
#include "../logs/log.h"

ConfigMgr* ConfigMgr::m_instance = 0;

ConfigMgr::ConfigMgr()
{
    m_auth = NULL;
    m_world = NULL;
}
ConfigMgr::~ConfigMgr()
{
    if (m_auth)
        delete m_auth;
    if (m_world)
        delete m_world;

    m_auth = NULL;
    m_world = NULL;
}

bool ConfigMgr::LoadAuthConfig(QString fileName)
{
    Configuration* authConfig = new Configuration();
    if (m_auth = authConfig->OpenFile(fileName))
        return true;

    return false;
}

bool ConfigMgr::LoadWorldConfig(QString fileName)
{
    Configuration* worldConfig = new Configuration();
    if (m_world = worldConfig->OpenFile(fileName))
        return true;

    return false;
}
