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
            int di = 0;
            while(j < m_tab.size() && !find)
            {
                find = m_tab[j].containPoint(pointSet[i]);
                if(!find)
                {
                    j++;
                }
            }

            if(find)
            {
                s = m_tab[j];
                std::vector<Simplexe> nouveau = s.decomposition(pointSet[i]);
                m_tab[j] = nouveau[0]; //Remplacement de l'ancien simplexe

                for(int k = 1; k < nouveau.size(); k++)
                {
                    m_tab.push_back(nouveau[k]);
                }
            }
            else
            {
                Simplexe s2(s.dimension());
                double d = -1;
                //Recherche du simplexe le plus proche
                for(int k = 0; k < m_tab.size(); k ++)
                {
                    double temp = m_tab[k].distance(pointSet[i]);

                    if(d == -1 || temp < d)
                    {
                        d = temp;
                        s2 = m_tab[k];
                        di = k;
                    }
                }

                Simplexe s3(s2.dimension()); //Futur nouveau simplexe

                //Si le nombre de dm*dmp est égal à la dimension de l'espace alors on peut crée un nouveau simplex
                //Sinon si le nombre de dm*dmp est égal à la dimension + 1 alors on décompose s2
                //(voir fct calcul de simplexe)
                std::vector<int> c = s2.calcul(pointSet[i]);
                if(c.size() > 0 && c.size() < s2.dimension()+1)
                {
                    for(int a = 0; a < c.size(); a++)
                    {
                        for(int f = 0; f <= s2.dimension(); f++)
                        {
                            if(f != c[a])
                            {
                                s3(f) = s2(f);
                            }
                            else
                            {
                                s3(f) = pointSet[i];
                            }
                        }

                        m_tab.push_back(s3);
                    }
                }
             }
        }
    }
    else
    {
        throw std::string("Nombre de points insuffisants pour le pavage");
    }
}

Simplexe PavageNaif::getSimplexe(const Point & p) const
{
    Simplexe ret;

    for(std::vector<Simplexe>::const_iterator it = m_tab.begin();
        it != m_tab.end(); it ++)
    {
        if(it->containPoint(p))
        {
            ret = *it;
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
