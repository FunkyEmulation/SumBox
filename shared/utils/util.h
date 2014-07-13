#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <ctime>
#include <QString>

class Utils
{
public:
    static bool IsValidName(QString name);
    static QString GenerateRandomString(quint8 length);
    static QString CryptPassword(QString password, QString hashKey);
    static char* ToChar(QString string);

    static quint16 GetCellId(QString cellString);
    static QString GetCellString(quint16 cellId);

private:
    static bool initializeRandom;
    static QString charset;
};

#endif
