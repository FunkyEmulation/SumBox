#ifndef AUTHCONFIG_H
#define AUTHCONFIG_H

#include <QFile>
#include <QtXml>
#include <iostream>

class AuthConfig
{
public:
    static AuthConfig* getInstance(QString name = "authconfig.xml");
    void LoadConfig(QString confName);
    QMap<QString,QString> getConfig();
    bool Error();

private:
    AuthConfig (QString confName);

    static AuthConfig* m_instance;
    bool m_error;
    QMap<QString,QString> m_AuthConfiguration;
};

#endif // AUTHCONFIG_H
