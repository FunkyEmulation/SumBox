#include "Util.h"
#include <QRegExp>
#include <QList>

QString Utils::charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
bool Utils::initializeRandom = true;

bool Utils::IsValidName(QString name)
{
    return name.contains(QRegExp("^[a-zA-Z\-]{3,15}$"));
}

QString Utils::GenerateRandomString(quint8 length)
{
    if (initializeRandom)
    {
        initializeRandom = false;
        srand(time(NULL));
    }

    QString result;
    for(quint8 i = 0; i < length; ++i)
        result[i] = charset[rand() % charset.length()];

    return result;
}

QString Utils::CryptPassword(QString password, QString hashKey)
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

char* Utils::ToChar(QString string)
{
    return string.toLatin1().data();
}

quint16 Utils::GetCellId(QString cellString)
{
    quint16 number1 = (quint16)charset.indexOf(cellString.at(0)) * charset.length();
    quint16 number2 = (quint16)charset.indexOf(cellString.at(1));

    return number1 + number2;
}

QString Utils::GetCellString(quint16 cellId)
{
    quint16 charNumber2 = (quint16)cellId % charset.length();
    quint16 charNumber1 = (quint16)(cellId - charNumber2) / charset.length();

    return QString(charset.at(charNumber1)) + QString(charset.at(charNumber2));
}
