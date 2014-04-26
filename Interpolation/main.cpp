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
}

void testLecture()
{
    std::ifstream file;
    file.open("test.txt", std::ios::in);

    int d;
    file>>d;

    while(!file.eof())
    {
        Point p(d);

        file>>p;

        std::cout<<p<<std::endl;
    }

    file.close();
}

void testPavage()
{
    std::ifstream file;
    file.open("test3D.txt", std::ios::in);
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
    pv.affichage();

//    file.open("test_eval.txt", std::ios::in);
//    file>>d;
//    std::vector<Point> pse;
//    while(!file.eof())
//    {
//        Point p(d);
//        file>>p;
//        pse.push_back(p);
//    }
//    file.close();

//    std::cout<<"Avant eval"<<std::endl;
//    for(int i = 0; i < pse.size(); i ++)
//    {
//        std::cout<<"Evaluation "<<pse[i]<<" = "<<pv.eval(pse[i])<<std::endl;
//    }
}

int main()
{
    testPavage();
//    int i,j,k;
//    try
//    {
//        std::cout<<testTree()<<std::endl;
//    }
//    catch(std::string c)
//    {
//        std::cout<<c<<std::endl;
//    }

//    testFactoriel();
//    testPuissance2();
//    //    testDistance();
//    testVolume();
//    testLecture();
    /*ublas::matrix<double> m1 (3, 3);
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

    return 0;
}

