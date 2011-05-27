//  endian_io_test.cpp  ----------------------------------------------------------------//

//  Copyright Beman Dawes, 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/types.hpp>
#include <boost/io/detail/bin_manip.hpp>
#include <iostream>

using namespace boost;
using namespace boost::endian;

int main()
{
  int_least32_t v = 0x31323334L;  // = ASCII { '1', '2', '3', '4' }
                                  // value chosen to work on text stream
  big32_t    b(v);
  little32_t l(v);

  std::cout << std::hex << "Hello, endian world!\n\n";

  std::cout << "hex stream output: int_least32_t=" << v
            << ", big32_t=" << b << ", little32_t=" << l << '\n';
  std::cout << "bin stream output: int_least32_t=" << bin(v) 
            << ", big32_t=" << bin(b) << ", little32_t=" << bin(l) << '\n';
}

// Output on a little endian machine:
//
//   Hello, endian world!
//  
//   hex stream output: int_least32_t=31323334, big32_t=31323334, little32_t=31323334
//   bin stream output: int_least32_t=4321, big32_t=1234, little32_t=4321
