#ifndef SOCKETREADER_H
#define SOCKETREADER_H

#include <QTcpSocket>

class SocketReader : public QObject
{
    Q_OBJECT

public:
    SocketReader(QTcpSocket* socket);

public slots:
    void OnRead();

protected:
    QTcpSocket* m_socket;
    QString m_packet;

    virtual void ProcessPacket(QString packet) = 0;
};

#endif // SOCKETREADER_H
