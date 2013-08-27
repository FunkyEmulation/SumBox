#include "worlddatabase.h"

void WorldDatabase::LoadQueries()
{
    LoadQuery(SELECT_ALL_MAPS, "SELECT * FROM maps");
    LoadQuery(SELECT_RACE_START_INFOS, "SELECT *  FROM race_start_infos");
}
