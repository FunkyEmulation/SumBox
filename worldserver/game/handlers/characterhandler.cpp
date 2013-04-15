#include "../server/worldsession.h"



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

    QSqlQuery req = Database::Char()->PQuery(SELECT_ACCOUNT_CHARACTERS, m_infos["account_id"].toInt());

    CharsList << QDateTime(m_infos["subscription_time"].toDateTime()).toTime_t() << "|";
    CharsList << req.size();

    while (req.next())
    {
        qDebug() << "boucle";
        CharsList << "|";
        CharsList << req.value(req.record().indexOf("guid")).toUInt() + ";";
        CharsList << req.value(req.record().indexOf("name")).toString() + ";";
        CharsList << req.value(req.record().indexOf("level")).toUInt() + ";";
        CharsList << req.value(req.record().indexOf("gfx_id")).toUInt() + ";";
        CharsList << req.value(req.record().indexOf("color_1")).toInt() + ";"; // Colors en hexa
        CharsList << req.value(req.record().indexOf("color_2")).toInt() + ";";
        CharsList << req.value(req.record().indexOf("color_3")).toInt() + ";";
        CharsList << ";"; // Accessories
        CharsList << "0;"; // Merchant ?
        CharsList << ";"; // ServeurId
        CharsList << "0;"; // Est mort ?
        CharsList << ";"; // DeathCount
        CharsList << "200;"; // LevelMax
    }

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

    WorldPacket randomPseudo(MSG_RANDOM_PSEUDO);
    randomPseudo << pseudo;
    SendPacket(randomPseudo);
}

void WorldSession::HandleCreatePerso(QString& /*packet*/)
{
    cout << "Creation perso " << endl;
}
