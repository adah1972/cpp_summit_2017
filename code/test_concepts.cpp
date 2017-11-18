#include <armadillo>
#include <iostream>
#include "concepts.h"

using namespace std;

#define TEST_CONCEPT(Concept, Type...) \
    cout << #Concept << '<' << #Type << ">: " << Concept<Type> << endl

int main()
{
    TEST_CONCEPT(Semiregular, std::unique_ptr<int>);
    TEST_CONCEPT(EqualityComparable, std::unique_ptr<int>);
    TEST_CONCEPT(Readable, int);
    TEST_CONCEPT(Readable, std::unique_ptr<int>);
    TEST_CONCEPT(Writable, std::unique_ptr<int>, int);
    TEST_CONCEPT(Semiregular, arma::imat);
    TEST_CONCEPT(Assignable, arma::imat&, arma::imat&);
    TEST_CONCEPT(Semiregular, arma::imat22);
    TEST_CONCEPT(Assignable, arma::imat22&, arma::imat22&);
    TEST_CONCEPT(Regular, int);
    TEST_CONCEPT(Regular, char);
    TEST_CONCEPT(Integer, int);
    TEST_CONCEPT(Integer, char);
}
