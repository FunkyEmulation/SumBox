#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <QtCore>
#include "Map.h"

class Pathfinding
{
public:
    Pathfinding(QString currentPath, Map* currentMap, quint16 currentCellId, quint16 currentOrientation);
    ~Pathfinding();

    QString FindPath();

private:
    QString m_currentPath;
    Map* m_currentMap;
    quint16 m_currentCellId;
    quint16 m_currentOrientation;

    quint16 m_destination;
    quint16 m_newOrientation;
};

#endif // MAP_H
