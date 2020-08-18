#include <armadillo>
#include <iostream>
#include "concepts.h"

using namespace std;

#define TEST_CONCEPT(Concept, Type...) \
    cout << #Concept << '<' << #Type << ">: " << Concept<Type> << endl

int main()
{
    cout << __cplusplus << endl;
    cout << __cpp_concepts << endl;
    TEST_CONCEPT(semiregular, std::unique_ptr<int>);
    TEST_CONCEPT(equality_comparable, std::unique_ptr<int>);
    TEST_CONCEPT(readable, int);
    TEST_CONCEPT(readable, std::unique_ptr<int>);
    TEST_CONCEPT(writable, std::unique_ptr<int>, int);
    TEST_CONCEPT(semiregular, arma::imat);
    TEST_CONCEPT(assignable_from, arma::imat&, arma::imat&);
    TEST_CONCEPT(semiregular, arma::imat22);
    TEST_CONCEPT(assignable_from, arma::imat22&, arma::imat22&);
    TEST_CONCEPT(regular, int);
    TEST_CONCEPT(regular, char);
    TEST_CONCEPT(integral, int);
    TEST_CONCEPT(integral, char);
    TEST_CONCEPT(Integer, int);
    TEST_CONCEPT(Integer, char);
}
