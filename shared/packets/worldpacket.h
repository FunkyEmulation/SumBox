#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include "../shared/opcodes/opcodes.h"
#include "../shared/packets/worldbuffer.h"

class WorldPacket : public WorldBuffer
{
public:
    WorldPacket(quint8 opcode) : WorldBuffer(&m_packet, QIODevice::WriteOnly)
    {
        m_opcode = opcode;
        *this << GetOpcodeHeader(m_opcode);
    }

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
