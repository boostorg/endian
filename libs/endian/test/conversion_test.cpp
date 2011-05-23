//  conversion_test.cpp  ---------------------------------------------------------------//

//  Copyright Beman Dawes 2010

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#include <boost/endian/conversion.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

namespace be = boost::endian;

namespace
{

  void test_in_place_flip()
  {
    std::cout << "test_in_place_flip...\n";

    boost::int64_t i64 = 0x0102030405060708;
    be::flip(i64);
    BOOST_TEST_EQ(i64, 0x0807060504030201);
    be::flip(i64);
    BOOST_TEST_EQ(i64, 0x0102030405060708);

    i64 = 0xfefdfcfbfaf9f8f7;
    be::flip(i64);
    BOOST_TEST_EQ(i64, static_cast<boost::int64_t>(0xf7f8f9fafbfcfdfe));
    be::flip(i64);
    BOOST_TEST_EQ(i64, static_cast<boost::int64_t>(0xfefdfcfbfaf9f8f7));

    boost::int32_t i32 = 0x01020304;
    be::flip(i32);
    BOOST_TEST_EQ(i32, 0x04030201);
    be::flip(i32);
    BOOST_TEST_EQ(i32, 0x01020304);

    i32 = 0xfefdfcfb;
    be::flip(i32);
    BOOST_TEST_EQ(i32, static_cast<boost::int32_t>(0xfbfcfdfe));
    be::flip(i32);
    BOOST_TEST_EQ(i32, static_cast<boost::int32_t>(0xfefdfcfb));

    boost::int16_t i16 = 0x0102;
    be::flip(i16);
    BOOST_TEST_EQ(i16, 0x0201);
    be::flip(i16);
    BOOST_TEST_EQ(i16, 0x0102);

    i16 = static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfefd));
    be::flip(i16);
    BOOST_TEST_EQ(i16, static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfdfe)));
    be::flip(i16);
    BOOST_TEST_EQ(i16, static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfefd)));

    boost::uint64_t ui64 = 0x0102030405060708;
    be::flip(ui64);
    BOOST_TEST_EQ(ui64, static_cast<boost::uint64_t>(0x0807060504030201));
    be::flip(ui64);
    BOOST_TEST_EQ(ui64, static_cast<boost::uint64_t>(0x0102030405060708));

    boost::uint32_t ui32 = 0x01020304;
    be::flip(ui32);
    BOOST_TEST_EQ(ui32, static_cast<boost::uint32_t>(0x04030201));
    be::flip(ui32);
    BOOST_TEST_EQ(ui32, static_cast<boost::uint32_t>(0x01020304));

    boost::uint16_t ui16 = 0x0102;
    be::flip(ui16);
    BOOST_TEST_EQ(ui16, 0x0201);
    be::flip(ui16);
    BOOST_TEST_EQ(ui16, 0x0102);
    
    std::cout << "  test_in_place_flip complete\n";
  }

  void test_copying_flip()
  {
    std::cout << "test_copying_flip...\n";

    boost::int64_t i64 = 0x0102030405060708, j64, k64;
    be::flip(i64, j64);
    BOOST_TEST_EQ(j64, 0x0807060504030201);
    BOOST_TEST_EQ(i64, 0x0102030405060708);
    be::flip(j64, k64);
    BOOST_TEST_EQ(k64, 0x0102030405060708);

    i64 = 0xfefdfcfbfaf9f8f7;
    be::flip(i64, j64);
    BOOST_TEST_EQ(j64, static_cast<boost::int64_t>(0xf7f8f9fafbfcfdfe));
    be::flip(j64, k64);
    BOOST_TEST_EQ(k64, static_cast<boost::int64_t>(0xfefdfcfbfaf9f8f7));

    boost::int32_t i32 = 0x01020304, j32, k32;
    be::flip(i32, j32);
    BOOST_TEST_EQ(j32, 0x04030201);
    be::flip(j32, k32);
    BOOST_TEST_EQ(k32, 0x01020304);

    i32 = 0xfefdfcfb;
    be::flip(i32, j32);
    BOOST_TEST_EQ(j32, static_cast<boost::int32_t>(0xfbfcfdfe));
    be::flip(j32, k32);
    BOOST_TEST_EQ(k32, static_cast<boost::int32_t>(0xfefdfcfb));

    boost::int16_t i16 = 0x0102, j16, k16;
    be::flip(i16, j16);
    BOOST_TEST_EQ(j16, 0x0201);
    be::flip(j16, k16);
    BOOST_TEST_EQ(k16, 0x0102);

    i16 = static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfefd)), j16, k16;
    be::flip(i16, j16);
    BOOST_TEST_EQ(j16, static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfdfe)));
    be::flip(j16, k16);
    BOOST_TEST_EQ(k16, static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfefd)));

    boost::uint64_t ui64 = 0x0102030405060708, uj64, uk64;
    be::flip(ui64, uj64);
    BOOST_TEST_EQ(uj64, static_cast<boost::uint64_t>(0x0807060504030201));
    be::flip(uj64, uk64);
    BOOST_TEST_EQ(uk64, static_cast<boost::uint64_t>(0x0102030405060708));

    boost::uint32_t ui32 = 0x01020304, uj32, uk32;
    be::flip(ui32, uj32);
    BOOST_TEST_EQ(uj32, static_cast<boost::uint32_t>(0x04030201));
    be::flip(uj32, uk32);
    BOOST_TEST_EQ(uk32, static_cast<boost::uint32_t>(0x01020304));

    boost::uint16_t ui16 = 0x0102, uj16, uk16;
    be::flip(ui16, uj16);
    BOOST_TEST_EQ(uj16, 0x0201);
    be::flip(uj16, uk16);
    BOOST_TEST_EQ(uk16, 0x0102);
    
    std::cout << "  test_copying_flip complete\n";
  }

  const boost::int64_t ni64 = 0x0102030405060708;
