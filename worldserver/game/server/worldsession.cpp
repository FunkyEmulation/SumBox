#include "worldsession.h"
#include "../shared/opcodes/opcodes.h"
#include "../shared/logs/log.h"
#include "../shared/configuration/configmgr.h"

WorldSession::WorldSession(QTcpSocket *socket)
{
    m_socket = socket;
    m_packet = "";
    m_state = OnDetails;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));

    WorldPacket data(SMSG_HELLO_GAME_SERVER);
    SendPacket(data);

    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toAscii().data());
}

WorldSession::~WorldSession() {}

void WorldSession::OnRead()
{
    QDataStream in(m_socket);

    char *curPacket = new char;

    while(in.readRawData(curPacket, 1) != -1)
    {
        if(*curPacket != 0x00)
        {
            if(*curPacket != '\n' && *curPacket != '\r')
                m_packet += *curPacket;
        }
        else
            break;
    }

    if(!m_packet.isEmpty() && *curPacket == 0x00)
    {
        Log::Write(LOG_TYPE_DEBUG, "Received packet from <%s> : %s", m_socket->peerAddress().toString().toAscii().data(), m_packet.toAscii().data());

        QString header2 = m_packet.left(2);
        QString header3 = m_packet.left(3);

        OpcodeStruct opcode = GetOpcodeByHeader(header3);

        if (opcode.name == "MSG_UNKNOWN_OPCODE")
            opcode = GetOpcodeByHeader(header2);

        if (opcode.name != "MSG_UNKNOWN_OPCODE")
            (this->*opcode.handler)(m_packet);
        else
            Log::Write(LOG_TYPE_DEBUG, "Packet <%s> is unhandled. Content : %s", header2.toAscii().data(), m_packet.toAscii().data());

        m_packet = "";
    }
}

void WorldSession::OnClose()
{
    Log::Write(LOG_TYPE_NORMAL, "Closing connection with %s", m_socket->peerAddress().toString().toAscii().data());
    m_socket->deleteLater();
}

void WorldSession::SendPacket(WorldPacket data)
{
    m_socket->write(data.GetPacket() + (char)0x00);
    Log::Write(LOG_TYPE_DEBUG, "Send packet %s ( Header : %s )", GetOpcodeName(data.GetOpcode()).toAscii().data(), GetOpcodeHeader(data.GetOpcode()).toAscii().data());
    if(data.GetPacket().length() > 0)
        Log::Write(LOG_TYPE_DEBUG, "Packet data : %s", QString(data.GetPacket()).toAscii().data());
}

void WorldSession::HandleQueue(QString& /*packet*/)
{
    WorldPacket queuePosition(SMSG_QUEUE_POSITION);

    if(!WorldQueue::Instance()->ClientInQueue(this)) // Non dans la file
    {
        queuePosition << "1|1|0|1|-1";
    }
    else
    {
        queuePosition << QString::number(WorldQueue::Instance()->GetClientPosition(this)).toAscii().data() << "|"; // Position dans la file
        queuePosition << QString::number(WorldQueue::Instance()->GetClientsCount()).toAscii().data() << "|"; // Nombre d'abonnés dans la file
        queuePosition << "0|"; // Nombre de non abonnés
        queuePosition << "1|"; // Abonné ?
        queuePosition << "1"; // Queue id
    }

    SendPacket(queuePosition);
}

void WorldSession::HandleTicketResponse(QString& packet)
{
    QString ticket = packet.mid(2);
    QSqlQuery req = Database::Auth()->PQuery(AUTH_SELECT_ACCOUNT_SESSION_KEY, ticket.toAscii().data());

    if(req.first()) // Key valide
    {
        // Infos account
        m_infos.insert("id", req.value(req.record().indexOf("account_id")).toString());
        m_infos.insert("account", req.value(req.record().indexOf("username")).toString());
        m_infos.insert("pseudo", req.value(req.record().indexOf("pseudo")).toString());
        m_infos.insert("gmlevel", req.value(req.record().indexOf("gm_level")).toInt());
        m_infos.insert("question", req.value(req.record().indexOf("secret_question")).toString());
        m_infos.insert("answer", req.value(req.record().indexOf("secret_answer")).toString());
        m_infos.insert("subscription_time", req.value(req.record().indexOf("subscription_time")).toInt());

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
    WorldPacket RegionalVersion(SMSG_REGIONAL_VERSION);
    RegionalVersion << "0";
    SendPacket(RegionalVersion);
}

void WorldSession::HandleListGifts(QString& /*packet*/)
{
    if(!m_infos["gifts"].isNull())
    {
     //WorldPacket ListPacket(SMSG_LIST_GIFTS);
    }
}

void WorldSession::HandleKey(QString& packet)
{
    m_infos.insert("key",packet.mid(2));
    Log::Write(LOG_TYPE_DETAIL,"Key : '%s'",packet.mid(2).toAscii().data());
}

void WorldSession::HandleCharactersList(QString& /*packet*/)
{
    m_state = OnQueue;
    WorldQueue::Instance()->AddClient(this);
}

void WorldSession::SendCharacters()
{
    cout << "Send persos" << endl;
}
