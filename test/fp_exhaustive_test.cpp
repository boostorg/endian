//  fp_exhaustive_test.cpp  ------------------------------------------------------------//

//  Copyright Beman Dawes 2015

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

//--------------------------------------------------------------------------------------//

#include <boost/endian/detail/disable_warnings.hpp>

//#define BOOST_ENDIAN_LOG
#include <boost/endian/conversion.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/endian/detail/lightweight_test.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <limits>
#include <climits>
#include <cstring>

using namespace boost::endian;
using std::cout;
using std::endl;
using std::hex;
using std::dec;
using std::numeric_limits;


namespace
{
} // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int, char *[])
{
#ifdef BOOST_BIG_ENDIAN
  cout << "platform is big endian\n";
#else
  cout << "platform is little endian\n";
#endif
  cout << "byte swap intrinsics: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

#ifdef BOOST_NO_CXX11_NUMERIC_LIMITS
  cout << "BOOST_NO_CXX11_NUMERIC_LIMITS is defined" << endl;
#endif
 
  cout << "Iterations: " << endl;

  uint32_t i = 0;
  do
  {
    if (i % 1000000 == 0)
      cout << i << endl;

    float x = *reinterpret_cast<const float*>(&i);
    float rtx = endian_reverse(endian_reverse(x));
    if (!BOOST_TEST_MEM_EQ(x, rtx))
    {
      float erx = endian_reverse(x);
      cout << "i = 0X" << detail::to_hex(i) << "\n";
      cout << "x = 0X" << detail::to_hex(x) << "\n";
      cout << "erx = 0X" << detail::to_hex(erx) << "\n";
      cout << "rtx = 0X" << detail::to_hex(rtx) << "\n";
      //cout << "i = " << i << " [0X" << hex << i << dec << "], or "
      //  << *reinterpret_cast<const float*>(&i) << " as float\n"
      //  "but endian_reverse(endian_reverse()) round-trip yields "
      //  << endian_reverse(endian_reverse(*reinterpret_cast<const float*>(&i))) << "\n"
      //  ;
//      erx = endian_reverse(x);
      break;
    }
    ++i;
  } while (i != 0);

  cout << "\n  done" << endl;

  return ::boost::endian::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
