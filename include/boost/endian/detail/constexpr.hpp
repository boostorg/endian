#ifndef BOOST_ENDIAN_DETAIL_CONSTEXPR_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_CONSTEXPR_HPP_INCLUDED

// Copyright 2024 Julien Blanc
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#if __cpp_lib_is_constant_evaluated >= 201802L && __cpp_lib_bit_cast >= 201806L
#define BOOST_ENDIAN_CXX20_CONSTEXPR constexpr
#define BOOST_ENDIAN_HAS_CXX20_CONSTEXPR 1
#else
#define BOOST_ENDIAN_CXX20_CONSTEXPR inline
#define BOOST_ENDIAN_HAS_CXX20_CONSTEXPR 0
#endif

#endif  // BOOST_ENDIAN_DETAIL_CONSTEXPR_HPP_INCLUDED
