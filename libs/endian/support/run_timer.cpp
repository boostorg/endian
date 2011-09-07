//  boost run_timer.cpp  -----------------------------------------------------//

//  Copyright Beman Dawes 1994-2006

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/system for documentation.

//----------------------------------------------------------------------------//

// define BOOST_ENDIAN_SOURCE so that <boost/endian/detail/config.hpp> knows
// the library is being built (possibly exporting rather than importing code)
#define BOOST_ENDIAN_SOURCE

#include <boost/endian/support/timer.hpp>
#include <boost/system/system_error.hpp>
#include <boost/io/ios_state.hpp>
#include <boost/throw_exception.hpp>
#include <boost/cerrno.hpp>
#include <cstring>
#include <cassert>

using boost::endian::microsecond_t;
using boost::endian::times_t;
using boost::system::error_code;

# if defined(BOOST_WINDOWS_API)
#   include <windows.h>
# elif defined(BOOST_POSIX_API)
#   include <sys/times.h>
# else
# error unknown API
# endif

namespace
{
  const char * default_format =
    " %ws wall, %us user + %ss system = %ts cpu (%p%)\n";

void show_time(const char * format, int places, std::ostream& os,
    const times_t& times)
  //  NOTE WELL: Will truncate least-significant digits to LDBL_DIG, which may
  //  be as low as 10, although will be 15 for many common platforms.
  {
    if (times.wall < microsecond_t(0))
      return;
    if (places > 6)
      places = 6;
    else if (places < 0)
      places = 0;

    boost::io::ios_flags_saver ifs(os);
    boost::io::ios_precision_saver ips(os);
    os.setf(std::ios_base::fixed, std::ios_base::floatfield);
    os.precision(places);

    const long double sec = 1000000.0L;
    microsecond_t total = times.system + times.user;
    long double wall_sec = times.wall / sec;
    long double total_sec = total / sec;

    for (; *format; ++format)
    {
      if (*format != '%' || !*(format+1) || !std::strchr("wustp", *(format+1)))
        os << *format;
      else
      {
        ++format;
        switch (*format)
        {
        case 'w':
          os << times.wall / sec;
          break;
        case 'u':
          os << times.user / sec;
          break;
        case 's':
          os << times.system / sec;
          break;
        case 't':
          os << total / sec;
          break;
        case 'p':
          os.precision(1);
          if (wall_sec > 0.001L && total_sec > 0.001L)
            os << (total_sec/wall_sec) * 100.0;
          else
            os << "n/a";
          os.precision(places);
          break;
        default:
          assert(0);
        }
      }
    }
  }

}  // unnamed namespace

namespace boost
{
  namespace endian
  {
    //  run_timer:: report  --------------------------------------//

    void run_timer::report()
    {
      show_time(!m_format
          ? default_format
          : m_format,
        m_places, m_os, this->stop());
    }

    error_code run_timer::report(error_code& ec)
    {
      try
      {
        report();
        ec = error_code();
      }

      catch (...) // eat any exceptions
      {
        ec = error_code(EIO, system::generic_category());
      }

      return ec;
    }

  } // namespace endian
} // namespace boost
