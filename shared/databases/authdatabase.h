#ifndef AUTHDATABASE_H
#define AUTHDATABASE_H

#include <QtCore>
#include "mysqlconnection.h"

class AuthDatabase : public MysqlConnection
{
public:
    AuthDatabase(ConnectionInfo& connectionInfo) : MysqlConnection(connectionInfo) {}

    virtual void LoadQueries();
};

enum AuthDatabaseQueries
{
    /**
     * DATABASE_STATEMENT_SUMMARY
     */
    AUTH_SELECT_ACCOUNT,
    AUTH_UPDATE_ACCOUNT_STATE,
    AUTH_SELECT_ACCOUNT_SESSION_KEY,
    AUTH_UPDATE_ACCOUNT_SESSION_KEY,
    AUTH_UPDATE_ACCOUNT_CHARS,
    AUTH_SELECT_ACCOUNT_CHARACTERS,
    AUTH_SEARCH_FRIEND,

    AUTH_SELECT_IP_BANNED,

    AUTH_SELECT_ALL_SERVERS,
    AUTH_SELECT_SERVER
};

#endif
