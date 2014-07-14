#ifndef NONPLAYABLECHARACTER_H
#define NONPLAYABLECHARACTER_H

#include "Entities/Unit/Unit.h"

// NPC : actions = startExchange / startDialog
// initiating or advancing a quest, buying or selling items,
// offering an exchange, or simply engaging the player in a bit of amusing or informative dialog

/*
 *    _loc1.initialize = function (sID, clipClass, sGfxFile, cellNum, dir, gfxID, customArtwork)
    {
        super.initialize(sID, clipClass, sGfxFile, cellNum, dir);
        this._gfxID = gfxID;
        this._nCustomArtwork = customArtwork;
    };
    */


/*
    _loc1.createNonPlayableCharacter = function (sID, nUnicID, oData)
    {
        var _loc5 = this.api.datacenter.Sprites.getItemAt(sID);
        if (_loc5 == undefined)
        {
            _loc5 = new dofus.datacenter.NonPlayableCharacter(sID, ank.battlefield.mc.Sprite, dofus.Constants.CLIPS_PERSOS_PATH + oData.gfxID + ".swf", oData.cell, oData.dir, oData.gfxID, oData.customArtwork);
            this.api.datacenter.Sprites.addItemAt(sID, _loc5);
        } // end if
        _loc5.GameActionsManager.init();
        _loc5.cellNum = oData.cell;
        _loc5.unicID = nUnicID;
        _loc5.scaleX = oData.scaleX;
        _loc5.scaleY = oData.scaleY;
        _loc5.color1 = oData.color1 == -1 ? (oData.color1) : (Number("0x" + oData.color1));
        _loc5.color2 = oData.color2 == -1 ? (oData.color2) : (Number("0x" + oData.color2));
        _loc5.color3 = oData.color3 == -1 ? (oData.color3) : (Number("0x" + oData.color3));
        this.setSpriteAccessories(_loc5, oData.accessories);
        if (oData.extraClipID >= 0)
        {
            _loc5.extraClipID = oData.extraClipID;
        } // end if
        return (_loc5);
    };
*/

class NonPlayableCharacter : public Object
{
public:
    NonPlayableCharacter();
    ~NonPlayableCharacter();

protected:
    /*
     * customArtwork
     * extraClipId
     * actions
     */
};

#endif // NONPLAYABLECHARACTER_H
