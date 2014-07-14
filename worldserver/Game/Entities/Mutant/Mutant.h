#ifndef MUTANT_H
#define MUTANT_H

#include "Entities/Object/Object.h"

/*
    _loc1.createMutant = function (sID, oData)
    {

        _loc4.Guild = Number(oData.spriteType);
        _loc4.powerLevel = Number(oData.powerLevel);
        _loc4.Sex = oData.sex != undefined ? (oData.sex) : (1);
        _loc4.showIsPlayer = oData.showIsPlayer;
        _loc4.monsterID = oData.monsterID;
        _loc4.playerName = oData.playerName;
        this.setSpriteAccessories(_loc4, oData.accessories);
        if (oData.LP != undefined)
        {
            _loc4.LP = oData.LP;
        } // end if
        if (oData.LP != undefined)
        {
            _loc4.LPmax = oData.LP;
        } // end if
        if (oData.AP != undefined)
        {
            _loc4.AP = oData.AP;
        } // end if
        if (oData.AP != undefined)
        {
            _loc4.APinit = oData.AP;
        } // end if
        if (oData.MP != undefined)
        {
            _loc4.MP = oData.MP;
        } // end if
        if (oData.MP != undefined)
        {
            _loc4.MPinit = oData.MP;
        } // end if
        _loc4.Team = oData.team == undefined ? (null) : (oData.team);
        if (oData.emote != undefined && oData.emote.length != 0)
        {
            _loc4.direction = ank.battlefield.utils.Pathfinding.convertHeightToFourDirection(oData.dir);
            if (oData.emoteTimer != undefined && oData.emote.length != 0)
            {
                _loc4.startAnimationTimer = oData.emoteTimer;
            } // end if
            _loc4.startAnimation = "EmoteStatic" + oData.emote;
        } // end if
        if (oData.restrictions != undefined)
        {
            _loc4.restrictions = _global.parseInt(oData.restrictions, 36);
        } // end if
        return (_loc4);
    };
    */

class Mutant : public Object
{
public:
    Mutant();
    ~Mutant();


protected:
    /*
     * showIsPlayer
     * monsterId
     * powerLevel
     * playerName
     * resistances
     * Level
     * alignment
     * monsterName
     **/
};

#endif // MUTANT_H
