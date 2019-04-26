//  boost/endian/conversion.hpp  -------------------------------------------------------//

//  Copyright Beman Dawes 2010, 2011, 2014

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_CONVERSION_HPP
#define BOOST_ENDIAN_CONVERSION_HPP

#include <boost/endian/detail/endian_reverse.hpp>
#include <boost/core/scoped_enum.hpp>
#include <boost/predef/other/endian.h>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstring>  // for memcpy

//------------------------------------- synopsis ---------------------------------------//

namespace boost
{
namespace endian
{
  BOOST_SCOPED_ENUM_START(order)
  {
    big, little,
# if BOOST_ENDIAN_BIG_BYTE
      native = big
# else
      native = little
# endif
  }; BOOST_SCOPED_ENUM_END

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                             return-by-value interfaces                               //
//                             suggested by Phil Endecott                               //
//                                                                                      //
//                             user-defined types (UDTs)                                //
//                                                                                      //
//  All return-by-value conversion function templates are required to be implemented in //
//  terms of an unqualified call to "endian_reverse(x)", a function returning the       //
//  value of x with endianness reversed. This provides a customization point for any    //
//  UDT that provides a "endian_reverse" free-function meeting the requirements.        //
//  It must be defined in the same namespace as the UDT itself so that it will be found //
//  by argument dependent lookup (ADL).                                                 //
//                                                                                      //
//--------------------------------------------------------------------------------------//

  //  reverse byte order
  //  requires T to be a non-bool integral type
  //  in detail/endian_reverse.hpp
  template<class T> inline T endian_reverse( T x ) BOOST_NOEXCEPT;

  //  reverse byte order unless native endianness is big
  template <class EndianReversible >
    inline EndianReversible  big_to_native(EndianReversible  x) BOOST_NOEXCEPT;
    //  Returns: x if native endian order is big, otherwise endian_reverse(x)
  template <class EndianReversible >
    inline EndianReversible  native_to_big(EndianReversible  x) BOOST_NOEXCEPT;
    //  Returns: x if native endian order is big, otherwise endian_reverse(x)

  //  reverse byte order unless native endianness is little
  template <class EndianReversible >
    inline EndianReversible  little_to_native(EndianReversible  x) BOOST_NOEXCEPT;
    //  Returns: x if native endian order is little, otherwise endian_reverse(x)
  template <class EndianReversible >
    inline EndianReversible  native_to_little(EndianReversible  x) BOOST_NOEXCEPT;
    //  Returns: x if native endian order is little, otherwise endian_reverse(x)

  //  generic conditional reverse byte order
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To,
    class EndianReversible>
      inline EndianReversible  conditional_reverse(EndianReversible from) BOOST_NOEXCEPT;
    //  Returns: If From == To have different values, from.
    //           Otherwise endian_reverse(from).
    //  Remarks: The From == To test, and as a consequence which form the return takes, is
    //           is determined at compile time.

  //  runtime conditional reverse byte order
  template <class EndianReversible >
    inline EndianReversible  conditional_reverse(EndianReversible from,
      BOOST_SCOPED_ENUM(order) from_order, BOOST_SCOPED_ENUM(order) to_order)
        BOOST_NOEXCEPT;
      //  Returns: from_order == to_order ? from : endian_reverse(from).

  //------------------------------------------------------------------------------------//


  //  Q: What happened to bswap, htobe, and the other synonym functions based on names
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
  //  of an unqualified call to "endian_reverse_inplace(x)", a function reversing       //
  //  the endianness of x, which is a non-const reference. This provides a              //
  //  customization point for any UDT that provides a "reverse_inplace" free-function   //
  //  meeting the requirements. The free-function must be declared in the same          //
  //  namespace as the UDT itself so that it will be found by argument-dependent        //
  //   lookup (ADL).                                                                    //
  //                                                                                    //
  //------------------------------------------------------------------------------------//

  //  reverse in place
  //  in detail/endian_reverse.hpp
  template <class EndianReversible>
    inline void endian_reverse_inplace(EndianReversible& x) BOOST_NOEXCEPT;
    //  Effects: x = endian_reverse(x)

  //  reverse in place unless native endianness is big
  template <class EndianReversibleInplace>
    inline void big_to_native_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is big, otherwise endian_reverse_inplace(x)
  template <class EndianReversibleInplace>
    inline void native_to_big_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is big, otherwise endian_reverse_inplace(x)

  //  reverse in place unless native endianness is little
  template <class EndianReversibleInplace>
    inline void little_to_native_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is little, otherwise endian_reverse_inplace(x);
  template <class EndianReversibleInplace>
    inline void native_to_little_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is little, otherwise endian_reverse_inplace(x);

