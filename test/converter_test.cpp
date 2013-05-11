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

  const boost::int64_t ni64 = 0x0102030405060708LL;
# ifdef BOOST_BIG_ENDIAN
  const boost::int64_t bi64 = 0x0102030405060708LL;
  const boost::int64_t li64 = 0x0807060504030201LL;
# else
  const boost::int64_t bi64 = 0x0807060504030201LL;
  const boost::int64_t li64 = 0x0102030405060708LL;
# endif

  const boost::int32_t ni32 = 0x01020304;
# ifdef BOOST_BIG_ENDIAN
  const boost::int32_t bi32 = 0x01020304;
  const boost::int32_t li32 = 0x04030201;
# else
  const boost::int32_t bi32 = 0x04030201;
  const boost::int32_t li32 = 0x01020304;
# endif

  const boost::int16_t ni16 = 0x0102;
# ifdef BOOST_BIG_ENDIAN
  const boost::int16_t bi16 = 0x0102;
  const boost::int16_t li16 = 0x0201;
# else
  const boost::int16_t bi16 = 0x0201;
  const boost::int16_t li16 = 0x0102;
# endif

  const boost::int16_t ni16hi = static_cast<boost::int16_t>(0xf1f2U);
# ifdef BOOST_BIG_ENDIAN
  const boost::int16_t bi16hi = static_cast<boost::int16_t>(0xf1f2U);
  const boost::int16_t li16hi = static_cast<boost::int16_t>(0xf2f1U);
# else
  const boost::int16_t bi16hi = static_cast<boost::int16_t>(0xf2f1U);
  const boost::int16_t li16hi = static_cast<boost::int16_t>(0xf1f2U);
# endif

  const boost::uint64_t nui64 = 0x0102030405060708ULL;
# ifdef BOOST_BIG_ENDIAN
  const boost::uint64_t bui64 = 0x0102030405060708ULL;
  const boost::uint64_t lui64 = 0x0807060504030201ULL;
# else
  const boost::uint64_t bui64 = 0x0807060504030201ULL;
  const boost::uint64_t lui64 = 0x0102030405060708ULL;
# endif

  const boost::uint32_t nui32 = 0x01020304;
# ifdef BOOST_BIG_ENDIAN
  const boost::uint32_t bui32 = 0x01020304;
  const boost::uint32_t lui32 = 0x04030201;
# else
  const boost::uint32_t bui32 = 0x04030201;
  const boost::uint32_t lui32 = 0x01020304;
# endif

  const boost::uint16_t nui16 = 0x0102;
# ifdef BOOST_BIG_ENDIAN
  const boost::uint16_t bui16 = 0x0102;
  const boost::uint16_t lui16 = 0x0201;
# else
  const boost::uint16_t bui16 = 0x0201;
  const boost::uint16_t lui16 = 0x0102;
# endif

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

    BOOST_TEST_EQ(be::reverse_bytes(big), little);
    BOOST_TEST_EQ(be::reverse_bytes(little), big);
    BOOST_TEST_EQ(be::reverse_bytes<T>(big), little);
    BOOST_TEST_EQ(be::reverse_bytes<T>(little), big);

    BOOST_TEST_EQ(be::big(native), big);
    BOOST_TEST_EQ(be::little(native), little);
    BOOST_TEST_EQ(be::big(be::big(native)), native);
    BOOST_TEST_EQ(be::big(be::big(big)), big);
    BOOST_TEST_EQ(be::big(be::big(little)), little);
    BOOST_TEST_EQ(be::little(be::little(native)), native);
    BOOST_TEST_EQ(be::little(be::little(big)), big);
    BOOST_TEST_EQ(be::little(be::little(little)), little);

# ifdef BOOST_BIG_ENDIAN
    BOOST_TEST_EQ(be::reverse_bytes(native), little);
    BOOST_TEST_EQ(be::reverse_bytes<T>(native), little);
    BOOST_TEST_EQ(be::big(big), big);
    BOOST_TEST_EQ(be::big<T>(big), big);
    BOOST_TEST_EQ(be::big(little), little);
    BOOST_TEST_EQ(be::big<T>(little), little);
    BOOST_TEST_EQ(be::big(native), little);
    BOOST_TEST_EQ(be::big<T>(native), little);
