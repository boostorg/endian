//  boost/endian/types.hpp  ------------------------------------------------------------//

//  (C) Copyright Darin Adler 2000
//  (C) Copyright Beman Dawes 2006, 2009

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
#include <boost/detail/endian.hpp>
#define BOOST_MINIMAL_INTEGER_COVER_OPERATORS
#define BOOST_NO_IO_COVER_OPERATORS
#include <boost/endian/detail/cover_operators.hpp>
#undef  BOOST_NO_IO_COVER_OPERATORS
#undef  BOOST_MINIMAL_INTEGER_COVER_OPERATORS
#include <boost/type_traits/is_signed.hpp>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/scoped_enum_emulation.hpp>
#include <iosfwd>
#include <climits>

# if CHAR_BIT != 8
#   error Platforms with CHAR_BIT != 8 are not supported
# endif

# ifdef BOOST_NO_DEFAULTED_FUNCTIONS
#   define BOOST_ENDIAN_DEFAULT_CONSTRUCT {}          // C++03
# else
#   define BOOST_ENDIAN_DEFAULT_CONSTRUCT = default;  // C++0x
# endif

# if defined(BOOST_NO_DEFAULTED_FUNCTIONS) && defined(BOOST_ENDIAN_FORCE_PODNESS)
#   define BOOST_ENDIAN_NO_CTORS
# endif


namespace boost
{
namespace endian
{
  namespace detail
  {
    // Unrolled loops for loading and storing streams of bytes.

    template <typename T, std::size_t n_bytes,
      bool sign=boost::is_signed<T>::value >
    struct unrolled_byte_loops
    {
      typedef unrolled_byte_loops<T, n_bytes - 1, sign> next;

      static T load_big(const unsigned char* bytes)
        { return *(bytes - 1) | (next::load_big(bytes - 1) << 8); }
      static T load_little(const unsigned char* bytes)
        { return *bytes | (next::load_little(bytes + 1) << 8); }

      static void store_big(char* bytes, T value)
        {
          *(bytes - 1) = static_cast<char>(value);
          next::store_big(bytes - 1, value >> 8);
        }
      static void store_little(char* bytes, T value)
        {
          *bytes = static_cast<char>(value);
          next::store_little(bytes + 1, value >> 8);
        }
    };

    template <typename T>
    struct unrolled_byte_loops<T, 1, false>
    {
      static T load_big(const unsigned char* bytes)
        { return *(bytes - 1); }
      static T load_little(const unsigned char* bytes)
        { return *bytes; }
      static void store_big(char* bytes, T value)
        { *(bytes - 1) = static_cast<char>(value); }
      static void store_little(char* bytes, T value)
        { *bytes = static_cast<char>(value); }

    };

    template <typename T>
    struct unrolled_byte_loops<T, 1, true>
    {
      static T load_big(const unsigned char* bytes)
        { return *reinterpret_cast<const signed char*>(bytes - 1); }
      static T load_little(const unsigned char* bytes)
        { return *reinterpret_cast<const signed char*>(bytes); }
      static void store_big(char* bytes, T value)
        { *(bytes - 1) = static_cast<char>(value); }
      static void store_little(char* bytes, T value)
        { *bytes = static_cast<char>(value); }
    };

    template <typename T, std::size_t n_bytes>
    inline
    T load_big_endian(const void* bytes)
    {
      return unrolled_byte_loops<T, n_bytes>::load_big
        (static_cast<const unsigned char*>(bytes) + n_bytes);
    }

    template <typename T, std::size_t n_bytes>
    inline
    T load_little_endian(const void* bytes)
    {
      return unrolled_byte_loops<T, n_bytes>::load_little
        (static_cast<const unsigned char*>(bytes));
    }

    template <typename T, std::size_t n_bytes>
    inline
    void store_big_endian(void* bytes, T value)
    {
      unrolled_byte_loops<T, n_bytes>::store_big
        (static_cast<char*>(bytes) + n_bytes, value);
    }

    template <typename T, std::size_t n_bytes>
    inline
    void store_little_endian(void* bytes, T value)
    {
      unrolled_byte_loops<T, n_bytes>::store_little
        (static_cast<char*>(bytes), value);
    }

  } // namespace detail

# ifdef BOOST_ENDIAN_LOG
    bool endian_log(true);
# endif


