#include <iostream>
#include "point.h"
#include "simplexe.h"
#include "tree.h"
#include "Eigen/Dense"

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
    std::cout<<"fact(1) = "<<MetaProg::factorial<1>::value<<std::endl;
    std::cout<<"fact(2) = "<<MetaProg::factorial<2>::value<<std::endl;
    std::cout<<"fact(3) = "<<MetaProg::factorial<3>::value<<std::endl;
    std::cout<<"fact(4) = "<<MetaProg::factorial<4>::value<<std::endl;
    std::cout<<"fact(5) = "<<MetaProg::factorial<5>::value<<std::endl;

    std::cout<<"fFact(1) = "<<MetaProg::fFactorial(1)<<std::endl;
    std::cout<<"fFact(2) = "<<MetaProg::fFactorial(2)<<std::endl;
    std::cout<<"fFact(3) = "<<MetaProg::fFactorial(3)<<std::endl;
    std::cout<<"fFact(4) = "<<MetaProg::fFactorial(4)<<std::endl;
    std::cout<<"fFact(5) = "<<MetaProg::fFactorial(5)<<std::endl;
}

void testPuissance2()
{
    std::cout<<"pow2(1) = "<<MetaProg::pow2<1>::value<<std::endl;
    std::cout<<"pow2(2) = "<<MetaProg::pow2<2>::value<<std::endl;
    std::cout<<"pow2(3) = "<<MetaProg::pow2<3>::value<<std::endl;
    std::cout<<"pow2(4) = "<<MetaProg::pow2<4>::value<<std::endl;
    std::cout<<"pow2(5) = "<<MetaProg::pow2<5>::value<<std::endl;
    std::cout<<"pow2_5 = "<<pow2_5::value<<std::endl;

    std::cout<<"fPow(2,1) = "<<MetaProg::fPow(2,1)<<std::endl;
    std::cout<<"fPow(2,2) = "<<MetaProg::fPow(2,2)<<std::endl;
    std::cout<<"fPow(2,3) = "<<MetaProg::fPow(2,3)<<std::endl;
    std::cout<<"fPow(2,4) = "<<MetaProg::fPow(2,4)<<std::endl;
    std::cout<<"fPow(2,5) = "<<MetaProg::fPow(2,5)<<std::endl;

}

void testEigen()
{
    Eigen::MatrixXd test(10,10);

    test(1,2) = 42.0;

    std::cout<<test(0,0)<<"    "<<test(1,2)<<std::endl;
}

int main()
{
    try
    {
        std::cout<<testTree()<<std::endl;
    }
    catch(std::string c)
    {
        std::cout<<c<<std::endl;
    }

    testFactoriel();
    testPuissance2();
    return 0;
}

