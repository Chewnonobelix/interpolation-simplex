#ifndef SIMPLEXE_H
#define SIMPLEXE_H

#include "point.h"
#include <vector>
#include <iostream>


#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/matrix_expression.hpp"
#include "boost/numeric/ublas/triangular.hpp"
#include <boost/numeric/ublas/io.hpp>
#include "boost/numeric/ublas/vector.hpp"

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

    int fPow(double, int);
    int fFactorial(int);
}

typedef MetaProg::valueOf<1> valueOf1;
typedef MetaProg::valueOf<2> valueOf2;
typedef MetaProg::valueOf<3> valueOf3;
typedef MetaProg::valueOf<4> valueOf4;
typedef MetaProg::valueOf<5> valueOf5;

class Simplexe
{
private:
    std::vector<Point> m_points;
    int m_dimension;

public:
    Simplexe(int dimension = 2);
    Simplexe(const std::vector<Point>&);
    Simplexe(const Simplexe& s);
    virtual ~Simplexe();

    int dimension() const;

    Simplexe& operator= (const Simplexe& s);

    friend bool operator == (const Simplexe& , const Simplexe& );

    Point& operator ()(int index);

    const Point& operator()(int index) const;

    bool containPoint(const Point&) const;
    bool containPoint(const Point&, std::vector<double>&) const;

    std::vector<Simplexe> decomposition(const Point& p) const;
    std::vector<Simplexe> hyperFace(int); //Hyper face de dimension M, avec M < N

    std::vector<double> coordonneeBarycentrique(const Point& p) const; //Mauvais type de retour
    double distance(const Point&) const;

    double hyperVolume() const;
};

std::ostream& operator << (std::ostream& stream, const Simplexe& s);

#endif // SIMPLEXE_H
