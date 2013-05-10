//  boost/endian/conversion.hpp  -------------------------------------------------------//

//  Copyright Beman Dawes 2010, 2011

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_CONVERTERS_HPP
#define BOOST_ENDIAN_CONVERTERS_HPP

#include "boost/config.hpp"
#include <boost/detail/endian.hpp>
#include <boost/cstdint.hpp>
#include <boost/detail/scoped_enum_emulation.hpp>
#include <algorithm>

//------------------------------------- synopsis ---------------------------------------//

namespace boost
{
namespace endian
{
#ifndef BOOST_ENDIAN_ORDER_ENUM_DEFINED
  BOOST_SCOPED_ENUM_START(order) { big, little, native }; BOOST_SCOPED_ENUM_END
# define BOOST_ENDIAN_ORDER_ENUM_DEFINED
#endif
  
  // reverse byte order (i.e. endianness)
  //   value returning interface approach suggested by Phil Endecott.
  inline int16_t  reverse_bytes(int16_t x) BOOST_NOEXCEPT;
  inline int32_t  reverse_bytes(int32_t x) BOOST_NOEXCEPT;
  inline int64_t  reverse_bytes(int64_t x) BOOST_NOEXCEPT;
  inline uint16_t reverse_bytes(uint16_t x) BOOST_NOEXCEPT;
  inline uint32_t reverse_bytes(uint32_t x) BOOST_NOEXCEPT;
  inline uint64_t reverse_bytes(uint64_t x) BOOST_NOEXCEPT;

  //  reverse_bytes overloads for floating point types as requested by Vicente
  //  Botet and others.
  // TODO: Need implementation
  // TODO: Need to verify the return does not invoke undefined behavior (as might happen
  // if there are unutterable floating point values, such as happens with the unutterable
  // pointer values that cause an immediate abort on some legacy architectures
  // TODO: Track progress of Floating-Point Typedefs Having Specified Widths proposal (N3626)
  // and add boost equivalent from Paul, Chris, John, if available
  inline float    reverse_bytes(float x) BOOST_NOEXCEPT;    
  inline double   reverse_bytes(double x) BOOST_NOEXCEPT;   

  //  general reverse_bytes function template to meet requests for UDT support by Vicente
  //  Botet and others. 
  template <class T>
  inline T reverse_bytes(T x) BOOST_NOEXCEPT;  // convert little to big or visa versa

  //  reverse bytes if native endian order is not big
  template <class T>
  inline T big(T x) BOOST_NOEXCEPT;      
    //  Return: x if native endian order is big, otherwise reverse_bytes(x)

  //  reverse bytes if native endian order is not little
  template <class T>
  inline T little(T x) BOOST_NOEXCEPT; 
    //  Return: x if native endian order is little, otherwise reverse_bytes(x);

  //  compile-time generic byte order conversion
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To, class T>
  inline T convert_bytes(T from) BOOST_NOEXCEPT; 

  //  runtime actual byte-order determination
  inline BOOST_SCOPED_ENUM(order) actual_order(BOOST_SCOPED_ENUM(order) o) BOOST_NOEXCEPT;
    //  Return: o if o != native, otherwise big or little depending on native ordering
  
  //  runtime byte-order conversion
  template <class T>
  T convert_bytes(T from, BOOST_SCOPED_ENUM(order) from_order,
                  BOOST_SCOPED_ENUM(order) to_order) BOOST_NOEXCEPT;

//----------------------------------- implementation -----------------------------------//
//    -- reverse_bytes implementation approach suggested by tymofey, with avoidance of
//       undefined behavior as suggested by Giovanni Piero Deretta, and a further
//       refinement suggested by Pyry Jahkola.
                                                
  inline int16_t reverse_bytes(int16_t x) BOOST_NOEXCEPT
  {
    return (static_cast<uint16_t>(x) << 8)
      | (static_cast<uint16_t>(x) >> 8);
  }

  inline int32_t reverse_bytes(int32_t x) BOOST_NOEXCEPT
  {
    uint32_t step16;
    step16 = static_cast<uint32_t>(x) << 16 | static_cast<uint32_t>(x) >> 16;
    return
        ((static_cast<uint32_t>(step16) << 8) & 0xff00ff00)
      | ((static_cast<uint32_t>(step16) >> 8) & 0x00ff00ff);
  }

  inline int64_t reverse_bytes(int64_t x) BOOST_NOEXCEPT
  {
    uint64_t step32, step16;
    step32 = static_cast<uint64_t>(x) << 32 | static_cast<uint64_t>(x) >> 32;
    step16 = (step32 & 0x0000FFFF0000FFFF) << 16
           | (step32 & 0xFFFF0000FFFF0000) >> 16;
    return static_cast<int64_t>((step16 & 0x00FF00FF00FF00FF) << 8
           | (step16 & 0xFF00FF00FF00FF00) >> 8);
  }

  inline uint16_t reverse_bytes(uint16_t x) BOOST_NOEXCEPT
  {
    return (x << 8)
      | (x >> 8);
  }

  inline uint32_t reverse_bytes(uint32_t x) BOOST_NOEXCEPT
  {
    uint32_t step16;
    step16 = x << 16 | x >> 16;
    return
        ((step16 << 8) & 0xff00ff00)
      | ((step16 >> 8) & 0x00ff00ff);
  }

  inline uint64_t reverse_bytes(uint64_t x) BOOST_NOEXCEPT
  {
    uint64_t step32, step16;
    step32 = x << 32 | x >> 32;
    step16 = (step32 & 0x0000FFFF0000FFFF) << 16
           | (step32 & 0xFFFF0000FFFF0000) >> 16;
    return (step16 & 0x00FF00FF00FF00FF) << 8
           | (step16 & 0xFF00FF00FF00FF00) >> 8;
  }

//  general reverse_bytes function template implementation approach using std::reverse
//  suggested by Mathias Gaunard
  template <class T>
  inline T reverse_bytes(T x) BOOST_NOEXCEPT
  {
    T tmp;
    std::reverse(
      reinterpret_cast<const char*>(&x),
      reinterpret_cast<const char*>(&x) + sizeof(T),
      reinterpret_cast<char*>(&tmp));
    return tmp;
  }

  template <class T>
  inline T big(T x) BOOST_NOEXCEPT
  {
#   ifdef BOOST_BIG_ENDIAN
      return x;
#   else
      return reverse_bytes(x);
#   endif
  }

  template <class T>
  inline T little(T x) BOOST_NOEXCEPT    
  {
#   ifdef BOOST_LITTLE_ENDIAN
      return x;
#   else
      return reverse_bytes(x);
#   endif
  }

  inline BOOST_SCOPED_ENUM(order) actual_order(BOOST_SCOPED_ENUM(order) o) BOOST_NOEXCEPT
  {
    return o != order::native ? o :
 #   ifdef BOOST_LITTLE_ENDIAN
      order::little
#   else
      order::big
#   endif
    ;
  }

  template <class T>
  T convert_bytes(T from, BOOST_SCOPED_ENUM(order) from_order,
                  BOOST_SCOPED_ENUM(order) to_order) BOOST_NOEXCEPT
  {
    if (actual_order(from_order) == order::big)
      return actual_order(to_order) == order::big ? from : reverse_bytes(from);
    // actual from_order is little
    return actual_order(to_order) == order::little ? from : reverse_bytes(from);
  }

}  // namespace endian
}  // namespace boost

#endif // BOOST_ENDIAN_CONVERTERS_HPP
