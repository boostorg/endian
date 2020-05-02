#ifndef BOOST_ENDIAN_DETAIL_IS_FIXED_ENUM_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_IS_FIXED_ENUM_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/endian/detail/is_scoped_enum.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/config.hpp>

namespace boost
{
namespace endian
{
namespace detail
{

#if __cplusplus >= 201703L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)

// Thanks to Will Wray for the T{0} idea, which unfortunately only works in C++17+
//
// VS2017 works, VS2019 works from 19.20 to 19.22, then in 19.23 starts accepting
// T{0} for unscoped non-fixed enums as well. Sad!

template<class T, class E = T> struct is_fixed_enum_impl: boost::false_type
{
};

template<class T> struct is_fixed_enum_impl<T, decltype(T{0})>: boost::is_enum<T>
{
};

template<class T> struct is_fixed_enum: is_fixed_enum_impl< boost::remove_cv_t<T> >
{
};

#else

template<class T> struct is_fixed_enum: is_scoped_enum<T>
{
};

#endif

} // namespace detail
} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_IS_FIXED_ENUM_HPP_INCLUDED
