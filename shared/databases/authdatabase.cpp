#include "authdatabase.h"

void AuthDatabase::LoadQueries()
{
    // account queries
    LoadQuery(AUTH_SELECT_ACCOUNT, "SELECT *, UNIX_TIMESTAMP(`subscription_time`) - UNIX_TIMESTAMP(NOW()) AS `subscription_time` FROM `account` WHERE `username` = '%s'");
    LoadQuery(AUTH_UPDATE_ACCOUNT_STATE, "UPDATE account SET online = %u WHERE account_id = %u");
    LoadQuery(AUTH_SELECT_ACCOUNT_SESSION_KEY, "SELECT *, UNIX_TIMESTAMP(`subscription_time`) - UNIX_TIMESTAMP(NOW()) AS `subscription` FROM account WHERE session_key = '%s'");
    LoadQuery(AUTH_UPDATE_ACCOUNT_SESSION_KEY, "UPDATE account SET session_key = '%s' WHERE account_id = %u");
    LoadQuery(AUTH_UPDATE_ACCOUNT_CHARS, "REPLACE INTO `realm_characters` (`account_id`,`realm_id`, `num_characters`) VALUES (%u, %u, %u)");
    LoadQuery(AUTH_SELECT_ACCOUNT_CHARACTERS, "SELECT * FROM `realm_characters` WHERE `account_id` = %u");
    LoadQuery(AUTH_SEARCH_FRIEND, "SELECT `characters` FROM `account` WHERE pseudo = '%s'");

    // banned_ip queries
    LoadQuery(AUTH_SELECT_IP_BANNED, "SELECT * FROM ip_banned WHERE ip = '%s'");

    // realmlist queries
    LoadQuery(AUTH_SELECT_ALL_SERVERS, "SELECT realm_id, status, population, subscription FROM realmlist");
    LoadQuery(AUTH_SELECT_SERVER, "SELECT address, port FROM realmlist WHERE realm_id = %u");
}
