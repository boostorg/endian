//  conversion_test.cpp  ---------------------------------------------------------------//

//  Copyright Beman Dawes 2010

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/conversion2.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

namespace be = boost::endian2;

namespace
{

  void test_reorder()
  {
    std::cout << "test_reorder...\n";

    boost::int64_t i64 = 0x0102030405060708LL;
    BOOST_TEST_EQ(be::reorder(i64), 0x0807060504030201LL);
    BOOST_TEST_EQ(be::reorder(be::reorder(i64)), i64);

    i64 = 0xfefdfcfbfaf9f8f7LL;
    BOOST_TEST_EQ(be::reorder(i64), static_cast<boost::int64_t>(0xf7f8f9fafbfcfdfeULL));
    BOOST_TEST_EQ(be::reorder(be::reorder(i64)), i64);

    boost::int32_t i32 = 0x01020304;
    BOOST_TEST_EQ(be::reorder(i32), 0x04030201);
    BOOST_TEST_EQ(be::reorder(be::reorder(i32)), i32);

    i32 = 0xfefdfcfb;
    BOOST_TEST_EQ(be::reorder(i32), static_cast<boost::int32_t>(0xfbfcfdfe));
    BOOST_TEST_EQ(be::reorder(be::reorder(i32)), i32);

    boost::int16_t i16 = 0x0102;
    BOOST_TEST_EQ(be::reorder(i16), 0x0201);
    BOOST_TEST_EQ(be::reorder(be::reorder(i16)), i16);

    i16 = static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfefd));
    BOOST_TEST_EQ(be::reorder(i16), static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfdfe)));
    BOOST_TEST_EQ(be::reorder(be::reorder(i16)), i16);

    boost::uint64_t ui64 = 0x0102030405060708ULL;
    BOOST_TEST_EQ(be::reorder(ui64), 0x0807060504030201ULL);
    BOOST_TEST_EQ(be::reorder(be::reorder(ui64)), ui64);

    boost::uint32_t ui32 = 0x01020304;
    BOOST_TEST_EQ(be::reorder(ui32), static_cast<boost::uint32_t>(0x04030201));
    BOOST_TEST_EQ(be::reorder(be::reorder(ui32)), ui32);

    boost::uint16_t ui16 = 0x0102;
    BOOST_TEST_EQ(be::reorder(ui16), 0x0201);
    BOOST_TEST_EQ(be::reorder(be::reorder(ui16)), ui16);
    
    std::cout << "  test_reorder complete\n";
  }

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

  void test_in_place_conditional_reorder()
  {
    //std::cout << "test_in_place_conditional_reorder...\n";

    //boost::int64_t i64;

    //i64 = ni64;
    //be::native_to_big(i64);
    //BOOST_TEST_EQ(i64, bi64);

    //i64 = ni64;
    //be::native_to_little(i64);
    //BOOST_TEST_EQ(i64, li64);

    //i64 = bi64;
    //be::big_to_native(i64);
    //BOOST_TEST_EQ(i64, ni64);

    //i64 = li64;
    //be::little_to_native(i64);
    //BOOST_TEST_EQ(i64, ni64);

    //boost::uint64_t ui64;

    //ui64 = nui64;
    //be::native_to_big(ui64);
    //BOOST_TEST_EQ(ui64, bui64);

    //ui64 = nui64;
    //be::native_to_little(ui64);
    //BOOST_TEST_EQ(ui64, lui64);

    //ui64 = bui64;
    //be::big_to_native(ui64);
    //BOOST_TEST_EQ(ui64, nui64);

    //ui64 = lui64;
    //be::little_to_native(ui64);
    //BOOST_TEST_EQ(ui64, nui64);

    //boost::int32_t i32;

    //i32 = ni32;
    //be::native_to_big(i32);
    //BOOST_TEST_EQ(i32, bi32);

    //i32 = ni32;
    //be::native_to_little(i32);
    //BOOST_TEST_EQ(i32, li32);

    //i32 = bi32;
    //be::big_to_native(i32);
    //BOOST_TEST_EQ(i32, ni32);

    //i32 = li32;
    //be::little_to_native(i32);
    //BOOST_TEST_EQ(i32, ni32);

    //boost::uint32_t ui32;

    //ui32 = nui32;
    //be::native_to_big(ui32);
    //BOOST_TEST_EQ(ui32, bui32);

    //ui32 = nui32;
    //be::native_to_little(ui32);
    //BOOST_TEST_EQ(ui32, lui32);

    //ui32 = bui32;
    //be::big_to_native(ui32);
    //BOOST_TEST_EQ(ui32, nui32);

    //ui32 = lui32;
    //be::little_to_native(ui32);
    //BOOST_TEST_EQ(ui32, nui32);

    //boost::int16_t i16;

    //i16 = ni16;
    //be::native_to_big(i16);
    //BOOST_TEST_EQ(i16, bi16);

    //i16 = ni16;
    //be::native_to_little(i16);
    //BOOST_TEST_EQ(i16, li16);

    //i16 = bi16;
    //be::big_to_native(i16);
    //BOOST_TEST_EQ(i16, ni16);

    //i16 = li16;
    //be::little_to_native(i16);
    //BOOST_TEST_EQ(i16, ni16);

    //boost::uint16_t ui16;

    //ui16 = nui16;
    //be::native_to_big(ui16);
    //BOOST_TEST_EQ(ui16, bui16);

    //ui16 = nui16;
    //be::native_to_little(ui16);
    //BOOST_TEST_EQ(ui16, lui16);

    //ui16 = bui16;
    //be::big_to_native(ui16);
    //BOOST_TEST_EQ(ui16, nui16);

    //ui16 = lui16;
    //be::little_to_native(ui16);
    //BOOST_TEST_EQ(ui16, nui16);
    //
    //std::cout << "  test_in_place_conditional_reorder complete\n";
  }

  void test_copying_conditional_reorder()
  {
    //std::cout << "test_copying_conditional_reorder...\n";

    //boost::int64_t i64, ti64;

    //i64 = ni64;
    //be::native_to_big(i64, ti64);
    //BOOST_TEST_EQ(ti64, bi64);

    //i64 = ni64;
    //be::native_to_little(i64, ti64);
    //BOOST_TEST_EQ(ti64, li64);

    //i64 = bi64;
    //be::big_to_native(i64, ti64);
    //BOOST_TEST_EQ(ti64, ni64);

    //i64 = li64;
    //be::little_to_native(i64, ti64);
    //BOOST_TEST_EQ(ti64, ni64);

    //boost::uint64_t ui64, tui64;

    //ui64 = nui64;
    //be::native_to_big(ui64, tui64);
    //BOOST_TEST_EQ(tui64, bui64);

    //ui64 = nui64;
    //be::native_to_little(ui64, tui64);
    //BOOST_TEST_EQ(tui64, lui64);

    //ui64 = bui64;
    //be::big_to_native(ui64, tui64);
    //BOOST_TEST_EQ(tui64, nui64);

    //ui64 = lui64;
    //be::little_to_native(ui64, tui64);
    //BOOST_TEST_EQ(tui64, nui64);

    //boost::int32_t i32, ti32;

    //i32 = ni32;
    //be::native_to_big(i32, ti32);
    //BOOST_TEST_EQ(ti32, bi32);

    //i32 = ni32;
    //be::native_to_little(i32, ti32);
    //BOOST_TEST_EQ(ti32, li32);

    //i32 = bi32;
    //be::big_to_native(i32, ti32);
    //BOOST_TEST_EQ(ti32, ni32);

    //i32 = li32;
    //be::little_to_native(i32, ti32);
    //BOOST_TEST_EQ(ti32, ni32);

    //boost::uint32_t ui32, tui32;

    //ui32 = nui32;
    //be::native_to_big(ui32, tui32);
    //BOOST_TEST_EQ(tui32, bui32);

    //ui32 = nui32;
    //be::native_to_little(ui32, tui32);
    //BOOST_TEST_EQ(tui32, lui32);

    //ui32 = bui32;
    //be::big_to_native(ui32, tui32);
    //BOOST_TEST_EQ(tui32, nui32);

    //ui32 = lui32;
    //be::little_to_native(ui32, tui32);
    //BOOST_TEST_EQ(tui32, nui32);

    //boost::int16_t i16, ti16;

    //i16 = ni16;
    //be::native_to_big(i16, ti16);
    //BOOST_TEST_EQ(ti16, bi16);

    //i16 = ni16;
    //be::native_to_little(i16, ti16);
    //BOOST_TEST_EQ(ti16, li16);

    //i16 = bi16;
    //be::big_to_native(i16, ti16);
    //BOOST_TEST_EQ(ti16, ni16);

    //i16 = li16;
    //be::little_to_native(i16, ti16);
    //BOOST_TEST_EQ(ti16, ni16);

    //boost::uint16_t ui16, tui16;

    //ui16 = nui16;
    //be::native_to_big(ui16, tui16);
    //BOOST_TEST_EQ(tui16, bui16);

    //ui16 = nui16;
    //be::native_to_little(ui16, tui16);
    //BOOST_TEST_EQ(tui16, lui16);

    //ui16 = bui16;
    //be::big_to_native(ui16, tui16);
    //BOOST_TEST_EQ(tui16, nui16);

    //ui16 = lui16;
    //be::little_to_native(ui16, tui16);
    //BOOST_TEST_EQ(tui16, nui16);
    //
    std::cout << "  test_copying_conditional_reorder complete\n";
  }

}  // unnamed namespace

int cpp_main(int, char * [])
{
  std::cerr << std::hex;
  test_reorder();
  test_in_place_conditional_reorder();

  return ::boost::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
