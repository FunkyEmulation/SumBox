#include "database.h"
#include "configuration/configmgr.h"

template<> Database*  Singleton<Database>::m_instance = 0;

Database::Database()
{
    m_authDatabase = NULL;
    m_charDatabase = NULL;
    m_worldDatabase = NULL;
}

Database::~Database()
{
    if (m_authDatabase)
        m_authDatabase->Close();

    if (m_charDatabase)
        m_charDatabase->Close();

    if (m_worldDatabase)
        m_worldDatabase->Close();

    delete m_authDatabase;
    delete m_charDatabase;
    delete m_worldDatabase;
}

bool Database::OpenAuthDatabase()
{
    ConnectionInfo cinfos = ConnectionInfo(ConfigMgr::Auth()->GetQString("AuthDatabase"));
    m_authDatabase = new AuthDatabase(cinfos);

    if(!m_authDatabase->Open())
        return false;

    return true;
}

bool Database::OpenCharDatabase()
{
    ConnectionInfo cinfos = ConnectionInfo(ConfigMgr::World()->GetQString("CharDatabase"));
    m_charDatabase = new CharDatabase(cinfos);

    if(!m_charDatabase->Open())
        return false;

    return true;
}

bool Database::OpenWorldDatabase()
{
    ConnectionInfo cinfos = ConnectionInfo(ConfigMgr::World()->GetQString("WorldDatabase"));
    m_worldDatabase = new WorldDatabase(cinfos);

    if(!m_worldDatabase->Open())
        return false;

    return true;
}
