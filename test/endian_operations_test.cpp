//  endian_operations_test.cpp  ----------------------------------------------//

//  Copyright Beman Dawes 2008

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/endian

//----------------------------------------------------------------------------//

//  This test probes operator overloading, including interaction between
//  operand types.

//  See endian_test for tests of endianess correctness, size, and value.

//----------------------------------------------------------------------------//

#define _SCL_SECURE_NO_WARNINGS

#define BOOST_ENDIAN_LOG

#include <boost/endian/detail/disable_warnings.hpp>

#ifdef _MSC_VER
# pragma warning( disable : 4242 )  // conversion ..., possible loss of data
# pragma warning( disable : 4244 )  // conversion ..., possible loss of data
# pragma warning( disable : 4018 )  // signed/unsigned mismatch
# pragma warning( disable : 4365 )  // signed/unsigned mismatch
# pragma warning( disable : 4389 )  // signed/unsigned mismatch
#endif

#include <boost/endian/types.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <cassert>
#include <iostream>

namespace be = boost::endian;

template <class T1,  class T2>
struct default_construct
{
  static void test()
  {
    T1 o1;
    o1 = 1;         // quiet warnings
    if (o1) return; // quiet warnings
  }
};

template <class T1,  class T2>
struct construct
{
  static void test()
  {
    T2 o2(1);
    T1 o1(o2);
    ++o1;  // quiet gcc unused variable warning
  }
};

template <class T1,  class T2>
struct initialize
{
  static void test()
  {
    T1 o2(2);
    T1 o1 = o2;
    ++o1;  // quiet gcc unused variable warning
  }
};

template <class T1,  class T2>
struct assign
{
  static void test()
  {
    T2 o2;
    o2 = 1;
    T1 o1;
    o1 = o2;
    if (o1) return; // quiet warnings
  }
};

template <class T1,  class T2>
struct relational
{
  static void test()
  {
    T1 o1(1);
    T2 o2(2);
    if ( o1 == o2 ) return;
    if ( o1 != o2 ) return;
    if ( o1 < o2 ) return;
    if ( o1 <= o2 ) return;
    if ( o1 > o2 ) return;
    if ( o1 >= o2 ) return;
  }
};

template <class T1,  class T2>
struct op_plus
{
  static void test()
  {
    T1 o1(1);
    T2 o2(2);
    T1 o3;

    o3 = +o1;

    o3 = o1 + o2;

    o1 += o2;

    if (o3) return; // quiet warnings
  }
};

template <class T1,  class T2>
struct op_star
{
  static void test()
  {
    T1 o1(1);
    T2 o2(2);
    T1 o3;

    o3 = o1 * o2;

    o1 *= o2;

    if (o3) return; // quiet warnings
  }
};

