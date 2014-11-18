//  boost/endian/types.hpp  ------------------------------------------------------------//

//  (C) Copyright Darin Adler 2000
//  (C) Copyright Beman Dawes 2006, 2009, 2014

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

//--------------------------------------------------------------------------------------//

//  Original design developed by Darin Adler based on classes developed by Mark
//  Borgerding. Four original class templates were combined into a single endian
//  class template by Beman Dawes, who also added the unrolled_byte_loops sign
//  partial specialization to correctly extend the sign when cover integer size
//  differs from endian representation size.

// TODO: When a compiler supporting constexpr becomes available, try possible uses.

#ifndef BOOST_ENDIAN_HPP
#define BOOST_ENDIAN_HPP

#if defined(_MSC_VER)  
# pragma warning(push)  
# pragma warning(disable:4365)  // conversion ... signed/unsigned mismatch
#endif

#ifdef BOOST_ENDIAN_LOG
# include <iostream>
#endif

#if defined(__BORLANDC__) || defined( __CODEGEARC__)
# pragma pack(push, 1)
#endif

#include <boost/config.hpp>
#include <boost/predef/detail/endian_compat.h>
#include <boost/endian/conversion.hpp>
#include <boost/endian/buffers.hpp>
#define  BOOST_ENDIAN_MINIMAL_COVER_OPERATORS
#include <boost/endian/detail/cover_operators.hpp>
#undef   BOOST_ENDIAN_MINIMAL_COVER_OPERATORS
#include <boost/type_traits/is_signed.hpp>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/scoped_enum_emulation.hpp>
#include <iosfwd>
#include <climits>

# if CHAR_BIT != 8
#   error Platforms with CHAR_BIT != 8 are not supported
# endif

# ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#   define BOOST_ENDIAN_DEFAULT_CONSTRUCT {}          // C++03
# else
#   define BOOST_ENDIAN_DEFAULT_CONSTRUCT = default;  // C++0x
# endif

# if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) && defined(BOOST_ENDIAN_FORCE_PODNESS)
#   define BOOST_ENDIAN_NO_CTORS
# endif

# ifndef BOOST_ENDIAN_EXPLICIT_CTORS
#   define BOOST_ENDIAN_EXPLICIT_OPT
# else
#   define BOOST_ENDIAN_EXPLICIT_OPT explicit
# endif

