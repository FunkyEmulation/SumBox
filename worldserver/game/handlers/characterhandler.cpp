#include "../server/worldsession.h"
#include "utils/util.h"

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
    Log::Write(LOG_TYPE_DEBUG, "Send Character list");
    WorldPacket CharsList(SMSG_CHARACTER_LIST);
    CharsList << QString::number(m_account->GetSubscriptionTime()) << m_account->GetCharsString();
    SendPacket(CharsList);
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

    WorldPacket randomPseudo(CMSG_RANDOM_PSEUDO);
    randomPseudo << pseudo;
    SendPacket(randomPseudo);
}

void WorldSession::HandleCreatePerso(QString& packet)
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
    if(m_account->GetCharacters()->count() >= 5)
    {
        error << "f";
        SendPacket(error);
        return;
    }

    // TODO: Checker la validité de la race
    int gfxId = (datas[1] + datas[2]).toInt();
    Character* newCharacter = ObjectFactory::Instance()->CreateCharacter(m_account->GetId(), pseudo, datas[1].toInt(), datas[2].toInt(), gfxId, datas.at(3).toLatin1().data(), datas.at(4).toLatin1().data(), datas.at(5).toLatin1().data());
    if(newCharacter != NULL)
    {
        WorldPacket success(SMSG_CREATE_CHAR_OK);
        SendPacket(success);
        SendCharacterList();
    }
    else
    {
        SendPacket(error);
        return;
    }
}

void WorldSession::HandleDeleteChar(QString &packet)
{
    QStringList datas = packet.mid(2).split("|");
    if(datas.isEmpty())
        return; // Ne devrait pas arriver

    int charId = datas.at(0).toInt();
    Character* target;
    if((target = ObjectFactory::Instance()->GetCharacter(charId)) != NULL && target->GetAccount() == m_account)
    {
        if(target->GetLvl() < 20 || (target->GetLvl() >= 20 && datas.count() >= 2 && datas.at(1) == m_account->GetAnswer()))
        {
            Database::Char()->PQuery(DELETE_CHAR, charId);
            m_account->GetCharacters()->removeOne(target);
            Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_CHARS, m_account->GetId(), ConfigMgr::Instance()->World()->GetInt("ServerId"), m_account->GetCharacters()->count());
            SendCharacterList();
            return;
        }
    }

    SendPacket(WorldPacket(SMSG_DELETE_CHAR_ERROR));
}

void WorldSession::HandleSelectChar(QString &packet)
{

}
