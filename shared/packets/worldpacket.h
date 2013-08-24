#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include <QTextStream>

class WorldPacket
{
public:
    WorldPacket(quint8 opcode);

    qint8 GetOpcode()
    {
        return m_opcode;
    }

    QByteArray* GetPacket()
    {
        m_stream->flush();
        return m_buffer;
    }

    template<class T>
    WorldPacket& operator<<(const T& value)
    {
        *m_stream << value;
        return *this;
    }

private:
    QByteArray* m_buffer;
    QTextStream* m_stream;
    quint8 m_opcode;
};

#endif