//----------------------------------  synopsis  ----------------------------------------//

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

  template <BOOST_SCOPED_ENUM(order) Order, class T, std::size_t n_bits,
    BOOST_SCOPED_ENUM(align) A = align::no>
      class endian;

  // aligned big endian floating point types
  typedef endian<order::big, float, 32, align::yes>       big_align_float32_t;
  typedef endian<order::big, double, 64, align::yes>      big_align_float64_t;

  // aligned little endian floating point types
  typedef endian<order::little, float, 32, align::yes>    little_align_float32_t;
  typedef endian<order::little, double, 64, align::yes>   little_align_float64_t;

  // unaligned big endian floating point types
  typedef endian<order::big, float, 32, align::no>        big_float32_t;
  typedef endian<order::big, double, 64, align::no>       big_float64_t;

  // unaligned little endian floating point types
  typedef endian<order::little, float, 32, align::no>     little_float32_t;
  typedef endian<order::little, double, 64, align::no>    little_float64_t;

  // aligned big endian signed integer types
  typedef endian<order::big, int16_t, 16, align::yes>      big_align_int16_t;
  typedef endian<order::big, int32_t, 32, align::yes>      big_align_int32_t;
  typedef endian<order::big, int64_t, 64, align::yes>      big_align_int64_t;

  // aligned big endian unsigned integer types
  typedef endian<order::big, uint16_t, 16, align::yes>     big_align_uint16_t;
  typedef endian<order::big, uint32_t, 32, align::yes>     big_align_uint32_t;
  typedef endian<order::big, uint64_t, 64, align::yes>     big_align_uint64_t;

  // aligned little endian signed integer types
  typedef endian<order::little, int16_t, 16, align::yes>   little_align_int16_t;
  typedef endian<order::little, int32_t, 32, align::yes>   little_align_int32_t;
  typedef endian<order::little, int64_t, 64, align::yes>   little_align_int64_t;

  // aligned little endian unsigned integer types
  typedef endian<order::little, uint16_t, 16, align::yes>  little_align_uint16_t;
  typedef endian<order::little, uint32_t, 32, align::yes>  little_align_uint32_t;
  typedef endian<order::little, uint64_t, 64, align::yes>  little_align_uint64_t;

  // aligned native endian typedefs are not provided because
  // <cstdint> types are superior for this use case

  // unaligned big endian signed integer types
  typedef endian<order::big, int_least8_t, 8>        big_int8_t;
  typedef endian<order::big, int_least16_t, 16>      big_int16_t;
  typedef endian<order::big, int_least32_t, 24>      big_int24_t;
  typedef endian<order::big, int_least32_t, 32>      big_int32_t;
  typedef endian<order::big, int_least64_t, 40>      big_int40_t;
  typedef endian<order::big, int_least64_t, 48>      big_int48_t;
  typedef endian<order::big, int_least64_t, 56>      big_int56_t;
  typedef endian<order::big, int_least64_t, 64>      big_int64_t;

  // unaligned big endian unsigned integer types
  typedef endian<order::big, uint_least8_t, 8>       big_uint8_t;
  typedef endian<order::big, uint_least16_t, 16>     big_uint16_t;
  typedef endian<order::big, uint_least32_t, 24>     big_uint24_t;
  typedef endian<order::big, uint_least32_t, 32>     big_uint32_t;
  typedef endian<order::big, uint_least64_t, 40>     big_uint40_t;
  typedef endian<order::big, uint_least64_t, 48>     big_uint48_t;
  typedef endian<order::big, uint_least64_t, 56>     big_uint56_t;
  typedef endian<order::big, uint_least64_t, 64>     big_uint64_t;

  // unaligned little endian signed integer types
  typedef endian<order::little, int_least8_t, 8>     little_int8_t;
  typedef endian<order::little, int_least16_t, 16>   little_int16_t;
  typedef endian<order::little, int_least32_t, 24>   little_int24_t;
  typedef endian<order::little, int_least32_t, 32>   little_int32_t;
  typedef endian<order::little, int_least64_t, 40>   little_int40_t;
  typedef endian<order::little, int_least64_t, 48>   little_int48_t;
  typedef endian<order::little, int_least64_t, 56>   little_int56_t;
  typedef endian<order::little, int_least64_t, 64>   little_int64_t;

  // unaligned little endian unsigned integer types
  typedef endian<order::little, uint_least8_t, 8>    little_uint8_t;
  typedef endian<order::little, uint_least16_t, 16>  little_uint16_t;
  typedef endian<order::little, uint_least32_t, 24>  little_uint24_t;
  typedef endian<order::little, uint_least32_t, 32>  little_uint32_t;
  typedef endian<order::little, uint_least64_t, 40>  little_uint40_t;
  typedef endian<order::little, uint_least64_t, 48>  little_uint48_t;
  typedef endian<order::little, uint_least64_t, 56>  little_uint56_t;
  typedef endian<order::little, uint_least64_t, 64>  little_uint64_t;

# ifdef BOOST_BIG_ENDIAN
  // unaligned native endian signed integer types
  typedef big_int8_t   native_int8_t;
  typedef big_int16_t  native_int16_t;
  typedef big_int24_t  native_int24_t;
  typedef big_int32_t  native_int32_t;
  typedef big_int40_t  native_int40_t;
  typedef big_int48_t  native_int48_t;
  typedef big_int56_t  native_int56_t;
  typedef big_int64_t  native_int64_t;

  // unaligned native endian unsigned integer types
  typedef big_uint8_t   native_uint8_t;
  typedef big_uint16_t  native_uint16_t;
  typedef big_uint24_t  native_uint24_t;
  typedef big_uint32_t  native_uint32_t;
  typedef big_uint40_t  native_uint40_t;
  typedef big_uint48_t  native_uint48_t;
  typedef big_uint56_t  native_uint56_t;
  typedef big_uint64_t  native_uint64_t;

  // native endian floating point types
  typedef big_float32_t native_float32_t;
  typedef big_float64_t native_float64_t;
  typedef big_align_float32_t native_align_float32_t;
  typedef big_align_float64_t native_align_float64_t;
