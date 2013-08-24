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

    // Faire un template

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

    WorldBuffer &operator<<(quint32 value)
    {
        m_buffer->write((char*)&value, sizeof(quint32));
        return *this;
    }

    WorldBuffer &operator<<(quint64 value)
    {
        m_buffer->write((char*)&value, sizeof(quint64));
        return *this;
    }

    WorldBuffer &operator<<(qint8 value)
    {
        m_buffer->write((char*)&value, sizeof(qint8));
        return *this;
    }

    WorldBuffer &operator<<(qint16 value)
    {
        m_buffer->write((char*)&value, sizeof(qint16));
        return *this;
    }

    WorldBuffer &operator<<(qint32 value)
    {
        m_buffer->write((char*)&value, sizeof(qint32));
        return *this;
    }

    WorldBuffer &operator<<(qint64 value)
    {
        m_buffer->write((char*)&value, sizeof(qint64));
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
