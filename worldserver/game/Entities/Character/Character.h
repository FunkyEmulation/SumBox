#ifndef CHARACTER_H
#define CHARACTER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "databases/database.h"
#include "define.h"
#include "game/server/worldsession.h"
#include "game/Entities/Unit/Unit.h"

class Character : public Unit
{
public:
    Character();
    ~Character();

    bool Create();
    bool LoadFromDB();

private:
    WorldSession* m_session;
};

#endif // WORLDSESSION_H
