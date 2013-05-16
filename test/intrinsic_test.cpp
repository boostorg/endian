//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#include "intrinsic.hpp"
#include <iostream>
#include <cassert>
#include <cstdint>

int main()
{
  std::cout << "BOOST_ENDIAN_INTRINSIC_MSG: " BOOST_ENDIAN_INTRINSIC_MSG << std::endl;

#ifndef BOOST_ENDIAN_NO_INTRINSICS
  uint16_t x2 = 0x1122U;
  assert(BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x2) == 0x2211U);
  uint32_t x4 = 0x11223344UL;
  assert(BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(x4) == 0x44332211UL);
  uint64_t x8 = 0x1122334455667788U;
  assert(BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x8) == 0x8877665544332211ULL);
#endif
  return 0;
}
