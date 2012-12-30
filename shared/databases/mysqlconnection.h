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

class MysqlConnection
{
public:
    MysqlConnection(ConnectionInfo& connectionInfo);
    ~MysqlConnection();

    bool Open();
    void Close();

    bool Query(QString sqlQuery); // Select data
    bool Execute(QString sqlQuery); // Modify data

    bool PQuery(QString sqlQuery, ...); // Select data with args
    bool PExecute(QString sqlQuery, ...); // Modify data with args

private:
    ConnectionInfo m_connectionInfo;
    QSqlDatabase m_db;
    QMutex m_lock;
};

#endif
