#include "util.h"
#include <QRegExp>
#include <QList>

QString charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
static bool initialize = true;

bool IsValidName(QString name)
{
    bool valid = true;

    if(!name.contains(QRegExp("^[a-zA-Z\-]{3,15}$")))
        valid = false;

    return valid;
}

QString GenerateRandomString(quint8 length)
{
    if(initialize)
    {
        srand(time(NULL));
        initialize = false;
    }

    QString result;
    for(quint8 i = 0; i < length; ++i)
        result[i] = charset[rand() % charset.length()];

    return result;
}

QString CryptPassword(QString password, QString hashKey)
{
    QString crypted = "";

    for (int i = 0; i < password.length(); i++)
    {
        char PPass = password[i].toLatin1();
        char PKey = hashKey[i].toLatin1();

        int APass = (int)PPass / 16;
        int AKey = (int)PPass % 16;

        int ANB = (APass + (int)PKey) % charset.length();
        int ANB2 = (AKey + (int)PKey) % charset.length();

        crypted += charset[ANB];
        crypted += charset[ANB2];
    }
    return crypted;
}

char* ToChar(QString string)
{
    return string.toLatin1().data();
}
