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

#define BOOST_ENDIAN_LOG

#include <boost/endian/detail/disable_warnings.hpp>

#ifdef _MSC_VER
# pragma warning( disable : 4242 )  // conversion ..., possible loss of data
# pragma warning( disable : 4244 )  // conversion ..., possible loss of data
# pragma warning( disable : 4018 )  // signed/unsigned mismatch
# pragma warning( disable : 4365 )  // signed/unsigned mismatch
# pragma warning( disable : 4389 )  // signed/unsigned mismatch
#endif

#include <boost/endian/integers.hpp>
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
  Test<T1, be::big16_t>::test();
  Test<T1, be::ubig64_t>::test();
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
  Test<T1, be::big8_t>::test();
  Test<T1, be::big16_t>::test();
  Test<T1, be::big24_t>::test();
  Test<T1, be::big32_t>::test();
  Test<T1, be::big40_t>::test();
  Test<T1, be::big48_t>::test();
  Test<T1, be::big56_t>::test();
  Test<T1, be::big64_t>::test();
  Test<T1, be::ubig8_t>::test();
  Test<T1, be::ubig16_t>::test();
  Test<T1, be::ubig24_t>::test();
  Test<T1, be::ubig32_t>::test();
  Test<T1, be::ubig40_t>::test();
  Test<T1, be::ubig48_t>::test();
  Test<T1, be::ubig56_t>::test();
  Test<T1, be::ubig64_t>::test();
  Test<T1, be::little8_t>::test();
  Test<T1, be::little16_t>::test();
  Test<T1, be::little24_t>::test();
  Test<T1, be::little32_t>::test();
  Test<T1, be::little40_t>::test();
  Test<T1, be::little48_t>::test();
  Test<T1, be::little56_t>::test();
  Test<T1, be::little64_t>::test();
  Test<T1, be::ulittle8_t>::test();
  Test<T1, be::ulittle16_t>::test();
  Test<T1, be::ulittle24_t>::test();
  Test<T1, be::ulittle32_t>::test();
  Test<T1, be::ulittle40_t>::test();
  Test<T1, be::ulittle48_t>::test();
  Test<T1, be::ulittle56_t>::test();
  Test<T1, be::ulittle64_t>::test();
  Test<T1, be::native8_t>::test();
  Test<T1, be::native16_t>::test();
  Test<T1, be::native24_t>::test();
  Test<T1, be::native32_t>::test();
  Test<T1, be::native40_t>::test();
  Test<T1, be::native48_t>::test();
  Test<T1, be::native56_t>::test();
  Test<T1, be::native64_t>::test();
  Test<T1, be::unative8_t>::test();
  Test<T1, be::unative16_t>::test();
  Test<T1, be::unative24_t>::test();
  Test<T1, be::unative32_t>::test();
  Test<T1, be::unative40_t>::test();
  Test<T1, be::unative48_t>::test();
  Test<T1, be::unative56_t>::test();
  Test<T1, be::unative64_t>::test();
#endif
}

template <template<class,  class> class Test>
void op_test()
{
#ifdef BOOST_SHORT_ENDIAN_TEST
  op_test_aux<Test, unsigned short>();
  op_test_aux<Test, int>();
  op_test_aux<Test, be::big32_t>();
  op_test_aux<Test, be::ubig32_t>();
  op_test_aux<Test, be::little48_t>();
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
  op_test_aux<Test, be::big8_t>();
  op_test_aux<Test, be::big16_t>();
  op_test_aux<Test, be::big24_t>();
  op_test_aux<Test, be::big32_t>();
  op_test_aux<Test, be::big40_t>();
  op_test_aux<Test, be::big48_t>();
  op_test_aux<Test, be::big56_t>();
  op_test_aux<Test, be::big64_t>();
  op_test_aux<Test, be::ubig8_t>();
  op_test_aux<Test, be::ubig16_t>();
  op_test_aux<Test, be::ubig24_t>();
  op_test_aux<Test, be::ubig32_t>();
  op_test_aux<Test, be::ubig40_t>();
  op_test_aux<Test, be::ubig48_t>();
  op_test_aux<Test, be::ubig56_t>();
  op_test_aux<Test, be::ubig64_t>();
  op_test_aux<Test, be::little8_t>();
  op_test_aux<Test, be::little16_t>();
  op_test_aux<Test, be::little24_t>();
  op_test_aux<Test, be::little32_t>();
  op_test_aux<Test, be::little40_t>();
  op_test_aux<Test, be::little48_t>();
  op_test_aux<Test, be::little56_t>();
  op_test_aux<Test, be::little64_t>();
  op_test_aux<Test, be::ulittle8_t>();
  op_test_aux<Test, be::ulittle16_t>();
  op_test_aux<Test, be::ulittle24_t>();
  op_test_aux<Test, be::ulittle32_t>();
  op_test_aux<Test, be::ulittle40_t>();
  op_test_aux<Test, be::ulittle48_t>();
  op_test_aux<Test, be::ulittle56_t>();
  op_test_aux<Test, be::ulittle64_t>();
  op_test_aux<Test, be::native8_t>();
  op_test_aux<Test, be::native16_t>();
  op_test_aux<Test, be::native24_t>();
  op_test_aux<Test, be::native32_t>();
  op_test_aux<Test, be::native40_t>();
  op_test_aux<Test, be::native48_t>();
  op_test_aux<Test, be::native56_t>();
  op_test_aux<Test, be::native64_t>();
  op_test_aux<Test, be::unative8_t>();
  op_test_aux<Test, be::unative16_t>();
  op_test_aux<Test, be::unative24_t>();
  op_test_aux<Test, be::unative32_t>();
  op_test_aux<Test, be::unative40_t>();
  op_test_aux<Test, be::unative48_t>();
  op_test_aux<Test, be::unative56_t>();
  op_test_aux<Test, be::unative64_t>();
#endif
}

//  main  ------------------------------------------------------------------------------//

int cpp_main(int, char * [])
{
  be::endian_log = false;

  //  make sure some simple things work

  be::big32_t o1(1);
  be::big32_t o2(2L);
  be::big32_t o3(3LL);
  be::big64_t o4(1);

  //  use cases; if BOOST_ENDIAN_LOG is defined, will output to clog info on
  //  what overloads and conversions are actually being performed.

  be::endian_log = true;

  std::clog << "set up test values\n";
  be::big32_t      big(12345);
  be::ulittle16_t  ulittle(10);
  be::big64_t      result;


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

  std::clog << "\nresult = big * ulittle\n";
  result = big * ulittle;

  std::clog << "\nbig *= ulittle\n";
  big *= ulittle;

  std::clog << "\nresult = ulittle * big\n";
  result = ulittle * big;

  std::clog << "\nresult = big * 5\n";
  result = big * 5;

  std::clog << "\nbig *= 5\n";
  big *= 5;

  std::clog << "\nresult = 5 * big\n";
  result = 5 * big;

  std::clog << "\nresult = ulittle * 5\n";
  result = ulittle * 5;

  std::clog << "\nresult = 5 * ulittle\n";
  result = 5 * ulittle;

  std::clog << "\nresult = 5 * 10\n";
  result = 5 * 10;
  std::clog << "\n";

  be::endian_log = false;

  //  test from Roland Schwarz that detected ambiguities
  unsigned u;
  be::ulittle32_t u1;
  be::ulittle32_t u2;

  u = 1;
  u1 = 1;
  u2 = u1 + u;

  //  one more wrinkle
  be::ulittle16_t u3(3);
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
