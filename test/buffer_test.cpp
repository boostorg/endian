//  buffer_test.cpp  -------------------------------------------------------------------//

//  Copyright Beman Dawes 2014

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

//--------------------------------------------------------------------------------------//

#include <boost/endian/detail/disable_warnings.hpp>

#define BOOST_ENDIAN_LOG
#include <boost/endian/buffers.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

namespace bel = boost::endian;
using std::cout;
using std::endl;


int cpp_main(int, char *[])
{
  cout << "byte swap intrinsics: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

  cout << "  construct big endian aligned" << endl;
  bel::big_int32_buf_t x(1122334455);

  cout << "  assign to buffer from built-in integer" << endl;
  x = 1234567890;

  cout << "  operator==(buffer.value(), built-in)" << endl;
  bool b1(x.value() == 1234567890);
  BOOST_TEST(b1);

  cout << "  construct little endian unaligned" << endl;
  bel::little_int32_buf_ut x2(1122334455);

  cout << "  assign to buffer from built-in integer" << endl;
  x2 = 1234567890;

  cout << "  operator==(buffer.value(), built-in)" << endl;
  bool b2(x2.value() == 1234567890);
  BOOST_TEST(b2);

  cout << "  done" << endl;

  return ::boost::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
