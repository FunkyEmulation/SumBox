#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QtCore>
#include "databases/database.h"
#include "utils/singleton.h"

enum GuidType
{
    GUIDTYPE_NONE      = 0,
    GUIDTYPE_CHARACTER = 1
};

class Character;

class ObjectMgr : public Singleton<ObjectMgr>
{
public:
    ObjectMgr();
    ~ObjectMgr();

    void SetHighestGuids();
    quint32 GenerateGuid(GuidType type);

private:
    quint32 m_highCharacterGuid;
};

#endif // OBJECTFACTORY_H
