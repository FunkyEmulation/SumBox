#include "Server/WorldSession.h"

void WorldSession::HandleServerDate(QString& /*packet*/)
{
    QDate date = QDate::currentDate();
    WorldPacket data(MSG_SERVER_DATE);
    data << date.toString("yyyy");
    data << date.toString("MM");
    data << date.toString("dd");
    SendPacket(data);
}

void WorldSession::HandleServerTime(QString& /*packet*/)
{
    WorldPacket data(MSG_SERVER_TIME);
    data << 0; // quel format ?
    SendPacket(data);
}