# else
  // unaligned native endian signed integer types
  typedef little_int8_t   native_int8_t;
  typedef little_int16_t  native_int16_t;
  typedef little_int24_t  native_int24_t;
  typedef little_int32_t  native_int32_t;
  typedef little_int40_t  native_int40_t;
  typedef little_int48_t  native_int48_t;
  typedef little_int56_t  native_int56_t;
  typedef little_int64_t  native_int64_t;

  // unaligned native endian unsigned integer types
  typedef little_uint8_t   native_uint8_t;
  typedef little_uint16_t  native_uint16_t;
  typedef little_uint24_t  native_uint24_t;
  typedef little_uint32_t  native_uint32_t;
  typedef little_uint40_t  native_uint40_t;
  typedef little_uint48_t  native_uint48_t;
  typedef little_uint56_t  native_uint56_t;
  typedef little_uint64_t  native_uint64_t;

  // native endian floating point types
  typedef little_float32_t native_float32_t;
  typedef little_float64_t native_float64_t;
  typedef little_align_float32_t native_align_float32_t;
  typedef little_align_float64_t native_align_float64_t;
# endif
}  // namespace boost
}  // namespace endian

//----------------------------------  end synopsis  ------------------------------------//

namespace boost
{
namespace endian
{

//  endian class template specializations  ---------------------------------------------//

    //  Specializations that represent unaligned bytes.
    //  Taking an integer type as a parameter provides a nice way to pass both
    //  the size and signness of the desired integer and get the appropriate
    //  corresponding integer type for the interface.

    //  unaligned integer big endian specialization
    template <typename T, std::size_t n_bits>
    class endian< order::big, T, n_bits, align::no >
      : public endian_buffer< order::big, T, n_bits, align::no >,
        cover_operators<endian<order::big, T, n_bits>, T>
    {
        BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
      public:
        typedef T value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        BOOST_ENDIAN_EXPLICIT_OPT endian(T val) BOOST_NOEXCEPT
        { 
#       ifdef BOOST_ENDIAN_LOG
          if ( endian_log )
            std::cout << "big, unaligned, " << n_bits << "-bits, construct(" << val << ")\n";
#       endif
          detail::store_big_endian<T, n_bits/8>(this->m_value, val);
        }
#     endif
        endian & operator=(T val) BOOST_NOEXCEPT
          { detail::store_big_endian<T, n_bits/8>(this->m_value, val); return *this; }
        operator value_type() const BOOST_NOEXCEPT { return this->value(); }
    };
 
    //  unaligned float big endian specialization
    template <>
    class endian< order::big, float, 32, align::no >
      : public endian_buffer< order::big, float, 32, align::no >,
        cover_operators< endian< order::big, float, 32 >, float >
    {
      public:
        typedef float value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        BOOST_ENDIAN_EXPLICIT_OPT endian(value_type val) BOOST_NOEXCEPT
          { detail::big_reverse_copy(val, this->m_value); }
#     endif
        endian & operator=(value_type val) BOOST_NOEXCEPT
          { detail::big_reverse_copy(val, this->m_value); return *this; }
        operator value_type() const BOOST_NOEXCEPT { return this->value(); }
    };

    //  unaligned double big endian specialization
    template <>
    class endian< order::big, double, 64, align::no >
      : public endian_buffer< order::big, double, 64, align::no >,
        cover_operators< endian< order::big, double, 64 >, double >
    {
      public:
        typedef double value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        BOOST_ENDIAN_EXPLICIT_OPT endian(value_type val) BOOST_NOEXCEPT
          { detail::big_reverse_copy(val, this->m_value); }
#     endif
        endian & operator=(value_type val) BOOST_NOEXCEPT
          { detail::big_reverse_copy(val, this->m_value); return *this; }
        operator value_type() const BOOST_NOEXCEPT { return this->value(); }
    };
 
    //  unaligned float little endian specialization
    template <>
    class endian< order::little, float, 32, align::no >
      : public endian_buffer< order::little, float, 32, align::no >,
        cover_operators< endian< order::little, float, 32 >, float >
    {
      public:
        typedef float value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        BOOST_ENDIAN_EXPLICIT_OPT endian(value_type val) BOOST_NOEXCEPT
          { detail::little_reverse_copy(val, this->m_value); }
#     endif
        endian & operator=(value_type val) BOOST_NOEXCEPT
          { detail::little_reverse_copy(val, this->m_value); return *this; }
        operator value_type() const BOOST_NOEXCEPT { return this->value(); }
    };

