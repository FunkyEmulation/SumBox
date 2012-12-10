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

    WorldBuffer &operator<<(quint32 value)
    {
        m_buffer->write((char*)&value, sizeof(quint32));
        return *this;
    }

    WorldBuffer &operator<<(QString value)
    {
        qDebug() << value;
        const char* s = value.toLocal8Bit().data();
        qDebug() << s;
        if (!s) {
            *this << (quint32)0;
            return *this;
        }
        uint len = qstrlen(s) + 1;                        // also write null terminator
        *this << (quint32)len;                        // write length specifier
        m_buffer->write(s, len);
        return *this;
    }

private:
    QBuffer* m_buffer;
};

#endif