template <template<class,  class> class Test,  class T1>
void op_test_aux()
{
#ifdef BOOST_SHORT_ENDIAN_TEST
  Test<T1, int>::test();
  Test<T1, unsigned int>::test();
  Test<T1, be::big_int16un_t>::test();
  Test<T1, be::big_uint64un_t>::test();
#else
  Test<T1, char>::test();
  Test<T1, unsigned char>::test();
  Test<T1, signed char>::test();
  Test<T1, short>::test();
  Test<T1, unsigned short>::test();
  Test<T1, int>::test();
  Test<T1, unsigned int>::test();
  Test<T1, long>::test();
  Test<T1, unsigned long>::test();
  Test<T1, long long>::test();
  Test<T1, unsigned long long>::test();
  Test<T1, be::big_int8un_t>::test();
  Test<T1, be::big_int16un_t>::test();
  Test<T1, be::big_int24un_t>::test();
  Test<T1, be::big_int32un_t>::test();
  Test<T1, be::big_int40un_t>::test();
  Test<T1, be::big_int48un_t>::test();
  Test<T1, be::big_int56un_t>::test();
  Test<T1, be::big_int64un_t>::test();
  Test<T1, be::big_uint8un_t>::test();
  Test<T1, be::big_uint16un_t>::test();
  Test<T1, be::big_uint24un_t>::test();
  Test<T1, be::big_uint32un_t>::test();
  Test<T1, be::big_uint40un_t>::test();
  Test<T1, be::big_uint48un_t>::test();
  Test<T1, be::big_uint56un_t>::test();
  Test<T1, be::big_uint64un_t>::test();
  Test<T1, be::little_int8un_t>::test();
  Test<T1, be::little_int16un_t>::test();
  Test<T1, be::little_int24un_t>::test();
  Test<T1, be::little_int32un_t>::test();
  Test<T1, be::little_int40un_t>::test();
  Test<T1, be::little_int48un_t>::test();
  Test<T1, be::little_int56un_t>::test();
  Test<T1, be::little_int64un_t>::test();
  Test<T1, be::little_uint8un_t>::test();
  Test<T1, be::little_uint16un_t>::test();
  Test<T1, be::little_uint24un_t>::test();
  Test<T1, be::little_uint32un_t>::test();
  Test<T1, be::little_uint40un_t>::test();
  Test<T1, be::little_uint48un_t>::test();
  Test<T1, be::little_uint56un_t>::test();
  Test<T1, be::little_uint64un_t>::test();
  Test<T1, be::native_int8un_t>::test();
  Test<T1, be::native_int16un_t>::test();
  Test<T1, be::native_int24un_t>::test();
  Test<T1, be::native_int32un_t>::test();
  Test<T1, be::native_int40un_t>::test();
  Test<T1, be::native_int48un_t>::test();
  Test<T1, be::native_int56un_t>::test();
  Test<T1, be::native_int64un_t>::test();
  Test<T1, be::native_uint8un_t>::test();
  Test<T1, be::native_uint16un_t>::test();
  Test<T1, be::native_uint24un_t>::test();
  Test<T1, be::native_uint32un_t>::test();
  Test<T1, be::native_uint40un_t>::test();
  Test<T1, be::native_uint48un_t>::test();
  Test<T1, be::native_uint56un_t>::test();
  Test<T1, be::native_uint64un_t>::test();
#endif
}

template <template<class,  class> class Test>
void op_test()
{
#ifdef BOOST_SHORT_ENDIAN_TEST
  op_test_aux<Test, unsigned short>();
  op_test_aux<Test, int>();
  op_test_aux<Test, be::big_int32un_t>();
  op_test_aux<Test, be::big_uint32un_t>();
  op_test_aux<Test, be::little_int48un_t>();
#else
  op_test_aux<Test, char>();
  op_test_aux<Test, unsigned char>();
  op_test_aux<Test, signed char>();
  op_test_aux<Test, short>();
  op_test_aux<Test, unsigned short>();
  op_test_aux<Test, int>();
  op_test_aux<Test, unsigned int>();
  op_test_aux<Test, long>();
  op_test_aux<Test, unsigned long>();
  op_test_aux<Test, long long>();
  op_test_aux<Test, unsigned long long>();
  op_test_aux<Test, be::big_int8un_t>();
  op_test_aux<Test, be::big_int16un_t>();
  op_test_aux<Test, be::big_int24un_t>();
  op_test_aux<Test, be::big_int32un_t>();
  op_test_aux<Test, be::big_int40un_t>();
  op_test_aux<Test, be::big_int48un_t>();
  op_test_aux<Test, be::big_int56un_t>();
  op_test_aux<Test, be::big_int64un_t>();
  op_test_aux<Test, be::big_uint8un_t>();
  op_test_aux<Test, be::big_uint16un_t>();
  op_test_aux<Test, be::big_uint24un_t>();
  op_test_aux<Test, be::big_uint32un_t>();
  op_test_aux<Test, be::big_uint40un_t>();
  op_test_aux<Test, be::big_uint48un_t>();
  op_test_aux<Test, be::big_uint56un_t>();
  op_test_aux<Test, be::big_uint64un_t>();
  op_test_aux<Test, be::little_int8un_t>();
  op_test_aux<Test, be::little_int16un_t>();
  op_test_aux<Test, be::little_int24un_t>();
  op_test_aux<Test, be::little_int32un_t>();
  op_test_aux<Test, be::little_int40un_t>();
  op_test_aux<Test, be::little_int48un_t>();
  op_test_aux<Test, be::little_int56un_t>();
  op_test_aux<Test, be::little_int64un_t>();
  op_test_aux<Test, be::little_uint8un_t>();
  op_test_aux<Test, be::little_uint16un_t>();
  op_test_aux<Test, be::little_uint24un_t>();
  op_test_aux<Test, be::little_uint32un_t>();
  op_test_aux<Test, be::little_uint40un_t>();
  op_test_aux<Test, be::little_uint48un_t>();
  op_test_aux<Test, be::little_uint56un_t>();
  op_test_aux<Test, be::little_uint64un_t>();
  op_test_aux<Test, be::native_int8un_t>();
  op_test_aux<Test, be::native_int16un_t>();
  op_test_aux<Test, be::native_int24un_t>();
  op_test_aux<Test, be::native_int32un_t>();
  op_test_aux<Test, be::native_int40un_t>();
  op_test_aux<Test, be::native_int48un_t>();
  op_test_aux<Test, be::native_int56un_t>();
  op_test_aux<Test, be::native_int64un_t>();
  op_test_aux<Test, be::native_uint8un_t>();
  op_test_aux<Test, be::native_uint16un_t>();
  op_test_aux<Test, be::native_uint24un_t>();
  op_test_aux<Test, be::native_uint32un_t>();
  op_test_aux<Test, be::native_uint40un_t>();
  op_test_aux<Test, be::native_uint48un_t>();
  op_test_aux<Test, be::native_uint56un_t>();
  op_test_aux<Test, be::native_uint64un_t>();
#endif
}

