#include "log.h"

Log* Log::m_instance = 0;

Log::Log()
{
}

Log::~Log()
{
    if(m_file)
        m_file->close();
}

void Log::OpenFile(QString fileName)
{
    m_file = new QFile(fileName);
    if(m_file->open(QIODevice::WriteOnly))
        return;

    QString error = m_file->errorString();
    m_file = NULL;
    Log::Write(LOG_TYPE_NORMAL, "Cannot open log file %s : %s", fileName.toAscii().data(), error.toAscii().data());
}

void Log::WriteLog(QString logMessage)
{
    cout << logMessage.toAscii().data() << endl;

    if(m_file)
        m_file->write(logMessage.toAscii());
}

void Log::Write(LogType logType, QString message, ...)
{
    // Faire un système pour vérifier quel log level est activé et si écrit dans fichier ou juste console
    QString logTypeString = Log::GetLogTypeString(logType);

    va_list ap;
    va_start(ap, message);
    QString logMessage;
    logMessage.vsprintf(message.toAscii().data(), ap);

    logMessage = logTypeString + logMessage;
    Log::Instance()->WriteLog(logMessage);
}
