#include "Character.h"
#include "utils/util.h"

Character::Character(WorldSession* session) : Unit()
{
    m_session = session;

    SetGuid(0);
    m_name = QString();
    m_race = 0;
    m_gender = 0;
    m_gfxId = 0;
    m_color1 = 0;
    m_color2 = 0;
    m_color3 = 0;
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
    m_map       = MapMgr::Instance()->LoadMap(characterCreateInfos.mapId);
    m_cellId    = characterCreateInfos.cellId;

    return true;
}

bool Character::LoadFromDB(quint32 guid)
{
    QSqlQuery result = Database::Char()->PQuery(SELECT_CHARACTER, guid, GetSession()->GetAccountInfos().id);

    if (!result.first())
    {
        // Log -> character not found or accountId != db account id
        return false;
    }

    QSqlRecord rows = result.record();

    m_guid = guid;
    m_name = result.value(rows.indexOf("name")).toString();
    m_race = (quint8)result.value(rows.indexOf("race")).toUInt();
    m_gender = (quint8)result.value(rows.indexOf("gender")).toUInt();
    m_gfxId = (quint16)result.value(rows.indexOf("gfx_id")).toUInt();
    m_color1 = result.value(rows.indexOf("color_1")).toInt();
    m_color2 = result.value(rows.indexOf("color_2")).toInt();
    m_color3 = result.value(rows.indexOf("color_3")).toInt();
    m_map = MapMgr::Instance()->LoadMap(result.value(rows.indexOf("map_id")).toUInt());
    m_cellId = result.value(rows.indexOf("cell_id")).toUInt();

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
    GetSession()->SendPacket(data);

    /*
    As = Account Stats =

    XP,xpLow(?),maxXp |
    kamas |
    ptsCaracts|
    ptsSorts |
    fakeAli(=idAli si unFake) ~ idAli , 1(?), rangAli , ptsHonneur , 0(deshonnor?), showAli |
    vie , maxVie |
    energie, maxEnergie |
    initiative |
    prospection |
     // 42 lignes de stats ; base        | equipement   | dons           | boost        //
                 basePA       , equipPA      , donsPA        , boostPa      |
                 basePM       , equipPM      , donsPM        , boostPM      |
                 force        , force        , force         , force        |
                 vita         , vita         , vita          , vita         |
                 sasa         , sasa         , sasa          , sasa         |
                 eau          , eau          , eau           , eau          |
                 air          , air          , air           , air          |
                 feu          , feu          , feu           , feu          |
                 eau          , eau          , eau           , eau          |
                     portee       , portee       , portee        , portee       |
                 invocs       , invocs       , invocs        , invocs       |
                 bonusDeg     , bonusDeg     , bonusDeg      , bonusDeg     |
                 bonDegPhys   , bonDegPhys   , bonDegPhys    , bonDegPhys   |
                 bonMaitrises , bonMaitrises , bonMaitrises  , bonMaitrises |
                 bonDmgs      , bonDmgs      , bonDmgs       , bonDmgs      |
                 bonPieges    , bonPieges    , bonPieges     , bonPieges    |
                 bonPrCentPieg, bonPrCentPieg, bonPrCentPieg , bonPrCentPieg|
                 bonSoins     , bonSoins     , bonSoins      , bonSoins     |
                 renvoiDmgs   , renvoiDmgs   , renvoiDmgs    , renvoiDmgs   |
                 bonCoupCriti , bonCoupCriti , bonCoupCriti  , bonCoupCriti |
                 bonEcheCriti , bonEcheCriti , bonEcheCriti  , bonEcheCriti |
                 esquivePA    , esquivePA    , esquivePA     , esquivePA    |
                 esquivePM    , esquivePM    , esquivePM     , esquivePM    |

                 resisNeutreFixe,
                 resisNeutre%,
                      resisNeutrePvpFixe,
                      resisNeutrePvP%,
                 resisTerreFixe,
                 resisTerre%,
                      resisTerrePvpFixe,
                      resisTerrePvp%,
                 resisFeuFixe,
                 resisFeu%,
                      resisFeuPvpFixe,
                      resisFeuPvp%,
                 resisEauFixe,
                 resisEau%,
                      resisEauPvpFixe,
                      resisEauPvp%,
                 resisAirFixe,
                 resisAir%,
                      resisAirPvpFixe,
                      resisAirPvp%
    */
}
