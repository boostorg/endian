//  floating_point_test.cpp  -----------------------------------------------------------//

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

using namespace boost::endian;
using std::cout;
using std::endl;
using std::hex;
using std::dec;
using std::numeric_limits;


namespace
{
  // to_big() and to_little() provide convenient independent functions for
  // creating test values of known endianness.

  template <class T>
  T to_big(T x)
  {
# ifdef BOOST_LITTLE_ENDIAN
    std::reverse(reinterpret_cast<char*>(&x), reinterpret_cast<char*>(&x) + sizeof(T));
# endif
    return x;
  }

  template <class T>
  T to_little(T x)
  {
# ifdef BOOST_BIG_ENDIAN
    std::reverse(reinterpret_cast<char*>(&x), reinterpret_cast<char*>(&x) + sizeof(T));
# endif
    return x;
  }


  template <class T>
  std::string to_hex(const T& x)
  {
    const char hex[] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
    std::string tmp;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&x);
    const unsigned char* e = p + sizeof(T);

    for (; p < e; ++p)
    {
      tmp += hex[*p >> 4];    // high-order nibble
      tmp += hex[*p & 0x0f];  // low-order nibble
    }
    return tmp;
  }

  template <class T>
  void show_value(const char* desc, const T& value)
  {
    cout << "  " << desc << " " << value 
      << ", native 0x" << to_hex(value)
      << ", big 0x" << to_hex(native_to_big(value))
      << ", little 0x" << to_hex(native_to_little(value)) << "\n";
  }

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
    cout << "  digits " << numeric_limits<T>::digits << "\n";
    cout << "  digits10 " << numeric_limits<T>::digits10 << "\n";
//    cout << "  max_digits10 " << numeric_limits<T>::max_digits10 << "\n";
    cout << "  radix " << numeric_limits<T>::radix << "\n";
    cout << "  min_exponent " << numeric_limits<T>::min_exponent << "\n";
    cout << "  min_exponent10 " << numeric_limits<T>::min_exponent10 << "\n";
    cout << "  max_exponent " << numeric_limits<T>::max_exponent << "\n";
    cout << "  max_exponent10 " << numeric_limits<T>::max_exponent10 << "\n";
    show_value("min()", numeric_limits<T>::min());
    show_value("max()", numeric_limits<T>::max());
//    show_value("lowest()", numeric_limits<T>::lowest());
//    show_value("epsilon()", numeric_limits<T>::epsilon());
    show_value("round_error()", numeric_limits<T>::round_error());
    show_value("infinity()", numeric_limits<T>::infinity());
    show_value("-infinity()", -numeric_limits<T>::infinity());
    show_value("quiet_NaN()", numeric_limits<T>::quiet_NaN());
    show_value("signaling_NaN()", numeric_limits<T>::signaling_NaN());
    show_value("denorm_min()", numeric_limits<T>::denorm_min());
    show_value("0.0", static_cast<T>(0.0));
    show_value("1.0", static_cast<T>(1.0));
  }

  template <class T>
  void round_trip_test(const char* type)
  {
    cout << type << " round trip test..." << endl;
    BOOST_TEST_MEM_EQ(static_cast<T>(1.0), static_cast<T>(1.0));  // reality check
    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::min())),
      numeric_limits<T>::min());
    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::max())),
      numeric_limits<T>::max());
//    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::lowest())),
//      numeric_limits<T>::lowest());
    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::epsilon())),
      numeric_limits<T>::epsilon());
    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::round_error())),
      numeric_limits<T>::round_error());
    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::infinity())),
      numeric_limits<T>::infinity());
    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::quiet_NaN())),
      numeric_limits<T>::quiet_NaN());
    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::signaling_NaN())),
      numeric_limits<T>::signaling_NaN());
    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::denorm_min())),
      numeric_limits<T>::denorm_min());
  }

  void float_value_test()
  {
    cout << "float value test..." << endl;
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::min()), to_big(0x00800000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::min()), to_little(0x00800000));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::max()), to_big(0x7f7fffff));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::max()), to_little(0x7f7fffff));
//    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::lowest()), to_big(0xff7fffff));
//    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::lowest()), to_little(0xff7fffff));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::epsilon()), to_big(0x34000000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::epsilon()), to_little(0x34000000));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::round_error()), to_big(0x3f000000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::round_error()), to_little(0x3f000000));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::infinity()), to_big(0x7f800000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::infinity()), to_little(0x7f800000));
    BOOST_TEST_MEM_EQ(native_to_big(-numeric_limits<float>::infinity()), to_big(0xff800000));
    BOOST_TEST_MEM_EQ(native_to_little(-numeric_limits<float>::infinity()), to_little(0xff800000));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::quiet_NaN()), to_big(0x7fc00000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::quiet_NaN()), to_little(0x7fc00000));
