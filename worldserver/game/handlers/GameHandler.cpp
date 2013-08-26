#include "game/server/worldsession.h"

void WorldSession::HandleGameCreate(QString& packet)
{
    quint8 gameType = packet.mid(2).toUInt();
    qDebug() << gameType;

    // TODO
}