  //  generic conditional reverse in place
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To,
    class EndianReversibleInplace>
  inline void conditional_reverse_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;

  //  runtime reverse in place
  template <class EndianReversibleInplace>
  inline void conditional_reverse_inplace(EndianReversibleInplace& x,
    BOOST_SCOPED_ENUM(order) from_order,  BOOST_SCOPED_ENUM(order) to_order)
    BOOST_NOEXCEPT;

//----------------------------------- end synopsis -------------------------------------//

  namespace detail
  {
    //  generic reverse function template implementation approach using std::reverse
    //  suggested by Mathias Gaunard. Primary motivation for inclusion is to have an
    //  independent implementation to test against.

    template <class T>
    inline T std_endian_reverse(T x) BOOST_NOEXCEPT
    {
      T tmp(x);
      std::reverse(
        reinterpret_cast<unsigned char*>(&tmp),
        reinterpret_cast<unsigned char*>(&tmp) + sizeof(T));
      return tmp;
    }

    //  conditional unaligned reverse copy, patterned after std::reverse_copy
    template <class T>
      inline void big_reverse_copy(T from, char* to) BOOST_NOEXCEPT;
    template <class T>
      inline void big_reverse_copy(const char* from, T& to) BOOST_NOEXCEPT;
    template <class T>
      inline void little_reverse_copy(T from, char* to) BOOST_NOEXCEPT;
    template <class T>
      inline void little_reverse_copy(const char* from, T& to) BOOST_NOEXCEPT;
  }  // namespace detail

  template <class EndianReversible >
  inline EndianReversible  big_to_native(EndianReversible  x) BOOST_NOEXCEPT
  {
#   if BOOST_ENDIAN_BIG_BYTE
    return x;
#   else
    return endian_reverse(x);
#   endif
  }

  template <class EndianReversible >
  inline EndianReversible  native_to_big(EndianReversible  x) BOOST_NOEXCEPT
  {
#   if BOOST_ENDIAN_BIG_BYTE
    return x;
#   else
    return endian_reverse(x);
#   endif
  }

  template <class EndianReversible >
  inline EndianReversible  little_to_native(EndianReversible  x) BOOST_NOEXCEPT
  {
#   if BOOST_ENDIAN_LITTLE_BYTE
    return x;
#   else
    return endian_reverse(x);
#   endif
  }

  template <class EndianReversible >
  inline EndianReversible  native_to_little(EndianReversible  x) BOOST_NOEXCEPT
  {
#   if BOOST_ENDIAN_LITTLE_BYTE
    return x;
#   else
    return endian_reverse(x);
#   endif
  }

  namespace detail
  {
    //  Primary template and specializations to support endian_reverse().
    //  See rationale in endian_reverse() below.
    template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To,
        class EndianReversible>
      class value_converter ;  // primary template
    template <class T> class value_converter <order::big, order::big, T>
      {public: T operator()(T x) BOOST_NOEXCEPT {return x;}};
    template <class T> class value_converter <order::little, order::little, T>
      {public: T operator()(T x) BOOST_NOEXCEPT {return x;}};
    template <class T> class value_converter <order::big, order::little, T>
      {public: T operator()(T x) BOOST_NOEXCEPT {return endian_reverse(x);}};
    template <class T> class value_converter <order::little, order::big, T>
      {public: T operator()(T x) BOOST_NOEXCEPT {return endian_reverse(x);}};
  }

  //  generic conditional reverse
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To,
    class EndianReversible>
  inline EndianReversible  conditional_reverse(EndianReversible from) BOOST_NOEXCEPT  {
    //  work around lack of function template partial specialization by instantiating
    //  a function object of a class that is partially specialized on the two order
    //  template parameters, and then calling its operator().
    detail::value_converter <From, To, EndianReversible> tmp;
    return tmp(from);
  }

  //  runtime conditional reverse
  template <class EndianReversible >
  inline EndianReversible  conditional_reverse(EndianReversible  from,
    BOOST_SCOPED_ENUM(order) from_order, BOOST_SCOPED_ENUM(order) to_order) BOOST_NOEXCEPT
  {
    return from_order == to_order ? from : endian_reverse(from);
  }

//--------------------------------------------------------------------------------------//
//                           reverse-in-place implementation                            //
//--------------------------------------------------------------------------------------//

