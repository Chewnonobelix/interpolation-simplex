#include "pavagenaif.h"

PavageNaif::PavageNaif(int dimension): AbstractPavage(dimension)
{
}

void PavageNaif::pavage(const std::vector<Point> & pointSet)
{
    if(pointSet.size() >= dimension() + 1)
    {
        Simplexe first(dimension());

        for(int i = 0; i < dimension()+1; i ++)
        {
            first(i) = pointSet[i];
        }

        m_tab.push_back(first);
        for(int i = dimension() + 1; i< pointSet.size(); i ++)
        {
            Simplexe s(dimension());
            int j = 0;
            bool find = false;

            while(j < m_tab.size() && !find)
            {
                find = m_tab[j].containPoint(pointSet[i]);
            }

            if(find)
            {
                s = m_tab[j];
                std::vector<Simplexe> nouveau = s.decomposition(pointSet[i]);
                m_tab[j] = nouveau[0];
//                std::cout<<"Taille "<<nouveau.size()<<std::endl;
                for(int k = 1; k < nouveau.size(); k++)
                {
//                    std::cout<<"k = "<<k<<std::endl<<nouveau[k]<<std::endl;
                    m_tab.push_back(nouveau[k]);
                }
            }
            else
            {
                Simplexe s2(s.dimension());
                double d = -1;

                for(int k = 0; k < m_tab.size(); k ++)
                {
                    double temp = m_tab[k].distance(pointSet[i]);

                    if(d == -1 || temp < d)
                    {
                        d = temp;
                        s2 = m_tab[k];
                    }
                }

                int c = 0;

                for(int b = 0; b <= s2.dimension(); b++)
                {
                    ublas::matrix<double> m, mp;

                    // Début remplissage Matrice

                    // Fin remplissage Matrice

                    double dm, dmp;
                    dm = determinant(m);
                    dmp = determinant(mp);

                    if(dm*dmp >= 0)
                    {
                        c ++;
                    }
                }

                if(c == s2.dimension())
                {

                }
            }
        }
    }
    else
    {
        throw std::string("Nombre de points insuffisants");
    }
}

Simplexe PavageNaif::getSimplexe(const Point & p, std::vector<double> & cb) const
{
    Simplexe ret;


    for(std::vector<Simplexe>::const_iterator it = m_tab.begin();
        it != m_tab.end(); it ++)
    {
        if(it->containPoint(p, cb))
        {
            ret = *it;
            std::cout<<"return "<<ret<<std::endl;
            return ret;
        }
    }

     return ret;
}

void PavageNaif::affichage() const
{
    std::cout<<"Pavage"<<std::endl;
    for(int i = 0; i < m_tab.size(); i ++)
    {
        std::cout<<m_tab[i]<<std::endl;
    }
}
