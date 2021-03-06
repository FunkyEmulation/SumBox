#ifndef WORLDDATABASE_H
#define WORLDDATABASE_H

#include <QtCore>
#include "MysqlConnection.h"

class WorldDatabase : public MysqlConnection
{
public:
    WorldDatabase(ConnectionInfo& connectionInfo) : MysqlConnection(connectionInfo) {}

    virtual void LoadQueries();
};

enum WorldDatabaseQueries
{
    /**
     * DATABASE_STATEMENT_SUMMARY
     */
    SELECT_ALL_MAPS,
    SELECT_RACE_START_INFOS
};

#endif
