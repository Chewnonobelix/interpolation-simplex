#ifndef PAVAGENAIF_H
#define PAVAGENAIF_H

#include "abstractpavage.h"
#include <vector>
#include "boost/numeric/ublas/lu.hpp"

/*
 * Idée de génie ?
 * Considérer les m points d'un ensemble M (m > n) comme m-1 simplex
 * Puis prendre les petits simplex (considérer les hyper volumes) tel que:
 * -Ts les m points soit utiliser
 * - Aucun n-simplexe ne se chevauche (à hyperface près)
 * - Puis reconstruire l'arbre depuis les feuilles vers la racine
 */

class PavageNaif: public AbstractPavage<Simplexe>
{
public:
    PavageNaif(int dimension);
    void pavage(const std::vector<Point>&);
    Simplexe getSimplexe(const Point&, std::vector<double>&) const;

    void affichage() const;
};

#endif // PAVAGENAIF_H