  //  endian class template and specializations  ---------------------------------------//

#ifndef BOOST_ENDIAN_ORDER_ENUM_DEFINED
  BOOST_SCOPED_ENUM_START(order) { big, little, native }; BOOST_SCOPED_ENUM_END
# define BOOST_ENDIAN_ORDER_ENUM_DEFINED
#endif
  BOOST_SCOPED_ENUM_START(alignment) { unaligned, aligned }; BOOST_SCOPED_ENUM_END

  template <BOOST_SCOPED_ENUM(order) E, typename T, std::size_t n_bits,
    BOOST_SCOPED_ENUM(alignment) A = alignment::unaligned>
    class endian;

    //  Specializations that represent unaligned bytes.
    //  Taking an integer type as a parameter provides a nice way to pass both
    //  the size and signedness of the desired integer and get the appropriate
    //  corresponding integer type for the interface.

    //  unaligned big endian specialization
    template <typename T, std::size_t n_bits>
    class endian< order::big, T, n_bits, alignment::unaligned >
      : cover_operators< endian< order::big, T, n_bits >, T >
    {
        BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
      public:
        typedef T value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        explicit endian(T val)
        { 
#       ifdef BOOST_ENDIAN_LOG
          if ( endian_log )
            std::clog << "big, unaligned, " << n_bits << "-bits, construct(" << val << ")\n";
#       endif
          detail::store_big_endian<T, n_bits/8>(m_value, val);
        }
#     endif
        endian & operator=(T val) { detail::store_big_endian<T, n_bits/8>(m_value, val); return *this; }
        operator T() const
        { 
#       ifdef BOOST_ENDIAN_LOG
          if ( endian_log )
            std::clog << "big, unaligned, " << n_bits << "-bits, convert(" << detail::load_big_endian<T, n_bits/8>(m_value) << ")\n";
#       endif
          return detail::load_big_endian<T, n_bits/8>(m_value);
        }
        const char* data() const  { return m_value; }
      private:
  	    char m_value[n_bits/8];
    };

    //  unaligned little endian specialization
    template <typename T, std::size_t n_bits>
    class endian< order::little, T, n_bits, alignment::unaligned >
      : cover_operators< endian< order::little, T, n_bits >, T >
    {
        BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
      public:
        typedef T value_type;
#     ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
        explicit endian(T val)
        { 
#       ifdef BOOST_ENDIAN_LOG
          if ( endian_log )
            std::clog << "little, unaligned, " << n_bits << "-bits, construct(" << val << ")\n";
#       endif
          detail::store_little_endian<T, n_bits/8>(m_value, val);
        }
#     endif
        endian & operator=(T val) { detail::store_little_endian<T, n_bits/8>(m_value, val); return *this; }
        operator T() const
        { 
#       ifdef BOOST_ENDIAN_LOG
          if ( endian_log )
            std::clog << "little, unaligned, " << n_bits << "-bits, convert(" << detail::load_little_endian<T, n_bits/8>(m_value) << ")\n";
#       endif
          return detail::load_little_endian<T, n_bits/8>(m_value);
        }
        const char* data() const  { return m_value; }
      private:
  	    char m_value[n_bits/8];
    };

    //  unaligned native endian specialization
    template <typename T, std::size_t n_bits>
    class endian< order::native, T, n_bits, alignment::unaligned >
      : cover_operators< endian< order::native, T, n_bits >, T >
    {
        BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
      public:
        typedef T value_type;
#   ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
#     ifdef BOOST_BIG_ENDIAN
        explicit endian(T val)    { detail::store_big_endian<T, n_bits/8>(m_value, val); }
#     else
        explicit endian(T val)    { detail::store_little_endian<T, n_bits/8>(m_value, val); }
#     endif
#   endif
#   ifdef BOOST_BIG_ENDIAN  
        endian & operator=(T val) { detail::store_big_endian<T, n_bits/8>(m_value, val); return *this; }
        operator T() const        { return detail::load_big_endian<T, n_bits/8>(m_value); }
#   else
        endian & operator=(T val) { detail::store_little_endian<T, n_bits/8>(m_value, val); return *this; }
        operator T() const        { return detail::load_little_endian<T, n_bits/8>(m_value); }
#   endif
        const char* data() const  { return m_value; }
      private:
  	    char m_value[n_bits/8];
    };

