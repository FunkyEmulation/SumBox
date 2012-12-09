#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <ctime>

bool initialize = true;
QString charset = "abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

QString GenerateRandomString(quint8 length)
{
    if(initialize)
    {
        srand(time(NULL));
        initialize = false;
    }

    QString result;
    for(quint8 i = 1; i < length; ++i)
        result[i] = charset[rand() % charset.length()];

    return result;
}

#endif
