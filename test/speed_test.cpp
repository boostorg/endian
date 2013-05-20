//  speed_test.cpp  --------------------------------------------------------------------//

//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

//#define BOOST_ENDIAN_NO_INTRINSICS

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/conversion.hpp>
#include <boost/endian/types.hpp>
#include <boost/cstdint.hpp>
#include <boost/timer/timer.hpp>
#include <iostream>
#include <cstdlib>
#include <boost/detail/lightweight_main.hpp>

using namespace boost;
using namespace boost::endian;

using std::cout;
using std::endl;

namespace
{
  typedef  boost::timer::nanosecond_type nanosecond_t;
  std::string command_args;
  uint64_t n;                 // number of test cases to run
  int places = 3;             // decimal places for times
  bool verbose (false);

  struct result_type
  {
    nanosecond_t cpu_time;   // system + user time
    uint64_t v;              // value computed; returning this may prevent
                             // optimizer from optimizing away the timing loop
  };

  void process_command_line(int argc, char * argv[])
  {
    for (int a = 0; a < argc; ++a)
    {
      command_args += argv[a];
      if (a != argc-1)
        command_args += ' ';
    }

    cout << command_args << '\n';;

    if (argc >=2)
#ifndef _MSC_VER
      n = std::atoll(argv[1]);
#else
      n = _atoi64(argv[1]);
#endif

    for (; argc > 2; ++argv, --argc) 
    {
      if ( *(argv[2]+1) == 'p' )
        places = atoi( argv[2]+2 );
      else if ( *(argv[2]+1) == 'v' )
        verbose = true;
      else
      {
        cout << "Error - unknown option: " << argv[2] << "\n\n";
        argc = -1;
        break;
      }
    }

    if (argc < 2) 
    {
      cout << "Usage: benchmark n [Options]\n"
              "  The argument n specifies the number of test cases to run\n"
              "  Options:\n"
              "   -v       Verbose messages\n"
              "   -p#      Decimal places for times; default -p" << places << "\n";
      return std::exit(1);
    }
  }

//--------------------------------------------------------------------------------------//

  template <class T, class EndianT>
  result_type test_inc(T x)
  {
    cout << "++ a value..." << endl;
    result_type result;
    result.v = 0;
    T y(x);
    boost::timer::auto_cpu_timer t(places);                  
    for (uint64_t i = 0; i < n; ++i)
    {
      ++y;
    }
    t.stop();
    result.v = static_cast<uint64_t>(y);
    boost::timer::cpu_times times = t.elapsed();
    result.cpu_time = (times.system + times.user);
    t.report();
    return result;
  }

  template <class T, class EndianT>
  result_type test_rev_inc(T x)
  {
    cout << "reverse, then ++, then reverse a value..." << endl;
    result_type result;
    result.v = 0;
    T y(x);
    boost::timer::auto_cpu_timer t(places);                  
    for (uint64_t i = 0; i < n; ++i)
    {
      reverse(y);
      ++y;
      reverse(y);
    }
    t.stop();
    result.v = static_cast<uint64_t>(y);
    boost::timer::cpu_times times = t.elapsed();
    result.cpu_time = (times.system + times.user);
    t.report();
    return result;
  }

  template <class T, class EndianT>
  result_type test_endian_inc(T x)
  {
    cout << "++ an endian value..." << endl;
    result_type result;
    result.v = 0;
    EndianT y(x);
    boost::timer::auto_cpu_timer t(places);                  
    for (uint64_t i = 0; i < n; ++i)
    {
      ++y;
    }
    t.stop();
    result.v = static_cast<uint64_t>(y);
    boost::timer::cpu_times times = t.elapsed();
    result.cpu_time = (times.system + times.user);
    t.report();
    return result;
  }

  template <class T, class EndianT>
  void test(T x)
  {
    test_inc<T, EndianT>(x);
    test_rev_inc<T, EndianT>(x);
    test_endian_inc<T, EndianT>(x);
  }

}  // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int argc, char* argv[])
{
  process_command_line(argc, argv);
  
  cout << "\nbyte swap intrinsics used: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

  cout << endl << "int16_t, big_int16_t" << endl;
  test<int16_t, big_int16_t>(0x1122);

  cout << endl << "int16_t, little_int16_t" << endl;
  test<int16_t, little_int16_t>(0x1122);

  cout << endl << "int32_t, big_int32_t" << endl;
  test<int32_t, big_int32_t>(0x11223344);

  cout << endl << "int32_t, little_int32_t" << endl;
  test<int32_t, little_int32_t>(0x11223344);

  cout << endl << "int64_t, big_int64_t" << endl;
  test<int64_t, big_int64_t>(0x1122334455667788);

  cout << endl << "int64_t, little_int64_t" << endl;
  test<int64_t, little_int64_t>(0x1122334455667788);

  //cout << "float" << endl;
  //test<float>(1.2345f);

  //cout << "double" << endl;
  //test<double>(1.23456789);

  return 0;
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
