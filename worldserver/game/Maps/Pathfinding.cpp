#include "Pathfinding.h"

Pathfinding::Pathfinding(QString currentPath, Map *currentMap, quint16 currentCellId, quint16 currentOrientation)
{
    m_currentPath = currentPath;
    m_currentMap = currentMap;
    m_currentCellId = currentCellId;
    m_currentOrientation = currentOrientation;
}

Pathfinding::~Pathfinding() {}

QString Pathfinding::FindPath()
{
    // 1. Ajouter le point de départ à la liste ouverte

    // 2. Tant que la liste ouverte n'est pas vide

        // 2.1 Chercher la case ayant le coût F le plus faible dans la liste ouverte et définir comme case en cours

        // 2.2 Passer la case en cours de la liste ouverte à la liste fermée

        // 2.3 Pour les 8 cases adjacentes à la case en cours :
            // 2.3.1 Si on ne peut pas traverser : on l'ignore
            // 2.3.2 Si elle n'est pas dans la liste ouverte, on l'ajoute.
                // 2.3.2.1 La case en cours devient le parent de cette case. On calcule les coûts F, G et H de cette case.
            // 2.3.2.bis Sinon on teste si le chmein passant par la case en cours et meilleurs en comparant les coûts G.
                      // Un coût G inférieur signifie un chemin meilleur. Si c'est le cas on change le parent de la case pour la case en cours et on recalcule les coûts F et G.
                            // Dans ce cas la liste ouverte doit être retrée par coût F.

        // 2.4 Su ka case de destination est ajoutée à la liste fermée : fin de la boucle
}
