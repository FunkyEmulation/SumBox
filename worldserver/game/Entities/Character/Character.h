#ifndef CHARACTER_H
#define CHARACTER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "databases/database.h"
#include "define.h"
#include "game/server/worldsession.h"
#include "game/Entities/Unit/Unit.h"
#include "CharacterStats.h"

struct sCharacterCreateInfos
{
    sCharacterCreateInfos(QString name, quint8 race, quint8 gender, quint16 gfxId, qint32 color1, qint32 color2, qint32 color3, quint16 mapId, quint16 cellId) :
        name(name), race(race), gender(gender), gfxId(gfxId), color1(color1), color2(color2), color3(color3), mapId(mapId), cellId(cellId) {}

    QString name;
    quint8 race;
    quint8 gender;
    quint16 gfxId;
    qint32 color1;
    qint32 color2;
    qint32 color3;
    quint16 mapId;
    quint16 cellId;
};

class Character : public Unit
{
public:
    Character(WorldSession * session);
    ~Character();

    WorldSession* GetSession() { return m_session; }

    quint8 GetRace() const { return m_race; }
    quint8 GetGender() const { return m_gender; }
    quint32 GetColor1() const { return m_color1; }
    quint32 GetColor2() const { return m_color1; }
    quint32 GetColor3() const { return m_color1; }

    bool Create(quint32 guid, sCharacterCreateInfos characterCreateInfos);
    bool LoadFromDB(quint32 guid);
    void SaveToDB(bool create = false);

    void SendCharacterStats();

private:
    WorldSession* m_session;

    quint8 m_race;
    quint8 m_gender;
    quint32 m_color1;
    quint32 m_color2;
    quint32 m_color3;

    QMap<CharacterStats, sCharacterStats> m_stats;
};

#endif // CHARACTER_H
