#include "authdatabase.h"

void AuthDatabase::LoadQueries()
{
    LOAD_QUERY(AUTH_SELECT_ACCOUNT, 'SELECT * FROM account WHERE account = %u');
    LOAD_QUERY(AUTH_SELECT_ALL_SERVERS, 'SELECT * FROM servers');
    LOAD_QUERY(AUTH_SELECT_SERVER, 'SELECT * FROM servers WHERE id = %u');
    LOAD_QUERY(AUTH_SELECT_IP_BANNED, 'SELECT * FROM banips');
    LOAD_QUERY(AUTH_UPDATE_ACCOUNT_STATE, 'UPDATE accounts SET logged = %u WHERE id = %u');
}
