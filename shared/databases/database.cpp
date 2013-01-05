#include "database.h"
#include "AuthConfig.h"

Database* Database::m_instance = 0;

Database::Database()
{
    m_error = false;

    ConnectionInfo auth = ConnectionInfo(AuthConfig::getInstance()->GetStringConfig("AuthDatabase"));
    m_authDatabase = new AuthDatabase(auth);

    if(!m_authDatabase->Open())
    {
        m_error = true;
        return;
    }
}

Database::~Database()
{
    delete m_authDatabase;
}
