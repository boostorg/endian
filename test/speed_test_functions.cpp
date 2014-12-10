//  speed_test_functions.cpp  ----------------------------------------------------------//
                                                      
//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

//  These functions are in a separate compilation unit partially to defeat optimizers
//  and partially to create a worst case scenario. They are in a user namespace for
//  realism.

//--------------------------------------------------------------------------------------//

#define _SCL_SECURE_NO_WARNINGS

#include "speed_test_functions.hpp"

namespace user
{

  int16_t return_x_big_int16(int16_t x, big_int16_ut) BOOST_NOEXCEPT { return x; }
  int16_t return_x_little_int16(int16_t x, little_int16_ut) BOOST_NOEXCEPT { return x; }
  int16_t return_x_value_big_int16(int16_t x, big_int16_ut) BOOST_NOEXCEPT
  {
    return conditional_reverse<order::native, order::big>(x);
  }
  int16_t return_x_value_little_int16(int16_t x, little_int16_ut) BOOST_NOEXCEPT
  {
    return conditional_reverse<order::native, order::little>(x);
  }
  int16_t return_x_in_place_big_int16(int16_t x, big_int16_ut) BOOST_NOEXCEPT
  {
    conditional_reverse_in_place<order::native, order::big>(x); return x;
  }
  int16_t return_x_in_place_little_int16(int16_t x, little_int16_ut) BOOST_NOEXCEPT
  {
    conditional_reverse_in_place<order::native, order::little>(x); return x;
  }
  int16_t return_y_big_int16(int16_t x, big_int16_ut y) BOOST_NOEXCEPT { return y; }
  int16_t return_y_little_int16(int16_t x, little_int16_ut y) BOOST_NOEXCEPT { return y; }

  int32_t return_x_big_int32(int32_t x, big_int32_ut) BOOST_NOEXCEPT { return x; }
  int32_t return_x_little_int32(int32_t x, little_int32_ut) BOOST_NOEXCEPT { return x; }
  int32_t return_x_value_big_int32(int32_t x, big_int32_ut) BOOST_NOEXCEPT
  {
    return conditional_reverse<order::native, order::big>(x);
  }
  int32_t return_x_value_little_int32(int32_t x, little_int32_ut) BOOST_NOEXCEPT
  {
    return conditional_reverse<order::native, order::little>(x);
  }
  int32_t return_x_in_place_big_int32(int32_t x, big_int32_ut) BOOST_NOEXCEPT
  {
    conditional_reverse_in_place<order::native, order::big>(x); return x;
  }
  int32_t return_x_in_place_little_int32(int32_t x, little_int32_ut) BOOST_NOEXCEPT
  {
    conditional_reverse_in_place<order::native, order::little>(x); return x;
  }
  int32_t return_y_big_int32(int32_t x, big_int32_ut y) BOOST_NOEXCEPT { return y; }
  int32_t return_y_little_int32(int32_t x, little_int32_ut y) BOOST_NOEXCEPT { return y; }

  int64_t return_x_big_int64(int64_t x, big_int64_ut) BOOST_NOEXCEPT { return x; }
  int64_t return_x_little_int64(int64_t x, little_int64_ut) BOOST_NOEXCEPT { return x; }
  int64_t return_x_value_big_int64(int64_t x, big_int64_ut) BOOST_NOEXCEPT
  {
    return conditional_reverse<order::native, order::big>(x);
  }
  int64_t return_x_value_little_int64(int64_t x, little_int64_ut) BOOST_NOEXCEPT
  {
    return conditional_reverse<order::native, order::little>(x);
  }
  int64_t return_x_in_place_big_int64(int64_t x, big_int64_ut) BOOST_NOEXCEPT
  {
    conditional_reverse_in_place<order::native, order::big>(x); return x;
  }
  int64_t return_x_in_place_little_int64(int64_t x, little_int64_ut) BOOST_NOEXCEPT
  {
    conditional_reverse_in_place<order::native, order::little>(x); return x;
  }
  int64_t return_y_big_int64(int64_t x, big_int64_ut y) BOOST_NOEXCEPT { return y; }
  int64_t return_y_little_int64(int64_t x, little_int64_ut y) BOOST_NOEXCEPT { return y; }

}
