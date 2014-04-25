#include <iostream>
#include "point.h"
#include "simplexe.h"
//#include "parser.h"
#include "tree.h"
#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/matrix_expression.hpp"
#include "boost/numeric/ublas/triangular.hpp"
#include <boost/numeric/ublas/io.hpp>
#include "boost/numeric/ublas/vector.hpp"
using namespace std;

bool testTree()
{
    Tree<double> test;

    test.setData(42.2);

    test.setChild(0, 13);

    try
    {
        test(13.0).setChild(2, 72);
    }
    catch(std::string c)
    {
        std::cout<<" 72 "<<c<<std::endl;
    }

    try
    {
        std::cout<<"Contain 42.2 "<<test.contain(42.2)<<std::endl;
        std::cout<<"Contain 13 "<<test.contain(13)<<std::endl;
        std::cout<<"Contain 72 "<<test.contain(72)<<std::endl;
        std::cout<<"Contain 0 "<<test.contain(0)<<std::endl;
    }
    catch(std::string c)
    {
        std::cout<<" IN "<<c<<std::endl;
    }

    std::cout<<"Nb Element "<<test.nbElement()<<std::endl;

    return test.contain(42.2) && test.contain(13) && test.contain(72) && !test.contain(0);
}

void testFactoriel()
{
    std::cout<<"fact(1) = "<<MetaProg::valueOf<1>::fact<<std::endl;
    std::cout<<"fact(2) = "<<MetaProg::valueOf<2>::fact<<std::endl;
    std::cout<<"fact(3) = "<<MetaProg::valueOf<3>::fact<<std::endl;
    std::cout<<"fact(4) = "<<MetaProg::valueOf<4>::fact<<std::endl;
    std::cout<<"fact(5) = "<<MetaProg::valueOf<5>::fact<<std::endl;

    std::cout<<"fFact(1) = "<<MetaProg::fFactorial(1)<<std::endl;
    std::cout<<"fFact(2) = "<<MetaProg::fFactorial(2)<<std::endl;
    std::cout<<"fFact(3) = "<<MetaProg::fFactorial(3)<<std::endl;
    std::cout<<"fFact(4) = "<<MetaProg::fFactorial(4)<<std::endl;
    std::cout<<"fFact(5) = "<<MetaProg::fFactorial(5)<<std::endl;
}

void testPuissance2()
{
    std::cout<<"pow2(1) = "<<MetaProg::valueOf<1>::pow2<<std::endl;
    std::cout<<"pow2(2) = "<<MetaProg::valueOf<2>::pow2<<std::endl;
    std::cout<<"pow2(3) = "<<MetaProg::valueOf<3>::pow2<<std::endl;
    std::cout<<"pow2(4) = "<<MetaProg::valueOf<4>::pow2<<std::endl;
    std::cout<<"pow2(5) = "<<MetaProg::valueOf<5>::pow2<<std::endl;
    std::cout<<"pow2_5 = "<<valueOf5::pow2<<std::endl;

    std::cout<<"fPow(2,1) = "<<MetaProg::fPow(2,1)<<std::endl;
    std::cout<<"fPow(2,2) = "<<MetaProg::fPow(2,2)<<std::endl;
    std::cout<<"fPow(2,3) = "<<MetaProg::fPow(2,3)<<std::endl;
    std::cout<<"fPow(2,4) = "<<MetaProg::fPow(2,4)<<std::endl;
    std::cout<<"fPow(2,5) = "<<MetaProg::fPow(2,5)<<std::endl;

}

void testDistance()
{
    Point p1(2), p2(2), p3(2);

    p1(0) = 0;
    p1(1) = 0;

    p2(0) = 3;
    p2(1) = 0;

    p3(0) = 3;
    p3(1) = 1;

    Simplexe s2(1);
    s2(0) = p2;
    s2(1) = p3;

    std::cout<<"Distance p1 à Simplexe(p2, p3) "<<s2.distance(p1)<<std::endl;
}

void testVolume()
{
    std::vector<Point> pt;
    Point p1(2), p2(2), p3(2);

    p1(0) = 0;
    p1(1) = 0;

    pt.push_back(p1);

    p2(0) = 3;
    p2(1) = 0;

    pt.push_back(p2);

    p3(0) = 3;
    p3(1) = 1;

    pt.push_back(p3);
    Simplexe s (pt);

    std::cout<<"Volume du triangle (0,0) (1,0) (1,1)"<<s.hyperVolume()<<std::endl;

}



