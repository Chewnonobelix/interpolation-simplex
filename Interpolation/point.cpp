#include "point.h"

Point::Point(int dimension):m_coordonnees(dimension, 0), m_dimension(dimension)
{}
Point::Point(const Point& p):m_coordonnees(p.m_coordonnees), m_dimension(p.dimension())
{}

Point::~Point(){}

int Point::dimension() const
{
    return m_dimension;
}

Point& Point::operator = (const Point& p)
{
    m_coordonnees.clear();
    m_dimension = p.dimension();
    m_coordonnees = p.m_coordonnees;

    return *this;
}

double& Point::operator ()(int index)
{
    if(index < dimension() && index >= 0)
    {
        return m_coordonnees(index);
    }
    throw std::string("Out of range");
}

double Point::operator ()(int index) const
{
    if(index < dimension() && index >= 0)
    {
        return m_coordonnees(index);
    }
    throw std::string("Out of range");
}

double Point::distance(const Point& p) const
{
    double ret = 0;

    if(p.dimension() == dimension())
    {
        for(int i = 0; i < dimension(); i ++)
        {
            ret += ((*this)(i) - p(i))*((*this)(i) - p(i));
        }
    }

    return sqrt(ret);
}

double Point::distance(const Point &p1, const Point& p2)
{
    double ret = 0;

    if(p1.dimension() == p2.dimension())
    {
        for(int i = 0; i < p1.dimension(); i ++)
        {
            ret += (p1(i) - p2(i))*(p1(i) - p2(i));
        }
    }
    return sqrt(ret);
}

std::ostream& operator << (std::ostream& stream, const Point& p)
{
    for(int i = 0; i < p.dimension(); i++)
    {
        stream<<p(i);
        if(i != p.dimension()-1)
        {
            stream<<", ";
        }
    }

    return stream;
}

bool operator == (const Point& p1, const Point& p2)
{
    bool ret = true;

    if(p1.dimension() == p2.dimension())
    {
        for(int i = 0 ; i < p1.dimension(); i ++)
        {
            ret &= p1(i) == p2(i);
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

std::ifstream& operator >>(std::ifstream& stream, Point & p)
{
    char c;

    for(int i = 0; i <  p.dimension(); i ++)
    {
        stream>>p(i)>>c;
    }
    std::cout <<"c : "<<c<<std::endl;
    return stream;
}
