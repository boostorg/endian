//  endian/example/uses_cases.cpp  -----------------------------------------------------//

//  Copyright Beman Dawes 2014

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#define _SCL_SECURE_NO_WARNINGS

#include <boost/endian/detail/disable_warnings.hpp>

#define BOOST_ENDIAN_LOG
#include <boost/endian/arithmetic.hpp>
#include <boost/endian/buffers.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

//  Maximize chance of name clashes for testing purposes
using namespace boost::endian;
using namespace std;

using std::cout;
using std::endl;
//using boost::int8_t;
//using boost::uint8_t;
//using boost::int16_t;
//using boost::uint16_t;
//using boost::int32_t;
//using boost::uint32_t;
//using boost::int64_t;
//using boost::uint64_t;

namespace
{
}  // unnamed namespace

int cpp_main(int, char *[])
{
  cout << "byte swap intrinsics: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

  big_int32_t i1(1), i2(2), i3;
  big_buf32_t b1(1), b2(2), b3;

  cout << "endian buffer tests" << endl;
  cout << "compute\n";
  i3 = i1 + 5;
  cout << "test\n";
  BOOST_TEST(i3 == 6);
  cout << "compute\n";
  i3 = i1 + i2;
  cout << "test\n";
  BOOST_TEST(i3 == 3);

  cout << "endian integer tests" << endl;
  cout << "compute\n";
  b3 = b1 + 5;
  cout << "test\n";
  BOOST_TEST(b3 == 6);
  cout << "compute\n";
  b3 = b1 + b2;
  cout << "test\n";
  BOOST_TEST(b3 == 3);




  return ::boost::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
