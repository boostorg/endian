//  float_test.cpp  --------------------------------------------------------------------//

//  Copyright Beman Dawes 2015

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

//--------------------------------------------------------------------------------------//

#include <boost/endian/detail/disable_warnings.hpp>

//#define BOOST_ENDIAN_LOG
#include <boost/endian/buffers.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>
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

}  // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int, char *[])
{
  cout << "byte swap intrinsics: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

  report_limits<float>("float");
  report_limits<double>("double");

  cout << "\n  done" << endl;

  return ::boost::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
