#ifndef SIMPLEXE_H
#define SIMPLEXE_H

#include "point.h"
#include <vector>
#include <iostream>



namespace MetaProg
{
    struct typeNull{};

    template<int N> struct factorial;
    template<int P> struct pow2;

    template<>
    struct factorial<1>
    {
        enum {value = 1};
    };

    template <int N>
    struct factorial
    {
        enum {value = N * MetaProg::factorial<N-1>::value};
    };

    template<>
    struct pow2<1>
    {
        enum {value = 2};
    };

    template<int P>
    struct pow2
    {
        enum {value = 2*pow2<P-1>::value};
    };

    int fPow(double, int);
    int fFactorial(int);
}

typedef MetaProg::factorial<1> fact1;
typedef MetaProg::factorial<2> fact2;
typedef MetaProg::factorial<3> fact3;
typedef MetaProg::factorial<4> fact4;
typedef MetaProg::factorial<5> fact5;

typedef MetaProg::pow2<1> pow2_1;
typedef MetaProg::pow2<2> pow2_2;
typedef MetaProg::pow2<3> pow2_3;
typedef MetaProg::pow2<4> pow2_4;
typedef MetaProg::pow2<5> pow2_5;


class Simplexe
{
private:
    std::vector<Point> m_points;
    int m_dimension;

public:
    Simplexe(int dimension = 2);
    Simplexe(const Simplexe& s);
    virtual ~Simplexe();

    int dimension() const;

    Simplexe& operator= (const Simplexe& s);

    friend bool operator == (const Simplexe& , const Simplexe& );

    Point& operator ()(int index);

    const Point& operator()(int index) const;

    bool containPoint(const Point&);

    std::vector<Simplexe> decomposition(const Point& p) const;
    std::vector<Simplexe> hyperFace(int); //Hyper face de dimension M, avec M < N

    double coordonneeBarycentrique(const Point& p) const;

    double hyperVolume() const;
};

std::ostream& operator << (std::ostream& stream, const Simplexe& s);

#endif // SIMPLEXE_H
