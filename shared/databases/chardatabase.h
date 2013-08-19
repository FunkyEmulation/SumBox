#ifndef CHARDATABASE_H
#define CHARDATABASE_H

#include <QtCore>
#include "mysqlconnection.h"

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

    INSERT_NEW_CHAR,
    DELETE_CHAR

};

#endif