//    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::signaling_NaN()), to_big(0x7fc00001));
//    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::signaling_NaN()), to_little(0x7fc00001));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::denorm_min()), to_big(0x00000001));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::denorm_min()), to_little(0x00000001));
    BOOST_TEST_MEM_EQ(native_to_big(0.0f), to_big(0x00000000));
    BOOST_TEST_MEM_EQ(native_to_little(0.0f), to_little(0x00000000));
    BOOST_TEST_MEM_EQ(native_to_big(1.0f), to_big(0x3f800000));
    BOOST_TEST_MEM_EQ(native_to_little(1.0f), to_little(0x3f800000));
  }

  void double_value_test()
  {
    cout << "double value test..." << endl;
    BOOST_TEST_MEM_EQ(to_big(numeric_limits<double>::min()), to_big(0x0010000000000000));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<double>::min()), to_big(0x0010000000000000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<double>::min()), to_little(0x0010000000000000));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<double>::max()), to_big(0x7fefffffffffffff)); 
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<double>::max()), to_little(0x7fefffffffffffff));
//    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<double>::lowest()), to_big(0xffefffffffffffff));
//    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<double>::lowest()), to_little(0xffefffffffffffff));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<double>::epsilon()), to_big(0x3cb0000000000000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<double>::epsilon()), to_little(0x3cb0000000000000));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<double>::round_error()), to_big(0x3fe0000000000000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<double>::round_error()), to_little(0x3fe0000000000000));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<double>::infinity()), to_big(0x7ff0000000000000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<double>::infinity()), to_little(0x7ff0000000000000));
    BOOST_TEST_MEM_EQ(native_to_big(-numeric_limits<double>::infinity()), to_big(0xfff0000000000000));
    BOOST_TEST_MEM_EQ(native_to_little(-numeric_limits<double>::infinity()), to_little(0xfff0000000000000));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<double>::quiet_NaN()), to_big(0x7ff8000000000000));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<double>::quiet_NaN()), to_little(0x7ff8000000000000));
//    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<double>::signaling_NaN()), to_big(0x7ff8000000000001));
//    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<double>::signaling_NaN()), to_little(0x7ff8000000000001));
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<double>::denorm_min()), to_big(0x0000000000000001ULL));
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<double>::denorm_min()), to_little(0x0000000000000001ULL));
    BOOST_TEST_MEM_EQ(native_to_big(0.0), to_big(0x0000000000000000ULL));
    BOOST_TEST_MEM_EQ(native_to_little(0.0), to_little(0x0000000000000000ULL));
    BOOST_TEST_MEM_EQ(native_to_big(1.0), to_big(0x3ff0000000000000ULL));
    BOOST_TEST_MEM_EQ(native_to_little(1.0), to_little(0x3ff0000000000000ULL));
  }

}  // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int, char *[])
{
  cout << "byte swap intrinsics: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

//#define BOOST_ENDIAN_FORCE_ERROR
#ifdef BOOST_ENDIAN_FORCE_ERROR
  BOOST_TEST_MEM_EQ(1.0f, 1.0);
  BOOST_TEST_MEM_EQ(1.0f, 1.1f);
  BOOST_TEST_MEM_EQ(1.0, 1.1);
#endif

  report_limits<float>("float");
  float_value_test();
  round_trip_test<float>("float");

  report_limits<double>("double");
  double_value_test();
  round_trip_test<double>("double");

  cout << "\n  done" << endl;

  return ::boost::endian::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
