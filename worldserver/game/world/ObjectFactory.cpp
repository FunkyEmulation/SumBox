#include "ObjectFactory.h"
#include "configuration/configmgr.h"

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
    QSqlQuery req = Database::Auth()->PQuery(AUTH_SELECT_ACCOUNT_SESSION_KEY, key.toLatin1().data());

    if (req.first())
    {
        if(m_accounts.contains(req.value(req.record().indexOf("account_id")).toInt()))
            return NULL;

        Account* acc = new Account(
            req.value(req.record().indexOf("account_id")).toInt(),
            req.value(req.record().indexOf("username")).toString(),
            req.value(req.record().indexOf("pseudo")).toString(),
            req.value(req.record().indexOf("gm_level")).toInt(),
            req.value(req.record().indexOf("secret_question")).toString(),
            req.value(req.record().indexOf("secret_answer")).toString(),
            ((ulong)req.value(req.record().indexOf("subscription")).toInt()) * 1000
        );
        if(acc->m_subscriptionTime < 0)
            acc->m_subscriptionTime = 0;
        m_accounts.insert(acc->GetId(), acc);

        LoadAccountCharacters(acc);

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

QList<Character*> ObjectFactory::LoadAccountCharacters(Account* const acc)
{
    QList<Character*> characters;

    if(!m_accounts.contains(acc->GetId()))
        return characters;

    QSqlQuery reqChars = Database::Char()->PQuery(SELECT_ACCOUNT_SERVER_CHARACTERS, acc->GetId(), ConfigMgr::World()->GetInt("ServerId"));
    while(reqChars.next())
    {
        if(m_characters.contains(reqChars.value(reqChars.record().indexOf("guid")).toInt()))
            continue;

        Character* curChar = new Character(
            reqChars.value(reqChars.record().indexOf("guid")).toInt(),
            reqChars.value(reqChars.record().indexOf("name")).toString(),
            reqChars.value(reqChars.record().indexOf("gender")).toInt(),
            reqChars.value(reqChars.record().indexOf("gfx_id")).toInt(),
            reqChars.value(reqChars.record().indexOf("color_1")).toInt(),
            reqChars.value(reqChars.record().indexOf("color_2")).toInt(),
            reqChars.value(reqChars.record().indexOf("color_3")).toInt(),
            100,
            reqChars.value(reqChars.record().indexOf("level")).toInt(),
            reqChars.value(reqChars.record().indexOf("class")).toInt()
        );
        curChar->m_account = acc;

        m_characters.insert(curChar->GetId(), curChar);
        characters.append(curChar);
    }

    acc->m_characters.append(characters);

    return characters;
}

Character* ObjectFactory::CreateCharacter(int account, QString name, int breed, int gender, int gfxId, char* color1, char* color2, char* color3)
{
    if(!m_accounts.contains(account))
        return NULL;

    Database::Char()->PQuery(INSERT_NEW_CHAR, account, ConfigMgr::World()->GetInt("ServerId"), name.toLatin1().data(), breed, gender, gfxId, color1, color2, color3);
    QList<Character*> charsCreated = LoadAccountCharacters(m_accounts.value(account));
    if(charsCreated.isEmpty())
        return NULL;
    else
        return charsCreated.last();
}
