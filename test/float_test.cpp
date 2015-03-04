//  float_test.cpp  --------------------------------------------------------------------//

//  Copyright Beman Dawes 2015

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

//--------------------------------------------------------------------------------------//

#include <boost/endian/detail/disable_warnings.hpp>

//#define BOOST_ENDIAN_LOG
#include <boost/endian/buffers.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>
#include <sstream>

using namespace boost::endian;
using std::cout;
using std::endl;
using std::numeric_limits;

namespace
{
  template <class T>
  void report_limits(const char* type)
  {
    cout << "\nHeader <limits> values for std::numeric_limits<" << type << ">\n\n";
    cout << "  is_specialized " << numeric_limits<T>::is_specialized << "\n";
    cout << "  min() " << numeric_limits<T>::min() << "\n";
    cout << "  max() " << numeric_limits<T>::max() << "\n";
    cout << "  lowest() " << numeric_limits<T>::lowest() << "\n";
    cout << "  digits " << numeric_limits<T>::digits << "\n";
    cout << "  digits10 " << numeric_limits<T>::digits10 << "\n";
    cout << "  max_digits10 " << numeric_limits<T>::max_digits10 << "\n";
  }

}  // unnamed namespace

//--------------------------------------------------------------------------------------//

int cpp_main(int, char *[])
{
  cout << "byte swap intrinsics: " BOOST_ENDIAN_INTRINSIC_MSG << endl;

  report_limits<float>("float");
  report_limits<double>("double");

  cout << "\n  done" << endl;

  return ::boost::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
