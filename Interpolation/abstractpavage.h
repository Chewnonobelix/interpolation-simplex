#ifndef INTERFACEPAVAGE_H
#define INTERFACEPAVAGE_H

#include <vector>
#include "point.h"
#include "simplexe.h"
#include "boost/numeric/ublas/lu.hpp"

/**
 * @class AbstractPavage
 * @brief Classe abstraite définissant la fonction d'évaluation et ue fonction de calcul de déterminant
 */

template<class T>
class AbstractPavage
{
private:
    int m_dimension;

protected:
    std::vector<T> m_tab;

public:
    AbstractPavage(int dimension): m_dimension(dimension)
    {}

    inline int dimension() const
    {
        return m_dimension;
    }

    /**
     * @brief Fonction abstraite de pavage de l'espace en fct d'un ensemble de point caractéristique
     * @param[in] ensPoint ensemble des points caracéristique
     */
    virtual void pavage(const std::vector<Point>&) = 0;

    /**
     * @brief Fonction abstraite de recherche de Simplexe
     * @return Simplexe contenant le point p
     * @param[in] p Point
     * @param[out] coefficientBarycentrique coefficient barycentrique du point p dans le simplexe renvoyer
     */
    virtual Simplexe getSimplexe(const Point&, std::vector<double>&) const = 0;

    /**
     * @brief Fonction d'évaluation de p dans le pavage
     * @param[in, out] p Point
     * @return évaluation de p
     */
    double eval(Point & p)
    {
        std::vector<double> cb;
        Simplexe s = getSimplexe(p, cb);

        double ret = 0;
        for(int i = 0; i < cb.size(); i++)
        {
            ret += cb[i]*s(i).eval();
        }

        p.setEval(ret);

        return ret;
    }

    /*
     * determinant_sign et determinant fct utilisé pour calculer les déterminant de matrices ublas
     */

    static int determinant_sign(const ublas::permutation_matrix<std ::size_t>& pm)
    {
        int pm_sign=1;
        std::size_t size = pm.size();
        for (std::size_t i = 0; i < size; ++i)
            if (i != pm(i))
                pm_sign *= -1.0; // swap_rows would swap a pair of rows here, so we change sign
        return pm_sign;
    }

    static double determinant( ublas::matrix<double>& m ) {
        ublas::permutation_matrix<std::size_t> pm(m.size1());
        double det = 1.0;
        if( ublas::lu_factorize(m,pm) ) {
            det = 0.0;
        } else {
            for(int i = 0; i < m.size1(); i++)
                det *= m(i,i); // multiply by elements on diagonal
            det = det * determinant_sign( pm );
        }
        return det;
    }
};

#endif // INTERFACEPAVAGE_H
