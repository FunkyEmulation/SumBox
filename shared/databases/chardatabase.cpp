#include "chardatabase.h"

void CharDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_CHARACTERS, "SELECT * FROM `character` WHERE `account` = %u");
    LoadQuery(CHECK_CHAR_EXISTS, "SELECT count(`guid`) AS `count` FROM `character` WHERE `name` = %u");
}
