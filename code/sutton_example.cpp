// Adapted from Andrew Sutton's example code at
//   <URL:https://accu.org/index.php/journals/2157>
//   <URL:https://accu.org/index.php/journals/2198>

#include <string>
#include <type_traits>
#include <vector>
#include "concepts.h"

using namespace std;

template <typename R, typename T>
bool in(R const& rng, T const& value)
    CONCEPT_REQUIRES((ranges::range<R> &&
                      equality_comparable_with<T, typename R::value_type>))
{
    for (auto const& x : rng)
        if (x == value)
            return true;
    return false;
}

int main()
{
    vector<string> v{"Hello", "World"};
    in(v, 0);
}
