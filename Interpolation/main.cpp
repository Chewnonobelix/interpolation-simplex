#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#include <iostream>
#include "point.h"
#include "simplexe.h"
#include "pavagenaif.h"
//#include "parser.h"
#include "tree.h"
#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/matrix_expression.hpp"
#include "boost/numeric/ublas/triangular.hpp"
#include <boost/numeric/ublas/io.hpp>
#include "boost/numeric/ublas/vector.hpp"
using namespace std;

void testFactoriel()
{
    std::cout<<"Test factoriel"<<std::endl;
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

    std::cout<<"Fin test factoriel"<<std::endl;
}

void testPuissance2()
{
    std::cout<<"Test Puissance de 2"<<std::endl;

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

    std::cout<<"Fin test puissance de 2"<<std::endl;
}

void testDistance()
{
    std::cout<<"Test distance"<<std::endl;

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


    std::cout<<"Fin test distance"<<std::endl;
}

void testVolume()
{
    std::cout<<"Test volume"<<std::endl;
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


    Point c1(3),c2(3),c3(3),c4(3);
    std::vector<Point> pt2;

    c1(0) = 1;
    c1(1) = 1;
    c1(2) = 1;

    c2(0) = 1;
    c2(1) = 1;
    c2(2) = 2;

    c3(0) = 1;
    c3(1) = 2;
    c3(2) = 1;

    c4(0) = 2;
    c4(1) = 1;
    c4(2) = 1;

    pt2.push_back(c1);
    pt2.push_back(c2);
    pt2.push_back(c3);
    pt2.push_back(c4);

    Simplexe s2(pt2);
    Simplexe s3(2);
    Simplexe s4(1);
    s3(0) = c2;
    s3(1) = c3;
    s3(2) = c4;

    s4(0) = c3;
    s4(1) = c4;

    std::cout<<"distance C3->C4 = "<<Point::distance(c3,c4)<<std::endl;
    std::cout<<"Volume C2,C3,C4 = "<<s3.hyperVolume()<<std::endl;
    std::cout<<"Volume C3,C4 = "<<s4.hyperVolume()<<std::endl;
    std::cout<<"Distance C2, S4 = "<<s4.distance(c2)<<std::endl;
    std::cout<<"Distance C1, S3 = "<<s3.distance(c1)<<std::endl;
    std::cout<<"S2"<<std::endl;
    try
    {
        std::cout<<"Volume s2 = "<<s2.hyperVolume()<<std::endl;
    }
    catch(std::string e)
    {
        std::cout<<"Erreur volume "<<e<<std::endl;
    }


    std::cout<<"Fin test Volume"<<std::endl;
}

void testPavage(std::string dim)
{
    std::cout<<"Test pavage "<<dim<<std::endl;
    std::ifstream file;
    file.open(("fichier_test\\pav"+dim+".txt").c_str(), std::ios::in);
    int d;
    file>>d;
    std::vector<Point> ps;
    while(!file.eof())
    {
        Point p(d);
        file>>p;
        ps.push_back(p);
    }
    file.close();
    PavageNaif pv(d);

    pv.pavage(ps);
    std::cout<<"Affichage point"<<std::endl;
    for(int i = 0; i <ps.size();i++)
    {
        std::cout<<ps[i]<<std::endl;
    }
    pv.affichage();

    file.open(std::string(("fichier_test\\eval")+dim+".txt").c_str(), std::ios::in);
    file>>d;
    std::vector<Point> pse;
    while(!file.eof())
    {
        Point p(d);
        file>>p;
        pse.push_back(p);
    }
    file.close();

    for(int i = 0; i < pse.size(); i ++)
    {
        std::cout<<"Evaluation "<<pse[i]<<" = "<<pv.eval(pse[i])<<std::endl;
    }

    std::cout<<"Fin test pavage "<<dim<<std::endl;
}

int main()
{
    testFactoriel();
    testPuissance2();
    testDistance();
    testVolume();
    testPavage("2D");
    testPavage("3D");
    testPavage("4D");

    return 0;
}

