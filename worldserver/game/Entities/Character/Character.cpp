#include "Character.h"
#include "Utils/Util.h"

Character::Character(WorldSession* session) : Unit()
{
    m_session = session;

    m_race = 0;
    m_gender = 0;
    m_color1 = 0;
    m_color2 = 0;
    m_color3 = 0;
    m_typeId = TYPEID_CHARACTER;

    for (quint8 i = 0; i < TOTAL_CHARACTER_STATS; ++i)
    {
        sCharacterStats stats;
        m_stats[(CharacterStats)i] = stats;
    }
}

Character::~Character()
{
}

bool Character::Create(quint32 guid, sCharacterCreateInfos characterCreateInfos)
{
    SetGuid(guid);

    m_name      = characterCreateInfos.name;
    m_race      = characterCreateInfos.race;
    m_gender    = characterCreateInfos.gender;
    m_gfxId     = characterCreateInfos.gfxId;
    m_color1    = characterCreateInfos.color1;
    m_color2    = characterCreateInfos.color2;
    m_color3    = characterCreateInfos.color3;

    SetMapId(characterCreateInfos.mapId);
    SetCellId(characterCreateInfos.cellId);

    return true;
}

bool Character::LoadFromDB(quint32 guid)
{
    QSqlQuery result = Database::Char()->PQuery(SELECT_CHARACTER, guid, GetSession()->GetAccountInfos().id);

    if (!result.first())
    {
        Log::Write(LOG_TYPE_NORMAL, "Character::LoadFromDB character with guid %u not found or wrong account");
        return false;
    }

    QSqlRecord rows = result.record();

    m_guid = guid;
    m_name = result.value(rows.indexOf("name")).toString();
    m_race = (quint8)result.value(rows.indexOf("race")).toUInt();
    m_gender = (quint8)result.value(rows.indexOf("gender")).toUInt();
    m_level = (quint16)result.value(rows.indexOf("level")).toUInt();
    m_gfxId = (quint16)result.value(rows.indexOf("gfx_id")).toUInt();
    m_color1 = result.value(rows.indexOf("color_1")).toInt();
    m_color2 = result.value(rows.indexOf("color_2")).toInt();
    m_color3 = result.value(rows.indexOf("color_3")).toInt();

    SetMapId((quint16)result.value(rows.indexOf("map_id")).toUInt());
    SetCellId((quint16)result.value(rows.indexOf("cell_id")).toUInt());

    m_map = MapMgr::Instance()->LoadMap(GetMapId());

    if (!m_map || !m_cellId)
    {
        // error
        return false;
    }

    /*
        this._curCarte = World.getCarte(map);
        this._savePos = savePos;
        if(_curCarte == null && World.getCarte(Ancestra.CONFIG_START_MAP) != null)
        {
            this._curCarte = World.getCarte(Ancestra.CONFIG_START_MAP);
            this._curCell = _curCarte.getCase(Ancestra.CONFIG_START_CELL);
        }else if (_curCarte == null && World.getCarte(Ancestra.CONFIG_START_MAP) == null)
        {
            GameServer.addToLog("Personnage mal positione, et position de départ non valide. Fermeture du serveur.");
            Ancestra.closeServers();
        }
        else if(_curCarte != null)
        {
            this._curCell = _curCarte.getCase(cell);
            if(_curCell == null)
            {
                this._curCarte = World.getCarte(Ancestra.CONFIG_START_MAP);
                this._curCell = _curCarte.getCase(Ancestra.CONFIG_START_CELL);
            }
        }
     */

    GetSession()->SetCharacter(this);

    return true;
}

void Character::SaveToDB(bool create)
{
    if (create)
    {
        Database::Char()->PQuery(INSERT_CHARACTER, GetGuid(), GetSession()->GetAccountInfos().id, m_name.toLatin1().data(), m_race, m_gender, m_gfxId, m_color1, m_color2, m_color3, m_map->GetData().id, m_cellId);
        Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_CHARS, GetSession()->GetAccountInfos().id, ConfigMgr::Instance()->World()->GetInt("ServerId"), GetSession()->GetCharsCount() + 1);
    }
    else
    {
        // Todo update player
    }
}

void Character::SendCharacterStats()
{
    WorldPacket data(SMSG_CHAR_STATS);

    data << 0 << ","; // current XP
    data << 0 << ","; // XP low
    data << 0 << "|"; // XP high

    data << 0 << "|"; // kamas
    data << 0 << "|"; // bonus points
    data << 0 << "|"; // spell bonus points

    // todo
    // fakeAli(=idAli si unFake) ~ idAli , 1(?), rangAli , ptsHonneur , 0(deshonnor?), showAli |
    data << "0~0,0,0,0,0,0|";

    data << 0 << ","; // HP
    data << 0 << "|"; // Max HP

    data << 0 << ","; // Energy
    data << 0 << "|"; // Max eneregy

    data << 0 << "|"; // initiative
    data << 0 << "|"; // Discernment

    // Character stats
    for (quint8 i = 0; i < TOTAL_CHARACTER_STATS; ++i)
        data << m_stats[(CharacterStats)i].ToPacketString();

    GetSession()->SendPacket(data);
}
