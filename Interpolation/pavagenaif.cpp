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

        for(int i = dimension() + 1; i< pointSet.size(); i ++)
        {
            bool contain = false;
            Simplexe s(dimension());
            int j = 0;
            while(!contain && j < m_tab.size())
            {
//                if(m_tab[j].contain(pointSet[i]))
//                {
//                    s = m_tab[j];
//                    std::vector<Simplexe> temp = s.decomposition(pointSet[i]);
//                    m_tab.erase(m_tab.begin() + j);
//                    m_tab.push_back(temp);
//                    contain = true;
//                }
                j++;
            }
            if(!contain)
            {
                s = Simplexe(dimension());
            }

        }
    }
    else
    {
        throw std::string("Nombre de points insuffisants");
    }
}

Simplexe PavageNaif::getSimplexe(const Point & p) const
{
    Simplexe ret;

    for(std::vector<Simplexe>::const_iterator it = m_tab.begin();
        it != m_tab.end(); it ++)
    {
//        if(it->containPoint(p))
//        {
//            ret = *it;
//        }
    }

     return ret;
}
