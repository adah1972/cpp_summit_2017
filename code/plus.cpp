#include "concepts.h"

auto plus(Integer x, Integer y)
{
    return x + y;
}

int main()
{
    plus(0, 1);        // OK
    plus(0, (long)1);  // Does not compile
}
