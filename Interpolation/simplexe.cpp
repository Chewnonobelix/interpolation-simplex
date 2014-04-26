#include "simplexe.h"

Simplexe::Simplexe(int dimension): m_points(dimension+1), m_dimension(dimension) {}
Simplexe::Simplexe(const std::vector<Point> & t):m_points(t), m_dimension(t.size() - 1) {}
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
    if(index >= 0 && index <= dimension())
    {
        return m_points[index];
    }

    throw std::string("Bad index simplex");
}

int Simplexe::dimension() const
{
    return m_dimension;
}

const Point& Simplexe::operator()(int index) const
{
    if(index >= 0 && index <= dimension())
    {
        return m_points[index];
    }

    throw std::string("Bad index simplexe");
}

bool Simplexe::containPoint(const Point& p) const
{
    std::vector<double> resultat = coordonneeBarycentrique(p);
    bool interieur = true;
    for(int i=0; i<resultat.size();i++){
        if(resultat[i] >= 0){}
        else{interieur=false;}
    }

    return interieur;
}

bool Simplexe::containPoint(const Point& p, std::vector<double>& bl) const
{
    bl.clear();
    std::vector<double> resultat = coordonneeBarycentrique(p);
    bool interieur = true;
    for(int i=0; i<resultat.size();i++){
        if(resultat[i] >= 0){}
        else{interieur=false;}
    }

    for(int a = resultat.size() - 1; a >= 0; a --)
    {
        bl.push_back(resultat[a]);
    }

    return interieur;
}

std::vector<Simplexe> Simplexe::decomposition(const Point& p) const
{
    std::vector<Simplexe> ret;

    if(p.dimension() == dimension())
    {
        for(int i = 0; i < p.dimension() + 1; i++)
        {
            Simplexe s(p.dimension());
            for(int j = 0; j <= p.dimension(); j++)
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

std::vector<double> Simplexe::coordonneeBarycentrique(const Point& p) const
{
    int dim = p.dimension();
    boost::numeric::ublas::matrix<double> m (dim+1, dim+2);
    int i,j,k;
    int h = dim+1;
    int l = dim+2;
    double pivot;

    // Remplissage du systeme
    for(i=0;i<h-1;i++){
        for(j=0;j<l-1;j++){
            m(i,j) = m_points[j](i) - p(i);
        }
        m(i,j) = 0;
    }
    for(j=0;j<l;j++){
        m(i,j) = 1;
    }

    for(i=0; i<h; i++){
        if(m(i,i) != 1){
            pivot=m(i,i);
            for(j=0; j<l;j++)
                m(i,j)=m(i,j)/pivot;
        }

        for(j=i+1; j<h;j++){
            // pour chaque ligne suivante
            pivot=m(j,i);
            for(k=0;k<l;k++)
                m(j,k)=m(j,k)-pivot*m(i,k);
        }
    }

    std::vector<double> resultat;
    for(i=h-1;i>=0;i--){
        double r = m(i,l-1); // partie droite
        // puis on soustraire avec la partie gauche
        k=l-1-1; //le dernier (en enlevent la partie droite)
        for(j=0;j<resultat.size();j++){
            r -= resultat[j]*m(i,k);
            k--;
        }
        resultat.push_back(r);
    }


    return resultat;

}

std::ostream& operator << (std::ostream& stream, const Simplexe& s)
{
    for(int i = 0; i <= s.dimension(); i ++)
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
    if(dimension() >= 2)
    {
        std::vector<Point> temp;
        const Point& p = m_points[0];

        temp.assign(m_points.begin() + 1, m_points.end() );
        const Simplexe st(temp);
        return (st.hyperVolume()*(st.distance(p)))/dimension();
    }
    else
    {
        return m_points[0].distance(m_points[1]);
    }

}

double Simplexe::distance(const Point & p) const
{
    ublas::matrix<double> matPoint(dimension(), dimension());

    for(int i = 0; i < dimension(); i ++)
    {
        for(int j = 0; j < dimension(); j ++)
        {
            matPoint(i,j) = m_points[i](j);
        }
    }

    ublas::vector<double> sol;
    ublas::vector<double> eg(dimension());

    for(int i = 0; i < dimension(); i ++)
    {
        eg(i) = -1;
    }

    sol = ublas::solve(matPoint,eg, ublas::lower_tag());
    double ret1 = 0, ret2 = 0;

    for(int i = 0; i < dimension(); i ++)
    {
        ret1 += sol(i)*p(i);
        ret2 += sol(i)*sol(i);
    }

    return ((abs(ret1) + 1)/sqrt(ret2));
}
