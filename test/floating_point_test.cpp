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
#include <boost/array.hpp>
#include <boost/math/constants/constants.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cstring>

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
  struct test_case
  {
    std::string    desc;
    T              value;   // native value and representation
    std::string    big;     // as hex characters; invariant size() == 2*sizeof(T)
    std::string    little;  // as hex characters; invariant size() == 2*sizeof(T)
    // big and little endian expected values are held as strings so representation is
    // independent of platform endianness and readers do not have to perform mental
    // gymnastics to reason about what the expected representation is for a platform.

    const test_case& assign(const std::string& desc_, const T& value_,
      const std::string& big_, const std::string& little_)
    {
      desc = desc_;
      std::memcpy(&value, &value_, sizeof(T));  // use memcpy in case copy assignment or 
                                                // copy construction alters representation
      big = big_;
      little = little_;
      return *this;
    }
  };

  // to_big_inplace() and to_little_inplace() provide convenient independent functions to
  // aid creating test values of known endianness. They do so in place to avoid the
  // possibility that floating point assignment or copy construction modifies the
  // representation, such as for normalization.

  template <class T>
  void to_big_inplace(T& x)
  {
# ifdef BOOST_LITTLE_ENDIAN
    std::reverse(reinterpret_cast<char*>(&x), reinterpret_cast<char*>(&x) + sizeof(T));
# endif
  }

  template <class T>
  void to_little_inplace(T& x)
  {
# ifdef BOOST_BIG_ENDIAN
    std::reverse(reinterpret_cast<char*>(&x), reinterpret_cast<char*>(&x) + sizeof(T));
# endif
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

  const std::size_t n_test_cases = 16;
  boost::array<test_case<float>, n_test_cases> float_test_cases;
  boost::array<test_case<double>, n_test_cases> double_test_cases;

  void build_auto_test_cases()
  {
    using namespace boost::math::constants;
    int i = 0;

//  template for cut-and-paste of new values 
//    float_test_cases[i].assign("", , "", "");
//    double_test_cases[i++].assign("", , "", "");

    float_test_cases[i].assign("numeric_limits<float>::min()",
      numeric_limits<float>::min(), "00800000", "00008000");
    double_test_cases[i++].assign("numeric_limits<double>::min()",
      numeric_limits<double>::min(), "0010000000000000", "0000000000001000");

    float_test_cases[i].assign("numeric_limits<float>::max()",
      numeric_limits<float>::max(), "7f7fffff", "ffff7f7f");
    double_test_cases[i++].assign("numeric_limits<double>::max()",
      numeric_limits<double>::max(), "7fefffffffffffff", "ffffffffffffef7f");

    float_test_cases[i].assign("numeric_limits<float>::lowest()",
      numeric_limits<float>::lowest(), "ff7fffff", "ffff7fff");
    double_test_cases[i++].assign("numeric_limits<double>::lowest()",
      numeric_limits<double>::lowest(), "ffefffffffffffff", "ffffffffffffefff");

    float_test_cases[i].assign("numeric_limits<float>::epsilon()",
      numeric_limits<float>::epsilon(), "34000000", "00000034");
    double_test_cases[i++].assign("numeric_limits<double>::epsilon()",
      numeric_limits<double>::epsilon(), "3cb0000000000000", "000000000000b03c");

    float_test_cases[i].assign("numeric_limits<float>::round_error()",
      numeric_limits<float>::round_error(), "3f000000", "0000003f");
    double_test_cases[i++].assign("numeric_limits<double>::round_error()",
      numeric_limits<double>::round_error(), "3fe0000000000000", "000000000000e03f");

    float_test_cases[i].assign("numeric_limits<float>::infinity()",
      numeric_limits<float>::infinity(), "7f800000", "0000807f");
    double_test_cases[i++].assign("numeric_limits<double>::infinity()",
      numeric_limits<double>::infinity(), "7ff0000000000000", "000000000000f07f");

    float_test_cases[i].assign("-numeric_limits<float>::infinity()",
      -numeric_limits<float>::infinity(), "ff800000", "000080ff");
    double_test_cases[i++].assign("-numeric_limits<double>::infinity()",
      -numeric_limits<double>::infinity(), "fff0000000000000", "000000000000f0ff");

    float_test_cases[i].assign("numeric_limits<float>::quiet_NaN()",
      numeric_limits<float>::quiet_NaN(), "7fc00000", "0000c07f");
    double_test_cases[i++].assign("numeric_limits<double>::quiet_NaN()",
      numeric_limits<double>::quiet_NaN(), "7ff8000000000000", "000000000000f87f");

    float_test_cases[i].assign("numeric_limits<float>::signaling_NaN()",
      numeric_limits<float>::signaling_NaN(), "7fc00001", "0100c07f");
    double_test_cases[i++].assign("numeric_limits<double>::signaling_NaN()",
      numeric_limits<double>::signaling_NaN(), "7ff8000000000001", "010000000000f87f");

    float_test_cases[i].assign("numeric_limits<float>::denorm_min()",
      numeric_limits<float>::denorm_min(), "00000001", "01000000");
    double_test_cases[i++].assign("numeric_limits<double>::denorm_min()",
      numeric_limits<double>::denorm_min(), "0000000000000001", "0100000000000000");

    float_test_cases[i].assign("0.0f", 0.0f, "00000000", "00000000");
    double_test_cases[i++].assign("0.0", 0.0, "0000000000000000", "0000000000000000");

    float_test_cases[i].assign("-0.0f", -0.0f, "80000000", "00000080");
    double_test_cases[i++].assign("-0.0", -0.0, "8000000000000000", "0000000000000080");

    float_test_cases[i].assign("1.0f", 1.0f, "3f800000", "0000803f");
    double_test_cases[i++].assign("1.0", 1.0, "3ff0000000000000", "000000000000f03f");

    float_test_cases[i].assign("-1.0f", -1.0f, "bf800000", "000080bf");
    double_test_cases[i++].assign("-1.0", -1.0, "bff0000000000000", "000000000000f0bf");

    uint32_t vf1 (0x12345678U);
    float_test_cases[i].assign("native uint32_t 0x12345678U as float",
      *reinterpret_cast<const float*>(&vf1), "12345678", "78563412");
    uint64_t vd1 (0x0123456789abcdefULL);
    double_test_cases[i++].assign("native uint64_t 0x0123456789abcdefULL as double",
      *reinterpret_cast<const double*>(&vd1), "0123456789abcdef", "efcdab8967452301");

    float_test_cases[i].assign("pi<float>()",
      pi<float>(), "40490fdb", "db0f4940");
    double_test_cases[i++].assign("pi<double>()",
      pi<double>(), "400921fb54442d18", "182d4454fb210940");

    BOOST_ASSERT(i == n_test_cases);
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
    using namespace boost::math::constants;
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
    show_value("-0.0", static_cast<T>(-0.0));
    show_value("1.0", static_cast<T>(1.0));
    show_value("-1.0", static_cast<T>(-1.0));
    show_value("pi()", pi<T>());
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

template <class T>
void auto_test(const char* msg, const boost::array<test_case<T>, n_test_cases>& cases)
{
  cout << "auto test " << msg << " ..." << endl;

  for (int i = 0; i < n_test_cases; ++i)
  {
    cout << "  " << cases[i].desc << endl;
    BOOST_TEST_EQ(to_hex(native_to_big(cases[i].value)), cases[i].big);
    BOOST_TEST_EQ(to_hex(native_to_little(cases[i].value)), cases[i].little);
  }
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

  build_auto_test_cases();
  auto_test<float>("float", float_test_cases);
  auto_test<double>("double", double_test_cases);

  cout << "\n  done" << endl;

  return ::boost::endian::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
