#ifndef INTERFACEPAVAGE_H
#define INTERFACEPAVAGE_H

#include <vector>
#include "point.h"
#include "simplexe.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
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
    virtual Simplexe getSimplexe(const Point&) const = 0;

    /**
     * @brief Fonction d'évaluation de p dans le pavage
     * @param[in, out] p Point
     * @return évaluation de p
     */
    double eval(Point & p)
    {
        std::vector<double> cb;
        Simplexe s = getSimplexe(p);
        double ret = 0;

        if(s.init())
        {
            cb = s.coordonneeBarycentrique(p);
            for(int i = 0; i < cb.size(); i++)
            {
                ret += cb[i]*s(i).eval();
            }

            p.setEval(ret);
        }
        else
        {
            std::cout<<"Point a l'exterieur du pavage"<<std::endl;
        }
        return ret;
    }
};

#endif // INTERFACEPAVAGE_H
