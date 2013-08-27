#ifndef ACCOUNTMGR_H
#define ACCOUNTMGR_H

#include <QtCore>
#include "databases/database.h"
#include "game/Entities/Character/Character.h"
#include "utils/singleton.h"

class AccountMgr : public Singleton<AccountMgr>
{
public:
    AccountMgr();
    ~AccountMgr();

/*    Character* GetCharacter(int id);
    QList<Character*> LoadAccountCharacters(Account* const acc);
    Character* CreateCharacter(int account, QString name, int breed, int gender, int gfxId, char* color1, char* color2, char* color3);
*/
private:

};

#endif // ACCOUNTMGR_H
