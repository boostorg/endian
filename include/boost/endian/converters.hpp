//  boost/endian/converters.hpp  -------------------------------------------------------//

//  Copyright Beman Dawes 2010, 2011

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_CONVERTERS_HPP
#define BOOST_ENDIAN_CONVERTERS_HPP

#include <boost/config.hpp>
#include <boost/detail/endian.hpp>
#include <boost/cstdint.hpp>
#include <boost/endian/detail/intrinsic.hpp>
#include <boost/detail/scoped_enum_emulation.hpp>
#include <boost/static_assert.hpp>
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
  //  TODO: Track progress of Floating-Point Typedefs Having Specified Widths proposal (N3626)
  inline float    reverse_bytes(float x) BOOST_NOEXCEPT;
  inline double   reverse_bytes(double x) BOOST_NOEXCEPT;   

  //  general reverse_bytes function template to meet requests for UDT support by Vicente
  //  Botet and others. 
  template <class T>
  inline T reverse_bytes(T x) BOOST_NOEXCEPT;  // convert little to big or visa versa

  //  reverse bytes unless native endianness is big
  //  possible names: reverse_unless_native_big, reverse_bytes_unless_big, reverse_unless_big
  template <class T>
  inline T big(T x) BOOST_NOEXCEPT;    
    //  Return: x if native endian order is big, otherwise reverse_bytes(x)

  //  reverse bytes unless native endianness is little
  //  possible names: reverse_unless_native_little, reverse_bytes_unless_little, reverse_unless_little
  template <class T>
  inline T little(T x) BOOST_NOEXCEPT; 
    //  Return: x if native endian order is little, otherwise reverse_bytes(x);

  //  compile-time generic byte order conversion
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To, class T>
  T convert(T from) BOOST_NOEXCEPT; 

  //  runtime actual byte-order determination
  inline BOOST_SCOPED_ENUM(order) actual_order(BOOST_SCOPED_ENUM(order) o) BOOST_NOEXCEPT;
    //  Return: o if o != native, otherwise big or little depending on native ordering
  
  //  runtime byte-order conversion
  template <class T>
  T convert(T from, BOOST_SCOPED_ENUM(order) from_order,
            BOOST_SCOPED_ENUM(order) to_order) BOOST_NOEXCEPT;

//----------------------------------- implementation -----------------------------------//
//    -- reverse_bytes portable approach suggested by tymofey, with avoidance of
//       undefined behavior as suggested by Giovanni Piero Deretta, and a further
//       refinement suggested by Pyry Jahkola.
//    -- reverse_bytes intrinsic approach suggested by David Stone, who privided his
//       Boost licensed macro implementation.
                                                
  inline int16_t reverse_bytes(int16_t x) BOOST_NOEXCEPT
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    return (static_cast<uint16_t>(x) << 8)
      | (static_cast<uint16_t>(x) >> 8);
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(static_cast<uint16_t>(x));
# endif
  }

  inline int32_t reverse_bytes(int32_t x) BOOST_NOEXCEPT
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    uint32_t step16;
    step16 = static_cast<uint32_t>(x) << 16 | static_cast<uint32_t>(x) >> 16;
    return
        ((static_cast<uint32_t>(step16) << 8) & 0xff00ff00)
      | ((static_cast<uint32_t>(step16) >> 8) & 0x00ff00ff);
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(static_cast<uint32_t>(x));
# endif
  }

  inline int64_t reverse_bytes(int64_t x) BOOST_NOEXCEPT
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    uint64_t step32, step16;
    step32 = static_cast<uint64_t>(x) << 32 | static_cast<uint64_t>(x) >> 32;
    step16 = (step32 & 0x0000FFFF0000FFFF) << 16
           | (step32 & 0xFFFF0000FFFF0000) >> 16;
    return static_cast<int64_t>((step16 & 0x00FF00FF00FF00FF) << 8
           | (step16 & 0xFF00FF00FF00FF00) >> 8);
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(static_cast<uint64_t>(x));
# endif
  }

  inline uint16_t reverse_bytes(uint16_t x) BOOST_NOEXCEPT
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    return (x << 8)
      | (x >> 8);
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x);
# endif
  }

  inline uint32_t reverse_bytes(uint32_t x) BOOST_NOEXCEPT                           
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    uint32_t step16;
    step16 = x << 16 | x >> 16;
    return
        ((step16 << 8) & 0xff00ff00)
      | ((step16 >> 8) & 0x00ff00ff);
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(x);
# endif
  }

  inline uint64_t reverse_bytes(uint64_t x) BOOST_NOEXCEPT
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    uint64_t step32, step16;
    step32 = x << 32 | x >> 32;
    step16 = (step32 & 0x0000FFFF0000FFFF) << 16
           | (step32 & 0xFFFF0000FFFF0000) >> 16;
    return (step16 & 0x00FF00FF00FF00FF) << 8
           | (step16 & 0xFF00FF00FF00FF00) >> 8;
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x);
# endif
  }

  inline float reverse_bytes(float x) BOOST_NOEXCEPT
  {
    BOOST_STATIC_ASSERT_MSG(sizeof(float) == sizeof(uint32_t),
      "boost::endian only supprts sizeof(float) == 4; please report error to boost mailing list");
    uint32_t tmp = reverse_bytes(*(const uint32_t*)&x);
    return *(const float*)&tmp;
  }

  inline double reverse_bytes(double x) BOOST_NOEXCEPT
  {
    BOOST_STATIC_ASSERT_MSG(sizeof(double) == sizeof(uint64_t),
      "boost::endian only supprts sizeof(double) == 8; please report error to boost mailing list");
    uint64_t tmp = reverse_bytes(*(const uint64_t*)&x);
    return *(const double*)&tmp;
  }

