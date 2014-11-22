//  boost/endian/conversion.hpp  -------------------------------------------------------//

//  Copyright Beman Dawes 2010, 2011, 2014

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_CONVERTERS_HPP
#define BOOST_ENDIAN_CONVERTERS_HPP

#include <boost/config.hpp>
#include <boost/predef/detail/endian_compat.h>
#include <boost/cstdint.hpp>
#include <boost/endian/detail/intrinsic.hpp>
#include <boost/detail/scoped_enum_emulation.hpp>
#include <boost/static_assert.hpp>
#include <algorithm>
#include <cstring>  // for memcpy

//------------------------------------- synopsis ---------------------------------------//

namespace boost
{
namespace endian
{
#ifndef BOOST_ENDIAN_ORDER_ENUM_DEFINED
  BOOST_SCOPED_ENUM_START(order)
  {
    big, little,
# ifdef  BOOST_BIG_ENDIAN
      native = big
# else
      native = little
# endif
  }; BOOST_SCOPED_ENUM_END
# define BOOST_ENDIAN_ORDER_ENUM_DEFINED
#endif

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                             value returning interfaces                               //
//                        approach suggested by Phil Endecott                           //
//                                                                                      //
//                             user-defined types (UDTs)                                //
//                                                                                      //
//  All value returning conversion function templates are required to be implemented in //
//  terms of an unqualified call to "reverse(x)", a function returning the value of x   //
//  with endianness reversed. This provides a customization point for any UDT that      //
//  provides a "reverse" free-function meeting the requirements. It must be declared    //
//  in the same namespace as the UDT itself so that it will be found by argument        //
//  dependent lookup (ADL).                                                             //
//                                                                                      //
//--------------------------------------------------------------------------------------//
  
  //  value returning reverse byte order (i.e. endianness)
  inline int8_t   reverse(int8_t x) BOOST_NOEXCEPT;
  inline int16_t  reverse(int16_t x) BOOST_NOEXCEPT;
  inline int32_t  reverse(int32_t x) BOOST_NOEXCEPT;
  inline int64_t  reverse(int64_t x) BOOST_NOEXCEPT;
  inline uint8_t  reverse(uint8_t x) BOOST_NOEXCEPT;
  inline uint16_t reverse(uint16_t x) BOOST_NOEXCEPT;
  inline uint32_t reverse(uint32_t x) BOOST_NOEXCEPT;
  inline uint64_t reverse(uint64_t x) BOOST_NOEXCEPT;
  //  TODO: Track progress of Floating-Point Typedefs Having Specified Widths proposal (N3626)
  inline float    reverse(float x) BOOST_NOEXCEPT;
  inline double   reverse(double x) BOOST_NOEXCEPT;

  //  reverse byte order unless native endianness is big
  template <class ReversibleValue >
  inline ReversibleValue  big(ReversibleValue  x) BOOST_NOEXCEPT;    
  //  Returns: x if native endian order is big, otherwise reverse(x)

  //  reverse byte order unless native endianness is little
  template <class ReversibleValue >
  inline ReversibleValue  little(ReversibleValue  x) BOOST_NOEXCEPT;
  //  Returns: x if native endian order is little, otherwise reverse(x)

  //  generic conditional reverse byte order
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To,
            class ReversibleValue >
  ReversibleValue  reverse(ReversibleValue from) BOOST_NOEXCEPT;

  //  runtime byte order determination
  inline BOOST_SCOPED_ENUM(order) effective_order(BOOST_SCOPED_ENUM(order) o) BOOST_NOEXCEPT;
  //  Return: o if o != native, otherwise big or little depending on native ordering
  
  //  runtime conditional reverse byte order
  template <class ReversibleValue >
  ReversibleValue  reverse(ReversibleValue from, BOOST_SCOPED_ENUM(order) from_order,
    BOOST_SCOPED_ENUM(order) to_order) BOOST_NOEXCEPT;

  //  Q: What happended to bswap, htobe, and the other synonym functions based on names
  //     popularized by BSD, OS X, and Linux?
  //  A: Turned out these may be implemented as macros on some systems. Ditto POSIX names
  //     for such functionality. Since macros would cause endless problems with functions
  //     of the same names, and these functions are just synonyms anyhow, they have been
  //     removed.


