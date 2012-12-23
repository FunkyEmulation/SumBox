#include "AuthModel.h"

using namespace std;
AuthModel* AuthModel::m_instance = NULL;

AuthModel* AuthModel::getInstance(QString host,QString user,QString pass,QString dbname)
{
 if (m_instance == NULL)
    m_instance = new AuthModel(host,user,pass,dbname);

 return m_instance;
}

bool AuthModel::Error() { return m_error; }

AuthModel::AuthModel(QString host,QString user,QString pass,QString dbname)
{
    m_error = false;
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(host);
    m_db.setUserName(user);
    m_db.setPassword(pass);
    m_db.setDatabaseName(dbname);

    if(!m_db.open()) {
        cout << "Error during database connection : " << m_db.lastError().text().toAscii().data() << endl;
        m_error = true;
        return;
    }

    cout << "Database connection accomplished on " << dbname.toAscii().data() << endl;
}

QMap<QString,QString> AuthModel::getAccount(QString account)
{
    QMap<QString,QString> accountInfos;
    QSqlQuery req;
    req.prepare("SELECT * FROM accounts WHERE account=?");
    req.addBindValue(account.toAscii().data());

        if (!req.exec()) {
            cout << "SQL Query failed : " << req.lastError().text().toAscii().data() << endl;
            return accountInfos;
        }

        if (req.first())
        {
          accountInfos["account"]         = req.value(req.record().indexOf("account")).toString().toAscii().data();
          accountInfos["pseudo"]          = req.value(req.record().indexOf("pseudo")).toString().toAscii().data();
          accountInfos["password"]        = req.value(req.record().indexOf("password")).toString().toAscii().data();
          accountInfos["gmlevel"]         = req.value(req.record().indexOf("gmlevel")).toString().toAscii().data();
          accountInfos["servers"]         = req.value(req.record().indexOf("servers")).toString().toAscii().data();
          accountInfos["secret_question"] = req.value(req.record().indexOf("secret_question")).toString().toAscii().data();
          accountInfos["secret_answer"]   = req.value(req.record().indexOf("secret_answer")).toString().toAscii().data();
          accountInfos["logged"]          = req.value(req.record().indexOf("logged")).toString().toAscii().data();
          accountInfos["banned"]          = req.value(req.record().indexOf("banned")).toString().toAscii().data();

          cout << "Account = " << account.toAscii().data() << " >> " << accountInfos["account"].toAscii().data() << endl;

          return accountInfos;
        }
        return accountInfos;
}
