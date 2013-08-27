#include "worlddatabase.h"

void WorldDatabase::LoadQueries()
{
    LoadQuery(SELECT_ALL_MAPS, "SELECT * FROM maps");
}
