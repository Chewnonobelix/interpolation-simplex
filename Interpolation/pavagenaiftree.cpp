#include "pavagenaiftree.h"

PavageNaifTree::PavageNaifTree(int dim): AbstractPavage(dim)
{
}

void PavageNaifTree::pavage(const std::vector<Point> & pointSet)
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
                find = m_tab[j].data().containPoint(pointSet[i]);
                if(!find)
                {
                    j++;
                }
            }

            if(find)
            {
                Tree<Simplexe> ts = m_tab[j];
                while(ts.hasChild())
                {
                    bool next = false;
                    int j = 0;
                    while(!next && j < ts.nbChild())
                    {
                        if(ts.data().containPoint(pointSet[i]))
                        {
                            ts = ts.children()[j];
                            next = true;
                        }
                        else
                        {
                            j++;
                        }

                    }
                }

                s = ts.data();
                std::vector<Simplexe> nouveau = s.decomposition(pointSet[i]);
                for(int j = 0; j < nouveau.size(); j ++)
                {
                    ts.addChild(j, nouveau[j]);
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
                    double temp = m_tab[k].data().distance(pointSet[i]);

                    if(d == -1 || temp < d)
                    {
                        d = temp;
                        s2 = m_tab[k].data();
                        di = k;
                    }
                }

                Simplexe s3(s2.dimension()); //Futur nouveau simplexe
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

Simplexe PavageNaifTree::getSimplexe(const Point & p) const
{
    Simplexe ret;

    for(std::vector<Tree<Simplexe>>::const_iterator it = m_tab.begin();
        it != m_tab.end(); it ++)
    {
        if(!(ret == Simplexe(p.dimension())))
        {
            ret = treeSearch(*it, p).data();
        }
    }

    return ret;
}

void PavageNaifTree::affichage() const
{
    std::cout<<"Pavage"<<std::endl;
    for(int i = 0; i < m_tab.size(); i ++)
    {
        //        std::cout<<m_tab[i]<<std::endl;
    }
}

Tree<Simplexe> PavageNaifTree::treeSearch(const Tree<Simplexe> & t, const Point& p) const
{
    if(!t.hasChild() && t.data().containPoint(p))
    {
        return t;
    }
    else if(!t.hasChild())
    {
        return Simplexe(p.dimension());
    }
    else
    {
        bool find = false;
        int i = 0;

        while(!find && i < t.nbChild())
        {
            Tree<Simplexe> ret = treeSearch(t(i), p);
            if(!(ret.data() == Simplexe(p.dimension())))
            {
                return ret;
            }
        }
    }

    return Simplexe(p.dimension());
}
