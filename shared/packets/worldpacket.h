#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include <QTextStream>
#include "opcodes/opcodes.h"

class WorldPacket
{
public:
    WorldPacket(quint8 opcode) : m_opcode(opcode), m_stream(&m_buffer)
    {
        *this << GetOpcodeHeader(m_opcode);
    }

    qint8 GetOpcode()
    {
        return m_opcode;
    }

    QByteArray& GetPacket()
    {
        m_stream.flush();
        return m_buffer;
    }

    template<class T>
    WorldPacket& operator<<(const T& value)
    {
        m_stream << value;
        return *this;
    }

private:
    quint8 m_opcode;
    QByteArray m_buffer;
    QTextStream m_stream;
};

#endif
