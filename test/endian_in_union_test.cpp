//  endian_in_union_test.cpp  -------------------------------------------------//

//  Copyright Beman Dawes 2008

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/endian

//----------------------------------------------------------------------------//

#define BOOST_ENDIAN_FORCE_PODNESS

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/types.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <cassert>

using namespace boost::endian;

union U
{
  big_int8_t           big_int8;
  big_int16_t          big_int16;
  big_int24_t          big_int24;
  big_int32_t          big_int32;
  big_int40_t          big_int40;
  big_int48_t          big_int48;
  big_int56_t          big_int56;
  big_int64_t          big_int64;
                   
  big_uint8_t          big_uint8;
  big_uint16_t         big_uint16;
  big_uint24_t         big_uint24;
  big_uint32_t         big_uint32;
  big_uint40_t         big_uint40;
  big_uint48_t         big_uint48;
  big_uint56_t         big_uint56;
  big_uint64_t         big_uint64;
                   
  little_int8_t        little_int8;
  little_int16_t       little_int16;
  little_int24_t       little_int24;
  little_int32_t       little_int32;
  little_int40_t       little_int40;
  little_int48_t       little_int48;
  little_int56_t       little_int56;
  little_int64_t       little_int64;
                   
  little_uint8_t       little_uint8;
  little_uint16_t      little_uint16;
  little_uint24_t      little_uint24;
  little_uint32_t      little_uint32;
  little_uint40_t      little_uint40;
  little_uint48_t      little_uint48;
  little_uint56_t      little_uint56;
  little_uint64_t      little_uint64;
                   
  native_int8_t        native_int8;
  native_int16_t       native_int16;
  native_int24_t       native_int24;
  native_int32_t       native_int32;
  native_int40_t       native_int40;
  native_int48_t       native_int48;
  native_int56_t       native_int56;
  native_int64_t       native_int64;
                   
  native_uint8_t       native_uint8;
  native_uint16_t      native_uint16;
  native_uint24_t      native_uint24;
  native_uint32_t      native_uint32;
  native_uint40_t      native_uint40;
  native_uint48_t      native_uint48;
  native_uint56_t      native_uint56;
  native_uint64_t      native_uint64;
};

U foo;

int cpp_main(int, char * [])
{

  return 0;
}

