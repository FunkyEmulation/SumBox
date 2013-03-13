#include "authdatabase.h"

void AuthDatabase::LoadQueries()
{
    LoadQuery(AUTH_SELECT_ACCOUNT, "SELECT * FROM accounts WHERE account = '%s'");
    LoadQuery(AUTH_SELECT_ALL_SERVERS, "SELECT id, state, population, subscription FROM servers");
    LoadQuery(AUTH_SELECT_SERVER, "SELECT ip, port FROM servers WHERE id = %u");
    LoadQuery(AUTH_SELECT_IP_BANNED, "SELECT * FROM banips WHERE ip = '%s'");
    LoadQuery(AUTH_UPDATE_ACCOUNT_STATE, "UPDATE accounts SET logged = %u WHERE id = %u");
    LoadQuery(AUTH_INSERT_LIVE_CONNECTION, "INSERT INTO lives_connections (`id`,`account_id`, `session_key`) VALUES ('%u', '%u', '%s')");
    LoadQuery(AUTH_SELECT_LIVE_CONNECTION, "SELECT * FROM lives_connections WHERE session_key = '%s'");
    LoadQuery(AUTH_DELETE_LIVE_CONNECTION, "DELETE FROM lives_connections WHERE session_key = '%s'");
}
