#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>

class WorldSession
{
public:
    WorldSession();

    // Default handlers
    void HandleServerSide(QString& packet); // SMSG packets
    void HandleBeforeAuth(QString& packet); // CMSG packets before client auth (WorldSession don't exist at this moment)
};

#endif // WORLDSESSION_H
