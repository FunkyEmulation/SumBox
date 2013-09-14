#ifndef CHARACTER_H
#define CHARACTER_H

#include "Databases/Database.h"
#include "Define.h"
#include "Server/WorldSession.h"
#include "Entities/Unit/Unit.h"
#include "CharacterStats.h"

/*
   _loc1.createCharacter = function (sID, sName, oData)
    {
        var _loc5 = this.api.datacenter.Sprites.getItemAt(sID);
        if (_loc5 == undefined)
        {
            _loc5 = new dofus.datacenter.Character(sID, ank.battlefield.mc.Sprite, dofus.Constants.CLIPS_PERSOS_PATH + oData.gfxID + ".swf", oData.cell, oData.dir, oData.gfxID, oData.title);
            this.api.datacenter.Sprites.addItemAt(sID, _loc5);
        } // end if
        _loc5.GameActionsManager.init();
        _loc5.cellNum = Number(oData.cell);
        _loc5.scaleX = oData.scaleX;
        _loc5.scaleY = oData.scaleY;
        _loc5.name = sName;
        _loc5.Guild = Number(oData.spriteType);
        _loc5.Level = Number(oData.level);
        _loc5.Sex = oData.sex != undefined ? (oData.sex) : (1);
        _loc5.color1 = oData.color1 == -1 ? (oData.color1) : (Number("0x" + oData.color1));
        _loc5.color2 = oData.color2 == -1 ? (oData.color2) : (Number("0x" + oData.color2));
        _loc5.color3 = oData.color3 == -1 ? (oData.color3) : (Number("0x" + oData.color3));
        _loc5.Aura = oData.aura != undefined ? (oData.aura) : (0);
        _loc5.Merchant = oData.merchant == "1" ? (true) : (false);
        _loc5.serverID = Number(oData.serverID);
        _loc5.alignment = oData.alignment;
        _loc5.rank = oData.rank;
        _loc5.mount = oData.mount;
        _loc5.isDead = oData.isDead == 1;
        _loc5.deathState = Number(oData.isDead);
        _loc5.deathCount = Number(oData.deathCount);
        _loc5.lvlMax = Number(oData.lvlMax);
        _loc5.pvpGain = Number(oData.pvpGain);
        this.setSpriteAccessories(_loc5, oData.accessories);
        if (oData.LP != undefined)
        {
            _loc5.LP = oData.LP;
        } // end if
        if (oData.LP != undefined)
        {
            _loc5.LPmax = oData.LP;
        } // end if
        if (oData.AP != undefined)
        {
            _loc5.AP = oData.AP;
        } // end if
        if (oData.AP != undefined)
        {
            _loc5.APinit = oData.AP;
        } // end if
        if (oData.MP != undefined)
        {
            _loc5.MP = oData.MP;
        } // end if
        if (oData.MP != undefined)
        {
            _loc5.MPinit = oData.MP;
        } // end if
        if (oData.resistances != undefined)
        {
            _loc5.resistances = oData.resistances;
        } // end if
        _loc5.Team = oData.team == undefined ? (null) : (oData.team);
        if (oData.emote != undefined && oData.emote.length != 0)
        {
            _loc5.direction = ank.battlefield.utils.Pathfinding.convertHeightToFourDirection(oData.dir);
            if (oData.emoteTimer != undefined && oData.emote.length != 0)
            {
                _loc5.startAnimationTimer = oData.emoteTimer;
            } // end if
            _loc5.startAnimation = "EmoteStatic" + oData.emote;
        } // end if
        if (oData.guildName != undefined)
        {
            _loc5.guildName = oData.guildName;
        } // end if
        _loc5.emblem = this.createGuildEmblem(oData.emblem);
        if (oData.restrictions != undefined)
        {
            _loc5.restrictions = _global.parseInt(oData.restrictions, 36);
        } // end if
        if (sID == this.api.datacenter.Player.ID)
        {
            if (!this.api.datacenter.Player.haveFakeAlignment)
            {
                this.api.datacenter.Player.alignment = _loc5.alignment.clone();
            } // end if
        } // end if
        return (_loc5);
    };
*/

struct sCharacterCreateInfos
{
    sCharacterCreateInfos(QString name, quint8 race, quint8 gender, quint16 gfxId, qint32 color1, qint32 color2, qint32 color3, quint16 mapId, quint16 cellId) :
        name(name), race(race), gender(gender), gfxId(gfxId), color1(color1), color2(color2), color3(color3), mapId(mapId), cellId(cellId) {}

    QString name;
    quint8 race;
    quint8 gender;
    quint16 gfxId;
    qint32 color1;
    qint32 color2;
    qint32 color3;
    quint16 mapId;
    quint16 cellId;
};

class Character : public Unit
{
public:
    Character(WorldSession * session);
    ~Character();

    WorldSession* GetSession() { return m_session; }

    quint8 GetRace() const { return m_race; }
    quint8 GetGender() const { return m_gender; }
    quint32 GetColor1() const { return m_color1; }
    quint32 GetColor2() const { return m_color2; }
    quint32 GetColor3() const { return m_color3; }

    bool Create(quint32 guid, sCharacterCreateInfos characterCreateInfos);
    bool LoadFromDB(quint32 guid);
    void SaveToDB(bool create = false);

    void SendCharacterStats();

private:
    WorldSession* m_session;

    quint8 m_race;
    quint8 m_gender;
    quint32 m_color1;
    quint32 m_color2;
    quint32 m_color3;

    QMap<CharacterStats, sCharacterStats> m_stats;

    /*
     * canBeMerchant
     * currentJobID
     * EnergyMax
     * Force
     * mountXPPercent
     * VitalityXtra
     * restrictions
     * XPlow
     * currentWeight
     * weaponItem
     * cantInteractWithPrism
     * Wisdom
     * Vitality
     * XPHigh
     * inParty
     * Agility
     * MaxSummonedCreatures
     * alignment
     * Chance
     * isCurrentPlayer
     * canChallenge
     * specialization
     * MP
     * canExchange
     * craftPublicMode
     * RangeModerator
     * BonusPointsSpell
     * BonusPoints
     * data
     * canAttackMonstersAnywhereWhenMutant
     * canAttack
     * fakeAlignment
     * XP
     * Kama
     * Level
     * SummonedCreatures
     * clip
     * maxWeight
     * AP
     * LPmax
     * rank
     * canUseObject
     * color1
     * color2
     * isRiding
     * Discernment
     * color3
     * mount
     * Intelligence
     * isMutant
     * AgilityXtra
     * ID
     * IntelligenceXtra
     * Name
     * AgilityTotal
     * canAssault
     * canAttackDungeonMonstersWhenMutant
     * LP
     * cantSpeakNPC
     * Sex
     * canMoveInAllDirections
     * ChanceXtra
     * currentJob
     * FullStats
     * Guild
     * cantInteractWithTaxCollector
     * ForceXtra
     * canChatToAll
     * Initiative
     * WisdomXtra
     * canUseInteractiveObjects
     * CriticalHitBonus
     * Energy
     */
};

#endif // CHARACTER_H
