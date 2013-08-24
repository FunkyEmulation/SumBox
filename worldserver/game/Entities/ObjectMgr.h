#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QtCore>
#include "databases/database.h"
#include "utils/singleton.h"

class Character;

class ObjectMgr : public Singleton<ObjectMgr>
{
public:
    ObjectMgr();
    ~ObjectMgr();
/*
    Character* GetCharacter(int id);
    QList<Character*> LoadAccountCharacters(Account* const acc);
    Character* CreateCharacter(int account, QString name, int breed, int gender, int gfxId, char* color1, char* color2, char* color3);
*/
private:
    QMap<int, Character*> m_characters;
};

#endif // OBJECTFACTORY_H
