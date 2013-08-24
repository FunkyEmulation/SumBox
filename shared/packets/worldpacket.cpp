#include "worldpacket.h"
#include "opcodes/opcodes.h"

WorldPacket::WorldPacket(quint8 opcode)
{
    m_buffer = new QByteArray();
    m_stream = new QTextStream(m_buffer);
    m_opcode = opcode;

    *this << GetOpcodeHeader(m_opcode);
}
