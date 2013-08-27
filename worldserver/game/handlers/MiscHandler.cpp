#include "game/server/worldsession.h"

void WorldSession::HandleScreenInfo(QString& /*packet*/)
{
   /* Infos.as :
    _loc1.sendScreenInfo = function ()
    {
        Stage.scaleMode = "noScale";
        switch (Stage.displayState)
        {
            case "normal":
            {
                var _loc2 = "0";
                break;
            }
            case "fullscreen":
            {
                _loc2 = "1";
                break;
            }
            default:
            {
                _loc2 = "2";
            }
        } // End of switch
        this.aks.send("Ir" + Stage.width + ";" + Stage.height + ";" + _loc2);
        Stage.scaleMode = "showAll";
    };
   */
}
