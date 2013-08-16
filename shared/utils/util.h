#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <ctime>
#include <QString>

/*
 * Indique si le pseudo de personnage est valide
 */
bool IsValidName(QString name);
/*
 * Génère une chaine aléatoire de taille length et à partir des caractères de charset
 */
QString GenerateRandomString(quint8 length);
/*
 * Génère un pseudo aléatoire
 */
QString GenerateRandomPseudo(int minLength,int maxLength);
/*
 * Crypte un mot de passe servant à la comparaison lors de l'authentification
 */
QString cryptPassword(QString password, QString hashKey);

#endif
