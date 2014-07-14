#include "Server/WorldSession.h"

void WorldSession::HandleQueuePosition(QString& /*packet*/)
{
    WorldPacket queuePosition(MSG_QUEUE_POSITION);

    if(!WorldQueue::Instance()->ClientInQueue(this))
        queuePosition << "1|1|0|1|-1";
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
