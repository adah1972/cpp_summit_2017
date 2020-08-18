/*
 * Written by Yongwei Wu.  The code is considered in the public domain (i.e.
 * do whatever you like with it).
 *
 * This software is provided 'AS-IS', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * There are three code paths:
 *
 * 1. C++20 concepts
 * 2. C++17 + GCC concepts + STL2 <URL:https://github.com/caseycarter/cmcstl2>
 * 3. Workaroud macros when no concepts support is detected
 *
 */

#ifndef CONCEPTS_H
#define CONCEPTS_H

#if defined(__cpp_concepts)

// Macros for common compatibility purposes
#define BidirectionalIterator           bidirectional_iterator
#define Copyable                        copyable
#define CopyConstructible               copy_constructible
#define DefaultConstructible            default_initializable
#define EqualityComparable              equality_comparable
#define ForwardIterator                 forward_iterator
#define InputIterator                   input_iterator
#define Integral                        integral
#define Iterator                        input_or_output_iterator
#define Movable                         movable
#define MoveConstructible               move_constructible
#define OutputIterator                  output_iterator
#define RandomAccessIterator            random_access_iterator
#define Range                           ranges::range
#define Readable                        readable
#define Regular                         regular
#define Semiregular                     semiregular
#define StrictTotallyOrdered            totally_ordered
#define Swappable                       swappable
#define View                            ranges::view

#if __cpp_concepts >= 201811

#include <concepts>
#include <functional>

// Concepts that usually take more than one argument
using std::assignable_from;
using std::common_with;
using std::constructible_from;
using std::convertible_to;
using std::equality_comparable_with;
using std::invocable;
using std::same_as;
template <typename T, typename U>
concept writable = std::indirectly_writable<T, U>;

// Concepts that takes only one argument
using std::bidirectional_iterator;
using std::copy_constructible;
using std::copyable;
using std::default_initializable;
using std::destructible;
using std::equality_comparable;
using std::forward_iterator;
using std::input_iterator;
using std::input_or_output_iterator;
using std::integral;
using std::movable;
using std::move_constructible;
using std::output_iterator;
using std::predicate;
using std::random_access_iterator;
using std::regular;
using std::semiregular;
using std::swappable;
using std::totally_ordered;
template <typename T>
concept readable = std::indirectly_readable<T>;

// The ranges namespace
namespace ranges = std::ranges;

template <class F, class T>
concept SemigroupOperation =
    invocable<F, T, T> &&
    requires(F f, T a, T b) {
        { std::invoke(f, a, b) } -> same_as<T>;
    };

template <class T>
concept Semiring =
    regular<T> &&
    requires(T a, T b) {
        { a + b } -> same_as<T>;
        { a - b } -> same_as<T>;
        { a * b } -> same_as<T>;

        { a += b } -> same_as<T&>;
        { a -= b } -> same_as<T&>;
        { a *= b } -> same_as<T&>;

        { T{0} };
        { T{1} };
    };

template <class T>
concept Ring =
    Semiring<T> &&
    requires(T a) {
        { -a } -> same_as<T>;
    };

template <class T>
concept EuclideanDomain =
    Ring<T> &&
    requires(T a, T b) {
        { abs(a) };
        { a / b };
        { a % b };
        { a / b + a % b };
    };

template <class T>
concept Integer =
    Ring<T> &&
    requires(T a, T b) {
        { a == 0 } -> convertible_to<bool>;
        { a == 1 } -> convertible_to<bool>;
        { a / b } -> same_as<T>;
        { a % b } -> same_as<T>;
        { a /= b } -> same_as<T&>;
        { a %= b } -> same_as<T&>;
    };

#define CONCEPT_ASSERT(x)       static_assert(x)
#define CONCEPT_REQUIRES(x)     requires(x)

#else // __cpp_concepts < 201811

#include <experimental/ranges/concepts>

// Concepts that usually take more than one argument
using std::experimental::ranges::assignable_from;
using std::experimental::ranges::common_with;
using std::experimental::ranges::constructible_from;
using std::experimental::ranges::convertible_to;
using std::experimental::ranges::equality_comparable_with;
using std::experimental::ranges::invocable;
using std::experimental::ranges::same_as;
using std::experimental::ranges::writable;

