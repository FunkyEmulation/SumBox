#ifndef CHARDATABASE_H
#define CHARDATABASE_H

#include <QtCore>
#include "MysqlConnection.h"

class CharDatabase : public MysqlConnection
{
public:
    CharDatabase(ConnectionInfo& connectionInfo) : MysqlConnection(connectionInfo) {}

    virtual void LoadQueries();
};

enum CharDatabaseQueries
{    
    /**
     * DATABASE_STATEMENT_SUMMARY
     */
    SELECT_ACCOUNT_CHARACTERS,
    CHECK_CHAR_EXISTS,

    INSERT_CHARACTER,
    DELETE_CHARACTER,
    SELECT_CHARACTER_MAX_GUID,
    SELECT_CHARACTER
};

#endif
