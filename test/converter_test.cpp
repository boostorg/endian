//  conversion_test.cpp  ---------------------------------------------------------------//

//  Copyright Beman Dawes 2010

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/converters.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

namespace be = boost::endian;
using std::cout;
using std::endl;

namespace
{
  //  values for tests

  void native_value(int16_t& x) {x = static_cast<int16_t>(0xF102U);}
  void native_value(uint16_t& x) {x = static_cast<uint16_t>(0xF102U);}
# ifdef BOOST_BIG_ENDIAN
  void big_value(int16_t& x) {x = static_cast<int16_t>(0xF102U);}
  void big_value(uint16_t& x) {x = static_cast<uint16_t>(0xF102U);}
  void little_value(int16_t& x) {x = static_cast<int16_t>(0x02F1U);}
  void little_value(uint16_t& x) {x = static_cast<uint16_t>(0x02F1U);}
# else
  void big_value(int16_t& x) {x = static_cast<int16_t>(0x02F1U);}
  void big_value(uint16_t& x) {x = static_cast<uint16_t>(0x02F1U);}
  void little_value(int16_t& x) {x = static_cast<int16_t>(0xF102U);}
  void little_value(uint16_t& x) {x = static_cast<uint16_t>(0xF102U);}
# endif

  void native_value(int32_t& x) {x = static_cast<int32_t>(0xF1E21304UL);}
  void native_value(uint32_t& x) {x = static_cast<uint32_t>(0xF1E21304UL);}
# ifdef BOOST_BIG_ENDIAN
  void big_value(int32_t& x) {x = static_cast<int32_t>(0xF1E21304UL);}
  void big_value(uint32_t& x) {x = static_cast<uint32_t>(0xF1E21304UL);}
  void little_value(int32_t& x) {x = static_cast<int32_t>(0x0413E2F1UL);}
  void little_value(uint32_t& x) {x = static_cast<uint32_t>(0x0413E2F1UL);}
# else
  void big_value(int32_t& x) {x = static_cast<int32_t>(0x0413E2F1UL);}
  void big_value(uint32_t& x) {x = static_cast<uint32_t>(0x0413E2F1UL);}
  void little_value(int32_t& x) {x = static_cast<int32_t>(0xF1E21304UL);}
  void little_value(uint32_t& x) {x = static_cast<uint32_t>(0xF1E21304UL);}
# endif

  void native_value(int64_t& x) {x = static_cast<int64_t>(0xF1E2D3C444231201ULL);}
  void native_value(uint64_t& x) {x = static_cast<uint64_t>(0xF1E2D3C444231201ULL);}
# ifdef BOOST_BIG_ENDIAN
  void big_value(int64_t& x) {x = static_cast<int64_t>(0xF1E2D3C444231201ULL);}
  void big_value(uint64_t& x) {x = static_cast<uint64_t>(0xF1E2D3C444231201ULL);}
  void little_value(int64_t& x) {x = static_cast<int64_t>(0x01122344C4D3E2F1ULL);}
  void little_value(uint64_t& x) {x = static_cast<uint64_t>(0x01122344C4D3E2F1ULL);}
# else
  void big_value(int64_t& x) {x = static_cast<int64_t>(0x01122344C4D3E2F1ULL);}
  void big_value(uint64_t& x) {x = static_cast<uint64_t>(0x01122344C4D3E2F1ULL);}
  void little_value(int64_t& x) {x = static_cast<int64_t>(0xF1E2D3C444231201ULL);}
  void little_value(uint64_t& x) {x = static_cast<uint64_t>(0xF1E2D3C444231201ULL);}
# endif

  const float float_value = -1.234F;
  const double double_value = -1.234567;

  void native_value(float& x) {std::memcpy(&x, &float_value, sizeof(float));}
  void native_value(double& x) {memcpy(&x, &double_value, sizeof(double));}
# ifdef BOOST_BIG_ENDIAN
  void big_value(float& x) {memcpy(&x, &float_value, sizeof(float));}
  void big_value(double& x) {memcpy(&x, &double_value, sizeof(double));}
  void little_value(float& x)
  {
    memcpy(&x, &float_value, sizeof(float));
    std::reverse(reinterpret_cast<char*>(&x),
      reinterpret_cast<char*>(&x)+sizeof(float));
  }
  void little_value(double& x)
  {
    memcpy(&x, &double_value, sizeof(double));
    std::reverse(reinterpret_cast<char*>(&x),
      reinterpret_cast<char*>(&x)+sizeof(double));
  }
# else
  void big_value(float& x)
  {
    memcpy(&x, &float_value, sizeof(float));
    std::reverse(reinterpret_cast<char*>(&x),
      reinterpret_cast<char*>(&x)+sizeof(float));
  }
  void big_value(double& x)
  {
    memcpy(&x, &double_value, sizeof(double));
    std::reverse(reinterpret_cast<char*>(&x),
      reinterpret_cast<char*>(&x)+sizeof(double));
  }
  void little_value(float& x) {memcpy(&x, &float_value, sizeof(float));}
  void little_value(double& x) {memcpy(&x, &double_value, sizeof(double));}
# endif

