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
    bool Error();

private:
    AuthModel(QString host, QString user, QString pass, QString dbname);

    bool m_error;
    static AuthModel* m_instance;
    QSqlDatabase m_db;
};

#endif // AUTHMODEL_H
