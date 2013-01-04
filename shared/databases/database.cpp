#include "database.h"
#include "AuthConfig.h"

Database* Database::m_instance = 0;

Database::Database()
{
    ConnectionInfo auth = ConnectionInfo(AuthConfig::getInstance()->GetStringConfig("AuthDatabase"));
    m_authDatabase = new AuthDatabase(auth);

    if(!m_authDatabase->Open())
        qApp->quit(); // don't work
}

Database::~Database()
{
    delete m_authDatabase;
}
