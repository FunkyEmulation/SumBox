#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include "worldbuffer.h"

class WorldPacket : public WorldBuffer
{
public:
    WorldPacket(quint8 opcode);

    qint8 GetOpcode()
    {
        return m_opcode;
    }

    QByteArray GetPacket()
    {
        return m_packet;
    }

private:
    QByteArray m_packet;
    quint8 m_opcode;
};

#endif
