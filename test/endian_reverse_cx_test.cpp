// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/endian/conversion.hpp>
#include <boost/config/pragma_message.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>

#if defined(BOOST_NO_CXX11_CONSTEXPR)

BOOST_PRAGMA_MESSAGE("Test skipped because BOOST_NO_CXX11_CONSTEXPR is defined")

#elif defined(BOOST_ENDIAN_NO_INTRINSICS) && defined(BOOST_NO_CXX14_CONSTEXPR)

BOOST_PRAGMA_MESSAGE("Test skipped because BOOST_ENDIAN_NO_INTRINSICS and BOOST_NO_CXX14_CONSTEXPR are defined")

#else

using namespace boost::endian;

#define STATIC_ASSERT(expr) static_assert(expr, #expr)

STATIC_ASSERT( endian_reverse( static_cast<boost::uint8_t>( 0x01 ) ) == 0x01 );
STATIC_ASSERT( endian_reverse( static_cast<boost::uint16_t>( 0x0102 ) ) == 0x0201 );
STATIC_ASSERT( endian_reverse( static_cast<boost::uint32_t>( 0x01020304 ) ) == 0x04030201 );
STATIC_ASSERT( endian_reverse( static_cast<boost::uint64_t>( 0x0102030405060708 ) ) == 0x0807060504030201 );

#endif
