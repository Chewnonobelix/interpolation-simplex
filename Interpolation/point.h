#ifndef POINT_H
#define POINT_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/numeric/ublas/vector.hpp>

using namespace boost::numeric;

class Point
{
private:
    ublas::vector<double> m_coordonnees;
    int m_dimension;

public:
    Point(int dimension = 2);
    Point(const Point& p);

    virtual ~Point();

    int dimension() const;

    Point& operator = (const Point& p);

    friend bool operator == (const Point&, const Point&);

    double& operator ()(int index);

    double operator ()(int index) const;

    double distance(const Point& p) const;

    static double distance(const Point &p1, const Point& p2);
    //distance d'un point p à un hyperplan A
    // d(p, A) = |b+ a1p1 + a2p2 + ... + anpn|/sqrt(a1^2 + a2^2 + .... + an^2)

    friend std::ifstream& operator >>(std::ifstream&, Point&);

};

std::ostream& operator << (std::ostream& stream, const Point& p);

#endif // POINT_H
