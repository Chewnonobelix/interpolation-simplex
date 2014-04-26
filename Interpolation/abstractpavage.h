#ifndef INTERFACEPAVAGE_H
#define INTERFACEPAVAGE_H

#include <vector>
#include "point.h"
#include "simplexe.h"
#include "boost/numeric/ublas/lu.hpp"

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

    virtual void pavage(const std::vector<Point>&) = 0;
    virtual Simplexe getSimplexe(const Point&, std::vector<double>&) const = 0;

    double eval(Point & p)
    {
        std::vector<double> cb;
        std::cout<<"cb = "<<cb.size()<<std::endl;
        Simplexe s = getSimplexe(p, cb);

        std::cout<<"Coeff "<<cb.size()<<std::endl;
        double ret = 0;
        for(int i = 0; i < cb.size(); i++)
        {
            ret += cb[i]*s(i).eval();
        }

        p.setEval(ret);

        return ret;
    }

    int determinant_sign(const ublas::permutation_matrix<std ::size_t>& pm)
    {
        int pm_sign=1;
        std::size_t size = pm.size();
        for (std::size_t i = 0; i < size; ++i)
            if (i != pm(i))
                pm_sign *= -1.0; // swap_rows would swap a pair of rows here, so we change sign
        return pm_sign;
    }

    double determinant( ublas::matrix<double>& m ) {
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
