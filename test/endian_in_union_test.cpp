//  endian_in_union_test.cpp  -------------------------------------------------//

//  Copyright Beman Dawes 2008

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/endian

//----------------------------------------------------------------------------//

#define _SCL_SECURE_NO_WARNINGS

#define BOOST_ENDIAN_FORCE_PODNESS

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/types.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <cassert>

using namespace boost::endian;

union U
{
  big_int8un_t           big_8;
  big_int16un_t          big_16;
  big_int24un_t          big_24;
  big_int32un_t          big_32;
  big_int40un_t          big_40;
  big_int48un_t          big_48;
  big_int56un_t          big_56;
  big_int64un_t          big_64;
                   
  big_uint8un_t          big_u8;
  big_uint16un_t         big_u16;
  big_uint24un_t         big_u24;
  big_uint32un_t         big_u32;
  big_uint40un_t         big_u40;
  big_uint48un_t         big_u48;
  big_uint56un_t         big_u56;
  big_uint64un_t         big_u64;
                   
  little_int8un_t        little_8;
  little_int16un_t       little_16;
  little_int24un_t       little_24;
  little_int32un_t       little_32;
  little_int40un_t       little_40;
  little_int48un_t       little_48;
  little_int56un_t       little_56;
  little_int64un_t       little_64;
                   
  little_uint8un_t       little_u8;
  little_uint16un_t      little_u16;
  little_uint24un_t      little_u24;
  little_uint32un_t      little_u32;
  little_uint40un_t      little_u40;
  little_uint48un_t      little_u48;
  little_uint56un_t      little_u56;
  little_uint64un_t      little_u64;
                   
  native_int8un_t        native_8;
  native_int16un_t       native_16;
  native_int24un_t       native_24;
  native_int32un_t       native_32;
  native_int40un_t       native_40;
  native_int48un_t       native_48;
  native_int56un_t       native_56;
  native_int64un_t       native_64;
                   
  native_uint8un_t       native_u8;
  native_uint16un_t      native_u16;
  native_uint24un_t      native_u24;
  native_uint32un_t      native_u32;
  native_uint40un_t      native_u40;
  native_uint48un_t      native_u48;
  native_uint56un_t      native_u56;
  native_uint64un_t      native_u64;
};

U foo;

int cpp_main(int, char * [])
{

  return 0;
}