    //  unaligned double little endian specialization
    template <>
    class endian< order::little, double, 64, align::no >
      : public endian_buffer< order::little, double, 64, align::no >,
        cover_operators< endian< order::little, double, 64 >, double >
    {
      public:
        typedef double value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        BOOST_ENDIAN_EXPLICIT_OPT endian(value_type val) BOOST_NOEXCEPT
          { detail::little_reverse_copy(val, this->m_value); }
#     endif
        endian & operator=(value_type val) BOOST_NOEXCEPT
          { detail::little_reverse_copy(val, this->m_value); return *this; }
        operator value_type() const BOOST_NOEXCEPT { return this->value(); }
    };

    //  unaligned little endian specialization
    template <typename T, std::size_t n_bits>
    class endian< order::little, T, n_bits, align::no >
      : public endian_buffer< order::little, T, n_bits, align::no >,
        cover_operators< endian< order::little, T, n_bits >, T >
    {
        BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
      public:
        typedef T value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        BOOST_ENDIAN_EXPLICIT_OPT endian(T val) BOOST_NOEXCEPT
        { 
#       ifdef BOOST_ENDIAN_LOG
          if ( endian_log )
            std::cout << "little, unaligned, " << n_bits << "-bits, construct(" << val << ")\n";
#       endif
          detail::store_little_endian<T, n_bits/8>(this->m_value, val);
        }
#     endif
        endian & operator=(T val) BOOST_NOEXCEPT
          { detail::store_little_endian<T, n_bits/8>(this->m_value, val); return *this; }
        operator value_type() const BOOST_NOEXCEPT { return this->value(); }
    };

  //  align::yes specializations; only n_bits == 16/32/64 supported

    //  aligned big endian specialization
    template <typename T, std::size_t n_bits>
    class endian<order::big, T, n_bits, align::yes>
      : public endian_buffer< order::big, T, n_bits, align::yes >,
        cover_operators<endian<order::big, T, n_bits, align::yes>, T>
    {
        BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
        BOOST_STATIC_ASSERT( sizeof(T) == n_bits/8 );
      public:
        typedef T value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        BOOST_ENDIAN_EXPLICIT_OPT endian(T val) BOOST_NOEXCEPT
        {
#       ifdef BOOST_ENDIAN_LOG
          if ( endian_log )
            std::cout << "big, aligned, " << n_bits << "-bits, construct(" << val << ")\n";
#       endif
          this->m_value = ::boost::endian::big_endian_value(val);
        }

#     endif  
        endian& operator=(T val) BOOST_NOEXCEPT
        {
          this->m_value = ::boost::endian::big_endian_value(val);
          return *this;
        }
        operator value_type() const BOOST_NOEXCEPT { return this->value(); }
    };

    //  aligned little endian specialization
    template <typename T, std::size_t n_bits>
    class endian<order::little, T, n_bits, align::yes>
      : public endian_buffer< order::little, T, n_bits, align::yes >,
        cover_operators<endian<order::little, T, n_bits, align::yes>, T>
    {
        BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
        BOOST_STATIC_ASSERT( sizeof(T) == n_bits/8 );
      public:
        typedef T value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        BOOST_ENDIAN_EXPLICIT_OPT endian(T val) BOOST_NOEXCEPT
        {
#       ifdef BOOST_ENDIAN_LOG
          if ( endian_log )
            std::cout << "little, aligned, " << n_bits << "-bits, construct(" << val << ")\n";
#       endif
          this->m_value = ::boost::endian::little_endian_value(val);
        }
#     endif  
        endian& operator=(T val) BOOST_NOEXCEPT
        {
          this->m_value = ::boost::endian::little_endian_value(val);
          return *this;
        }
        operator value_type() const BOOST_NOEXCEPT { return this->value(); }
    };

} // namespace endian
} // namespace boost

#if defined(__BORLANDC__) || defined( __CODEGEARC__)
# pragma pack(pop)
#endif

#if defined(_MSC_VER)  
# pragma warning(pop)  
#endif 

#endif // BOOST_ENDIAN_HPP
