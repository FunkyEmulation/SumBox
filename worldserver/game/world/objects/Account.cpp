#include "Account.h"

QString Account::GetCharsString() const
{
    QString chars;

    for(int i = 0; i < m_characters.count(); ++i)
    {
        chars += "|";
        chars += QString::number(m_characters.at(i)->GetId()) + ";";
        chars += m_characters.at(i)->GetName() + ";";
        chars += QString::number(m_characters.at(i)->GetLvl()) + ";";
        chars += QString::number(m_characters.at(i)->GetGfxId()) + ";";
        chars += QString::number(m_characters.at(i)->GetColor1()) + ";"; // Colors en hexa
        chars += QString::number(m_characters.at(i)->GetColor2()) + ";";
        chars += QString::number(m_characters.at(i)->GetColor3()) + ";";
        chars += ";"; // Accessories
        chars += "0;"; // Merchant ?
        chars += ";"; // ServeurId
        chars += "0;"; // Est mort ?
        chars += ";"; // DeathCount
        chars += "200;"; // LevelMax
    }

    return chars;
}
