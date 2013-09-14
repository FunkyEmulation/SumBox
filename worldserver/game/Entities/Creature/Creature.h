#ifndef CREATURE_H
#define CREATURE_H

#include "Entities/Object/Object.h"

/*
    _loc1.createCreature = function (sID, sName, oData)
    {
        var _loc5 = this.api.datacenter.Sprites.getItemAt(sID);
        if (_loc5 == undefined)
        {
            _loc5 = new dofus.datacenter.Creature(sID, ank.battlefield.mc.Sprite, dofus.Constants.CLIPS_PERSOS_PATH + oData.gfxID + ".swf", oData.cell, oData.dir, oData.gfxID);
            this.api.datacenter.Sprites.addItemAt(sID, _loc5);
        } // end if
        _loc5.GameActionsManager.init();
        _loc5.cellNum = oData.cell;
        _loc5.name = sName;
        _loc5.powerLevel = oData.powerLevel;
        _loc5.scaleX = oData.scaleX;
        _loc5.scaleY = oData.scaleY;
        _loc5.noFlip = oData.noFlip;
        _loc5.color1 = oData.color1 == -1 ? (oData.color1) : (Number("0x" + oData.color1));
        _loc5.color2 = oData.color2 == -1 ? (oData.color2) : (Number("0x" + oData.color2));
        _loc5.color3 = oData.color3 == -1 ? (oData.color3) : (Number("0x" + oData.color3));
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
        if (oData.summoned != undefined)
        {
            _loc5.isSummoned = oData.summoned;
        } // end if
        _loc5.Team = oData.team == undefined ? (null) : (oData.team);
        return (_loc5);
        */

class Creature : public Object
{
public:
    Creature();
    ~Creature();

protected:
    /*
     * powerLevel
     * resistances
     * name
     * alignment
     * Level
     */
};

#endif // CREATURE_H
