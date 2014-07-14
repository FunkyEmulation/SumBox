#include "Server/WorldSession.h"

void WorldSession::HandleTicket(QString& packet)
{
    QString session_key = packet.mid(2);
    QSqlQuery result = Database::Auth()->PQuery(AUTH_SELECT_ACCOUNT_SESSION_KEY, session_key.toLatin1().data());

    SetAccountInfos(result);

    if (GetAccountInfos().id != 0)
    {
        WorldPacket data(SMSG_TICKET_ACCEPTED);
        SendPacket(data);
    }
    else
    {
        WorldPacket data(SMSG_TICKET_REFUSED);
        SendPacket(data);
    }
}

void WorldSession::HandleRegionalVersion(QString& /*packet*/)
{
    WorldPacket RegionalVersion(MSG_REGIONAL_VERSION);
    RegionalVersion << "0";
    SendPacket(RegionalVersion);
}

void WorldSession::HandleGiftsList(QString& /*packet*/)
{
    /*if(!m_infos["gifts"].isNull())
    {
     //WorldPacket ListPacket(SMSG_LIST_GIFTS);
    }*/
}

void WorldSession::HandleSessionKey(QString& packet)
{
    m_sessionKey = packet.mid(2);
    Log::Write(LOG_TYPE_DETAIL,"Key : '%s'",packet.mid(2).toLatin1().data());
}
