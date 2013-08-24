#include "chardatabase.h"

void CharDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_CHARACTERS, "SELECT * FROM `character` WHERE `account` = %u");
    LoadQuery(CHECK_CHAR_EXISTS, "SELECT count(`guid`) AS `count` FROM `character` WHERE `name` = '%s'");

    LoadQuery(INSERT_CHAR,"INSERT INTO `character`(`account`, `name`, `class`, `gender`, `gfx_id`, `color_1`, `color_2`, `color_3`) VALUES(%u, '%s', %u, %u, %u, '%s', '%s', '%s')");
    LoadQuery(DELETE_CHAR, "DELETE FROM `character` WHERE `guid` = %u");
}
