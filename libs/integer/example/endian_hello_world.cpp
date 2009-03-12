//  endian_io_test.cpp  ----------------------------------------------------------------//

//  Copyright Beman Dawes, 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

#include <boost/integer/endian_io.hpp>
#include <iostream>

using namespace boost;
using namespace boost::integer;

int main()
{
  long        value = 3224115L; // integer value of ASCII { '1', '2', '3' }
  big24_t     big( value );
  little24_t  little( value );

  std::cout << "Hello, endian world "<< value << ' ' << big << ' ' << little << '\n';
}