    //  Specializations that mimic built-in integer types.
    //  These typically have the same alignment as the underlying types.

    //  aligned big endian specialization
    template <typename T, std::size_t n_bits>
    class endian< order::big, T, n_bits, alignment::aligned  >
      : cover_operators< endian< order::big, T, n_bits, alignment::aligned >, T >
    {
        BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
        BOOST_STATIC_ASSERT( sizeof(T) == n_bits/8 );
      public:
        typedef T value_type;
#   ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
#     ifdef BOOST_BIG_ENDIAN
        endian(T val) : m_value(val) { }
#     else
        explicit endian(T val)    { detail::store_big_endian<T, sizeof(T)>(&m_value, val); }
#     endif
#   endif
#   ifdef BOOST_BIG_ENDIAN  
        endian & operator=(T val) { m_value = val; return *this; }
        operator T() const        { return m_value; }
#   else  
        endian & operator=(T val) { detail::store_big_endian<T, sizeof(T)>(&m_value, val); return *this; }
        operator T() const        { return detail::load_big_endian<T, sizeof(T)>(&m_value); }
#   endif  
        const char* data() const  { return reinterpret_cast<const char *>(&m_value); }
      private:
  	    T m_value;
    };

    //  aligned little endian specialization
    template <typename T, std::size_t n_bits>
    class endian< order::little, T, n_bits, alignment::aligned  >
      : cover_operators< endian< order::little, T, n_bits, alignment::aligned >, T >
    {
        BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
        BOOST_STATIC_ASSERT( sizeof(T) == n_bits/8 );
      public:
        typedef T value_type;
#   ifndef BOOST_ENDIAN_NO_CTORS
        endian() BOOST_ENDIAN_DEFAULT_CONSTRUCT
#     ifdef BOOST_LITTLE_ENDIAN
        endian(T val) : m_value(val) { }
#     else
        explicit endian(T val)    { detail::store_little_endian<T, sizeof(T)>(&m_value, val); }
#     endif
#   endif
#   ifdef BOOST_LITTLE_ENDIAN
        endian & operator=(T val) { m_value = val; return *this; }
        operator T() const        { return m_value; }
    #else
        endian & operator=(T val) { detail::store_little_endian<T, sizeof(T)>(&m_value, val); return *this; }
        operator T() const        { return detail::load_little_endian<T, sizeof(T)>(&m_value); }
    #endif
        const char* data() const  { return reinterpret_cast<const char *>(&m_value); }
      private:
  	    T m_value;
    };

  //  naming convention typedefs  ------------------------------------------------------//

    // unaligned big endian signed integer types
    typedef endian< order::big, int_least8_t, 8 >           big_8_t;
    typedef endian< order::big, int_least16_t, 16 >         big_16_t;
    typedef endian< order::big, int_least32_t, 24 >         big_24_t;
    typedef endian< order::big, int_least32_t, 32 >         big_32_t;
    typedef endian< order::big, int_least64_t, 40 >         big_40_t;
    typedef endian< order::big, int_least64_t, 48 >         big_48_t;
    typedef endian< order::big, int_least64_t, 56 >         big_56_t;
    typedef endian< order::big, int_least64_t, 64 >         big_64_t;

    // unaligned big endian unsigned integer types
    typedef endian< order::big, uint_least8_t, 8 >          big_u8_t;
    typedef endian< order::big, uint_least16_t, 16 >        big_u16_t;
    typedef endian< order::big, uint_least32_t, 24 >        big_u24_t;
    typedef endian< order::big, uint_least32_t, 32 >        big_u32_t;
    typedef endian< order::big, uint_least64_t, 40 >        big_u40_t;
    typedef endian< order::big, uint_least64_t, 48 >        big_u48_t;
    typedef endian< order::big, uint_least64_t, 56 >        big_u56_t;
    typedef endian< order::big, uint_least64_t, 64 >        big_u64_t;

    // unaligned little endian signed integer types
    typedef endian< order::little, int_least8_t, 8 >        little_8_t;
    typedef endian< order::little, int_least16_t, 16 >      little_16_t;
    typedef endian< order::little, int_least32_t, 24 >      little_24_t;
    typedef endian< order::little, int_least32_t, 32 >      little_32_t;
    typedef endian< order::little, int_least64_t, 40 >      little_40_t;
    typedef endian< order::little, int_least64_t, 48 >      little_48_t;
    typedef endian< order::little, int_least64_t, 56 >      little_56_t;
    typedef endian< order::little, int_least64_t, 64 >      little_64_t;

