#include "CharDatabase.h"

void CharDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_CHARACTERS, "SELECT * FROM `characters` WHERE `account_id` = %u");
    LoadQuery(CHECK_CHAR_EXISTS, "SELECT count(`guid`) AS `count` FROM `characters` WHERE `name` = '%s'");

    LoadQuery(INSERT_CHARACTER,"INSERT INTO characters(guid, account_id, name, race, gender, gfx_id, color_1, color_2, color_3, map_id, cell_id) VALUES(%u, %u, '%s', %u, %u, %u, %i, %i, %i, %u, %u)");
    LoadQuery(DELETE_CHARACTER, "DELETE FROM `characters` WHERE `guid` = %u");
    LoadQuery(SELECT_CHARACTER_MAX_GUID, "SELECT MAX(guid) FROM characters");
    LoadQuery(SELECT_CHARACTER, "SELECT * FROM characters WHERE guid = %u AND account_id = %u");
}
