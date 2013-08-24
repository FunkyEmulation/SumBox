#include "../server/worldsession.h"
#include "utils/util.h"
#include "game/Entities/Character/Character.h"

void WorldSession::HandleCharactersList(QString& /*packet*/)
{
    m_state = OnQueue;
    WorldQueue::Instance()->AddClient(this);
}

void WorldSession::HandleSendCharacterList(QString& /*packet*/)
{
    SendCharacterList();
}

void WorldSession::SendCharacterList()
{
    // Définir une nomanclature pour les logs.
    Log::Write(LOG_TYPE_DEBUG, "SMSG_CHARACTER_LIST");

    QSqlQuery queryResult = Database::Char()->PQuery(SELECT_ACCOUNT_CHARACTERS, GetAccountInfos().id);
    QSqlRecord rows = queryResult.record();

    WorldPacket data(SMSG_CHARACTER_LIST);
    data << GetAccountInfos().subscriptionTime;
    data << "|" << queryResult.size();

    while(queryResult.next())
    {
        qint32 guid = queryResult.value(rows.indexOf("guid")).toInt();

        data << "|";
        data << guid << ";";
        data << queryResult.value(rows.indexOf("name")).toString() << ";";
        data << queryResult.value(rows.indexOf("level")).toInt() << ";";
        data << queryResult.value(rows.indexOf("gfx_id")).toInt() << ";";
        data << queryResult.value(rows.indexOf("color_1")).toInt() << ";";
        data << queryResult.value(rows.indexOf("color_2")).toInt() << ";";
        data << queryResult.value(rows.indexOf("color_3")).toInt() << ";";

        data << ";"; // Accessories
        data << "0;"; // Merchant ?
        data << ConfigMgr::World()->GetUInt("ServerId") << ";";
        data << "0;"; // IsDead ?
        data << ";"; // DeathCount
        data << 200; // LevelMax

        // Rien pour la classe ?

        m_charsList.push_back(guid);
    }

    SendPacket(data);
}

void WorldSession::HandleRandomPseudo(QString& /*packet*/)
{
    int max = rand()%4 +4;

    QString voyelles = "aeiouy";
    QString consonnes = "bcdfghjklmnpqrstvwxz";
    QString pseudo = "";

    QList<QString> prefixes;
    prefixes << "mi" << "el" << "th" << "id" << "nu" << "ig" << "heo" << "er" << "am" << "vor";
    prefixes << "ga" << "in" << "may" <<  "sa" << "ar" << "se" << "ha" << "lu" << "gw" << "ea";
    prefixes << "fin" << "me" << "rami" << "ne" << "le" << "fe" << "or" << "pen" << "que" << "rod";
    prefixes << "cele" << "ar" << "sae" << "eg" << "ii" << "tu" << "ri" << "ta" << "ur" << "val" << "ol";

    // préfixe aléatoire
    pseudo += prefixes[rand() % prefixes.length()];

    while(pseudo.length() < max)
    {
        // Derniere lettre = voyelle ?
        if(voyelles.contains(pseudo[pseudo.length() - 1]))
            pseudo += consonnes[rand()%consonnes.length()];
        // derniere lettre = consonne
        else
            pseudo += voyelles[rand()%voyelles.length()];
    }

    pseudo.prepend("|");

    WorldPacket randomPseudo(CMSG_RANDOM_PSEUDO);
    randomPseudo << pseudo;
    SendPacket(randomPseudo);
}

void WorldSession::HandleCreateCharacter(QString& packet)
{
    QStringList datas = packet.mid(2).split("|");
    if(datas.size() < 6)
        return; // Ne devrait pas arriver sauf envoit manuel

    QString pseudo(datas.at(0));

    WorldPacket error(SMSG_CREATE_CHAR_ERROR);
    QSqlQuery req = Database::Char()->PQuery(CHECK_CHAR_EXISTS, pseudo.toLatin1().data());

    if(req.next() && req.value(req.record().indexOf("count")).toInt() >= 1)
    {
        error << "a";
        SendPacket(error);
        return;
    }

    if(!IsValidName(pseudo))
    {
        error << "n";
        SendPacket(error);
        return;
    }

    if(m_charsList.count() > 4)
    {
        error << "f";
        SendPacket(error);
        return;
    }

    // TODO: Checker la validité de la race
    quint16 gfxId = datas[1].toUInt() + datas[2].toUInt();

    sCharacterCreateInfos charCreateInfos(pseudo, toByte(datas[1]), toByte(datas[2]), gfxId, datas.at(3).toUInt(), datas.at(4).toUInt(), datas.at(5).toUInt());
    Character* newChar = new Character(this);

    quint32 guid = 0; // TODO : Generate GUID
    if(newChar->Create(guid, charCreateInfos))
    {
        newChar->SaveToDB(true);

        WorldPacket data(SMSG_CREATE_CHAR_OK);
        SendPacket(data);
        SendCharacterList();
    }
    else
        SendPacket(error);

    delete newChar;
}

void WorldSession::HandleDeleteCharacter(QString &packet)
{
    QStringList datas = packet.mid(2).split("|");
    if(datas.isEmpty())
        return;

    qint32 guid = datas.at(0).toInt();

    if(InCharsList(guid))
    {
        //if(target->GetLvl() < 20 || (target->GetLvl() >= 20 && datas.count() >= 2 && datas.at(1) == m_account->GetAnswer()))
        //{
            Database::Char()->PQuery(DELETE_CHAR, guid);
            Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_CHARS, GetAccountInfos().id, ConfigMgr::Instance()->World()->GetInt("ServerId"), (m_charsList.count() - 1));

            SendCharacterList();
            return;
        //}
    }

    WorldPacket data(SMSG_DELETE_CHAR_ERROR);
    SendPacket(data);
}

void WorldSession::HandleSelectChar(QString &packet)
{

}
