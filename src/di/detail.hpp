#ifndef LIB_DI_DETAIL_HPP
#define LIB_DI_DETAIL_HPP

#include <tuple>

namespace di {

namespace detail_ {

template <size_t N, typename... Args>
struct NthType;

template <size_t N, typename... Args>
using nth_type_t = typename NthType<N, Args...>::type;

template <size_t N, typename... Args>
struct NthTypeImpl;

template <size_t N, typename... Args>
struct NthType<N, std::tuple<Args...>> { using type = typename NthTypeImpl<N, Args...>::type; };

template <typename Arg, typename... Args>
struct NthTypeImpl<0, Arg, Args...> { using type = Arg; };

template <size_t N, typename Arg, typename... Args>
struct NthTypeImpl<N, Arg, Args...> { using type = typename NthTypeImpl<N - 1, Args...>::type; };

}  // namespace detail_

}  // namespace di

#endif  // LIB_DI_DETAIL_HPP
