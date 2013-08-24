#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>

/*
 * Entité objet ayant un id, un nom, une apparence
 */

class Object
{
public:
    // Getters
    int GetId() const { return m_id; }
    QString GetName() const { return m_name; }
    int GetGender() const { return m_gender; }
    int GetGfxId() const { return m_gfxId; }
    int GetColor1() const { return m_color1; }
    int GetColor2() const { return m_color2; }
    int GetColor3() const { return m_color3; }
    int GetSize() const { return m_size; }

protected:
    int m_id;
    QString m_name;
    int m_gender;
    int m_gfxId;
    int m_color1;
    int m_color2;
    int m_color3;
    int m_size;

};

#endif // OBJECT_H
