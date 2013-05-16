//  endian/detail/intrinsic.hpp  -------------------------------------------------------//

//  Copyright (C) 2012 David Stone
//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_INTRINSIC_HPP
#define BOOST_ENDIAN_INTRINSIC_HPP

#ifndef __has_builtin         // Optional of course
  #define __has_builtin(x) 0  // Compatibility with non-clang compilers
#endif

#if (defined(__clang__) && __has_builtin(__builtin_bswap16)) \
  || (defined(__GNUC__ ) && \
  (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)))
# define BOOST_ENDIAN_INTRINSIC_MSG "__builtin_bswap16, etc."

// prior to 4.8, gcc did not provide __builtin_bswap16 on some platforms so we emulate it
// see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=52624
# if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
#   define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x) __builtin_bswap16(x)
# else
#   define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x) __builtin_bswap32((x) << 16)
# endif

# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(x) __builtin_bswap32(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x) __builtin_bswap64(x)

#elif ((defined __GNUC__ && !defined(__MINGW32__)) || defined(__clang__))
# define BOOST_ENDIAN_INTRINSIC_MSG "__builtin_bswap_16, etc."
# include <byteswap.h>
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x) bswap_16(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(x) bswap_32(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x) bswap_64(x)

#elif defined _MSC_VER
//  Microsoft documents these as being compatible since Windows 95 and specificly
//  lists runtime library support since Visual Studio 2003 (aka 7.1).
# define BOOST_ENDIAN_INTRINSIC_MSG "_byteswap_ushort, etc."
# include <cstdlib>
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x) _byteswap_ushort(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(x) _byteswap_ulong(x)
# define BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x) _byteswap_uint64(x)
#else
# define BOOST_ENDIAN_NO_INTRINSICS
# define BOOST_ENDIAN_INTRINSIC_MSG "no byte swap intrinsics"
#endif

#endif // BOOST_ENDIAN_INTRINSIC_HPP