// Concepts that takes only one argument
using std::experimental::ranges::bidirectional_iterator;
using std::experimental::ranges::copy_constructible;
using std::experimental::ranges::copyable;
using std::experimental::ranges::default_initializable;
using std::experimental::ranges::destructible;
using std::experimental::ranges::equality_comparable;
using std::experimental::ranges::forward_iterator;
using std::experimental::ranges::input_iterator;
using std::experimental::ranges::input_or_output_iterator;
using std::experimental::ranges::integral;
using std::experimental::ranges::movable;
using std::experimental::ranges::move_constructible;
using std::experimental::ranges::output_iterator;
using std::experimental::ranges::predicate;
using std::experimental::ranges::random_access_iterator;
using std::experimental::ranges::readable;
using std::experimental::ranges::regular;
using std::experimental::ranges::semiregular;
using std::experimental::ranges::swappable;
using std::experimental::ranges::totally_ordered;

// The ranges namespace
namespace ranges = std::experimental::ranges;

template <class F, class T>
concept bool SemigroupOperation =
    invocable<F, T, T> &&
    requires(F f, T a, T b) {
        { std::experimental::ranges::invoke(f, a, b) } -> same_as<T>;
    };

template <class T>
concept bool Semiring =
    regular<T> &&
    requires(T a, T b) {
        // An old way is write the requirements like:
        //
        //   { a += b } -> same_as<T&>&&;
        //
        // Notice the ending `&&`, which is quite confusing but
        // necessary for concept implementations prior to P1084.
        //
        // In the future, we should be able to specify:
        //
        //   { a += b } -> same_as<T&>;
        //
        // See: <URL:http://wg21.link/p1084>
        //
        a + b; requires same_as<decltype(a + b), T>;
        a - b; requires same_as<decltype(a - b), T>;
        a * b; requires same_as<decltype(a * b), T>;

        a += b; requires same_as<decltype(a += b), T&>;
        a -= b; requires same_as<decltype(a -= b), T&>;
        a *= b; requires same_as<decltype(a *= b), T&>;

        T{0};
        T{1};
    };

template <class T>
concept bool Ring =
    Semiring<T> &&
    requires(T a) {
        -a; requires same_as<decltype(-a), T>;
    };

template <class T>
concept bool EuclideanDomain =
    Ring<T> &&
    requires(T a, T b) {
        { abs(a) };
        { a / b };
        { a % b };
        { a / b + a % b };
    };

template <class T>
concept bool Integer =
    Ring<T> &&
    requires(T a, T b) {
        { a == 0 } -> convertible_to<bool>;
        { a == 1 } -> convertible_to<bool>;
        a / b; requires same_as<decltype(a / b), T>;
        a % b; requires same_as<decltype(a % b), T>;
        a /= b; requires same_as<decltype(a /= b), T&>;
        a %= b; requires same_as<decltype(a %= b), T&>;
    };

#define CONCEPT_ASSERT(x)       static_assert(x)
#define CONCEPT_REQUIRES(x)     requires(x)

#endif

#else  // Concepts not supported

#define CONCEPT_ASSERT(x)
#define CONCEPT_REQUIRES(x)

// One-argument C++ concepts that used to be defined by STL2
#define BidirectionalIterator           typename
#define Copyable                        typename
#define CopyConstructible               typename
#define DefaultConstructible            typename
#define EqualityComparable              typename
#define ForwardIterator                 typename
#define InputIterator                   typename
#define Integral                        typename
#define Iterator                        typename
#define Movable                         typename
#define MoveConstructible               typename
#define OutputIterator                  typename
#define RandomAccessIterator            typename
#define Range                           typename
#define Readable                        typename
#define Regular                         typename
#define Semiregular                     typename
#define StrictTotallyOrdered            typename
#define Swappable                       typename
#define View                            typename

// A few more useful C++ concepts
#define EuclideanDomain                 typename
#define Integer                         typename
#define Semiring                        typename
#define Ring                            typename

#endif // End of concepts-related definitions

#endif // CONCEPTS_H
