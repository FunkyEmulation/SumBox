#include "chardatabase.h"

void CharDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_CHARACTERS, "SELECT * FROM `character` WHERE `account` = '%s'");
    LoadQuery(SELECT_ACCOUNT_SERVER_CHARACTERS, "SELECT * FROM `character` WHERE `account` = %u AND `server_id` = %u ORDER BY `guid`");
    LoadQuery(CHECK_CHAR_EXISTS, "SELECT count(`guid`) AS `count` FROM `character` WHERE `name` = '%s'");

    LoadQuery(INSERT_NEW_CHAR,"INSERT INTO `character`(`account`,`server_id`,`name`,`class`,`gender`,`level`,`gfx_id`,`color_1`, `color_2`, `color_3`) VALUES(%u, %u, '%s', %u, %u, 1, %u, '%s', '%s', '%s')");
}
