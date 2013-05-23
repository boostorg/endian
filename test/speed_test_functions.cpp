//  speed_test_functions.cpp  ----------------------------------------------------------//

//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

//  These functions are in a separate compilation unit partially to defeat optimizers
//  and partially to create a worst case scenario. They are in a user namespace for
//  realism.

//--------------------------------------------------------------------------------------//

#include "speed_test_functions.hpp"

namespace user
{

  int32_t return_x_big_int32(int32_t x, int32_t, big_int32_t) BOOST_NOEXCEPT {return x;}
  int32_t return_x_little_int32(int32_t x, int32_t, little_int32_t) BOOST_NOEXCEPT {return x;}

  int32_t return_x_plus_y_big_int32(int32_t x, int32_t y, big_int32_t) BOOST_NOEXCEPT {return x+y;}
  int32_t return_x_plus_y_little_int32(int32_t x, int32_t y, little_int32_t) BOOST_NOEXCEPT {return x+y;}

  int32_t return_x_plus_y_value_big_int32(int32_t x, int32_t y, big_int32_t) BOOST_NOEXCEPT {return x+big_endian_value(y);}
  int32_t return_x_plus_y_value_little_int32(int32_t x, int32_t y, little_int32_t) BOOST_NOEXCEPT {return x+little_endian_value(y);}

  int32_t return_x_plus_y_in_place_big_int32(int32_t x, int32_t y, big_int32_t) BOOST_NOEXCEPT {big_endian(y);return x+y;}
  int32_t return_x_plus_y_in_place_little_int32(int32_t x, int32_t y, little_int32_t) BOOST_NOEXCEPT {little_endian(y);return x+y;}

  int32_t return_x_plus_z_big_int32(int32_t x, int32_t, big_int32_t z) BOOST_NOEXCEPT {return x+z;}
  int32_t return_x_plus_z_little_int32(int32_t x, int32_t, little_int32_t z) BOOST_NOEXCEPT {return x+z;}

}
