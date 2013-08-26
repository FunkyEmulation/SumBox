#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "databases/database.h"
#include "queues/worldqueue.h"
#include "define.h"
#include "servers/SocketHandler.h"
#include "game/Entities/Character/Character.h"

struct sAccountInfos
{
    quint32 id;
	QString username;
	QString pseudo;
    quint8 gmLevel;
	QString secretQuestion;
	QString secretAnswer;
    qint64 subscriptionTime;
};

typedef QList<qint32> CharactersList;

class Character;

class WorldSession : public SocketHandler
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    void SetAccountInfos(QSqlQuery req);
    sAccountInfos GetAccountInfos() { return m_accountInfos; }

    bool InCharsList(qint32 guid) { return m_charsList.contains(guid); }
    quint32 GetCharsCount() { return m_charsList.count(); }

    void SetCharacter(Character* character) { m_character = character; }
    Character* GetCharacter() const { return m_character; }

    virtual void ProcessPacket(QString packet);

    // Default handlers
    void HandleNULL(QString& /*packet*/) {}
    void HandleServerSide(QString& /*packet*/) {} // SMSG packets

    // CMSG Handlers
    void HandleCharCreate(QString& packet);
    void HandleCharDelete(QString& packet);
    void HandleCharList(QString& packet);
    void SendCharacterList();
    void HandleGameCreate(QString& packet);
    void HandleGiftsList(QString& packet);
    void HandleSessionKey(QString& packet);
    void HandleTicket(QString& packet);

    // MSG Handlers
    void HandleCharRandomPseudo(QString& packet);
    void HandleCharSelect(QString& packet);
    void HandleQueuePosition(QString& packet);
    void HandleRegionalVersion(QString& packet);

public slots:
    void OnClose();

private:
    ClientState m_state;
    QString m_sessionKey;

	sAccountInfos m_accountInfos;
    CharactersList m_charsList;
    Character* m_character;
};

#endif // WORLDSESSION_H
