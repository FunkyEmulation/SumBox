#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <ctime>

bool initialize = true;
QString charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

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

QString GenerateRandomPseudo(int minLength,int maxLength)
{
    int max = rand()%(maxLength-minLength) +minLength;

    QString voyelles = "aeiouy";
    QString consonnes = "bcdfghjklmnpqrstvwxz";
    QString pseudo = "";

    QList<QString> prefixes;
    prefixes << "mi" << "el" << "th" << "id" << "nu" << "ig" << "heo" << "er" << "am" << "vor";
    prefixes << "ga" << "in" << "may" <<  "sa" << "ar" << "se" << "ha" << "lu" << "gw" << "ea";
    prefixes << "fin" << "me" << "rami" << "ne" << "le" << "fe" << "or" << "pen" << "que" << "rod";
    prefixes << "cele" << "ar" << "sae" << "eg" << "ii" << "tu" << "ri" << "ta" << "ur" << "val" << "ol";

    pseudo += prefixes[rand() % prefixes.length()]; // préfixe aléatoire
    while(pseudo.length() < max)
    {
        if(voyelles.contains(pseudo[pseudo.length() - 1])) // Derniere lettre = voyelle ?
        {
            pseudo += consonnes[rand()%consonnes.length()];
        } else // derniere lettre = consonne
        {
            pseudo += voyelles[rand()%voyelles.length()];
        }
    }

    pseudo.prepend("|");
    return pseudo;
}

QString cryptPassword(QString password, QString hashKey)
{
           QString crypted = "";

           for (int i = 0; i < password.length(); i++)
           {
               char PPass = password[i].toAscii();
               char PKey = hashKey[i].toAscii();

               int APass = (int)PPass / 16;

               int AKey = (int)PPass % 16;

               int ANB = (APass + (int)PKey) % charset.length();
               int ANB2 = (AKey + (int)PKey) % charset.length();

               crypted += charset[ANB];
               crypted += charset[ANB2];
           }
           return crypted;
}

#endif
