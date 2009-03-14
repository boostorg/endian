//  boost/binary_stream.hpp  ----------------------------------------------------------//

//  Copyright Beman Dawes, 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See documentation at http://www.boost.org/libs/utility

#ifndef BOOST_BINARY_STREAM_HPP
#define BOOST_BINARY_STREAM_HPP

#include <ostream>
#include <istream>
#include <string>
#include <cstring>  // for strlen
#include <cwchar>   // for wcslen

namespace boost
{

  //  binary input and output for built-in types

  //  omission of bool and void* is deliberate; any semantics would be questionable

  inline std::ostream& operator<=(std::ostream& os, short v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, short& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, unsigned short v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, unsigned short& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, int v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, int& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, unsigned int v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, unsigned int& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, long v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, long& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, unsigned long v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, unsigned long& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, long long v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, long long& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, unsigned long long v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, unsigned long long& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, float v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, float& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, double v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, double& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, long double v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, long double& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  inline std::ostream& operator<=(std::ostream& os, char c)
    { return os.put( c ); }
  inline std::istream& operator>=(std::istream& is, char& c)
    { return is.get( c ); }

  inline std::ostream& operator<=(std::ostream& os, signed char c)
    { return os.put( c ); }
  inline std::istream& operator>=(std::istream& is, signed char& c)
    { return is.get( reinterpret_cast<char&>(c) ); }

  inline std::ostream& operator<=(std::ostream& os, unsigned char c)
    { return os.put( c ); }
  inline std::istream& operator>=(std::istream& is, unsigned char& c)
    { return is.get( reinterpret_cast<char&>(c) ); }

  inline std::ostream& operator<=(std::ostream& os, wchar_t v)
    { return os.write( reinterpret_cast<const char*>(&v), sizeof(v) ); }
  inline std::istream& operator>=(std::istream& is, wchar_t& v)
    { return is.read( reinterpret_cast<char*>(&v), sizeof(v) ); }

  //  binary input and output for strings

  inline std::ostream& operator<=(std::ostream& os, const char* p)
    { return os.write( p, std::strlen(p)+1 ); }

  inline std::ostream& operator<=(std::ostream& os, const signed char* p)
    { return os.write( reinterpret_cast<const char*>(p), std::strlen(reinterpret_cast<const char*>(p))+1 ); }

  inline std::ostream& operator<=(std::ostream& os, const unsigned char* p)
    { return os.write( reinterpret_cast<const char*>(p), std::strlen(reinterpret_cast<const char*>(p))+1 ); }

  inline std::ostream& operator<=(std::ostream& os, const wchar_t* p)
    { return os.write( reinterpret_cast<const char*>(p), (std::wcslen(p)+1)*sizeof(wchar_t) ); }

  //  Caution: note the asymmetry between output and input; a string with embedded
  //  nulls will be output with the embedded nulls, but input will stop at the first null.
  //  So it probably isn't a good idea to use these functions for strings with nulls.
  inline std::ostream& operator<=(std::ostream& os, const std::string& s)
    { return os.write( s.c_str(), s.size()+1 ); }
  inline std::istream& operator>=(std::istream& is, std::string& s)
    { return getline(is, s, '\0'); }

  inline std::ostream& operator<=(std::ostream& os, const std::wstring& s)
    { return os.write( reinterpret_cast<const char*>(s.c_str()), (s.size()+1)*sizeof(wchar_t) ); }
  // TODO: provide input function


}  // namespace boost

#endif  // BOOST_BINARY_STREAM_HPP
