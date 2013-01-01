#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include <QtCore>
#include <QtSql>

struct ConnectionInfo
{
    ConnectionInfo() {}
    ConnectionInfo(QString connectionInfo)
    {
        QStringList infos = connectionInfo.split(';');

        host = infos.at(0);
        port = QString(infos.at(1)).toInt();
        database = infos.at(2);
        username = infos.at(3);
        password = infos.at(4);
    }

    QString host;
    int port;
    QString database;
    QString username;
    QString password;
};

typedef QMap<quint16, QString> QueriesMap;
#define LOAD_QUERY(a, b) m_queries[a] = b;

class MysqlConnection
{
public:
    MysqlConnection(ConnectionInfo& connectionInfo);
    ~MysqlConnection();

    virtual void LoadQueries() = 0;

    bool Open();
    void Close();

    bool Query(QString sqlQuery);
    bool PQuery(QString sqlQuery, ...);

protected:
    QueriesMap m_queries;

private:
    ConnectionInfo m_connectionInfo;
    QSqlDatabase m_db;
};

#endif
