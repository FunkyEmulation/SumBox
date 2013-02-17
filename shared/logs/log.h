#ifndef LOG_H
#define LOG_H

#include <QtCore>
#include <iostream>
#include "log.h"

using namespace std;

enum LogLevel
{
    LOG_LEVEL_NORMAL = 0,
    LOG_LEVEL_DETAIL = 1,
    LOG_LEVEL_DEBUG  = 2
};

enum LogType
{
    LOG_TYPE_NORMAL = 0,
    LOG_TYPE_DETAIL = 1,
    LOG_TYPE_DEBUG  = 2
};

class Log
{
public:
    static Log* Instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            mutex.lock();
            m_instance = new Log;
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

    static QString GetLogTypeString(LogType logType)
    {
        switch(logType)
        {
        case LOG_TYPE_DETAIL:
            return "[ Detail ]";
        case LOG_TYPE_DEBUG:
            return "[ Error ]";
        case LOG_TYPE_NORMAL:
        default:
            return "";
        }
    }

    void SetLogLevel(LogLevel level) { m_level = level; }
    void OpenFile(QString fileName);
    void WriteLog(QString logMessage);
    static void Write(LogType logType, QString message, ...);

private:
    Log();
    ~Log();

    static Log* m_instance;

    QFile* m_file;
    quint8 m_level;
};

#endif
