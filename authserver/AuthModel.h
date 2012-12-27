#ifndef AUTHMODEL_H
#define AUTHMODEL_H

#include <QCoreApplication>
#include <QtSql>
#include <iostream>

using namespace std;

class AuthModel
{
public:
    static AuthModel* getInstance(QString host = NULL, QString user = NULL, QString pass = NULL, QString dbname = NULL);
    QSqlDatabase getDb();
    QMap<QString,QString> getAccount(QString account);
    QList< QMap<QString, QString> > getServers(int id = -1,bool force = false);
    QList<QString> getBanips(bool force = false);
    bool Error();

private:
    AuthModel(QString host, QString user, QString pass, QString dbname);

    bool m_error;
    static AuthModel* m_instance;
    QSqlDatabase m_db;

    QList< QMap<QString, QString> > m_serversList;
    QList< QString > m_banips;
};

#endif // AUTHMODEL_H
