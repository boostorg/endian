//  endian_in_union_test.cpp  -------------------------------------------------//

//  Copyright Beman Dawes 2008

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/endian

//----------------------------------------------------------------------------//

#define BOOST_ENDIAN_FORCE_PODNESS

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/arithmetic.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <cassert>

using namespace boost::endian;

union U
{
  big_int8_ut           big_8;
  big_int16_ut          big_16;
  big_int24_ut          big_24;
  big_int32_ut          big_32;
  big_int40_ut          big_40;
  big_int48_ut          big_48;
  big_int56_ut          big_56;
  big_int64_ut          big_64;
                   
  big_uint8_ut          big_u8;
  big_uint16_ut         big_u16;
  big_uint24_ut         big_u24;
  big_uint32_ut         big_u32;
  big_uint40_ut         big_u40;
  big_uint48_ut         big_u48;
  big_uint56_ut         big_u56;
  big_uint64_ut         big_u64;
                   
  little_int8_ut        little_8;
  little_int16_ut       little_16;
  little_int24_ut       little_24;
  little_int32_ut       little_32;
  little_int40_ut       little_40;
  little_int48_ut       little_48;
  little_int56_ut       little_56;
  little_int64_ut       little_64;
                   
  little_uint8_ut       little_u8;
  little_uint16_ut      little_u16;
  little_uint24_ut      little_u24;
  little_uint32_ut      little_u32;
  little_uint40_ut      little_u40;
  little_uint48_ut      little_u48;
  little_uint56_ut      little_u56;
  little_uint64_ut      little_u64;
                   
  native_int8_ut        native_8;
  native_int16_ut       native_16;
  native_int24_ut       native_24;
  native_int32_ut       native_32;
  native_int40_ut       native_40;
  native_int48_ut       native_48;
  native_int56_ut       native_56;
  native_int64_ut       native_64;
                   
  native_uint8_ut       native_u8;
  native_uint16_ut      native_u16;
  native_uint24_ut      native_u24;
  native_uint32_ut      native_u32;
  native_uint40_ut      native_u40;
  native_uint48_ut      native_u48;
  native_uint56_ut      native_u56;
  native_uint64_ut      native_u64;
};

U foo;

int cpp_main(int, char * [])
{

  return 0;
}

