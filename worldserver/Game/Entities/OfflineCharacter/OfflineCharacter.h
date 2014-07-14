#ifndef OFFLINECHARACTER_H
#define OFFLINECHARACTER_H

#include "Entities/Unit/Unit.h"

// Currently, when people go offline, they simply get logged off, and if they're mid-fight, the battle will keep going on
// _loc1.initialize = function (sID, clipClass, sGfxFile, cellNum, dir, gfxID)

/*
    _loc1.createOfflineCharacter = function (sID, sName, oData)
    {
        var _loc5 = this.api.datacenter.Sprites.getItemAt(sID);
        if (_loc5 == undefined)
        {
            _loc5 = new dofus.datacenter.OfflineCharacter(sID, ank.battlefield.mc.Sprite, dofus.Constants.CLIPS_PERSOS_PATH + oData.gfxID + ".swf", oData.cell, oData.dir, oData.gfxID);
            this.api.datacenter.Sprites.addItemAt(sID, _loc5);
        } // end if
        _loc5.GameActionsManager.init();
        _loc5.cellNum = oData.cell;
        _loc5.name = sName;
        _loc5.scaleX = oData.scaleX;
        _loc5.scaleY = oData.scaleY;
        _loc5.color1 = oData.color1 == -1 ? (oData.color1) : (Number("0x" + oData.color1));
        _loc5.color2 = oData.color2 == -1 ? (oData.color2) : (Number("0x" + oData.color2));
        _loc5.color3 = oData.color3 == -1 ? (oData.color3) : (Number("0x" + oData.color3));
        this.setSpriteAccessories(_loc5, oData.accessories);
        if (oData.guildName != undefined)
        {
            _loc5.guildName = oData.guildName;
        } // end if
        _loc5.emblem = this.createGuildEmblem(oData.emblem);
        _loc5.offlineType = oData.offlineType;
        return (_loc5);
    };
*/

class OfflineCharacter : public Unit
{
public:
    OfflineCharacter();
    ~OfflineCharacter();

protected:
    /*
     * emblem
     * guildName
     * offlineType
     */
};

#endif // OFFLINECHARACTER_H
