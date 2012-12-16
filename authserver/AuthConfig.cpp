#include <AuthConfig.h>

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
             cout << "Error: Non-existent auth configuration file '" << confName.toAscii().data() << "' ..." << endl
                  << "Exiting ..." << endl;
             file.close();
             m_error = true;
             return;
         }
         if(!configDocument.setContent(&file))
         {
             cout << "Invalid xml configuration ..." << endl;
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

      cout << "Auth config loaded ..." << endl;
  }

