// Adapted from Andrew Sutton's example code at
//   <URL:https://accu.org/index.php/journals/2157>
//   <URL:https://accu.org/index.php/journals/2198>

#include <string>
#include <type_traits>
#include <vector>
#include "concepts.h"

using namespace std;

template <typename R, typename T>
auto in(R const& rng, T const& value) -> decltype(*begin(rng) == value)
{
    for (auto const& x : rng)
        if (x == value)
            return true;
    return false;
}

template <typename R>
auto in(R const& rng, size_t value) -> decltype(rng.size() == value)
{
    if (rng.size() == value)
        return true;
    return false;
}

int main()
{
    vector<string> v{"Hello", "World"};
    in(v, "Hello");
    in(v, 0);
}
