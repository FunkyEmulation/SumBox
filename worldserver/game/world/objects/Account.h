#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QtCore>
#include "Character.h"

class ObjectFactory;
class Character;

typedef QList<Character*> CharsList;

class Account
{
public:
    QString GetCharsString() const; // Renvoit la liste des personnages sous forme de string pour le packet AL
    // Getters
    CharsList GetCharacters() const { return m_characters; }
    int GetId() const { return m_id; }
    QString GetName() const { return m_accountName; }
    QString GetPseudo() const { return m_pseudo; }
    int GetGmLvl() const { return m_gmLevel; }
    QString GetQuestion() const { return m_secretQuestion; }
    QString GetAnswer() const { return m_secretAnswer; }
    ulong GetSubscriptionTime() const { return m_subscriptionTime; }

private:
    inline Account(int id, QString name, QString pseudo, int gmLevel, QString question, QString answer, ulong subscriptionTime)
    {
        m_id = id;
        m_accountName = name;
        m_pseudo = pseudo;
        m_gmLevel = gmLevel;
        m_secretQuestion = question;
        m_secretAnswer = answer;
        m_subscriptionTime = subscriptionTime;
    }

    int m_id;
    QString m_accountName;
    QString m_pseudo;
    int m_gmLevel;
    QString m_secretQuestion;
    QString m_secretAnswer;
    ulong m_subscriptionTime;
    CharsList m_characters;

    friend class ObjectFactory;
};

#endif // ACCOUNT_H
