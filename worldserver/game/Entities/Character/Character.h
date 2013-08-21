#ifndef CHARACTER_H
#define CHARACTER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "databases/database.h"
#include "define.h"
#include "game/server/worldsession.h"

class Character
{
public:
    Character();
    ~Character();

private:
    WorldSession* m_session;
};

#endif // WORLDSESSION_H
