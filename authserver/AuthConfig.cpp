#include <AuthConfig.h>
#include "../shared/logs/log.h"

using namespace std;
AuthConfig* AuthConfig::m_instance = NULL;

AuthConfig::AuthConfig(QString confName)
{
 m_error = false;
 LoadConfig(confName);
}

AuthConfig* AuthConfig::getInstance(QString name)
{
 if (m_instance == NULL)
    m_instance = new AuthConfig(name.toAscii().data());

 return m_instance;
}

QMap<QString,QString> AuthConfig::getConfig()
{
 return m_AuthConfiguration;
}

bool AuthConfig::Error()
{
  return m_error;
}

void AuthConfig::LoadConfig(QString confName)
  {
      QDomDocument configDocument("AuthConfiguration");
         QFile file(confName);
         if(!file.open(QIODevice::ReadOnly))
         {
             Log::Write(LOG_TYPE_NORMAL, "Error: Non-existent auth configuration file '%s'...", confName.toAscii().data());
             file.close();
             m_error = true;
             return;
         }
         if(!configDocument.setContent(&file))
         {
             Log::Write(LOG_TYPE_NORMAL, "Invalid xml configuration ...");
             file.close();
             m_error = true;
             return;
         }
         file.close();
         QDomElement configElement = configDocument.documentElement();

         QDomNode node = configElement.firstChild(); // Premier noeud

         while(!node.isNull()) // parcourt ...
         {
             QDomElement curEl = node.toElement();
             if(!curEl.isNull())
                 m_AuthConfiguration[curEl.tagName().toAscii().data()] = curEl.text().toAscii().data();
             node = node.nextSibling(); // On va  l'lment suivant
         }

         Log::Write(LOG_TYPE_NORMAL, "Auth config loaded ...");
  }