  //------------------------------------------------------------------------------------//
  //                                                                                    //
  //                            reverse in place interfaces                             //
  //                                                                                    //
  //                             user-defined types (UDTs)                              //
  //                                                                                    //
  //  All reverse in place function templates are required to be implemented in terms   // 
  //  of an unqualified call to "reverse_in_place(x)", a function reversing the         //
  //  endianness of x, which is a non-const reference. This provides a customization    //
  //  point for any UDT that provides a "reverse_in_place" free-function meeting the    //
  //  requirements. The free-function must be declared in the same namespace as the     //
  //  UDT itself so that it will be found by argument-dependent lookup (ADL).           //
  //                                                                                    //
  //------------------------------------------------------------------------------------//

  //  reverse byte-order in place (i.e. flip endianness)
  inline void reverse_in_place(int8_t& x) BOOST_NOEXCEPT;
  inline void reverse_in_place(int16_t& x) BOOST_NOEXCEPT;
  inline void reverse_in_place(int32_t& x) BOOST_NOEXCEPT;
  inline void reverse_in_place(int64_t& x) BOOST_NOEXCEPT;
  inline void reverse_in_place(uint8_t& x) BOOST_NOEXCEPT;
  inline void reverse_in_place(uint16_t& x) BOOST_NOEXCEPT;
  inline void reverse_in_place(uint32_t& x) BOOST_NOEXCEPT;
  inline void reverse_in_place(uint64_t& x) BOOST_NOEXCEPT;
  inline void reverse_in_place(float& x) BOOST_NOEXCEPT;
  inline void reverse_in_place(double& x) BOOST_NOEXCEPT;

  //  reverse in place unless native endianness is big
  template <class Reversible>
  inline void big_in_place(Reversible& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is big, otherwise reverse_in_place(x)

  //  reverse in place unless native endianness is little
  template <class Reversible>
  inline void little_in_place(Reversible& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is little, otherwise reverse_in_place(x);

  //  fully generic conditional reverse in place
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To, class Reversible>
  void reverse_in_place(Reversible& x) BOOST_NOEXCEPT; 

  //  runtime reverse in place
  template <class Reversible>
  void reverse_in_place(Reversible& x, BOOST_SCOPED_ENUM(order) from_order,
    BOOST_SCOPED_ENUM(order) to_order) BOOST_NOEXCEPT;

//----------------------------------- end synopsis -------------------------------------//

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                   implementation                                     //
//                                                                                      //
//    -- reverse portable approach suggested by tymofey, with avoidance of              //
//       undefined behavior as suggested by Giovanni Piero Deretta, and a further       //
//       refinement suggested by Pyry Jahkola.                                          //
//    -- reverse intrinsic approach suggested by reviewers, and by David Stone,         //
//       who provided his Boost licensed macro implementation (detail/intrinsic.hpp)    //
//                                                                                      //
//--------------------------------------------------------------------------------------//

  inline int8_t reverse(int8_t x) BOOST_NOEXCEPT
  {
    return x;
  }
                                                
  inline int16_t reverse(int16_t x) BOOST_NOEXCEPT
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    return (static_cast<uint16_t>(x) << 8)
      | (static_cast<uint16_t>(x) >> 8);
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(static_cast<uint16_t>(x));
# endif
  }

  inline int32_t reverse(int32_t x) BOOST_NOEXCEPT
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

  inline int64_t reverse(int64_t x) BOOST_NOEXCEPT
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    uint64_t step32, step16;
    step32 = static_cast<uint64_t>(x) << 32 | static_cast<uint64_t>(x) >> 32;
    step16 = (step32 & 0x0000FFFF0000FFFFULL) << 16
           | (step32 & 0xFFFF0000FFFF0000ULL) >> 16;
    return static_cast<int64_t>((step16 & 0x00FF00FF00FF00FFULL) << 8
           | (step16 & 0xFF00FF00FF00FF00ULL) >> 8);
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(static_cast<uint64_t>(x));
# endif
  }
  
