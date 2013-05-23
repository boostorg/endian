//  speed_test.cpp  --------------------------------------------------------------------//

//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

//#define BOOST_ENDIAN_NO_INTRINSICS
//#define BOOST_ENDIAN_LOG

#include <boost/endian/detail/disable_warnings.hpp>

#include "speed_test_functions.hpp"
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
      cout << "Usage: speed_test n [Options]\n"
              "  The argument n specifies the number of test cases to run\n"
              "  Options:\n"
              "   -v       Verbose messages\n"
              "   -p#      Decimal places for times; default -p" << places << "\n";
      return std::exit(1);
    }
  }

//--------------------------------------------------------------------------------------//

  template <class T, class EndianT, class Function>
  void time(Function f)
  {
    T x(0);
    T y(0);
    EndianT z(0);
    boost::timer::auto_cpu_timer t(places);                  
    for (uint64_t i = 0; i < n; ++i)
    {
      f(x, y, z);
    }
    t.stop();
    boost::timer::cpu_times times = t.elapsed();
//    result.cpu_time = (times.system + times.user);
    t.report();
  }

  void test_big_int32()
  {
    cout << " no +\n ";
    time<int32_t, big_int32_t>(user::return_x_big_int32);
    cout << " + int32_t argument\n ";
    time<int32_t, big_int32_t>(user::return_x_plus_y_big_int32);
    cout << " + int32_t by value\n ";
    time<int32_t, big_int32_t>(user::return_x_plus_y_value_big_int32);
    cout << " + int32_t in place\n ";
    time<int32_t, big_int32_t>(user::return_x_plus_y_in_place_big_int32);
    cout << " + big_int32_t\n ";
    time<int32_t, big_int32_t>(user::return_x_plus_z_big_int32);
  }

  void test_little_int32()
  {
    cout << " no +\n ";
    time<int32_t, little_int32_t>(user::return_x_little_int32);
    cout << " + int32_t argument\n ";
    time<int32_t, little_int32_t>(user::return_x_plus_y_little_int32);
    cout << " + int32_t by value\n ";
    time<int32_t, little_int32_t>(user::return_x_plus_y_value_little_int32);
    cout << " + int32_t in place\n ";
    time<int32_t, little_int32_t>(user::return_x_plus_y_in_place_little_int32);
    cout << " + little_int32_t\n ";
    time<int32_t, little_int32_t>(user::return_x_plus_z_little_int32);
  }

}  // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int argc, char* argv[])
{
  process_command_line(argc, argv);
  
  cout << "\nbyte swap intrinsics used: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

  cout << endl << "------------------------------------------------------" << endl;

  cout << endl << "big, 32-bit..." << endl;
  test_big_int32();
  cout << endl << "little, 32-bit..." << endl;
  test_little_int32();

  cout << endl << "------------------------------------------------------" << endl;

  //cout << "float" << endl;
  //test<float>(1.2345f);

  //cout << "double" << endl;
  //test<double>(1.23456789);

  return 0;
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
