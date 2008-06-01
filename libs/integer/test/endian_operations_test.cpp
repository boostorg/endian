//  endian_operations_test.cpp  ----------------------------------------------//

//  Copyright Beman Dawes 2008

//  Distributed under the Boost Software License,  Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/endian

//----------------------------------------------------------------------------//

#include <boost/integer/endian.hpp>
#include <cassert>

#ifdef _MSC_VER
# pragma warning( disable : 4244 )
#endif

using namespace boost::integer;

template <class T1,  class T2>
struct default_construct
{
  static void test()
  {
    T1 o1;
    o1 = 1; // quiet warnings
  }
};

template <class T1,  class T2>
struct construct
{
  static void test()
  {
    T2 o2(1);
    T1 o1(o2);
  }
};

template <class T1,  class T2>
struct assign
{
  static void test()
  {
    T2 o2;
    o2 = 123;
    T1 o1;
    o1 = 02;
  }
};

template <class T1,  class T2>
struct pass
{
  static void test()
  {
  }
};

template <class T1,  class T2>
struct compare
{
  static void test()
  {
    T1 o1 = 1;
    T2 o2 = 2;
    if (o1 == o2) return;
  }
};

template <template<class,  class> class Test,  class T1>
void op_test_aux()
{
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
  Test<T1, big8_t>::test();
  Test<T1, big16_t>::test();
  Test<T1, big24_t>::test();
  Test<T1, big32_t>::test();
  Test<T1, big40_t>::test();
  Test<T1, big48_t>::test();
  Test<T1, big56_t>::test();
  Test<T1, big64_t>::test();
  Test<T1, ubig8_t>::test();
  Test<T1, ubig16_t>::test();
  Test<T1, ubig24_t>::test();
  Test<T1, ubig32_t>::test();
  Test<T1, ubig40_t>::test();
  Test<T1, ubig48_t>::test();
  Test<T1, ubig56_t>::test();
  Test<T1, ubig64_t>::test();
  Test<T1, little8_t>::test();
  Test<T1, little16_t>::test();
  Test<T1, little24_t>::test();
  Test<T1, little32_t>::test();
  Test<T1, little40_t>::test();
  Test<T1, little48_t>::test();
  Test<T1, little56_t>::test();
  Test<T1, little64_t>::test();
  Test<T1, ulittle8_t>::test();
  Test<T1, ulittle16_t>::test();
  Test<T1, ulittle24_t>::test();
  Test<T1, ulittle32_t>::test();
  Test<T1, ulittle40_t>::test();
  Test<T1, ulittle48_t>::test();
  Test<T1, ulittle56_t>::test();
  Test<T1, ulittle64_t>::test();
  Test<T1, native8_t>::test();
  Test<T1, native16_t>::test();
  Test<T1, native24_t>::test();
  Test<T1, native32_t>::test();
  Test<T1, native40_t>::test();
  Test<T1, native48_t>::test();
  Test<T1, native56_t>::test();
  Test<T1, native64_t>::test();
  Test<T1, unative8_t>::test();
  Test<T1, unative16_t>::test();
  Test<T1, unative24_t>::test();
  Test<T1, unative32_t>::test();
  Test<T1, unative40_t>::test();
  Test<T1, unative48_t>::test();
  Test<T1, unative56_t>::test();
  Test<T1, unative64_t>::test();

}

template <template<class,  class> class Test>
void op_test()
{
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
  op_test_aux<Test, big8_t>();
  op_test_aux<Test, big16_t>();
  op_test_aux<Test, big24_t>();
  op_test_aux<Test, big32_t>();
  op_test_aux<Test, big40_t>();
  op_test_aux<Test, big48_t>();
  op_test_aux<Test, big56_t>();
  op_test_aux<Test, big64_t>();
  op_test_aux<Test, ubig8_t>();
  op_test_aux<Test, ubig16_t>();
  op_test_aux<Test, ubig24_t>();
  op_test_aux<Test, ubig32_t>();
  op_test_aux<Test, ubig40_t>();
  op_test_aux<Test, ubig48_t>();
  op_test_aux<Test, ubig56_t>();
  op_test_aux<Test, ubig64_t>();
  op_test_aux<Test, little8_t>();
  op_test_aux<Test, little16_t>();
  op_test_aux<Test, little24_t>();
  op_test_aux<Test, little32_t>();
  op_test_aux<Test, little40_t>();
  op_test_aux<Test, little48_t>();
  op_test_aux<Test, little56_t>();
  op_test_aux<Test, little64_t>();
  op_test_aux<Test, ulittle8_t>();
  op_test_aux<Test, ulittle16_t>();
  op_test_aux<Test, ulittle24_t>();
  op_test_aux<Test, ulittle32_t>();
  op_test_aux<Test, ulittle40_t>();
  op_test_aux<Test, ulittle48_t>();
  op_test_aux<Test, ulittle56_t>();
  op_test_aux<Test, ulittle64_t>();
  op_test_aux<Test, native8_t>();
  op_test_aux<Test, native16_t>();
  op_test_aux<Test, native24_t>();
  op_test_aux<Test, native32_t>();
  op_test_aux<Test, native40_t>();
  op_test_aux<Test, native48_t>();
  op_test_aux<Test, native56_t>();
  op_test_aux<Test, native64_t>();
  op_test_aux<Test, unative8_t>();
  op_test_aux<Test, unative16_t>();
  op_test_aux<Test, unative24_t>();
  op_test_aux<Test, unative32_t>();
  op_test_aux<Test, unative40_t>();
  op_test_aux<Test, unative48_t>();
  op_test_aux<Test, unative56_t>();
  op_test_aux<Test, unative64_t>();
}

int main()
{
  

  big32_t o1(1);
  big32_t o2(2L);
  big32_t o3(3LL);

  op_test<default_construct>();
  op_test<construct>();
  op_test<assign>();
  op_test<pass>();
  op_test<compare>();
  return 0;
}
