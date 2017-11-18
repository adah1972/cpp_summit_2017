#include <algorithm>            // std::copy
#include <iostream>             // std::cout
#include <iterator>             // std::begin/iterator_traits/ostream_iterator
#include <memory>               // std::allocator
#include <type_traits>          // std::integral_constant
#include <utility>              // std::declval
#include <vector>               // std::vector

namespace detail {

// Struct to check whether _T1 has a suitable reserve member function
// and _T2 has a suitable size member function.
template <class _T1, class _T2>
struct can_reserve
{
    struct good { char dummy; };
    struct bad { char dummy[2]; };
    template <class _Up, void   (_Up::*)(size_t)> struct _SFINAE1 {};
    template <class _Up, size_t (_Up::*)() const> struct _SFINAE2 {};
    template <class _Up> static good reserve(_SFINAE1<_Up, &_Up::reserve>*);
    template <class _Up> static bad  reserve(...);
    template <class _Up> static good size(_SFINAE2<_Up, &_Up::size>*);
    template <class _Up> static bad  size(...);
    static const bool value =
        (sizeof(reserve<_T1>(nullptr)) == sizeof(good) &&
         sizeof(size<_T2>(nullptr)) == sizeof(good));
};

// Does nothing.
template <class _T1, class _T2>
void try_reserve(_T1&, const _T2&, std::false_type)
{
}

// Reserves the destination with the source's size.
template <class _T1, class _T2>
void try_reserve(_T1& dest, const _T2& src, std::true_type)
{
    dest.reserve(src.size());
}

using std::begin;
using std::end;

// Function declarations to resolve begin/end using argument-dependent lookup
template <class _Rng>
auto adl_begin(_Rng&& rng) -> decltype(begin(rng));
template <class _Rng>
auto adl_end(_Rng&& rng) -> decltype(end(rng));

} /* namespace detail */

template <template <typename, typename> class _OutCont = std::vector,
          template <typename> class _Alloc = std::allocator,
          typename _Fn, class _Rng>
constexpr auto fmap(_Fn&& f, _Rng&& inputs) -> decltype(
    detail::adl_begin(inputs), detail::adl_end(inputs),
    _OutCont<
        std::decay_t<decltype(f(*detail::adl_begin(inputs)))>,
        _Alloc<std::decay_t<decltype(f(*detail::adl_begin(inputs)))>>>())
{
    typedef std::decay_t<decltype(f(*detail::adl_begin(inputs)))>
        result_type;
    _OutCont<result_type, _Alloc<result_type>> result;
    detail::try_reserve(
        result, inputs,
        std::integral_constant<
            bool, detail::can_reserve<decltype(result), _Rng>::value>());
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