    // unaligned little endian unsigned integer types
    typedef endian< order::little, uint_least8_t, 8 >       little_u8_t;
    typedef endian< order::little, uint_least16_t, 16 >     little_u16_t;
    typedef endian< order::little, uint_least32_t, 24 >     little_u24_t;
    typedef endian< order::little, uint_least32_t, 32 >     little_u32_t;
    typedef endian< order::little, uint_least64_t, 40 >     little_u40_t;
    typedef endian< order::little, uint_least64_t, 48 >     little_u48_t;
    typedef endian< order::little, uint_least64_t, 56 >     little_u56_t;
    typedef endian< order::little, uint_least64_t, 64 >     little_u64_t;

    // unaligned native endian signed integer types
    typedef endian< order::native, int_least8_t, 8 >        native_8_t;
    typedef endian< order::native, int_least16_t, 16 >      native_16_t;
    typedef endian< order::native, int_least32_t, 24 >      native_24_t;
    typedef endian< order::native, int_least32_t, 32 >      native_32_t;
    typedef endian< order::native, int_least64_t, 40 >      native_40_t;
    typedef endian< order::native, int_least64_t, 48 >      native_48_t;
    typedef endian< order::native, int_least64_t, 56 >      native_56_t;
    typedef endian< order::native, int_least64_t, 64 >      native_64_t;

    // unaligned native endian unsigned integer types
    typedef endian< order::native, uint_least8_t, 8 >       native_u8_t;
    typedef endian< order::native, uint_least16_t, 16 >     native_u16_t;
    typedef endian< order::native, uint_least32_t, 24 >     native_u24_t;
    typedef endian< order::native, uint_least32_t, 32 >     native_u32_t;
    typedef endian< order::native, uint_least64_t, 40 >     native_u40_t;
    typedef endian< order::native, uint_least64_t, 48 >     native_u48_t;
    typedef endian< order::native, uint_least64_t, 56 >     native_u56_t;
    typedef endian< order::native, uint_least64_t, 64 >     native_u64_t;

#define BOOST_HAS_INT16_T
#define BOOST_HAS_INT32_T
#define BOOST_HAS_INT64_T
  
  //  These types only present if platform has exact size integers:
  //     aligned big endian signed integer types
  //     aligned big endian unsigned integer types
  //     aligned little endian signed integer types
  //     aligned little endian unsigned integer types

  //     aligned native endian typedefs are not provided because
  //     <cstdint> types are superior for this use case

# if defined(BOOST_HAS_INT16_T)
    typedef endian< order::big, int16_t, 16, alignment::aligned >      big_int16_t;
    typedef endian< order::big, uint16_t, 16, alignment::aligned >     big_uint16_t;
    typedef endian< order::little, int16_t, 16, alignment::aligned >   little_int16_t;
    typedef endian< order::little, uint16_t, 16, alignment::aligned >  little_uint16_t;
# endif

# if defined(BOOST_HAS_INT32_T)
    typedef endian< order::big, int32_t, 32, alignment::aligned >      big_int32_t;
    typedef endian< order::big, uint32_t, 32, alignment::aligned >     big_uint32_t;
    typedef endian< order::little, int32_t, 32, alignment::aligned >   little_int32_t;
    typedef endian< order::little, uint32_t, 32, alignment::aligned >  little_uint32_t;
# endif

# if defined(BOOST_HAS_INT64_T)
    typedef endian< order::big, int64_t, 64, alignment::aligned >      big_int64_t;
    typedef endian< order::big, uint64_t, 64, alignment::aligned >     big_uint64_t;
    typedef endian< order::little, int64_t, 64, alignment::aligned >   little_int64_t;
    typedef endian< order::little, uint64_t, 64, alignment::aligned >  little_uint64_t;
# endif

} // namespace endian
} // namespace boost

#if defined(__BORLANDC__) || defined( __CODEGEARC__)
# pragma pack(pop)
#endif

#if defined(_MSC_VER)  
# pragma warning(pop)  
#endif 

#endif // BOOST_ENDIAN_HPP
