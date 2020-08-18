#include "concepts.h"

template <Integer N>
auto plus(N x, N y)
{
    return x + y;
}

int main()
{
    plus(0, 1);        // OK
    plus(0, (long)1);  // Does not compile
}
