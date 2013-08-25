#include "chardatabase.h"

void CharDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_CHARACTERS, "SELECT * FROM `characters` WHERE `account` = %u");
    LoadQuery(CHECK_CHAR_EXISTS, "SELECT count(`guid`) AS `count` FROM `characters` WHERE `name` = '%s'");

    LoadQuery(INSERT_CHARACTER,"INSERT INTO characters(guid, account, name, race, gender, gfx_id, color_1, color_2, color_3) VALUES(%u, %u, '%s', %u, %u, %u, %i, %i, %i)");
    LoadQuery(DELETE_CHAR, "DELETE FROM `characters` WHERE `guid` = %u");
    LoadQuery(SELECT_CHARACTER_MAX_GUID, "SELECT MAX(guid) FROM characters");
}
