#include "Server/WorldSession.h"
#include "Utils/Util.h"
#include "Entities/Character/Character.h"
#include "Entities/ObjectMgr.h"

void WorldSession::HandleCharList(QString& /*packet*/)
{
    m_state = OnQueue;
    WorldQueue::Instance()->AddClient(this);
}

void WorldSession::SendCharacterList()
{
    QSqlQuery result = Database::Char()->PQuery(SELECT_ACCOUNT_CHARACTERS, GetAccountInfos().id);
    QSqlRecord rows = result.record();
    m_charsList.clear();

    WorldPacket data(SMSG_CHAR_LIST);
    data << GetAccountInfos().subscriptionTime;
    data << "|" << result.size();

    while(result.next())
    {
        qint32 guid = result.value(rows.indexOf("guid")).toInt();

        data << "|";
        data << guid << ";";
        data << result.value(rows.indexOf("name")).toString() << ";";
        data << result.value(rows.indexOf("level")).toInt() << ";";
        data << result.value(rows.indexOf("gfx_id")).toInt() << ";";
        data << result.value(rows.indexOf("color_1")).toInt() << ";";
        data << result.value(rows.indexOf("color_2")).toInt() << ";";
        data << result.value(rows.indexOf("color_3")).toInt() << ";";

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

void WorldSession::HandleCharRandomPseudo(QString& /*packet*/)
{
    srand(time(NULL));
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

	// Todo vérifier si le nom existe déjà !
    WorldPacket data(MSG_CHAR_RANDOM_NAME);
    data << pseudo;
    SendPacket(data);
}

void WorldSession::HandleCharCreate(QString& packet)
{
    QStringList datas = packet.mid(2).split("|");
    if(datas.size() < 6)
        return; // Ne devrait pas arriver sauf envoit manuel

    QString pseudo(datas.at(0));

    WorldPacket data(SMSG_CHAR_CREATE_ERROR);
    QSqlQuery req = Database::Char()->PQuery(CHECK_CHAR_EXISTS, pseudo.toLatin1().data());

    if(req.next() && req.value(req.record().indexOf("count")).toInt() >= 1)
    {
        data << "a";
        SendPacket(data);
        return;
    }

    if(!IsValidName(pseudo))
    {
        data << "n";
        SendPacket(data);
        return;
    }

    if(m_charsList.count() > 4)
    {
        data << "f";
        SendPacket(data);
        return;
    }

    // TODO: Checker la validité de la race
    quint16 gfxId = (QString::number(datas[1].toUInt()) + QString::number(datas[2].toUInt())).toUInt();

    sRaceStartInfos startInfos = World::Instance()->GetRaceStartInfos(datas[1].toUInt());
    sCharacterCreateInfos charCreateInfos(pseudo, (quint8)datas[1].toUInt(), (quint8)datas[2].toUInt(), gfxId, datas.at(3).toInt(), datas.at(4).toInt(), datas.at(5).toInt(), startInfos.mapId, startInfos.cellId);
    QScopedPointer<Character> newChar(new Character(this));

    if(newChar->Create(ObjectMgr::Instance()->GenerateGuid(GUIDTYPE_CHARACTER), charCreateInfos))
    {
        newChar->SaveToDB(true);

        WorldPacket data(SMSG_CHAR_CREATE);
        SendPacket(data);
        SendCharacterList();
    }
    else
        SendPacket(data);
}

void WorldSession::HandleCharDelete(QString& packet)
{
    QStringList datas = packet.mid(2).split("|");
    if(datas.isEmpty())
        return;

    qint32 guid = datas.at(0).toInt();

    if(InCharsList(guid))
    {
        //if(target->GetLvl() < 20 || (target->GetLvl() >= 20 && datas.count() >= 2 && datas.at(1) == m_account->GetAnswer()))
        //{
            Database::Char()->PQuery(DELETE_CHARACTER, guid);
            Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_CHARS, GetAccountInfos().id, ConfigMgr::Instance()->World()->GetInt("ServerId"), (m_charsList.count() - 1));

            SendCharacterList();
            return;
        //}
    }

    WorldPacket data(SMSG_CHAR_DELETE);
    // Envoyer une donnée si suppression réussie ou pas?
    SendPacket(data);
}

void WorldSession::HandleCharSelect(QString& packet)
{
    quint32 guid = packet.mid(2).toUInt();

    Character* character = new Character(this);
    WorldPacket data(MSG_CHAR_SELECT);

    if (character->LoadFromDB(guid))
    {
        data << "||" << character->GetGuid();
        data << "|" << character->GetName();
        data << "|" << character->GetLevel();
        data << "|" << -1; // Guild
        data << "|" << character->GetGender();
        data << "|" << character->GetGfxId();
        data << "|" << character->GetColor1();
        data << "|" << character->GetColor2();
        data << "|" << character->GetColor3();
        data << "|"; // Items
    }
    else
        data << "E|";

    SendPacket(data);
}
