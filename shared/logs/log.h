#ifndef LOG_H
#define LOG_H

#include <QtCore>
#include <iostream>
#include "log.h"
#include "configuration/configmgr.h"

using namespace std;

enum LogType
{
    LOG_TYPE_NORMAL = 0,
    LOG_TYPE_DETAIL = 1,
    LOG_TYPE_DEBUG  = 2
};

class Log : QObject
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
            return "[ Detail ] ";
        case LOG_TYPE_DEBUG:
            return "[ Debug ] ";
        case LOG_TYPE_NORMAL:
        default:
            return "";
        }
    }

    void Init(ushort logConsoleLevel, ushort logFileLevel, QString logFile);
    void OpenFile(QString fileName);
    void WriteLog(QString logMessage, LogType logType);
    static void Write(LogType logType, QString message, ...);

private:
    Log();
    ~Log();

    static Log* m_instance;

    LogType m_logTypeConsole;
    LogType m_logTypeFile;
    QFile* m_file;
};

#endif
