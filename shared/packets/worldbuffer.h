#ifndef WORLDBUFFER_H
#define WORLDBUFFER_H

#include <QtCore>
#include <iostream>

class WorldBuffer
{
public:
    WorldBuffer(QByteArray *a, int mode)
    {
        m_buffer = new QBuffer(a);
        m_buffer->blockSignals(true);
        m_buffer->open(QIODevice::OpenMode(mode));
    }

    void seek(qint64 off)
    {
        m_buffer->seek(off);
    }

    WorldBuffer &operator<<(quint8 value)
    {
        m_buffer->write((char*)&value, sizeof(quint8));
        return *this;
    }

    WorldBuffer &operator<<(quint16 value)
    {
        m_buffer->write((char*)&value, sizeof(quint16));
        return *this;
    }

    WorldBuffer &operator<<(uint value)
    {
        m_buffer->write((char*)&value, sizeof(uint));
        return *this;
    }

    WorldBuffer &operator<<(int value)
    {
        m_buffer->write((char*)&value, sizeof(int));
        return *this;
    }

    WorldBuffer &operator<<(QString value)
    {
        m_buffer->buffer().append(value.toUtf8());
        return *this;
    }

private:
    QBuffer* m_buffer;
};

#endif