  inline uint8_t reverse(uint8_t x) BOOST_NOEXCEPT
  {
    return x;
  }

  inline uint16_t reverse(uint16_t x) BOOST_NOEXCEPT
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    return (x << 8)
      | (x >> 8);
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x);
# endif
  }

  inline uint32_t reverse(uint32_t x) BOOST_NOEXCEPT                           
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

  inline uint64_t reverse(uint64_t x) BOOST_NOEXCEPT
  {
# ifdef BOOST_ENDIAN_NO_INTRINSICS  
    uint64_t step32, step16;
    step32 = x << 32 | x >> 32;
    step16 = (step32 & 0x0000FFFF0000FFFFULL) << 16
           | (step32 & 0xFFFF0000FFFF0000ULL) >> 16;
    return (step16 & 0x00FF00FF00FF00FFULL) << 8
           | (step16 & 0xFF00FF00FF00FF00ULL) >> 8;
# else
    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x);
# endif
  }

  inline float reverse(float x) BOOST_NOEXCEPT
  {
    BOOST_STATIC_ASSERT_MSG(sizeof(float) == sizeof(uint32_t),
      "boost::endian only supprts sizeof(float) == 4; please report error to boost mailing list");
    return detail::generic_reverse(x);
  }

  inline double reverse(double x) BOOST_NOEXCEPT
  {
    BOOST_STATIC_ASSERT_MSG(sizeof(double) == sizeof(uint64_t),
      "boost::endian only supprts sizeof(double) == 8; please report error to boost mailing list");
    return detail::generic_reverse(x);
  }

  namespace detail
  {
    //  generic reverse function template implementation approach using std::reverse
    //  suggested by Mathias Gaunard.
    template <class T>
    inline T generic_reverse(T x) BOOST_NOEXCEPT
    {
      T tmp(x);
      std::reverse(
        reinterpret_cast<char*>(&tmp),
        reinterpret_cast<char*>(&tmp) + sizeof(T));
      return tmp;
    }
  }  // namespace detail

  template <class ReversibleValue >
  inline ReversibleValue  big(ReversibleValue  x) BOOST_NOEXCEPT
  {
#   ifdef BOOST_BIG_ENDIAN
      return x;
#   else
      return reverse(x);
#   endif
  }

  template <class ReversibleValue >
  inline ReversibleValue  little(ReversibleValue  x) BOOST_NOEXCEPT    
  {
#   ifdef BOOST_LITTLE_ENDIAN
      return x;
#   else
      return reverse(x);
#   endif
  }

  namespace detail
  {
    //  Primary template and specializations to support convert_value(). See rationale in
    //  convert_value() below.
    template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To, class Reversible>
      class value_converter ;  // primary template
    template <class T> class value_converter <order::big, order::big, T>
      {public: T operator()(T x) BOOST_NOEXCEPT {return x;}};
    template <class T> class value_converter <order::little, order::little, T>
      {public: T operator()(T x) BOOST_NOEXCEPT {return x;}};
    template <class T> class value_converter <order::big, order::little, T>
      {public: T operator()(T x) BOOST_NOEXCEPT {return reverse_value(x);}};
    template <class T> class value_converter <order::little, order::big, T>
      {public: T operator()(T x) BOOST_NOEXCEPT {return reverse_value(x);}};
  }

  //  compile-time generic convert return by value
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To, class Reversible>
  Reversible convert_value(Reversible x) BOOST_NOEXCEPT
  {
    //  work around lack of function template partial specialization by instantiating
    //  a function object of a class that is partially specialized on the two order
    //  template parameters, and then calling its operator().
    detail::value_converter <From, To, Reversible> tmp;
    return tmp(x);
  }

  inline BOOST_SCOPED_ENUM(order)
    effective_order(BOOST_SCOPED_ENUM(order) o) BOOST_NOEXCEPT
  {
    return o != order::native ? o :
 #   ifdef BOOST_LITTLE_ENDIAN
      order::little
#   else
      order::big
#   endif
    ;
  }

  template <class ReversibleValue >
  ReversibleValue  convert_value(ReversibleValue  from,
    BOOST_SCOPED_ENUM(order) from_order, BOOST_SCOPED_ENUM(order) to_order) BOOST_NOEXCEPT
  {
    return effective_order(from_order) == effective_order(to_order)
      ? from : reverse(from);
  }

