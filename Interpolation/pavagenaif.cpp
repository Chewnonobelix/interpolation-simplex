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
                int di = 0;
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

                int c = 0;
                int index = 0;
                Simplexe s3(s2.dimension()); //Futur nouveau simplexe
                ublas::matrix<double> m(s2.dimension(), s2.dimension()), mp(s2.dimension(), s2.dimension());

                for(int b = 0; b <= s2.dimension(); b++)
                {
                    // Début remplissage Matrice
                    int z = 0;
                    for(int q = 0; q <= s2.dimension(); q++)
                    {
                        if(b != q)
                        {
                            for(int t = 0; t < s2.dimension(); t ++)
                            {
                                mp(t, q-z) = s2(q)(t) - s2(b)(t);
                                m(t, q-z) = s2(q)(t) - pointSet[i](t);
                            }
                        }
                        else
                        {
                            z++;
                        }
                    }

                    // Fin remplissage Matrice

                    double dm, dmp;
                    dm = determinant(m);
                    dmp = determinant(mp);

                    //Si dm et dmp sont du même signe, ou si l'un est égal à 0, alors p et s2(b) sont du même coté de la face opposé à s2(b)
                    if(dm*dmp >= 0)
                    {
                        c ++;
                    }
                    else
                    {
                        index = b;
                    }
                }

                //Si le nombre de dm*dmp est égal à la dimension de l'espace alors on peut crée un nouveau simplex
                //Sinon si le nombre de dm*dmp est égal à la dimension + 1 alors on décompose s2
                if(c == s2.dimension())
                {
                    for(int f = 0; f <= s2.dimension(); f++)
                    {
                        if(f != index)
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
//                else if (c == s2.dimension() + 1)
//                {
//                    std::vector<Simplexe> nouveau = s2.decomposition(pointSet[i]);
//                    m_tab[di] = nouveau[0];
//                    for(int k = 1; k < nouveau.size(); k++)
//                    {
//                        m_tab.push_back(nouveau[k]);
//                    }
//                }
            }
        }
    }
    else
    {
        throw std::string("Nombre de points insuffisants pour le pavage");
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
