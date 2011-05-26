//  bin_manip_test.cpp  ----------------------------------------------------------------//

//  Copyright Beman Dawes 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/io/detail/bin_manip.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/detail/lightweight_test.hpp>

using namespace boost;
using namespace std;

int main()
{
  std::stringstream ss( std::ios_base::in | std::ios_base::out | std::ios_base::binary );

  short short_1(0x0102), short_2;
  ss.clear();
  ss << bin(short_1);
  ss >> bin(short_2);
  BOOST_TEST( short_1 == short_2 );

  unsigned short ushort_1(0x0102), ushort_2;
  ss.clear();
  ss << bin(ushort_1);
  ss >> bin(ushort_2);
  BOOST_TEST( ushort_1 == ushort_2 );

  int int_1(0x01020304), int_2;
  ss.clear();
  ss << bin(int_1);
  ss >> bin(int_2);
  BOOST_TEST( int_1 == int_2 );

  unsigned int uint_1(0x01020304), uint_2;
  ss.clear();
  ss << bin(uint_1);
  ss >> bin(uint_2);
  BOOST_TEST( uint_1 == uint_2 );

  long long_1(0x01020304L), long_2;
  ss.clear();
  ss << bin(long_1);
  ss >> bin(long_2);
  BOOST_TEST( long_1 == long_2 );

  unsigned long ulong_1(0x01020304UL), ulong_2;
  ss.clear();
  ss << bin(ulong_1);
  ss >> bin(ulong_2);
  BOOST_TEST( ulong_1 == ulong_2 );

  long long long_long_1(0x0102030405060708LL), long_long_2;
  ss.clear();
  ss << bin(long_long_1);
  ss >> bin(long_long_2);
  BOOST_TEST( long_long_1 == long_long_2 );

  unsigned long long ulong_long_1(0x0102030405060708ULL), ulong_long_2;
  ss.clear();
  ss << bin(ulong_long_1);
  ss >> bin(ulong_long_2);
  BOOST_TEST( ulong_long_1 == ulong_long_2 );

  float float_1(1.2F), float_2;
  ss.clear();
  ss << bin(float_1);
  ss >> bin(float_2);
  BOOST_TEST( float_1 == float_2 );

  double double_1(1.2), double_2;
  ss.clear();
  ss << bin(double_1);
  ss >> bin(double_2);
  BOOST_TEST( double_1 == double_2 );

  long double long_double_1(1.2), long_double_2;
  ss.clear();
  ss << bin(long_double_1);
  ss >> bin(long_double_2);
  BOOST_TEST( long_double_1 == long_double_2 );

  char char_1(0x01), char_2;
  ss.clear();
  ss << bin(char_1);
  ss >> bin(char_2);
  BOOST_TEST( char_1 == char_2 );

  signed char schar_1(0x01), schar_2;
  ss.clear();
  ss << bin(schar_1);
  ss >> bin(schar_2);
  BOOST_TEST( schar_1 == schar_2 );

  unsigned char uchar_1(0x01), uchar_2;
  ss.clear();
  ss << bin(uchar_1);
  ss >> bin(uchar_2);
  BOOST_TEST( uchar_1 == uchar_2 );

  wchar_t wchar_t_1(L'1'), wchar_t_2;
  ss.clear();
  ss << bin(wchar_t_1);
  ss >> bin(wchar_t_2);
  BOOST_TEST( wchar_t_1 == wchar_t_2 );

  return ::boost::report_errors();
}
