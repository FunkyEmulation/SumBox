#include "authdatabase.h"

void AuthDatabase::LoadQueries()
{
    LoadQuery(AUTH_SELECT_ACCOUNT, "SELECT * FROM accounts WHERE id = %u");
    LoadQuery(AUTH_SELECT_ALL_SERVERS, "SELECT * FROM servers");
    LoadQuery(AUTH_SELECT_SERVER, "SELECT * FROM servers WHERE id = %u");
    LoadQuery(AUTH_SELECT_IP_BANNED, "SELECT * FROM banips");
    LoadQuery(AUTH_UPDATE_ACCOUNT_STATE, "UPDATE accounts SET logged = %u WHERE id = %u");
}
