#include <algorithm>            // std::copy
#include <iostream>             // std::cout
#include <iterator>             // std::begin/iterator_traits/ostream_iterator
#include <memory>               // std::allocator
#include <type_traits>          // std::integral_constant
#include <utility>              // std::declval
#include <vector>               // std::vector
#include "concepts.h"

namespace detail {

template <typename _T1, typename _T2>
concept can_reserve = requires(_T1& dest, const _T2& src) {
    dest.reserve(src.size());
};

} /* namespace detail */

template <template <typename, typename> class _OutCont = std::vector,
          template <typename> class _Alloc = std::allocator,
          typename _Fn, class _Rng>
constexpr auto fmap(_Fn&& f, _Rng&& inputs)
    requires Range<_Rng>
{
    typedef std::decay_t<decltype(
        f(std::declval<typename std::decay_t<_Rng>::value_type>()))>
        result_type;
    _OutCont<result_type, _Alloc<result_type>> result;
    if constexpr (detail::can_reserve<decltype(result), _Rng>)
    {
        result.reserve(inputs.size());
    }
    for (auto& item : inputs)
        result.push_back(f(item));
    return result;
}

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    auto r = fmap([](int n) { return n + 1; }, v);
    std::copy(r.begin(), r.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
