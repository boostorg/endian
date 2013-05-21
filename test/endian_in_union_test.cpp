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
  big_8_t           big_8;
  big_16_t          big_16;
  big_24_t          big_24;
  big_32_t          big_32;
  big_40_t          big_40;
  big_48_t          big_48;
  big_56_t          big_56;
  big_64_t          big_64;
                   
  big_u8_t          big_u8;
  big_u16_t         big_u16;
  big_u24_t         big_u24;
  big_u32_t         big_u32;
  big_u40_t         big_u40;
  big_u48_t         big_u48;
  big_u56_t         big_u56;
  big_u64_t         big_u64;
                   
  little_8_t        little_8;
  little_16_t       little_16;
  little_24_t       little_24;
  little_32_t       little_32;
  little_40_t       little_40;
  little_48_t       little_48;
  little_56_t       little_56;
  little_64_t       little_64;
                   
  little_u8_t       little_u8;
  little_u16_t      little_u16;
  little_u24_t      little_u24;
  little_u32_t      little_u32;
  little_u40_t      little_u40;
  little_u48_t      little_u48;
  little_u56_t      little_u56;
  little_u64_t      little_u64;
                   
  native_8_t        native_8;
  native_16_t       native_16;
  native_24_t       native_24;
  native_32_t       native_32;
  native_40_t       native_40;
  native_48_t       native_48;
  native_56_t       native_56;
  native_64_t       native_64;
                   
  native_u8_t       native_u8;
  native_u16_t      native_u16;
  native_u24_t      native_u24;
  native_u32_t      native_u32;
  native_u40_t      native_u40;
  native_u48_t      native_u48;
  native_u56_t      native_u56;
  native_u64_t      native_u64;
};

U foo;

int cpp_main(int, char * [])
{

  return 0;
}

