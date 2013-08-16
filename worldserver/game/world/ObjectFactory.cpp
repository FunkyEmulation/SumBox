#include "ObjectFactory.h"
#include "objects/Account.h"
#include "objects/Character.h"

ObjectFactory* ObjectFactory::m_instance = NULL;

Account* ObjectFactory::GetAccount(int id)
{
    if(m_accounts.contains(id))
        return m_accounts.value(id);
    else
        return NULL;
}

Account* ObjectFactory::LoadAccount(QString key)
{
    QSqlQuery req = Database::Auth()->PQuery(AUTH_SELECT_ACCOUNT_SESSION_KEY, key.toAscii().data());

    if (req.first())
    {
        Account* acc = new Account(
            req.value(req.record().indexOf("account_id")).toInt(),
            req.value(req.record().indexOf("username")).toString(),
            req.value(req.record().indexOf("pseudo")).toString(),
            req.value(req.record().indexOf("gm_level")).toInt(),
            req.value(req.record().indexOf("secret_question")).toString(),
            req.value(req.record().indexOf("secret_answer")).toString(),
            ((ulong)req.value(req.record().indexOf("subscription")).toInt()) * 1000
        );

        QList<Character*> chars;
        QSqlQuery charsReq = Database::Char()->PQuery(SELECT_ACCOUNT_CHARACTERS, req.value(req.record().indexOf("account_id")).toInt());
        while(charsReq.next())
        {
            Character* curChar = LoadCharacter(charsReq);
            curChar->m_account = acc;
            chars.append(curChar);
        }
        acc->m_characters = chars;

        m_accounts.insert(req.value(req.record().indexOf("account_id")).toInt(), acc);

        return acc;
    }


    return NULL;
}

Character* ObjectFactory::GetCharacter(int id)
{
    if(m_characters.contains(id))
        return m_characters.value(id);
    else
        return NULL;
}

Character* ObjectFactory::LoadCharacter(QSqlQuery req)
{
    Character* Char = new Character(
        req.value(req.record().indexOf("guid")).toInt(),
        req.value(req.record().indexOf("name")).toString(),
        req.value(req.record().indexOf("gender")).toInt(),
        req.value(req.record().indexOf("gfx_id")).toInt(),
        req.value(req.record().indexOf("color_1")).toInt(),
        req.value(req.record().indexOf("color_2")).toInt(),
        req.value(req.record().indexOf("color_3")).toInt(),
        100,
        req.value(req.record().indexOf("level")).toInt(),
        req.value(req.record().indexOf("class")).toInt()
    );

    m_characters.insert(req.value(req.record().indexOf("guid")).toInt(), Char);
    return Char;
}