//--------------------------------------------------------------------------------------//
//                            reverse in place implementation                           //
//--------------------------------------------------------------------------------------//

  //  reverse byte-order in place (i.e. flip endianness)
  inline void reverse_in_place(int8_t& x) BOOST_NOEXCEPT   { x = reverse(x); }
  inline void reverse_in_place(int16_t& x) BOOST_NOEXCEPT  { x = reverse(x); }
  inline void reverse_in_place(int32_t& x) BOOST_NOEXCEPT  { x = reverse(x); }
  inline void reverse_in_place(int64_t& x) BOOST_NOEXCEPT  { x = reverse(x); }
  inline void reverse_in_place(uint8_t& x) BOOST_NOEXCEPT  { x = reverse(x); }
  inline void reverse_in_place(uint16_t& x) BOOST_NOEXCEPT { x = reverse(x); }
  inline void reverse_in_place(uint32_t& x) BOOST_NOEXCEPT { x = reverse(x); }
  inline void reverse_in_place(uint64_t& x) BOOST_NOEXCEPT { x = reverse(x); }
  inline void reverse_in_place(float& x) BOOST_NOEXCEPT    { x = reverse(x); }
  inline void reverse_in_place(double& x) BOOST_NOEXCEPT   { x = reverse(x); }

  //  reverse in place unless native endianness is big
  //    Effects: none if native endian order is big, otherwise reverse_in_place(x)
  template <class Reversible>
#   ifdef BOOST_BIG_ENDIAN
  inline void big_in_place(Reversible&) BOOST_NOEXCEPT {}
#   else
  inline void big_in_place(Reversible& x) BOOST_NOEXCEPT { reverse_in_place(x); }
#   endif

  //  reverse in placeunless native endianness is little
  //    Effects: none if native endian order is little, otherwise reverse_in_place(x)
  template <class Reversible>
#   ifdef BOOST_LITTLE_ENDIAN
  inline void little_in_place(Reversible&) BOOST_NOEXCEPT {}
#   else
  inline void little_in_place(Reversible& x) BOOST_NOEXCEPT { reverse_in_place(x); }
#   endif

  namespace detail
  {
    //  Primary template and specializations to support generic reverse_in_place().
    //  See rationale in reverse_in_place() below.
    template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To, class Reversible>
      class converter;  // primary template
    template <class T> class converter<order::big, order::big, T>
      {public: void operator()(T&) BOOST_NOEXCEPT {/*no effect*/}};
    template <class T> class converter<order::little, order::little, T>
      {public: void operator()(T&) BOOST_NOEXCEPT {/*no effect*/}};
    template <class T> class converter<order::big, order::little, T>
      {public: void operator()(T& x) BOOST_NOEXCEPT { reverse_in_place(x); }};
    template <class T> class converter<order::little, order::big, T>
      {public: void operator()(T& x) BOOST_NOEXCEPT { reverse_in_place(x); }};
  }  // namespace detail

  //  fully generic conditional reverse in place
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To, class Reversible>
  void reverse_in_place(Reversible& x) BOOST_NOEXCEPT
  {
    //  work around lack of function template partial specialization by instantiating
    //  a function object of a class that is partially specialized on the two order
    //  template parameters, and then calling its operator().
    detail::converter<From, To, Reversible> tmp;
    tmp(x);  // call operator ()
  }

  //  runtime reverse in place
  template <class Reversible>
  void reverse_in_place(Reversible& x, BOOST_SCOPED_ENUM(order) from_order,
            BOOST_SCOPED_ENUM(order) to_order) BOOST_NOEXCEPT
  {
    if (effective_order(from_order) != effective_order(to_order))
      reverse_in_place(x);
  }

}  // namespace endian
}  // namespace boost

#endif // BOOST_ENDIAN_CONVERTERS_HPP