# else
    BOOST_TEST_EQ(be::reverse_bytes(native), big);
    BOOST_TEST_EQ(be::reverse_bytes<T>(native), big);
    BOOST_TEST_EQ(be::big(big), little);
    BOOST_TEST_EQ(be::big<T>(big), little);
    BOOST_TEST_EQ(be::big(little), big);
    BOOST_TEST_EQ(be::big<T>(little), big);
    BOOST_TEST_EQ(be::big(native), big);
    BOOST_TEST_EQ(be::big<T>(native), big);
# endif
  }

  void test_compile_time_convert_bytes()
  {
    cout << "test_compile_time_convert_bytes...\n";

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::big>(bi16)), bi16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::little>(li16)), li16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::native>(ni16)), ni16);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::big>(bui16)), bui16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::little>(lui16)), lui16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::native>(nui16)), nui16);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::big>(bi32)), bi32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::little>(li32)), li32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::native>(ni32)), ni32);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::big>(bui32)), bui32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::little>(lui32)), lui32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::native>(nui32)), nui32);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::big>(bi64)), bi64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::little>(li64)), li64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::native>(ni64)), ni64);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::big>(bui64)), bui64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::little>(lui64)), lui64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::native>(nui64)), nui64);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::little>(bi16)), li16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::native>(bi16)), ni16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::big>(li16)), bi16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::native>(li16)), ni16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::big>(ni16)), bi16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::little>(ni16)), ni16);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::little>(bui16)), lui16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::native>(bui16)), nui16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::big>(lui16)), bui16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::native>(lui16)), nui16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::big>(nui16)), bui16);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::little>(nui16)), nui16);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::little>(bi32)), li32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::native>(bi32)), ni32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::big>(li32)), bi32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::native>(li32)), ni32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::big>(ni32)), bi32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::little>(ni32)), ni32);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::little>(bui32)), lui32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::native>(bui32)), nui32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::big>(lui32)), bui32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::native>(lui32)), nui32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::big>(nui32)), bui32);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::little>(nui32)), nui32);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::little>(bi64)), li64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::native>(bi64)), ni64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::big>(li64)), bi64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::native>(li64)), ni64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::big>(ni64)), bi64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::little>(ni64)), ni64);

    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::little>(bui64)), lui64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::big, be::order::native>(bui64)), nui64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::big>(lui64)), bui64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::little, be::order::native>(lui64)), nui64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::big>(nui64)), bui64);
    BOOST_TEST_EQ((be::convert_bytes<be::order::native, be::order::little>(nui64)), nui64);

    cout << "  test_compile_time_convert_bytes complete\n";
  }

  void test_runtime_convert_bytes()
  {
    cout << "test_runtime_convert_bytes...\n";
  
    BOOST_TEST_EQ((be::convert_bytes(bi16, be::order::big, be::order::big)), bi16);
    BOOST_TEST_EQ((be::convert_bytes(li16, be::order::little, be::order::little)), li16);
    BOOST_TEST_EQ((be::convert_bytes(ni16, be::order::native, be::order::native)), ni16);

    BOOST_TEST_EQ((be::convert_bytes(bui16, be::order::big, be::order::big)), bui16);
    BOOST_TEST_EQ((be::convert_bytes(lui16, be::order::little, be::order::little)), lui16);
    BOOST_TEST_EQ((be::convert_bytes(nui16, be::order::native, be::order::native)), nui16);

    BOOST_TEST_EQ((be::convert_bytes(bi16, be::order::big, be::order::little)), li16);
    BOOST_TEST_EQ((be::convert_bytes(bi16, be::order::big, be::order::native)), ni16);
    BOOST_TEST_EQ((be::convert_bytes(li16, be::order::little, be::order::big)), bi16);
    BOOST_TEST_EQ((be::convert_bytes(li16, be::order::little, be::order::native)), ni16);
    BOOST_TEST_EQ((be::convert_bytes(ni16, be::order::native, be::order::big)), bi16);
    BOOST_TEST_EQ((be::convert_bytes(ni16, be::order::native, be::order::little)), ni16);

    BOOST_TEST_EQ((be::convert_bytes(bui16, be::order::big, be::order::little)), lui16);
    BOOST_TEST_EQ((be::convert_bytes(bui16, be::order::big, be::order::native)), nui16);
    BOOST_TEST_EQ((be::convert_bytes(lui16, be::order::little, be::order::big)), bui16);
    BOOST_TEST_EQ((be::convert_bytes(lui16, be::order::little, be::order::native)), nui16);
    BOOST_TEST_EQ((be::convert_bytes(nui16, be::order::native, be::order::big)), bui16);
    BOOST_TEST_EQ((be::convert_bytes(nui16, be::order::native, be::order::little)), nui16);
  
    BOOST_TEST_EQ((be::convert_bytes(bi32, be::order::big, be::order::big)), bi32);
    BOOST_TEST_EQ((be::convert_bytes(li32, be::order::little, be::order::little)), li32);
    BOOST_TEST_EQ((be::convert_bytes(ni32, be::order::native, be::order::native)), ni32);

    BOOST_TEST_EQ((be::convert_bytes(bui32, be::order::big, be::order::big)), bui32);
    BOOST_TEST_EQ((be::convert_bytes(lui32, be::order::little, be::order::little)), lui32);
    BOOST_TEST_EQ((be::convert_bytes(nui32, be::order::native, be::order::native)), nui32);

    BOOST_TEST_EQ((be::convert_bytes(bi32, be::order::big, be::order::little)), li32);
    BOOST_TEST_EQ((be::convert_bytes(bi32, be::order::big, be::order::native)), ni32);
    BOOST_TEST_EQ((be::convert_bytes(li32, be::order::little, be::order::big)), bi32);
    BOOST_TEST_EQ((be::convert_bytes(li32, be::order::little, be::order::native)), ni32);
    BOOST_TEST_EQ((be::convert_bytes(ni32, be::order::native, be::order::big)), bi32);
    BOOST_TEST_EQ((be::convert_bytes(ni32, be::order::native, be::order::little)), ni32);

    BOOST_TEST_EQ((be::convert_bytes(bui32, be::order::big, be::order::little)), lui32);
    BOOST_TEST_EQ((be::convert_bytes(bui32, be::order::big, be::order::native)), nui32);
    BOOST_TEST_EQ((be::convert_bytes(lui32, be::order::little, be::order::big)), bui32);
    BOOST_TEST_EQ((be::convert_bytes(lui32, be::order::little, be::order::native)), nui32);
    BOOST_TEST_EQ((be::convert_bytes(nui32, be::order::native, be::order::big)), bui32);
    BOOST_TEST_EQ((be::convert_bytes(nui32, be::order::native, be::order::little)), nui32);
  
    BOOST_TEST_EQ((be::convert_bytes(bi64, be::order::big, be::order::big)), bi64);
    BOOST_TEST_EQ((be::convert_bytes(li64, be::order::little, be::order::little)), li64);
    BOOST_TEST_EQ((be::convert_bytes(ni64, be::order::native, be::order::native)), ni64);

    BOOST_TEST_EQ((be::convert_bytes(bui64, be::order::big, be::order::big)), bui64);
    BOOST_TEST_EQ((be::convert_bytes(lui64, be::order::little, be::order::little)), lui64);
    BOOST_TEST_EQ((be::convert_bytes(nui64, be::order::native, be::order::native)), nui64);

    BOOST_TEST_EQ((be::convert_bytes(bi64, be::order::big, be::order::little)), li64);
    BOOST_TEST_EQ((be::convert_bytes(bi64, be::order::big, be::order::native)), ni64);
    BOOST_TEST_EQ((be::convert_bytes(li64, be::order::little, be::order::big)), bi64);
    BOOST_TEST_EQ((be::convert_bytes(li64, be::order::little, be::order::native)), ni64);
    BOOST_TEST_EQ((be::convert_bytes(ni64, be::order::native, be::order::big)), bi64);
    BOOST_TEST_EQ((be::convert_bytes(ni64, be::order::native, be::order::little)), ni64);

    BOOST_TEST_EQ((be::convert_bytes(bui64, be::order::big, be::order::little)), lui64);
    BOOST_TEST_EQ((be::convert_bytes(bui64, be::order::big, be::order::native)), nui64);
    BOOST_TEST_EQ((be::convert_bytes(lui64, be::order::little, be::order::big)), bui64);
    BOOST_TEST_EQ((be::convert_bytes(lui64, be::order::little, be::order::native)), nui64);
    BOOST_TEST_EQ((be::convert_bytes(nui64, be::order::native, be::order::big)), bui64);
    BOOST_TEST_EQ((be::convert_bytes(nui64, be::order::native, be::order::little)), nui64);

     cout << "  test_runtime_convert_bytes complete\n";
  }

}  // unnamed namespace

int cpp_main(int, char * [])
{
  //std::cerr << std::hex;
  test_reverse_bytes();
  test_compile_time_convert_bytes();
  test_runtime_convert_bytes();

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
