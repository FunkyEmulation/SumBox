#include "game/server/worldsession.h"

void WorldSession::HandleQueue(QString& /*packet*/)
{
    WorldPacket queuePosition(MSG_QUEUE_POSITION);

    if(!WorldQueue::Instance()->ClientInQueue(this)) // Non dans la file
    {
        queuePosition << "1|1|0|1|-1";
    }
    else
    {
        queuePosition << WorldQueue::Instance()->GetClientPosition(this) << "|"; // Position dans la file
        queuePosition << WorldQueue::Instance()->GetClientsCount() << "|"; // Nombre d'abonnés dans la file
        queuePosition << "0|"; // Nombre de non abonnés
        queuePosition << "1|"; // Abonné ?
        queuePosition << "1"; // Queue id
    }

    SendPacket(queuePosition);
}

void WorldSession::HandleTicketResponse(QString& packet)
{
    QString ticket = packet.mid(2);
    m_account = ObjectFactory::Instance()->LoadAccount(ticket);

    if (m_account != NULL)
    {
        WorldPacket TicketAccepted(SMSG_TICKET_ACCEPTED);
        SendPacket(TicketAccepted);
    }
    else
    {
        WorldPacket TicketRefused(SMSG_TICKET_REFUSED);
        SendPacket(TicketRefused);
    }
}

void WorldSession::HandleRegionalVersion(QString& /*packet*/)
{
    WorldPacket RegionalVersion(MSG_REGIONAL_VERSION);
    RegionalVersion << "0";
    SendPacket(RegionalVersion);
}

void WorldSession::HandleListGifts(QString& /*packet*/)
{
    /*if(!m_infos["gifts"].isNull())
    {
     //WorldPacket ListPacket(SMSG_LIST_GIFTS);
    }*/
}

void WorldSession::HandleKey(QString& packet)
{
    m_ticket = packet.mid(2);
    Log::Write(LOG_TYPE_DETAIL,"Key : '%s'",packet.mid(2).toLatin1().data());
}
