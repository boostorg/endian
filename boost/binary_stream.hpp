//  boost/binary_stream.hpp  ----------------------------------------------------------//

//  Copyright Beman Dawes, 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See documentation at http://www.boost.org/libs/utility

#ifndef BOOST_BINARY_STREAM_HPP
#define BOOST_BINARY_STREAM_HPP

#include <ostream>
#include <istream>

namespace boost
{

  //  binary output for built-in types

  //  omission of bool is deliberate; semantics undecided
  inline std::ostream& operator<=(std::ostream& os, short v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, unsigned short v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, int v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, unsigned int v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, long v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, unsigned long v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, long long v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, unsigned long long v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, float v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, double v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, long double v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::ostream& operator<=(std::ostream& os, const void* p)
    { return os.write( static_cast<const char*>(p), sizeof(p) ); }
  inline std::ostream& operator<=(std::ostream& os, char c)
    { return os.put( c ); }
  inline std::ostream& operator<=(std::ostream& os, signed char c)
    { return os.put( c ); }
  inline std::ostream& operator<=(std::ostream& os, unsigned char c)
    { return os.put( c ); }
  inline std::ostream& operator<=(std::ostream& os, const char* p)
    { return os.write( p, std::strlen(p)+1 ); }
  inline std::ostream& operator<=(std::ostream& os, const signed char* p)
    { return os.write( static_cast<const char*>(p), std::strlen(p)+1 ); }
  inline std::ostream& operator<=(std::ostream& os, const unsigned char* p)
    { return os.write( static_cast<const char*>(p), std::strlen(p)+1 ); }


//// 27.6.2.6 Formatted output:
//basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>& (*pf)(basic_ostream<charT,traits>&));
//basic_ostream<charT,traits>& operator<<(basic_ios<charT,traits>& (*pf)(basic_ios<charT,traits>&));
//basic_ostream<charT,traits>& operator<<(ios_base& (*pf)(ios_base&));
//basic_ostream<charT,traits>& operator<<(bool n);
//basic_ostream<charT,traits>& operator<<(short n);
//basic_ostream<charT,traits>& operator<<(unsigned short n);
//basic_ostream<charT,traits>& operator<<(int n);
//basic_ostream<charT,traits>& operator<<(unsigned int n);
//basic_ostream<charT,traits>& operator<<(long n);
//basic_ostream<charT,traits>& operator<<(unsigned long n);
//basic_ostream<charT,traits>& operator<<(long long n);
//basic_ostream<charT,traits>& operator<<(unsigned long long n);
//basic_ostream<charT,traits>& operator<<(float f);
//basic_ostream<charT,traits>& operator<<(double f);
//basic_ostream<charT,traits>& operator<<(long double f);
//basic_ostream<charT,traits>& operator<<(const void* p);
//basic_ostream<charT,traits>& operator<<(basic_streambuf<char_type,traits>* sb);
//
//// 27.6.2.6.4 character inserters
//template<class charT, class traits>
//basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>&, charT);
//template<class charT, class traits>
//basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>&&, charT);
//template<class charT, class traits>
//basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>&, char);
//template<class charT, class traits>
//basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>&&, char);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&, char);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&&, char);
//
//// signed and unsigned
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&, signed char);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&&, signed char);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&, unsigned char);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&&, unsigned char);
//
//template<class charT, class traits>
//basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>&, const charT*);
//template<class charT, class traits>
//basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>&&, const charT*);
//template<class charT, class traits>
//basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>&, const char*);
//template<class charT, class traits>
//basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>&&, const char*);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&, const char*);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&&, const char*);
//
//// signed and unsigned
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&, const signed char*);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&&, const signed char*);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&, const unsigned char*);
//template<class traits>
//basic_ostream<char,traits>& operator<<(basic_ostream<char,traits>&&, const unsigned char*);
//
//// 21.3.8.9: inserters and extractors
//template<class charT, class traits, class Allocator>
//basic_istream<charT,traits>& operator>>(basic_istream<charT,traits>&& is, basic_string<charT,traits,Allocator>& str);
//template<class charT, class traits, class Allocator>
//basic_ostream<charT, traits>& operator<<(basic_ostream<charT, traits>&& os, const basic_string<charT,traits,Allocator>& str);
//template<class charT, class traits, class Allocator>
//basic_istream<charT,traits>& getline(basic_istream<charT,traits>&& is, basic_string<charT,traits,Allocator>& str, charT delim);
//template<class charT, class traits, class Allocator>
//basic_istream<charT,traits>& getline(basic_istream<charT,traits>&& is, basic_string<charT,traits,Allocator>& str);

}  // namespace boost

#endif  // BOOST_BINARY_STREAM_HPP
