#include "simplexe.h"

Simplexe::Simplexe(int dimension): m_points(dimension+1), m_dimension(dimension) {}
Simplexe::Simplexe(const Simplexe& s): m_points(s.m_points), m_dimension(s.dimension()) {}
Simplexe::~Simplexe() {}

Simplexe& Simplexe::operator= (const Simplexe& s)
{
    m_points.clear();
    m_points = s.m_points;
    m_dimension = s.dimension();
    return *this;
}

Point& Simplexe::operator ()(int index)
{
    if(index >= 0 && index < dimension() + 1)
    {
        return m_points[index];
    }

    throw std::string("Bad index");
}

int Simplexe::dimension() const
{
    return m_dimension;
}

const Point& Simplexe::operator()(int index) const
{
    if(index >= 0 && index < dimension()+1)
    {
        return m_points[index];
    }

    throw std::string("Bad index");
}

bool Simplexe::containPoint(const Point&)
{

    return false;
}

std::vector<Simplexe> Simplexe::decomposition(const Point& p) const
{
    std::vector<Simplexe> ret;

    if(p.dimension() == dimension())
    {
        for(int i = 0; i < p.dimension() + 1; i++)
        {
            Simplexe s(p.dimension());
            for(int j = 0; j < p.dimension(); j++)
            {
                if(j == i)
                {
                    s(j) = p;
                }
                else
                {
                    s(j) = (*this)(j);
                }
            }

            ret.push_back(s);
        }
    }
    return ret;
}

double Simplexe::coordonneeBarycentrique(const Point& p) const
{

    return 0;
}

std::ostream& operator << (std::ostream& stream, const Simplexe& s)
{
    for(int i = 0; i < s.dimension(); i ++)
    {
        stream<<s(i);

        if(i != s.dimension())
        {
            stream<< " ; ";
        }
    }

    stream<<std::endl;

    return stream;
}

bool operator == (const Simplexe& s1, const Simplexe& s2)
{
    bool ret = true;

    if(s1.dimension() == s2.dimension())
    {
        for(int i = 0; i < s1.dimension()+1; i ++)
        {
            //TODO A revoir
            ret &= s1(i) == s2(i);
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

int MetaProg::fFactorial( int f)
{
    int ret = 1;

    for(int i = 1; i <= f; i ++)
    {
        ret *= i;
    }

    return ret;
}

int MetaProg::fPow(double a, int p)
{
    int ret = 1;

    for(int i = 1; i <= p; i ++)
    {
        ret *= a;
    }

    return ret;
}

double Simplexe::hyperVolume() const
{

    int factn, p2;

    switch(dimension())
    {
    case 1:
        factn = fact1::value;
        p2 = pow2_1::value;
        break;
    case 2:
        factn = fact2::value;
        p2 = pow2_2::value;
        break;
    case 3:
        factn = fact3::value;
        p2 = pow2_3::value;
        break;
    case 4:
        factn = fact4::value;
        p2 = pow2_4::value;
        break;
    case 5:
        factn = fact5::value;
        p2 = pow2_5::value;
        break;
    default:
        factn = MetaProg::fFactorial(dimension());
        p2 = MetaProg::fPow(2,dimension());
        break;
    }

    return 0;
    //a hauteur du simplex en un point xi <=> distance de a à l'hyperlan Hp={xj | xj != xi}
    //return (MetaProg::fPow(a,dimension())/factn)*sqrt((dimension()+1)/p2);
}
