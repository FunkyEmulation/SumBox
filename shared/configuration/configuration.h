#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtCore>

typedef QMap<QString, QString> ConfigMap;

class Configuration
{
public:
    static Configuration* Instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            mutex.lock();
            m_instance = new Configuration;
            mutex.unlock();
        }
        return m_instance;
    }

    static void Close()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_instance;
        mutex.unlock();
    }

    static QString GetQString(QString name);
    static std::string GetString(QString name);
    static bool GetBool(QString name);
    static int GetInt(QString name);
    static int GetUInt(QString name);

    bool OpenFile(QString fileName);
    QString GetValue(QString name);

private:
    Configuration();
    ~Configuration();

    static Configuration* m_instance;

    QFile* m_file;
    ConfigMap m_config;
};

#endif