  template <class T>
  void test()
  {
    T native;
    T big;
    T little;
    native_value(native);
    big_value(big);
    little_value(little);

    BOOST_TEST_EQ(be::reverse_value(big), little);
    BOOST_TEST_EQ(be::reverse_value(little), big);
    BOOST_TEST_EQ(be::detail::reverse_value<T>(big), little);
    BOOST_TEST_EQ(be::detail::reverse_value<T>(little), big);

    BOOST_TEST_EQ(be::big_endian_value(native), big);
    BOOST_TEST_EQ(be::little_endian_value(native), little);
    BOOST_TEST_EQ(be::big_endian_value(be::big_endian_value(native)), native);
    BOOST_TEST_EQ(be::big_endian_value(be::big_endian_value(big)), big);
    BOOST_TEST_EQ(be::big_endian_value(be::big_endian_value(little)), little);
    BOOST_TEST_EQ(be::little_endian_value(be::little_endian_value(native)), native);
    BOOST_TEST_EQ(be::little_endian_value(be::little_endian_value(big)), big);
    BOOST_TEST_EQ(be::little_endian_value(be::little_endian_value(little)), little);

# ifdef BOOST_BIG_ENDIAN
    BOOST_TEST_EQ(be::reverse_value(native), little);
    BOOST_TEST_EQ(be::detail::reverse_value<T>(native), little);
    BOOST_TEST_EQ(be::big_endian_value(big), big);
    BOOST_TEST_EQ(be::big_endian_value<T>(big), big);
    BOOST_TEST_EQ(be::big_endian_value(little), little);
    BOOST_TEST_EQ(be::big_endian_value<T>(little), little);
    BOOST_TEST_EQ(be::big_endian_value(native), little);
    BOOST_TEST_EQ(be::big_endian_value<T>(native), little);
# else
    BOOST_TEST_EQ(be::reverse_value(native), big);
    BOOST_TEST_EQ(be::detail::reverse_value<T>(native), big);
    BOOST_TEST_EQ(be::big_endian_value(big), little);
    BOOST_TEST_EQ(be::big_endian_value<T>(big), little);
    BOOST_TEST_EQ(be::big_endian_value(little), big);
    BOOST_TEST_EQ(be::big_endian_value<T>(little), big);
    BOOST_TEST_EQ(be::big_endian_value(native), big);
    BOOST_TEST_EQ(be::big_endian_value<T>(native), big);
# endif

    //  compile time order determination

    BOOST_TEST_EQ((be::convert_value<be::order::big, be::order::big>(big)), big);
    BOOST_TEST_EQ((be::convert_value<be::order::little, be::order::little>(little)), little);
    BOOST_TEST_EQ((be::convert_value<be::order::native, be::order::native>(native)), native);

    BOOST_TEST_EQ((be::convert_value<be::order::big, be::order::little>(big)), little);
    BOOST_TEST_EQ((be::convert_value<be::order::big, be::order::native>(big)), native);
    BOOST_TEST_EQ((be::convert_value<be::order::little, be::order::big>(little)), big);
    BOOST_TEST_EQ((be::convert_value<be::order::little, be::order::native>(little)), native);
    BOOST_TEST_EQ((be::convert_value<be::order::native, be::order::big>(native)), big);
    BOOST_TEST_EQ((be::convert_value<be::order::native, be::order::little>(native)), native);

    //  runtime order determination

    BOOST_TEST_EQ((be::convert_value(big, be::order::big, be::order::big)), big);
    BOOST_TEST_EQ((be::convert_value(little, be::order::little, be::order::little)), little);
    BOOST_TEST_EQ((be::convert_value(native, be::order::native, be::order::native)), native);

    BOOST_TEST_EQ((be::convert_value(big, be::order::big, be::order::little)), little);
    BOOST_TEST_EQ((be::convert_value(big, be::order::big, be::order::native)), native);
    BOOST_TEST_EQ((be::convert_value(little, be::order::little, be::order::big)), big);
    BOOST_TEST_EQ((be::convert_value(little, be::order::little, be::order::native)), native);
    BOOST_TEST_EQ((be::convert_value(native, be::order::native, be::order::big)), big);
    BOOST_TEST_EQ((be::convert_value(native, be::order::native, be::order::little)), native);
 
    //  light test of modify-in-place functions

    T x;

    x = big; be::reverse(x); BOOST_TEST_EQ(x, little);
    x = big; be::convert<be::order::big, be::order::little>(x); BOOST_TEST_EQ(x, little);
    x = big; be::convert(x, be::order::big, be::order::little); BOOST_TEST_EQ(x, little);

# ifdef BOOST_BIG_ENDIAN
    x = native; be::big_endian(x); BOOST_TEST_EQ(x, big);
    x = big; be::big_endian(x); BOOST_TEST_EQ(x, big);
    x = little; be::big_endian(x); BOOST_TEST_EQ(x, little);
    x = native; be::little_endian(x); BOOST_TEST_EQ(x, little);
    x = big; be::little_endian(x); BOOST_TEST_EQ(x, little);
    x = little; be::little_endian(x); BOOST_TEST_EQ(x, big);
# else
    x = native; be::big_endian(x); BOOST_TEST_EQ(x, big);
    x = big; be::big_endian(x); BOOST_TEST_EQ(x, little);
    x = little; be::big_endian(x); BOOST_TEST_EQ(x, big);
    x = native; be::little_endian(x); BOOST_TEST_EQ(x, little);
    x = big; be::little_endian(x); BOOST_TEST_EQ(x, big);
    x = little; be::little_endian(x); BOOST_TEST_EQ(x, little);
# endif

  }
}  // unnamed namespace

int cpp_main(int, char * [])
{
  //std::cerr << std::hex;

  cout << "int16_t" << endl;
  test<int16_t>();
  cout << "uint16_t" << endl;
  test<uint16_t>();
  cout << "int32_t" << endl;
  test<int32_t>();
  cout << "uint32_t" << endl;
  test<uint32_t>();
  cout << "int64_t" << endl;
  test<int64_t>();
  cout << "uint64_t" << endl;
  test<uint64_t>();
  cout << "float" << endl;
  test<float>();
  cout << "double" << endl;
  test<double>();

  return ::boost::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
