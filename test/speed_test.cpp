//  speed_test.cpp  --------------------------------------------------------------------//

//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

//#define BOOST_ENDIAN_NO_INTRINSICS
//#define BOOST_ENDIAN_LOG

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

  template <class T>
  result_type test_add_T_to_T(T x)
  {
    cout << "Add T to T ..." << endl;
    result_type result;
    T y(0);
    boost::timer::auto_cpu_timer t(places);                  
    for (uint64_t i = 0; i < n; ++i)
    {
      y += x;
    }
    t.stop();
    result.v = static_cast<uint64_t>(y);
    boost::timer::cpu_times times = t.elapsed();
    result.cpu_time = (times.system + times.user);
    t.report();
    return result;
  }

  struct big_tag {};
  struct little_tag {};

  template <class T>
  result_type test_add_conditionally_reversed_T_to_T(T x, big_tag)
  {
    cout << "add_conditionally_reversed_T_to_T (big)..." << endl;
    result_type result;
    T y(0);
    boost::timer::auto_cpu_timer t(places);                  
    for (uint64_t i = 0; i < n; ++i)
    {
      y += ::boost::endian::big_endian_value(x);
    }
    t.stop();
    result.v = static_cast<uint64_t>(y);
    boost::timer::cpu_times times = t.elapsed();
    result.cpu_time = (times.system + times.user);
    t.report();
    return result;
  }

  template <class T>
  result_type test_add_conditionally_reversed_T_to_T(T x, little_tag)
  {
    cout << "add_conditionally_reversed_T_to_T (little)..." << endl;
    result_type result;
    T y(0);
    boost::timer::auto_cpu_timer t(places);                  
    for (uint64_t i = 0; i < n; ++i)
    {
      y += ::boost::endian::little_endian_value(x);
    }
    t.stop();
    result.v = static_cast<uint64_t>(y);
    boost::timer::cpu_times times = t.elapsed();
    result.cpu_time = (times.system + times.user);
    t.report();
    return result;
  }

  template <class T, class EndianT>
  result_type test_add_Endian_to_T(EndianT x)
  {
    cout << "add_Endian_to_T..." << endl;
    result_type result;
    T y(0);
    boost::timer::auto_cpu_timer t(places);                  
    for (uint64_t i = 0; i < n; ++i)
    {
      y += x;
    }
    t.stop();
    result.v = static_cast<uint64_t>(y);
    boost::timer::cpu_times times = t.elapsed();
    result.cpu_time = (times.system + times.user);
    t.report();
    return result;
  }

  template <class T, BOOST_SCOPED_ENUM(order) Order, class EndianT>
  void test(T x)
  {
    test_add_T_to_T<T>(x);
    if (Order == order::big)
      test_add_conditionally_reversed_T_to_T<T>(x, big_tag());
    else
      test_add_conditionally_reversed_T_to_T<T>(x, little_tag());
    test_add_Endian_to_T<T, EndianT>(EndianT(x));
  }

}  // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int argc, char* argv[])
{
  process_command_line(argc, argv);
  
  cout << "\nbyte swap intrinsics used: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

  cout << endl << "------------------------------------------------------" << endl;

  cout << endl << "int16_t, big_16_t" << endl;
  test<int16_t, order::big, big_16_t>(0x1122);
  cout << endl << "int16_t, big_int16_t" << endl;
  test<int16_t, order::big, big_int16_t>(0x1122);

  cout << endl << "int16_t, little_16_t" << endl;
  test<int16_t, order::little, little_16_t>(0x1122);
  cout << endl << "int16_t, little_int16_t" << endl;
  test<int16_t, order::little, little_int16_t>(0x1122);

  cout << endl << "------------------------------------------------------" << endl;

  cout << endl << "int32_t, big_32_t" << endl;
  test<int32_t, order::big, big_32_t>(0x11223344);
  cout << endl << "int32_t, big_int32_t" << endl;
  test<int32_t, order::big, big_int32_t>(0x11223344);

  cout << endl << "int32_t, little_32_t" << endl;
  test<int32_t, order::little, little_32_t>(0x11223344);
  cout << endl << "int32_t, little_int32_t" << endl;
  test<int32_t, order::little, little_int32_t>(0x11223344);

  cout << endl << "------------------------------------------------------" << endl;

  cout << endl << "int64_t, big_64_t" << endl;
  test<int64_t, order::big, big_64_t>(0x1122334455667788);
  cout << endl << "int64_t, big_int64_t" << endl;
  test<int64_t, order::big, big_int64_t>(0x1122334455667788);

  cout << endl << "int64_t, little_64_t" << endl;
  test<int64_t, order::little, little_64_t>(0x1122334455667788);
  cout << endl << "int64_t, little_int64_t" << endl;
  test<int64_t, order::little, little_int64_t>(0x1122334455667788);

  cout << endl << "------------------------------------------------------" << endl;

  //cout << "float" << endl;
  //test<float>(1.2345f);

  //cout << "double" << endl;
  //test<double>(1.23456789);

  return 0;
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