int main()
{
    int i,j,k;
    /*try
    {
        std::cout<<testTree()<<std::endl;
    }
    catch(std::string c)
    {
        std::cout<<c<<std::endl;
    }

    testFactoriel();
    testPuissance2();
    testDistance();
    testVolume();

    ublas::matrix<double> m1 (3, 3);
    ublas::vector<double> m2 (3);
    for (unsigned i = 0; i < 3; ++ i)
        for (unsigned j = 0; j < 3; ++ j)
        {
            m1 (i, j) = 3 * i + j + 1;
            m2 (i) = i;
        }
    std::cout << "m1 = "<< m1 << std::endl;
    std::cout << "m2 = "<< m2 << std::endl;
    std::cout << ublas::solve (m1, m2, ublas::lower_tag ()) << std::endl; //M1*result = M2
    std::cout << ublas::solve (m2, m1, ublas::lower_tag ()) << std::endl; //M2*result = M1
    std::cout << "m1*m2 = "<<prod(m1,m2) << std::endl;
    std::cout << "m2*m1 = "<<prod(m2,m1) << std::endl;
*/
//    parser p;
//    p.lecture();

    std::ifstream file;
    file.open("fichier.txt", std::ios::in);
    std::vector<Point> liste;
    int dim;
    file>>dim;
    std::cout << dim <<std::endl;
    i=0;
    Point p;
    while(!file.eof())
    {
        int c;
        file>>c;
        //std::cout << c <<std::endl;
        p(i) = c;
        i++;
        if(i==dim){
            Point p2(p);
            liste.push_back(p2);
            std::cout<<"point :"<<p2<<std::endl;
            i=0;
        }
    }
    std::cout <<"taille : "<< liste.size() <<std::endl;





    // Création d'un simplexe de base (de taille de la dimension)
    std::vector<Point> tmp;
    for(i=0; i<dim+1;i++)
        tmp.push_back(liste[i]);
    std::cout<<"taille tmp "<<tmp.size()<<std::endl;

    // Nouveau point
    Point g(liste[i]);


    //double ligne1[4] = {tmp[0](0)-g(0), tmp[1](0)-g(0), tmp[2](0)-g(0),0};
    //double ligne2[4] = {tmp[0](1)-g(1), tmp[1](1)-g(1), tmp[2](1)-g(1),0};
    //double ligne3[4] = {0,0,0,0};

    double ligne1[4] = {1,-1,2,5};
    double ligne2[4] = {3,2,1,10};
    double ligne3[4] = {2,-3,-2,-10};
    double pivot;

    std::cout<<"l1 : "<<ligne1[0]<<"a + "<<ligne1[1]<<"b + "<<ligne1[2]<<"c = "<<ligne1[3]<<std::endl;
    std::cout<<"l2 : "<<ligne2[0]<<"a + "<<ligne2[1]<<"b + "<<ligne2[2]<<"c = "<<ligne2[3]<<std::endl;
    std::cout<<"l3 : "<<ligne3[0]<<"a + "<<ligne3[1]<<"b + "<<ligne3[2]<<"c = "<<ligne3[3]<<std::endl<<std::endl;

    if(ligne1[0] != 1){
        pivot = ligne1[0];
        ligne1[0] = ligne1[0]/pivot;
        ligne1[1] = ligne1[1]/pivot;
        ligne1[2] = ligne1[2]/pivot;
        ligne1[3] = ligne1[3]/pivot;
    }
    pivot = ligne2[0];
    ligne2[0] = ligne2[0]-pivot*ligne1[0];
    ligne2[1] = ligne2[1]-pivot*ligne1[1];
    ligne2[2] = ligne2[2]-pivot*ligne1[2];
    ligne2[3] = ligne2[3]-pivot*ligne1[3];
    pivot = ligne3[0];
    ligne3[0] = ligne3[0]-pivot*ligne1[0];
    ligne3[1] = ligne3[1]-pivot*ligne1[1];
    ligne3[2] = ligne3[2]-pivot*ligne1[2];
    ligne3[3] = ligne3[3]-pivot*ligne1[3];

    std::cout<<"l1 : "<<ligne1[0]<<"a + "<<ligne1[1]<<"b + "<<ligne1[2]<<"c = "<<ligne1[3]<<std::endl;
    std::cout<<"l2 : "<<ligne2[0]<<"a + "<<ligne2[1]<<"b + "<<ligne2[2]<<"c = "<<ligne2[3]<<std::endl;
    std::cout<<"l3 : "<<ligne3[0]<<"a + "<<ligne3[1]<<"b + "<<ligne3[2]<<"c = "<<ligne3[3]<<std::endl<<std::endl;

    if(ligne2[1] != 1){
        pivot = ligne2[1];
        ligne2[0] = ligne2[0]/pivot;
        ligne2[1] = ligne2[1]/pivot;
        ligne2[2] = ligne2[2]/pivot;
        ligne2[3] = ligne2[3]/pivot;
    }
    std::cout<<"l1 : "<<ligne1[0]<<"a + "<<ligne1[1]<<"b + "<<ligne1[2]<<"c = "<<ligne1[3]<<std::endl;
    std::cout<<"l2 : "<<ligne2[0]<<"a + "<<ligne2[1]<<"b + "<<ligne2[2]<<"c = "<<ligne2[3]<<std::endl;
    std::cout<<"l3 : "<<ligne3[0]<<"a + "<<ligne3[1]<<"b + "<<ligne3[2]<<"c = "<<ligne3[3]<<std::endl<<std::endl;
    //ok

    pivot = ligne3[1];
    ligne3[0] = ligne3[0]-pivot*ligne2[0];
    ligne3[1] = ligne3[1]-pivot*ligne2[1];
    ligne3[2] = ligne3[2]-pivot*ligne2[2];
    ligne3[3] = ligne3[3]-pivot*ligne2[3];

    std::cout<<"l1 : "<<ligne1[0]<<"a + "<<ligne1[1]<<"b + "<<ligne1[2]<<"c = "<<ligne1[3]<<std::endl;
    std::cout<<"l2 : "<<ligne2[0]<<"a + "<<ligne2[1]<<"b + "<<ligne2[2]<<"c = "<<ligne2[3]<<std::endl;
    std::cout<<"l3 : "<<ligne3[0]<<"a + "<<ligne3[1]<<"b + "<<ligne3[2]<<"c = "<<ligne3[3]<<std::endl<<std::endl;

    if(ligne3[2] != 1){
        pivot = ligne3[2];
        ligne3[0] = ligne3[0]/pivot;
        ligne3[1] = ligne3[1]/pivot;
        ligne3[2] = ligne3[2]/pivot;
        ligne3[3] = ligne3[3]/pivot;
    }

    double c = ligne3[3];
    double b = ligne2[3] - ligne2[2]*c;
    double a = ligne1[3] - ligne1[1]*b - ligne1[2]*c;
    std::cout<<"c = "<<c<<std::endl;
    std::cout<<"b = "<<b<<std::endl;
    std::cout<<"a = "<<a<<std::endl;



    boost::numeric::ublas::matrix<double> m (dim+1, dim+2);
    m(0,0) = 1; m(0,1) = -1; m(0,2)=2; m(0,3)=5;
    m(1,0) = 3; m(1,1) = 2; m(1,2)=1; m(1,3)=10;
    m(2,0) = 2; m(2,1) = -3; m(2,2)=-2; m(2,3)=-10;

    int h = dim+1;
    int l = dim+2;
    int x,y;
    std::cout<<"matrice "<<std::endl;
    for(x=0; x<h; x++){
        for(y=0; y<l; y++)
            std::cout<<m(x,y)<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    for(i=0; i<h; i++){

        std::cout<<"matrice "<<i<<std::endl;
        for(x=0; x<h; x++){
            for(y=0; y<l; y++)
                std::cout<<m(x,y)<<" ";
            std::cout<<std::endl;
        }
        std::cout<<std::endl;

        if(m(i,i) != 1){
            std::cout<<"div pour 1"<<std::endl;
            pivot=m(i,i);
            for(j=0; j<l;j++)
                m(i,j)=m(i,j)/pivot;
            for(x=0; x<h; x++){
                for(y=0; y<l; y++)
                    std::cout<<m(x,y)<<" ";
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }



        for(j=i+1; j<h;j++){
            // pour chaque ligne suivante
            std::cout<<"****************modif ligne "<<j<<std::endl;

            pivot=m(j,i);
            for(k=0;k<l;k++)
                m(j,k)=m(j,k)-pivot*m(i,k);
            std::cout<<"matrice "<<i<<std::endl;
            for(x=0; x<h; x++){
                for(y=0; y<l; y++)
                    std::cout<<m(x,y)<<" ";
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }


    }

    std::cout<<"matrice "<<std::endl;
    for(x=0; x<h; x++){
        for(y=0; y<l; y++)
            std::cout<<m(x,y)<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    std::vector<double> resultat;
    for(i=h-1;i>=0;i--){
        double r = m(i,l-1); // partie droite
        // puis on soustraire avec la partie gauche
        k=l-1-1; //le dernier (en enlevent la partie droite)
        for(j=0;j<resultat.size();j++){
            r -= resultat[j]*m(i,k);
            k--;
        }
        std::cout<<r<<std::endl;
        resultat.push_back(r);
    }
    std::cout<<"resultat : ";
    for(i=0; i<resultat.size();i++){
        std::cout<<resultat[i]<<" ";
    }
    std::cout<<std::endl;

    return 0;
}

