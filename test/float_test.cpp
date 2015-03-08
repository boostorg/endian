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
#include <iomanip>
#include <sstream>

using namespace boost::endian;
using std::cout;
using std::endl;
using std::hex;
using std::dec;
using std::numeric_limits;


namespace
{
  std::string to_hex(const float& x)
  {
    std::stringstream stream;
    stream << "0x"
      << std::setfill('0') << std::setw(sizeof(float) * 2)
      << std::hex << *reinterpret_cast<const uint32_t*>(&x);
    return stream.str();
  }

  std::string to_hex(const double& x)
  {
    std::stringstream stream;
    stream << "0x"
      << std::setfill('0') << std::setw(sizeof(double) * 2)
      << std::hex << *reinterpret_cast<const uint64_t*>(&x);
    return stream.str();
  }

  template <class T>
  void show_value(const char* desc, const T& value)
  {
    cout << "  " << desc << " " << value 
      << ", big " << to_hex(native_to_big(value))
      << ", little " << to_hex(native_to_little(value)) << "\n";
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
    cout << "  max_digits10 " << numeric_limits<T>::max_digits10 << "\n";
    cout << "  radix " << numeric_limits<T>::radix << "\n";
    cout << "  min_exponent " << numeric_limits<T>::min_exponent << "\n";
    cout << "  min_exponent10 " << numeric_limits<T>::min_exponent10 << "\n";
    cout << "  max_exponent " << numeric_limits<T>::max_exponent << "\n";
    cout << "  max_exponent10 " << numeric_limits<T>::max_exponent10 << "\n";
    //cout << "  min() " << numeric_limits<T>::min() << ", " << to_hex(numeric_limits<T>::min()) << "\n";
    //cout << "  max() " << numeric_limits<T>::max() << "\n";
    //cout << "  lowest() " << numeric_limits<T>::lowest() << "\n";
    //cout << "  epsilon() " << numeric_limits<T>::epsilon() << "\n";
    //cout << "  round_error() " << numeric_limits<T>::round_error() << "\n";
    //cout << "  infinity() " << numeric_limits<T>::infinity() << "\n";
    //cout << "  quiet_NaN() " << numeric_limits<T>::quiet_NaN() << "\n";
    //cout << "  signaling_NaN() " << numeric_limits<T>::signaling_NaN() << "\n";
    //cout << "  denorm_min() " << numeric_limits<T>::denorm_min() << "\n";
    show_value("min()", numeric_limits<T>::min());
    show_value("max()", numeric_limits<T>::max());
    show_value("lowest()", numeric_limits<T>::lowest());
    show_value("epsilon()", numeric_limits<T>::epsilon());
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
    BOOST_TEST_MEM_EQ(endian_reverse(endian_reverse(numeric_limits<T>::lowest())),
      numeric_limits<T>::lowest());
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
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::min()), 0x00008000);
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::min()), 0x00800000);
  }

  void double_value_test()
  {
    cout << "double value test..." << endl;
    BOOST_TEST_MEM_EQ(native_to_big(numeric_limits<float>::min()), 0x0000000000001000);
    BOOST_TEST_MEM_EQ(native_to_little(numeric_limits<float>::min()), 0x0010000000000000);
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
