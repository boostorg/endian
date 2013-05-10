// Copyright (C) 2012 David Stone
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://www.boost.org/libs/endian/ for documentation.

#ifndef BOOST_ENDIAN_INTRINSIC_HPP
#define BOOST_ENDIAN_INTRINSIC_HPP

#ifndef BOOST_DETAIL_ENDIAN_HPP
#  include <boost/detail/endian.hpp>
#endif
#ifndef BOOST_CSTDINT_HPP
#  include <boost/cstdint.hpp>
#endif


#undef BOOST_ENDIAN_NO_INTRINSICS
#undef BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2
#undef BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4
#undef BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8

#if (defined __GNUC__ || defined __clang__)
    #include <byteswap.h>
    #define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2 bswap_16
    #define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4 bswap_32
    #define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8 bswap_64
#elif defined _MSC_VER
    #include <cstdlib>
    #define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2 _byteswap_ushort
    #define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4 _byteswap_ulong
    #define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8 _byteswap_uint64
#else
    #define BOOST_ENDIAN_NO_INTRINSICS
#endif

#endif BOOST_ENDIAN_INTRINSIC_HPP
