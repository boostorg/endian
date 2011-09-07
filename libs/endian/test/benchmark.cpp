//  benchmark.cpp  ---------------------------------------------------------------------//

//  Copyright Beman Dawes 2011

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#define _CRT_SECURE_NO_WARNINGS

#include <boost/endian/conversion.hpp>
#include <boost/random.hpp>
#include <boost/cstdint.hpp>
#include <boost/endian/support/timer.hpp>
#include <iostream>

using namespace boost;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

#define BENCHMARK(Function)                     \
{                                               \
  cout << "\nRunning benchmark..." << endl << ' ';     \
  int64_t sum = 0;                              \
  int32_t value;                                \
                                                \
  endian::run_timer t;                          \
                                                \
  for (int32_t i = n; i; --i)                   \
  {                                             \
    value = 0x01020304;                         \
    Function(value);                            \
    sum += value ;                              \
  }                                             \
                                                \
  t.report();                                   \
                                                \
  cout << "  Benchmark complete\n"              \
          "    sum is " << sum << endl;         \
}

namespace
{
  std::string command_args;
  long n;
  long seed = 1;
  int places = 2;

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
      n = std::atol(argv[1]);

    for (; argc > 2; ++argv, --argc) 
    {
      if ( *(argv[2]+1) == 'p' )
        places = atoi( argv[2]+2 );
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
              "   -p#      Decimal places for times; default -p" << places << "\n";
      return std::exit(1);
    }
  }

  inline void noop(int32_t&) {}

  inline void shift_and_mask(int32_t& x)
  {
    x = ((x << 24) & 0xff000000) | ((x << 8) & 0x00ff0000) | ((x >> 24) & 0x000000ff)
      | ((x >> 8) & 0x0000ff00);
  }

} // unnamed namespace

//-------------------------------------- main()  ---------------------------------------//

int main(int argc, char * argv[]) 
{
  process_command_line(argc, argv);

  BENCHMARK(noop);
  BENCHMARK(endian::reorder);
  BENCHMARK(shift_and_mask);

  return 0;
}
