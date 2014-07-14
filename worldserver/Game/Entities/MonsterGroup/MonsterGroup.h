#ifndef MONSTERGROUP_H
#define MONSTERGROUP_H

#include "Entities/Object/Object.h"

/*
    _loc1.createMonsterGroup = function (sID, sName, oData)
    {
        var _loc5 = this.api.datacenter.Sprites.getItemAt(sID);
        if (_loc5 == undefined)
        {
            _loc5 = new dofus.datacenter.MonsterGroup(sID, ank.battlefield.mc.Sprite, dofus.Constants.CLIPS_PERSOS_PATH + oData.gfxID + ".swf", oData.cell, oData.dir, oData.bonusValue);
            this.api.datacenter.Sprites.addItemAt(sID, _loc5);
        } // end if
        _loc5.GameActionsManager.init();
        _loc5.cellNum = oData.cell;
        _loc5.name = sName;
        _loc5.Level = oData.level;
        _loc5.scaleX = oData.scaleX;
        _loc5.scaleY = oData.scaleY;
        _loc5.noFlip = oData.noFlip;
        _loc5.color1 = oData.color1 == -1 ? (oData.color1) : (Number("0x" + oData.color1));
        _loc5.color2 = oData.color2 == -1 ? (oData.color2) : (Number("0x" + oData.color2));
        _loc5.color3 = oData.color3 == -1 ? (oData.color3) : (Number("0x" + oData.color3));
        this.setSpriteAccessories(_loc5, oData.accessories);
        return (_loc5);
    };
    */

class MonsterGroup : public Object
{
public:
    MonsterGroup();
    ~MonsterGroup();

protected:
    /*
     * alignment
     * name
     * bonusValue
     * totalLevel
     * Level
     */
};

#endif // MONSTERGROUP_H
