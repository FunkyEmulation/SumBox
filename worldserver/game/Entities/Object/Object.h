#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>

/*
 * Entité objet ayant un id, un nom, une apparence
 */

class Object
{
public:
    void SetGuid(quint32 guid) { m_guid = guid; }
    quint32 GetGuid() const { return m_guid; }

    QString GetName() const { return m_name; }
    int GetGfxId() const { return m_gfxId; }
    int GetSize() const { return m_size; }

protected:
    quint32 m_guid;
    QString m_name;
    int m_gfxId;
    int m_size;
};

#endif // OBJECT_H