# ifdef BOOST_BIG_ENDIAN
  const boost::int64_t bi64 = 0x0102030405060708;
  const boost::int64_t li64 = 0x0807060504030201;
# else
  const boost::int64_t bi64 = 0x0807060504030201;
  const boost::int64_t li64 = 0x0102030405060708;
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

  const boost::uint64_t nui64 = 0x0102030405060708;
# ifdef BOOST_BIG_ENDIAN
  const boost::uint64_t bui64 = 0x0102030405060708;
  const boost::uint64_t lui64 = 0x0807060504030201;
# else
  const boost::uint64_t bui64 = 0x0807060504030201;
  const boost::uint64_t lui64 = 0x0102030405060708;
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

  void test_in_place_conditional_flip()
  {
    std::cout << "test_in_place_conditional_flip...\n";

    boost::int64_t i64;

    i64 = ni64;
    be::to_big(i64);
    BOOST_TEST_EQ(i64, bi64);

    i64 = ni64;
    be::to_little(i64);
    BOOST_TEST_EQ(i64, li64);

    i64 = bi64;
    be::from_big(i64);
    BOOST_TEST_EQ(i64, ni64);

    i64 = li64;
    be::from_little(i64);
    BOOST_TEST_EQ(i64, ni64);

    boost::uint64_t ui64;

    ui64 = nui64;
    be::to_big(ui64);
    BOOST_TEST_EQ(ui64, bui64);

    ui64 = nui64;
    be::to_little(ui64);
    BOOST_TEST_EQ(ui64, lui64);

    ui64 = bui64;
    be::from_big(ui64);
    BOOST_TEST_EQ(ui64, nui64);

    ui64 = lui64;
    be::from_little(ui64);
    BOOST_TEST_EQ(ui64, nui64);

    boost::int32_t i32;

    i32 = ni32;
    be::to_big(i32);
    BOOST_TEST_EQ(i32, bi32);

    i32 = ni32;
    be::to_little(i32);
    BOOST_TEST_EQ(i32, li32);

    i32 = bi32;
    be::from_big(i32);
    BOOST_TEST_EQ(i32, ni32);

    i32 = li32;
    be::from_little(i32);
    BOOST_TEST_EQ(i32, ni32);

    boost::uint32_t ui32;

    ui32 = nui32;
    be::to_big(ui32);
    BOOST_TEST_EQ(ui32, bui32);

    ui32 = nui32;
    be::to_little(ui32);
    BOOST_TEST_EQ(ui32, lui32);

    ui32 = bui32;
    be::from_big(ui32);
    BOOST_TEST_EQ(ui32, nui32);

    ui32 = lui32;
    be::from_little(ui32);
    BOOST_TEST_EQ(ui32, nui32);

    boost::int16_t i16;

    i16 = ni16;
    be::to_big(i16);
    BOOST_TEST_EQ(i16, bi16);

    i16 = ni16;
    be::to_little(i16);
    BOOST_TEST_EQ(i16, li16);

    i16 = bi16;
    be::from_big(i16);
    BOOST_TEST_EQ(i16, ni16);

    i16 = li16;
    be::from_little(i16);
    BOOST_TEST_EQ(i16, ni16);

    boost::uint16_t ui16;

    ui16 = nui16;
    be::to_big(ui16);
    BOOST_TEST_EQ(ui16, bui16);

    ui16 = nui16;
    be::to_little(ui16);
    BOOST_TEST_EQ(ui16, lui16);

    ui16 = bui16;
    be::from_big(ui16);
    BOOST_TEST_EQ(ui16, nui16);

    ui16 = lui16;
    be::from_little(ui16);
    BOOST_TEST_EQ(ui16, nui16);



    i32 = 0x01020304;
    be::flip(i32);
    BOOST_TEST_EQ(i32, 0x04030201);
    be::flip(i32);
    BOOST_TEST_EQ(i32, 0x01020304);

    i32 = 0xfefdfcfb;
    be::flip(i32);
    BOOST_TEST_EQ(i32, static_cast<boost::int32_t>(0xfbfcfdfe));
    be::flip(i32);
    BOOST_TEST_EQ(i32, static_cast<boost::int32_t>(0xfefdfcfb));

    i16 = 0x0102;
    be::flip(i16);
    BOOST_TEST_EQ(i16, 0x0201);
    be::flip(i16);
    BOOST_TEST_EQ(i16, 0x0102);

    i16 = static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfefd));
    be::flip(i16);
    BOOST_TEST_EQ(i16, static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfdfe)));
    be::flip(i16);
    BOOST_TEST_EQ(i16, static_cast<boost::int16_t>(static_cast<boost::uint16_t>(0xfefd)));

    ui64 = 0x0102030405060708;
    be::flip(ui64);
    BOOST_TEST_EQ(ui64, static_cast<boost::uint64_t>(0x0807060504030201));
    be::flip(ui64);
    BOOST_TEST_EQ(ui64, static_cast<boost::uint64_t>(0x0102030405060708));

    ui32 = 0x01020304;
    be::flip(ui32);
    BOOST_TEST_EQ(ui32, static_cast<boost::uint32_t>(0x04030201));
    be::flip(ui32);
    BOOST_TEST_EQ(ui32, static_cast<boost::uint32_t>(0x01020304));

    ui16 = 0x0102;
    be::flip(ui16);
    BOOST_TEST_EQ(ui16, 0x0201);
    be::flip(ui16);
    BOOST_TEST_EQ(ui16, 0x0102);
    
    std::cout << "  test_in_place_conditional_flip complete\n";
  }

}  // unnamed namespace

int cpp_main(int, char * [])
{
  std::cerr << std::hex;
  test_in_place_flip();
  test_copying_flip();
  test_in_place_conditional_flip();

  return ::boost::report_errors();
}
