#ifndef INTERFACEPAVAGE_H
#define INTERFACEPAVAGE_H

#include <vector>
#include "point.h"
#include "simplexe.h"

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
    virtual Simplexe getSimplexe(const Point&) const = 0;
};

#endif // INTERFACEPAVAGE_H
