//  pair_test.cpp  ---------------------------------------------------------------------//

//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/std_pair.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace boost::endian;
using std::cout;
using std::endl;
using boost::int16_t;
using boost::uint16_t;
using boost::int32_t;
using boost::uint32_t;
using boost::int64_t;
using boost::uint64_t;

namespace
{

  typedef std::pair<int16_t, int32_t> MyPair;

  template <class OS>
  OS& operator<<(OS& os, MyPair my)
  {
    const char* first = reinterpret_cast<const char*>(&my.first);
    const char* second = reinterpret_cast<const char*>(&my.second);

    os << std::hex 
       << int(*first) << ' ' << int(*(first+1)) << ", "
       << int(*second) << ' ' << int(*(second+1)) << ' '
       << int(*(second+2)) << ' ' << int(*(second+3))
       << std::dec << std::endl;
    return os;
  }

}  // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int, char * [])
{
  cout << "pair_test" << endl << endl;

  MyPair x(0x0102, 0x01020304);
  MyPair y(big_endian_value(x));
  MyPair z(little_endian_value(x));

  cout << "native: " << x;
  cout << "   big: " << y;
  cout << "little: " << z << endl;

  big_endian(x);
  cout << "   big: " << x;
  reverse(x);
  little_endian(x);
  cout << "little: " << x << endl;

  convert(x, order::little, order::native);
  y = MyPair(0, 0);
  y = convert_value(x, order::native, order::big);
  z = x;
  little_endian(z);
  cout << "native: " << x;
  cout << "   big: " << y;
  cout << "little: " << z << endl;

  cout << "   big: " << y;
  convert<order::big, order::little>(y);
  cout << "little: " << y << endl;
  convert<order::little, order::big>(y);

  return ::boost::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
