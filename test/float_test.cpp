//  float_test.cpp  --------------------------------------------------------------------//

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
#include <sstream>

using namespace boost::endian;
using std::cout;
using std::endl;
using std::numeric_limits;


namespace
{
  template <class T>
  void report_limits(const char* type)
  {
    cout << "\nHeader <limits> values for std::numeric_limits<" << type << ">\n\n";
    cout << "  is_specialized " << numeric_limits<T>::is_specialized << "\n";
    cout << "  is_signed " << numeric_limits<T>::is_signed << "\n";
    cout << "  is_integer " << numeric_limits<T>::is_integer << "\n";
    cout << "  is_exact " << numeric_limits<T>::is_exact << "\n";
    cout << "  is_iec559 " << numeric_limits<T>::is_iec559 << "\n";
    cout << "  is_bounded " << numeric_limits<T>::is_bounded << "\n";
    cout << "  is_modulo " << numeric_limits<T>::is_modulo << "\n";
    cout << "  traps " << numeric_limits<T>::traps << "\n";
    cout << "  tinyness_before " << numeric_limits<T>::tinyness_before << "\n";
    cout << "  round_style " << numeric_limits<T>::round_style << "\n";
    cout << "  has_infinity " << numeric_limits<T>::has_infinity << "\n";
    cout << "  has_quiet_NaN " << numeric_limits<T>::has_quiet_NaN << "\n";
    cout << "  has_signaling_NaN " << numeric_limits<T>::has_signaling_NaN << "\n";
    cout << "  has_denorm " << numeric_limits<T>::has_denorm << "\n";
    cout << "  min() " << numeric_limits<T>::min() << "\n";
    cout << "  max() " << numeric_limits<T>::max() << "\n";
    cout << "  lowest() " << numeric_limits<T>::lowest() << "\n";
    cout << "  digits " << numeric_limits<T>::digits << "\n";
    cout << "  digits10 " << numeric_limits<T>::digits10 << "\n";
    cout << "  max_digits10 " << numeric_limits<T>::max_digits10 << "\n";
    cout << "  radix " << numeric_limits<T>::radix << "\n";
    cout << "  epsilon() " << numeric_limits<T>::epsilon() << "\n";
    cout << "  round_error() " << numeric_limits<T>::round_error() << "\n";
    cout << "  min_exponent " << numeric_limits<T>::min_exponent << "\n";
    cout << "  min_exponent10 " << numeric_limits<T>::min_exponent10 << "\n";
    cout << "  max_exponent " << numeric_limits<T>::max_exponent << "\n";
    cout << "  max_exponent10 " << numeric_limits<T>::max_exponent10 << "\n";
    cout << "  infinity() " << numeric_limits<T>::infinity() << "\n";
    cout << "  quiet_NaN() " << numeric_limits<T>::quiet_NaN() << "\n";
    cout << "  signaling_NaN() " << numeric_limits<T>::signaling_NaN() << "\n";
    cout << "  denorm_min() " << numeric_limits<T>::denorm_min() << "\n";
  }

  template <class T>
  void round_trip_test(const char* type)
  {
    BOOST_TEST_MEMCMP_EQ(static_cast<T>(1.0), static_cast<T>(1.0));  // reality check
    BOOST_TEST_MEMCMP_EQ(endian_reverse(endian_reverse(numeric_limits<T>::min())),
      numeric_limits<T>::min());
    BOOST_TEST_MEMCMP_EQ(endian_reverse(endian_reverse(numeric_limits<T>::max())),
      numeric_limits<T>::max());
    BOOST_TEST_MEMCMP_EQ(endian_reverse(endian_reverse(numeric_limits<T>::lowest())),
      numeric_limits<T>::lowest());
    BOOST_TEST_MEMCMP_EQ(endian_reverse(endian_reverse(numeric_limits<T>::epsilon())),
      numeric_limits<T>::epsilon());
    BOOST_TEST_MEMCMP_EQ(endian_reverse(endian_reverse(numeric_limits<T>::round_error())),
      numeric_limits<T>::round_error());
    BOOST_TEST_MEMCMP_EQ(endian_reverse(endian_reverse(numeric_limits<T>::infinity())),
      numeric_limits<T>::infinity());
    BOOST_TEST_MEMCMP_EQ(endian_reverse(endian_reverse(numeric_limits<T>::quiet_NaN())),
      numeric_limits<T>::quiet_NaN());
    BOOST_TEST_MEMCMP_EQ(endian_reverse(endian_reverse(numeric_limits<T>::signaling_NaN())),
      numeric_limits<T>::signaling_NaN());
    BOOST_TEST_MEMCMP_EQ(endian_reverse(endian_reverse(numeric_limits<T>::denorm_min())),
      numeric_limits<T>::denorm_min());
  }

}  // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int, char *[])
{
  cout << "byte swap intrinsics: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

//#define BOOST_ENDIAN_FORCE_ERROR
#ifdef BOOST_ENDIAN_FORCE_ERROR
  BOOST_TEST_MEMCMP_EQ(1.0f, 1.0);
  BOOST_TEST_MEMCMP_EQ(1.0f, 1.1f);
  BOOST_TEST_MEMCMP_EQ(1.0, 1.1);
#endif

  report_limits<float>("float");
  round_trip_test<float>("float");

  report_limits<double>("double");
  round_trip_test<double>("double");

  cout << "\n  done" << endl;

  return ::boost::endian::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
