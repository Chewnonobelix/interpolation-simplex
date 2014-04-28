#ifndef PAVAGENAIFTREE_H
#define PAVAGENAIFTREE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "abstractpavage.h"
#include "tree.h"

class PavageNaifTree: public AbstractPavage<Tree<Simplexe>>
{
private:
    Tree<Simplexe> treeSearch(const Tree<Simplexe>&, const Point &) const;
public:
    PavageNaifTree(int);
    void pavage(const std::vector<Point>&);
    Simplexe getSimplexe(const Point &) const;
    void affichage() const;

};

#endif // PAVAGENAIFTREE_H