//  general reverse_bytes function template implementation approach using std::reverse
//  suggested by Mathias Gaunard
  template <class T>
  inline T reverse_bytes(T x) BOOST_NOEXCEPT
  {
    T tmp(x);
    std::reverse(
      reinterpret_cast<char*>(&tmp),
      reinterpret_cast<char*>(&tmp) + sizeof(T));
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

  template<> inline int16_t convert<order::big, order::big>(int16_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline int16_t convert<order::little, order::little>(int16_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline int16_t convert<order::native, order::native>(int16_t x) BOOST_NOEXCEPT {return x;}

  template<> inline uint16_t convert<order::big, order::big>(uint16_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline uint16_t convert<order::little, order::little>(uint16_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline uint16_t convert<order::native, order::native>(uint16_t x) BOOST_NOEXCEPT {return x;}

  template<> inline int32_t convert<order::big, order::big>(int32_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline int32_t convert<order::little, order::little>(int32_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline int32_t convert<order::native, order::native>(int32_t x) BOOST_NOEXCEPT {return x;}

  template<> inline uint32_t convert<order::big, order::big>(uint32_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline uint32_t convert<order::little, order::little>(uint32_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline uint32_t convert<order::native, order::native>(uint32_t x) BOOST_NOEXCEPT {return x;} 

  template<> inline int64_t convert<order::big, order::big>(int64_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline int64_t convert<order::little, order::little>(int64_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline int64_t convert<order::native, order::native>(int64_t x) BOOST_NOEXCEPT {return x;}

  template<> inline uint64_t convert<order::big, order::big>(uint64_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline uint64_t convert<order::little, order::little>(uint64_t x) BOOST_NOEXCEPT {return x;} 
  template<> inline uint64_t convert<order::native, order::native>(uint64_t x) BOOST_NOEXCEPT {return x;} 

  template<> inline float convert<order::big, order::big>(float x) BOOST_NOEXCEPT {return x;} 
  template<> inline float convert<order::little, order::little>(float x) BOOST_NOEXCEPT {return x;} 
  template<> inline float convert<order::native, order::native>(float x) BOOST_NOEXCEPT {return x;} 

  template<> inline double convert<order::big, order::big>(double x) BOOST_NOEXCEPT {return x;} 
  template<> inline double convert<order::little, order::little>(double x) BOOST_NOEXCEPT {return x;} 
  template<> inline double convert<order::native, order::native>(double x) BOOST_NOEXCEPT {return x;} 

  template<> inline int16_t convert<order::big, order::little>(int16_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline int16_t convert<order::big, order::native>(int16_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline int16_t convert<order::little, order::big>(int16_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline int16_t convert<order::little, order::native>(int16_t x) BOOST_NOEXCEPT {return little(x);}
  template<> inline int16_t convert<order::native, order::big>(int16_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline int16_t convert<order::native, order::little>(int16_t x) BOOST_NOEXCEPT {return little(x);}

  template<> inline uint16_t convert<order::big, order::little>(uint16_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline uint16_t convert<order::big, order::native>(uint16_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline uint16_t convert<order::little, order::big>(uint16_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline uint16_t convert<order::little, order::native>(uint16_t x) BOOST_NOEXCEPT {return little(x);}
  template<> inline uint16_t convert<order::native, order::big>(uint16_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline uint16_t convert<order::native, order::little>(uint16_t x) BOOST_NOEXCEPT {return little(x);}

  template<> inline int32_t convert<order::big, order::little>(int32_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline int32_t convert<order::big, order::native>(int32_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline int32_t convert<order::little, order::big>(int32_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline int32_t convert<order::little, order::native>(int32_t x) BOOST_NOEXCEPT {return little(x);}
  template<> inline int32_t convert<order::native, order::big>(int32_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline int32_t convert<order::native, order::little>(int32_t x) BOOST_NOEXCEPT {return little(x);}

  template<> inline uint32_t convert<order::big, order::little>(uint32_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline uint32_t convert<order::big, order::native>(uint32_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline uint32_t convert<order::little, order::big>(uint32_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline uint32_t convert<order::little, order::native>(uint32_t x) BOOST_NOEXCEPT {return little(x);}
  template<> inline uint32_t convert<order::native, order::big>(uint32_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline uint32_t convert<order::native, order::little>(uint32_t x) BOOST_NOEXCEPT {return little(x);}

  template<> inline int64_t convert<order::big, order::little>(int64_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline int64_t convert<order::big, order::native>(int64_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline int64_t convert<order::little, order::big>(int64_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline int64_t convert<order::little, order::native>(int64_t x) BOOST_NOEXCEPT {return little(x);}
  template<> inline int64_t convert<order::native, order::big>(int64_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline int64_t convert<order::native, order::little>(int64_t x) BOOST_NOEXCEPT {return little(x);}

  template<> inline uint64_t convert<order::big, order::little>(uint64_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline uint64_t convert<order::big, order::native>(uint64_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline uint64_t convert<order::little, order::big>(uint64_t x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline uint64_t convert<order::little, order::native>(uint64_t x) BOOST_NOEXCEPT {return little(x);}
  template<> inline uint64_t convert<order::native, order::big>(uint64_t x) BOOST_NOEXCEPT {return big(x);}
  template<> inline uint64_t convert<order::native, order::little>(uint64_t x) BOOST_NOEXCEPT {return little(x);}

  template<> inline float convert<order::big, order::little>(float x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline float convert<order::big, order::native>(float x) BOOST_NOEXCEPT {return big(x);}
  template<> inline float convert<order::little, order::big>(float x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline float convert<order::little, order::native>(float x) BOOST_NOEXCEPT {return little(x);}
  template<> inline float convert<order::native, order::big>(float x) BOOST_NOEXCEPT {return big(x);}
  template<> inline float convert<order::native, order::little>(float x) BOOST_NOEXCEPT {return little(x);}

  template<> inline double convert<order::big, order::little>(double x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline double convert<order::big, order::native>(double x) BOOST_NOEXCEPT {return big(x);}
  template<> inline double convert<order::little, order::big>(double x) BOOST_NOEXCEPT {return reverse_bytes(x);}
  template<> inline double convert<order::little, order::native>(double x) BOOST_NOEXCEPT {return little(x);}
  template<> inline double convert<order::native, order::big>(double x) BOOST_NOEXCEPT {return big(x);}
  template<> inline double convert<order::native, order::little>(double x) BOOST_NOEXCEPT {return little(x);}

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
  T convert(T from, BOOST_SCOPED_ENUM(order) from_order,
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
