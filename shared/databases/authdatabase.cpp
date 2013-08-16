#include "authdatabase.h"

void AuthDatabase::LoadQueries()
{
    // account queries
    LoadQuery(AUTH_SELECT_ACCOUNT, "SELECT * FROM account WHERE username = '%s'");
    LoadQuery(AUTH_UPDATE_ACCOUNT_STATE, "UPDATE account SET online = %u WHERE account_id = %u");
    LoadQuery(AUTH_SELECT_ACCOUNT_SESSION_KEY, "SELECT `account_id`,`username`,`pseudo`,`hash_password`,`session_key`,`gm_level`,`secret_question`,`secret_answer`,`last_login`,`last_ip`,`online`,`banned`, UNIX_TIMESTAMP(`subscription_time`) - UNIX_TIMESTAMP(NOW()) AS `subscription` FROM account WHERE session_key = '%s'");
    LoadQuery(AUTH_UPDATE_ACCOUNT_SESSION_KEY, "UPDATE account SET session_key = '%s' WHERE account_id = %u");

    // banned_ip queries
    LoadQuery(AUTH_SELECT_IP_BANNED, "SELECT * FROM ip_banned WHERE ip = '%s'");

    // realmlist queries
    LoadQuery(AUTH_SELECT_ALL_SERVERS, "SELECT realm_id, status, population, subscription FROM realmlist");
    LoadQuery(AUTH_SELECT_SERVER, "SELECT address, port FROM realmlist WHERE realm_id = %u");
}
