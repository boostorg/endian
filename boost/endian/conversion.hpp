//  boost/endian/conversion.hpp  -------------------------------------------------------//

//  Copyright Beman Dawes 2010, 2011

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_CONVERSION_HPP
#define BOOST_ENDIAN_CONVERSION_HPP

#include <boost/detail/endian.hpp>
#include <boost/cstdint.hpp>

//------------------------------------- synopsis ---------------------------------------//

namespace boost
{
namespace endian
{
  // unconditional modifying (i.e. in-place) endianness reversal

  inline void flip(int16_t& x);
  inline void flip(int32_t& x);
  inline void flip(int64_t& x);
  inline void flip(uint16_t& x);
  inline void flip(uint32_t& x);
  inline void flip(uint64_t& x);

  // unconditional non-modifying endianness reversing copy

  inline void flip(int16_t source, int16_t& target);
  inline void flip(int32_t source, int32_t& target);
  inline void flip(int64_t source, int64_t& target);
  inline void flip(uint16_t source, uint16_t& target);
  inline void flip(uint32_t source, uint32_t& target);
  inline void flip(uint64_t source, uint64_t& target);

  // conditional modifying (i.e. in-place) endianness reversal;
  //  no effect if native endianness and specified endianness are the same

  template <class T> inline void to_big(T& x);       // if different, convert native to big
  template <class T> inline void to_little(T& x);    // if different, convert native to little
  template <class T> inline void from_big(T& x);     // if different, convert big to native
  template <class T> inline void from_little(T& x);  // if different, convert little to native

  // non-modifying copy, conditionally reversing endianness;
  //   copy the first argument to the second argument, converting to or from the
  //   specified endianness if different than native endianness

  template <class T> inline void to_big(T native, T& big);
  template <class T> inline void to_little(T native, T& little);
  template <class T> inline void from_big(T big, T& native);
  template <class T> inline void from_little(T little, T& native);

//----------------------------------- implementation -----------------------------------//
                                                
  inline void flip(int16_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+1);
    *(rep+1) = tmp;
  }

  inline void flip(int32_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+3);
    *(rep+3) = tmp;
    tmp = *(rep+1);
    *(rep+1) = *(rep+2);
    *(rep+2) = tmp;
  }

  inline void flip(int64_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+7);
    *(rep+7) = tmp;
    tmp = *(rep+1);
    *(rep+1) = *(rep+6);
    *(rep+6) = tmp;
    tmp = *(rep+2);
    *(rep+2) = *(rep+5);
    *(rep+5) = tmp;
    tmp = *(rep+3);
    *(rep+3) = *(rep+4);
    *(rep+4) = tmp;
  }

  inline void flip(uint16_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+1);
    *(rep+1) = tmp;
  }

  inline void flip(uint32_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+3);
    *(rep+3) = tmp;
    tmp = *(rep+1);
    *(rep+1) = *(rep+2);
    *(rep+2) = tmp;
  }

  inline void flip(uint64_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+7);
    *(rep+7) = tmp;
    tmp = *(rep+1);
    *(rep+1) = *(rep+6);
    *(rep+6) = tmp;
    tmp = *(rep+2);
    *(rep+2) = *(rep+5);
    *(rep+5) = tmp;
    tmp = *(rep+3);
    *(rep+3) = *(rep+4);
    *(rep+4) = tmp;
  }

  inline void flip(int16_t source, int16_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
  }

  inline void flip(int32_t source, int32_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
  }

  inline void flip(int64_t source, int64_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
  }

  inline void flip(uint16_t source, uint16_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
  }

  inline void flip(uint32_t source, uint32_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
  }

  inline void flip(uint64_t source, uint64_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
  }

  template <class T> inline void to_big(T& x)
  {
#   ifdef BOOST_LITTLE_ENDIAN
      flip(x);
#   endif
  }

  template <class T> inline void to_little(T& x)
  {
#   ifdef BOOST_BIG_ENDIAN
      flip(x);
#   endif
  }

  template <class T> inline void from_big(T& x)
  {
#   ifdef BOOST_LITTLE_ENDIAN
      flip(x);
#   endif
  }

  template <class T> inline void from_little(T& x)
  {
#   ifdef BOOST_BIG_ENDIAN
      flip(x);
#   endif
  }

  template <class T> inline void to_big(T native, T& big)
  {
#   ifdef BOOST_LITTLE_ENDIAN
      flip(native, big);
#   else
      big = native;
#   endif
  }

  template <class T> inline void to_little(T native, T& little)
  {
#   ifdef BOOST_BIG_ENDIAN
      flip(native, little);
#   else
      little = native;
#   endif
  }

  template <class T> inline void from_big(T big, T& native)
  {
#   ifdef BOOST_LITTLE_ENDIAN
      flip(big, native);
#   else
      native = big;
#   endif
  }

  template <class T> inline void from_little(T little, T& native)
  {
#   ifdef BOOST_BIG_ENDIAN
      flip(little, native);
#   else
      native = little;
#   endif
  }
}  // namespace endian
}  // namespace boost

#endif // BOOST_ENDIAN_CONVERSION_HPP
