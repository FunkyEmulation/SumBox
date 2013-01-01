#include "mysqlconnection.h"

MysqlConnection::MysqlConnection(ConnectionInfo& connectionInfo)
{
    m_connectionInfo = connectionInfo;

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(m_connectionInfo.host);
    m_db.setPort(m_connectionInfo.port);
    m_db.setDatabaseName(m_connectionInfo.database);
    m_db.setUserName(m_connectionInfo.username);
    m_db.setPassword(m_connectionInfo.password);

    m_queries.clear();
}

MysqlConnection::~MysqlConnection()
{
    Close();
}

bool MysqlConnection::Open()
{
    if(!m_db.open())
        return false;

    LoadQueries();
    qDebug() << "Database connection accomplished on " << m_connectionInfo.database;
    return true;
}

void MysqlConnection::Close()
{
    m_db.close();
    qDebug() << "Closing database connection on " << m_connectionInfo.database;
}

bool MysqlConnection::Query(QString sqlQuery)
{
    if(sqlQuery.isEmpty() || !m_db.isOpen())
        return false;

    QSqlQuery req;
    bool res = req.exec(sqlQuery);

    if(res)
        return true;

    qDebug() << "SQL error with " << sqlQuery << " : ";
    qDebug() << req.lastError();
    return false;
}

bool MysqlConnection::PQuery(QString sqlQuery, ...)
{
    if(sqlQuery.isEmpty() || !m_db.isOpen())
        return false;

    va_list ap;
    va_start(ap, sqlQuery);
    QString query;
    query.vsprintf(sqlQuery.toAscii().data(), ap);

    return Query(query);
}
