#ifndef POINT_H
#define POINT_H
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/vector.hpp>

using namespace boost::numeric;

/**
 * @class Point
 * @brief Classe stockant les coordonnées d'un point en dimension N, ainsi que son évaluation
 */
class Point
{
private:
    ublas::vector<double> m_coordonnees;
    int m_dimension;
    double m_eval;

public:
    Point(int dimension = 2);
    Point(const Point& p);

    virtual ~Point();

    int dimension() const;

    Point& operator = (const Point& p);

    friend bool operator == (const Point&, const Point&);

    /**
     * @brief operator ()
     * @param[in] index int
     * @return Composante du point, avec 0<=index<dimension
     * @throw Out of range si index < 0 ou index >= dimension
     */

    double& operator ()(int index);
    double operator ()(int index) const;

    /**
     * @brief distance
     * @param[in] p Point
     * @return distance entre this et p;
     */
    double distance(const Point& p) const;

    static double distance(const Point &p1, const Point& p2);
    //distance d'un point p à un hyperplan A
    // d(p, A) = |b+ a1p1 + a2p2 + ... + anpn|/sqrt(a1^2 + a2^2 + .... + an^2)

    friend std::ifstream& operator >>(std::ifstream&, Point&);

    double eval() const;
    void setEval(double eval);
};

std::ostream& operator << (std::ostream& stream, const Point& p);

#endif // POINT_H
