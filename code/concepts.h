/*
 * Written by Yongwei Wu.  The code is considered in the public domain (i.e.
 * do whatever you like with it).
 *
 * This software is provided 'AS-IS', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * STL2 <URL:https://github.com/caseycarter/cmcstl2> needs to be in the
 * include path.  Currently (November 2017) only GCC is supported, and
 * "-std=c++17 -fconcepts" needs to be specified on the command line.
 * Unless, of course, you want the code to take the no-concepts path and
 * only define workaround macros.
 *
 */

#ifndef CONCEPTS_H
#define CONCEPTS_H

#if defined(__cpp_concepts) && \
    __cpp_concepts >= 201500 && \
    __cpp_concepts <= 201507

#include <stl2/concepts.hpp>

using std::experimental::ranges::v1::value_type_t;

// Concepts that usually take more than one argument
using std::experimental::ranges::v1::Assignable;
using std::experimental::ranges::v1::Common;
using std::experimental::ranges::v1::Constructible;
using std::experimental::ranges::v1::ConvertibleTo;
using std::experimental::ranges::v1::EqualityComparableWith;
using std::experimental::ranges::v1::Invocable;
using std::experimental::ranges::v1::Same;
using std::experimental::ranges::v1::Writable;

// Concepts that takes only one argument
using std::experimental::ranges::v1::BidirectionalIterator;
using std::experimental::ranges::v1::Boolean;
using std::experimental::ranges::v1::Copyable;
using std::experimental::ranges::v1::CopyConstructible;
using std::experimental::ranges::v1::DefaultConstructible;
using std::experimental::ranges::v1::Destructible;
using std::experimental::ranges::v1::EqualityComparable;
using std::experimental::ranges::v1::ForwardIterator;
using std::experimental::ranges::v1::InputIterator;
using std::experimental::ranges::v1::Integral;
using std::experimental::ranges::v1::Iterator;
using std::experimental::ranges::v1::Movable;
using std::experimental::ranges::v1::MoveConstructible;
using std::experimental::ranges::v1::OutputIterator;
using std::experimental::ranges::v1::Predicate;
using std::experimental::ranges::v1::RandomAccessIterator;
using std::experimental::ranges::v1::Range;
using std::experimental::ranges::v1::Readable;
using std::experimental::ranges::v1::Regular;
using std::experimental::ranges::v1::Semiregular;
using std::experimental::ranges::v1::StrictTotallyOrdered;
using std::experimental::ranges::v1::Swappable;

template<class T>
concept bool ContextuallyConvertibleToBool =
    requires(T&& t) {
        static_cast<T&&>(t) ? true : false;
    };

template <class F, class T>
concept bool SemigroupOperation =
    Invocable<F, T, T> &&
    requires(F f, T a, T b) {
        { std::experimental::ranges::v1::invoke(f, a, b) } -> Same<T>;
    };

template <class T>
concept bool Semiring =
    Regular<T> &&
    requires(T a, T b) {
        { a + b } -> Same<T>;
        { a - b } -> Same<T>;
        { a * b } -> Same<T>;

        { a += b } -> Same<T&>&&;
        { a -= b } -> Same<T&>&&;
        { a *= b } -> Same<T&>&&;

        { T{0} };
        { T{1} };
    };

template <class T>
concept bool Ring =
    Semiring<T> &&
    requires(T a) {
        { -a } -> Same<T>&&;
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
        { a == 0 } -> Boolean;
        { a == 1 } -> Boolean;
        { a / b } -> Same<T>;
        { a % b } -> Same<T>;
        { a /= b } -> Same<T&>&&;
        { a %= b } -> Same<T&>&&;
    };

#define CONCEPT_ASSERT(x)       static_assert(x)
#define CONCEPT_REQUIRES(x)     requires(x)

#else  // Concepts not supported

#define CONCEPT_ASSERT(x)
#define CONCEPT_REQUIRES(x)

// One-argument C++ concepts that are defined by STL2
#define BidirectionalIterator          typename
#define Boolean                        typename
#define Constructible                  typename
#define Copyable                       typename
#define CopyConstructible              typename
#define DefaultConstructible           typename
#define EqualityComparable             typename
#define ForwardIterator                typename
#define InputIterator                  typename
#define Integral                       typename
#define Iterator                       typename
#define Movable                        typename
#define MoveConstructible              typename
#define OutputIterator                 typename
#define RandomAccessIterator           typename
#define Range                          typename
#define Readable                       typename
#define Regular                        typename
#define Semiregular                    typename
#define StrictTotallyOrdered           typename
#define Swappable                      typename

// A few more useful C++ concepts
#define ContextuallyConvertibleToBool  typename
#define EuclideanDomain                typename
#define Integer                        typename
#define Semiring                       typename
#define Ring                           typename

#endif // End of concepts-related definitions

#endif // CONCEPTS_H
