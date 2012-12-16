#ifndef AUTHCONFIG_H
#define AUTHCONFIG_H

#include <QFile>
#include <QtXml>
#include <iostream>

class AuthConfig
{
public:
  static AuthConfig* getInstance(QString name = "authconfig.xml");
  QMap<QString,QString> getConfig();
  bool Error();

private:
  bool m_error;
  static AuthConfig* m_instance;

  QMap<QString,QString> m_AuthConfiguration;
  AuthConfig (QString confName);
  void LoadConfig(QString confName);
};


#endif // AUTHCONFIG_H
