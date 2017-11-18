#include <iostream>
#include "concepts.h"

template <Integer N>
inline bool odd(N n)
{
    return bool(n & 0x1);
}

int main()
{
    std::cout << odd(1) << std::endl;
    std::cout << odd(1.0) << std::endl;  // Does not compile
    std::cout << odd('a') << std::endl;  // Now it stops compiling!
}
