// Adapted from Andrew Sutton's example code at
//   <URL:https://accu.org/index.php/journals/2157>
//   <URL:https://accu.org/index.php/journals/2198>

#include <string>
#include <type_traits>
#include <vector>
#include "concepts.h"

using namespace std;

template <typename R, typename T>
bool in(R const& range, T const& value)
    CONCEPT_REQUIRES((Range<R> &&
                      EqualityComparableWith<T, value_type_t<R>>))
{
    for (auto const& x : range)
        if (x == value)
            return true;
    return false;
}

template <typename R>
bool in(R const& range, size_t value)
    CONCEPT_REQUIRES((requires (R r) { r.size(); }))
{
    if (range.size() == value)
        return true;
    return false;
}

int main()
{
    vector<string> v{"Hello", "World"};
    in(v, "Hello");
    in(v, 0);
}