  template <class EndianReversibleInplace>
#   if BOOST_ENDIAN_BIG_BYTE
  inline void big_to_native_inplace(EndianReversibleInplace&) BOOST_NOEXCEPT {}
#   else
  inline void big_to_native_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT
    { endian_reverse_inplace(x); }
#   endif
  template <class EndianReversibleInplace>
#   if BOOST_ENDIAN_BIG_BYTE
  inline void native_to_big_inplace(EndianReversibleInplace&) BOOST_NOEXCEPT {}
#   else
  inline void native_to_big_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT
  {
    endian_reverse_inplace(x);
  }
#   endif

  template <class EndianReversibleInplace>
#   if BOOST_ENDIAN_LITTLE_BYTE
  inline void little_to_native_inplace(EndianReversibleInplace&) BOOST_NOEXCEPT {}
#   else
  inline void little_to_native_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT
    { endian_reverse_inplace(x); }
#   endif
  template <class EndianReversibleInplace>
#   if BOOST_ENDIAN_LITTLE_BYTE
  inline void native_to_little_inplace(EndianReversibleInplace&) BOOST_NOEXCEPT {}
#   else
  inline void native_to_little_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT
  {
    endian_reverse_inplace(x);
  }
#   endif

  namespace detail
  {
    //  Primary template and specializations support generic
    //  endian_reverse_inplace().
    //  See rationale in endian_reverse_inplace() below.
    template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To,
        class EndianReversibleInplace>
      class converter;  // primary template
    template <class T> class converter<order::big, order::big, T>
      {public: void operator()(T&) BOOST_NOEXCEPT {/*no effect*/}};
    template <class T> class converter<order::little, order::little, T>
      {public: void operator()(T&) BOOST_NOEXCEPT {/*no effect*/}};
    template <class T> class converter<order::big, order::little, T>
      {public: void operator()(T& x) BOOST_NOEXCEPT { endian_reverse_inplace(x); }};
    template <class T> class converter<order::little, order::big, T>
      {public: void operator()(T& x) BOOST_NOEXCEPT { endian_reverse_inplace(x); }};
  }  // namespace detail

  //  generic conditional reverse in place
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To,
    class EndianReversibleInplace>
  inline void conditional_reverse_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT
  {
    //  work around lack of function template partial specialization by instantiating
    //  a function object of a class that is partially specialized on the two order
    //  template parameters, and then calling its operator().
    detail::converter<From, To, EndianReversibleInplace> tmp;
    tmp(x);  // call operator ()
  }

  //  runtime reverse in place
  template <class EndianReversibleInplace>
  inline void conditional_reverse_inplace(EndianReversibleInplace& x,
    BOOST_SCOPED_ENUM(order) from_order,  BOOST_SCOPED_ENUM(order) to_order)
    BOOST_NOEXCEPT
  {
    if (from_order != to_order)
      endian_reverse_inplace(x);
  }


  namespace detail
  {
    template <class T>
    inline void big_reverse_copy(T from, char* to) BOOST_NOEXCEPT
    {
#     if BOOST_ENDIAN_BIG_BYTE
      std::memcpy(to, reinterpret_cast<const char*>(&from), sizeof(T));
#     else
      std::reverse_copy(reinterpret_cast<const char*>(&from),
        reinterpret_cast<const char*>(&from) + sizeof(T), to);
#     endif
    }
    template <class T>
    inline void big_reverse_copy(const char* from, T& to) BOOST_NOEXCEPT
    {
#     if BOOST_ENDIAN_BIG_BYTE
      std::memcpy(reinterpret_cast<char*>(&to), from, sizeof(T));
#     else
      std::reverse_copy(from, from + sizeof(T), reinterpret_cast<char*>(&to));
#     endif
    }
    template <class T>
    inline void little_reverse_copy(T from, char* to) BOOST_NOEXCEPT
    {
#     if BOOST_ENDIAN_LITTLE_BYTE
      std::memcpy(to, reinterpret_cast<const char*>(&from), sizeof(T));
#     else
      std::reverse_copy(reinterpret_cast<const char*>(&from),
        reinterpret_cast<const char*>(&from) + sizeof(T), to);
#     endif
    }
    template <class T>
    inline void little_reverse_copy(const char* from, T& to) BOOST_NOEXCEPT
    {
#     if BOOST_ENDIAN_LITTLE_BYTE
      std::memcpy(reinterpret_cast<char*>(&to), from, sizeof(T));
#     else
      std::reverse_copy(from, from + sizeof(T), reinterpret_cast<char*>(&to));
#     endif
    }
  }  // namespace detail
}  // namespace endian
}  // namespace boost

#endif // BOOST_ENDIAN_CONVERSION_HPP
