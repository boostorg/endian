//  speed_test.cpp  --------------------------------------------------------------------//

//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/converters.hpp>
#include <boost/endian/integers.hpp>
#include <boost/chrono.hpp>
#include <boost/cstdint.hpp>
#include <iostream>
#include <cstdlib>
#include <boost/detail/lightweight_main.hpp>

using namespace boost::endian;
using namespace boost::chrono;

using std::cout;
using std::endl;
using boost::int16_t;
using boost::uint16_t;
using boost::int32_t;
using boost::uint32_t;
using boost::int64_t;
using boost::uint64_t;

namespace
{
  long default_length(1);
  steady_clock::duration length = seconds(default_length);

  template <class T, class Endian>
  uint32_t test(T x)
  {
    uint32_t count = 0;
    T y = x;
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end = start + length; 
    while (steady_clock::now() < end)
    {
      ++count;
      reverse(y);
      ++y;
      reverse(y);
    }

    cout << "  loop executed " << count << " times" << endl;
//    cout << "  x is 0x" << std::hex << x << std::dec << endl;

    count = 0;
    //Endian z(x);
    Endian z;
    start = steady_clock::now();
    end = start + length; 
    while (steady_clock::now() < end)
    {
      ++count;
      ++z;
    }

    cout << "  loop executed " << count << " times" << endl;

    return count;
  }

  uint32_t nop_test()
  {
    uint32_t count = 0;
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end = start + length; 
    while (steady_clock::now() < end)
    {
      ++count;
    }

    cout << "  loop executed " << count << " times" << endl;

    return count;
  }


}  // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int argc, char* argv[])
{
  if (argc > 1)
    length = seconds(atol(argv[1]));
  else
  {
    cout << "Invoke: speed_test [s]\n"
      "  where s is the number of seconds each test will be run (default "
      << default_length << (default_length <= 1 ? " second)" : " seconds)") << endl;
  }
  
  cout << "\nbyte swap intrinsics used: " BOOST_ENDIAN_INTRINSIC_MSG << endl << endl;
  
  //std::cerr << std::hex;

  cout << "nop" << endl;
  nop_test();


  cout << "int16_t, big16_t" << endl;
  test<int16_t, big16_t>(0x1122);

  cout << "uint16_t" << endl;
  test<uint16_t, ubig16_t>(0x1122U);

  cout << "int32_t, big32_t" << endl;
  test<int32_t, big32_t>(0x11223344);

  cout << "uint32_t, ubig32_t" << endl;
  test<uint32_t, ubig32_t>(0x11223344UL);

  cout << "int64_t, big64_t" << endl;
  test<int64_t, big64_t>(0x1122334455667788);

  cout << "uint64_t, ubig64_t" << endl;
  test<uint64_t, ubig64_t>(0x1122334455667788ULL);

  //cout << "float" << endl;
  //test<float>(1.2345f);

  //cout << "double" << endl;
  //test<double>(1.23456789);

  return 0;
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
