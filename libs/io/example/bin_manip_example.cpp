//  binary_stream_example.cpp  ---------------------------------------------------------//

//  Copyright Beman Dawes 2011

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/io/detail/bin_manip.hpp>
#include <boost/integer.hpp>
#include <boost/assert.hpp>
#include <fstream>

using namespace boost;
using namespace std;

int main()
{
  fstream f("binary_stream_example.dat",
    std::ios_base::trunc | std::ios_base::in | std::ios_base::out | std::ios_base::binary);

  int32_t x = 0x01020304;
  int32_t y = 0;

  f << bin(x);
  f.seekg(0);
  f >> bin(y);
  BOOST_ASSERT(x == y);

  return 0;
}
