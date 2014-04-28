#ifndef SIMPLEXE_H
#define SIMPLEXE_H
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

#include "point.h"
#include <vector>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/matrix_expression.hpp"
#include "boost/numeric/ublas/triangular.hpp"
#include <boost/numeric/ublas/io.hpp>
#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/lu.hpp"

using namespace boost::numeric;

/**
 * @namespace MetaProg
 * @brief Structure de meta-programmation utilisé initialement pour certain calcul de n! ou 2^n, finalement inutilisé
 */
namespace MetaProg
{
    struct typeNull{};

    template<int N> struct valueOf;

    template<>
    struct valueOf<1>
    {
        enum {fact = 1, pow2 = 2};
    };

    template <int N>
    struct valueOf
    {
        enum {fact = N * valueOf<N-1>::fact,
             pow2 = 2*valueOf<N-1>::pow2};
    };

    /**
     * @brief fPow
     * @param[in] a double
     * @param[in] n int
     * @return a^n
     */
    int fPow(double, int);

    /**
     * @brief fFactorial
     * @param[in] n int
     * @return n!
     */
    int fFactorial(int);
}

typedef MetaProg::valueOf<1> valueOf1;
typedef MetaProg::valueOf<2> valueOf2;
typedef MetaProg::valueOf<3> valueOf3;
typedef MetaProg::valueOf<4> valueOf4;
typedef MetaProg::valueOf<5> valueOf5;

/**
 * @class Simplexe
 * @brief Classe gérant un simplexe en dimension N
 */
class Simplexe
{
private:
    std::vector<Point> m_points;
    int m_dimension;
    bool m_init;

public:
    Simplexe(int dimension = 2);
    Simplexe(const std::vector<Point>&);
    Simplexe(const Simplexe& s);
    virtual ~Simplexe();

    int dimension() const;

    Simplexe& operator= (const Simplexe& s);

    friend bool operator == (const Simplexe& , const Simplexe& );

    /**
     * @brief operator ()
     * @param[in] index int
     * @return Le index-ème point du simplexe, avec 0<=index<=dimension
     * @throw Bad index si index < 0 ou index > dimension
     */
    Point& operator ()(int index);
    const Point& operator()(int index) const;

    bool containPoint(const Point&) const;

    /**
     * @brief decomposition
     * @param[in] p Point, p doit être contenu dans this
     * @return N+1 simplexe crée à partir de p,
     */
    std::vector<Simplexe> decomposition(const Point& p) const;

    /**
     * @brief hyperFace
     * @return L'ensemble des M-faces de this, M<dimension
     * @param[in] m dimension des faces
     */
    std::vector<Simplexe> hyperFace(int); //Hyper face de dimension M, avec M < N

    /**
     * @brief coordonneeBarycentrique
     * @param[in] p Point
     * @return les coefficient barycentrique de p dans this
     */
    std::vector<double> coordonneeBarycentrique(const Point& p) const;

    /**
     * @brief distance
     * @return La distance entre this et p
     * @param[in] p Point
     */
    double distance(const Point&) const;

    /**
     * @brief hyperVolume
     * @return Le volume de this
     */
    double hyperVolume() const;
    bool init() const;
    void setInit(bool init);

    std::vector<int> calcul(const Point&) const;

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

std::ostream& operator << (std::ostream& stream, const Simplexe& s);

#endif // SIMPLEXE_H
