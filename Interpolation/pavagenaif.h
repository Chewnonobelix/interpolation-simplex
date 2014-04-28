#ifndef PAVAGENAIF_H
#define PAVAGENAIF_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "abstractpavage.h"
#include <vector>

/**
 * @class PavageNaif
 * @brief Méthode de pavage basique, nous commençons par crée un premier simplexe avec les N+1 premiers point.
 * Ensuite nous bouclons sur les points restant,
 * si p[i] est inclue dans un simplexe existant alors nous décomposons le simplexe, supprimont l'ancien simplexe et ajoutons les nouveaux simplexe à la liste,
 * sinon nous créons un nouveau simplexe et l'ajoutons à la liste.
 *
 */
class PavageNaif: public AbstractPavage<Simplexe>
{
public:
    PavageNaif(int dimension);
    void pavage(const std::vector<Point>&);
    /**
     * @brief Fonction de recherche dans une liste de simplexe
     */
    Simplexe getSimplexe(const Point&) const;

    void affichage() const;
};

#endif // PAVAGENAIF_H
