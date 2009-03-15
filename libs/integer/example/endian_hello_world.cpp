//  endian_io_test.cpp  ----------------------------------------------------------------//

//  Copyright Beman Dawes, 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

#include <boost/integer/endian.hpp>
#include <boost/integer/endian_binary_stream.hpp>
#include <iostream>

using namespace boost;
using namespace boost::integer;

int main()
{
  int_least32_t value = 0x313233L;  // = 3224115 = ASCII { '1', '2', '3' }
  big24_t       big( value );       
  little24_t    little( value );

  std::cout << "Hello, endian world!\n";
  std::cout << " cout << value--: " << value  << " sizeof(value): " << sizeof(value)
          << "\n cout << big----: " << big    << " sizeof(big): " << sizeof(big)
          << "\n cout << little-: " << little << " sizeof(little): " << sizeof(little)
          << '\n';
}