//  main  ------------------------------------------------------------------------------//

int cpp_main(int, char * [])
{
  be::endian_log = false;

  //  make sure some simple things work

  be::big_int32un_t o1(1);
  be::big_int32un_t o2(2L);
  be::big_int32un_t o3(3LL);
  be::big_int64un_t o4(1);

  //  use cases; if BOOST_ENDIAN_LOG is defined, will output to clog info on
  //  what overloads and conversions are actually being performed.

  be::endian_log = true;

  std::clog << "set up test values\n";
  be::big_int32un_t      big(12345);
  be::little_uint16un_t  little_u(10);
  be::big_int64un_t      result;


  std::clog << "\nresult = +big\n";
  result = +big;

  std::clog << "\nresult = -big\n";
  result = -big;

  std::clog << "\n++big\n";
  ++big;

  std::clog << "\nresult = big++\n";
  result = big++;

  std::clog << "\n--big\n";
  --big;

  std::clog << "\nbig--\n";
  big--;

  std::clog << "\nresult = big * big\n";
  result = big * big;

  std::clog << "\nresult = big * big\n";
  result = big * big;

  std::clog << "\nresult = big * little_u\n";
  result = big * little_u;

  std::clog << "\nbig *= little_u\n";
  big *= little_u;

  std::clog << "\nresult = little_u * big\n";
  result = little_u * big;

  std::clog << "\nresult = big * 5\n";
  result = big * 5;

  std::clog << "\nbig *= 5\n";
  big *= 5;

  std::clog << "\nresult = 5 * big\n";
  result = 5 * big;

  std::clog << "\nresult = little_u * 5\n";
  result = little_u * 5;

  std::clog << "\nresult = 5 * little_u\n";
  result = 5 * little_u;

  std::clog << "\nresult = 5 * 10\n";
  result = 5 * 10;
  std::clog << "\n";

  be::endian_log = false;

  //  test from Roland Schwarz that detected ambiguities
  unsigned u;
  be::little_uint32un_t u1;
  be::little_uint32un_t u2;

  u = 1;
  u1 = 1;
  u2 = u1 + u;

  //  one more wrinkle
  be::little_uint16un_t u3(3);
  u3 = 3;
  u2 = u1 + u3;
    
  //  perform the indicated test on ~60*60 operand types

  op_test<default_construct>();
  op_test<construct>();  // includes copy construction
  op_test<initialize>();
  op_test<assign>();
  op_test<relational>();
  op_test<op_plus>();
  op_test<op_star>();

  return 0;
}
