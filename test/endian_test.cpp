//  endian_test.cpp  ---------------------------------------------------------//

//  Copyright Beman Dawes 1999-2008

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

//----------------------------------------------------------------------------//

//  This test probes for correct endianess, size, and value.

//  See endian_operations_test for tests of operator correctness and interaction
//  between operand types.

//----------------------------------------------------------------------------//

#define _SCL_SECURE_NO_WARNINGS

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/types.hpp>
#include <boost/cstdint.hpp>
#include <boost/detail/lightweight_main.hpp>

#include <iostream>
#include <limits>
#include <climits>
#include <cstdlib>    // for atoi(), exit()
#include <cstring>    // for memcmp()

using namespace std;             // Not the best programming practice, but I
using namespace boost;           //   want to verify this combination of using
using namespace boost::endian;   //   namespaces works. See endian_operations_test
//                               //   for tests that don't do "using namespace".

#define VERIFY(predicate) verify( predicate, __LINE__ )
#define VERIFY_SIZE(actual, expected) verify_size( actual, expected, __LINE__ )
#define VERIFY_VALUE_AND_OPS(endian_t,expected_t,expected) verify_value_and_ops<endian_t, expected_t>( expected, __LINE__ )
#define VERIFY_BIG_REPRESENTATION(t) verify_representation<t>( true, __LINE__ )
#define VERIFY_LITTLE_REPRESENTATION(t) verify_representation<t>( false, __LINE__ )
#define VERIFY_NATIVE_REPRESENTATION(t) verify_native_representation<t>( __LINE__ )

namespace
{
  int err_count;

  void verify( bool x, int line )
  {
    if ( x ) return;
    ++err_count;
    cout << "Error: verify failed on line " << line << endl;
  }

  void verify_size( size_t actual, size_t expected, int line )
  {
    if ( actual == expected ) return;
    ++err_count;
    cout << "Error: verify size failed on line " << line << endl;
    cout << " A structure with an expected sizeof() " << expected
         << " had an actual sizeof() " << actual
         << "\n This will cause uses of endian types to fail\n";
  } 

  template <class Endian, class Base>
  void verify_value_and_ops( const Base & expected, int line )
  {
    Endian v( expected );
    verify( v == expected, line );

    Endian v2;
    v2.operator=( expected );
    verify( v2 == expected, line );

    ++v; // verify integer_cover_operators being applied to this type -
         // will fail to compile if no endian<> specialization is present

    Endian x(v+v);
    if ( x == x ) // silence warning
      return;
  }

  const char * big_rep    = "\x12\x34\x56\x78\x9A\xBC\xDE\xF0";
  const char * little_rep = "\xF0\xDE\xBC\x9A\x78\x56\x34\x12";

  template <class Endian>
  void verify_representation( bool is_big, int line )
  {
    int silence = 0;
    Endian x ( static_cast<typename Endian::value_type>
      (0x123456789abcdef0LL + silence) ); // will truncate

    if ( is_big )
      verify( memcmp( &x,
        reinterpret_cast<const char*>(big_rep)+8-sizeof(Endian),
          sizeof(Endian) ) == 0, line );
    else
      verify( memcmp( &x, little_rep, sizeof(Endian) ) == 0, line );
  }

  template <class Endian>
  inline void verify_native_representation( int line )
  {
#   ifdef BOOST_BIG_ENDIAN
      verify_representation<Endian>( true, line );
#   else
      verify_representation<Endian>( false, line );
#   endif
  }

  //  detect_order  -----------------------------------------------------//

  void detect_order()
  {
    union View
    { 
      long long i;
      unsigned char c[8];
    };

    View v = { 0x0102030405060708LL };  // initialize v.i
    
    if ( memcmp( v.c, "\10\7\6\5\4\3\2\1", 8) == 0 )
    {
      cout << "This machine is little-endian.\n";
  #   ifndef BOOST_LITTLE_ENDIAN
        cout << "yet boost/detail/endian.hpp does not define BOOST_LITTLE_ENDIAN.\n"
          "The Boost Endian library must be revised to work correctly on this system.\n"
          "Please report this problem to the Boost mailing list.\n";
        exit(1);
  #   endif
    } 
    else if ( memcmp( v.c, "\1\2\3\4\5\6\7\10", 8) == 0 )
    {
      cout << "This machine is big-endian.\n";
  #   ifndef BOOST_BIG_ENDIAN
        cout << "yet boost/detail/endian.hpp does not define BOOST_BIG_ENDIAN.\n"
          "The Boost Endian library must be revised to work correctly on this system.\n"
          "Please report this problem to the Boost mailing list.\n";
        exit(1);
  #   endif
    }
    else
    { 
      cout << "This machine is neither strict big-endian nor strict little-endian\n"
        "The Boost Endian library must be revised to work correctly on this system.\n"
          "Please report this problem to the Boost mailing list.\n";
      exit(1);
    }
    cout << "That should not matter and is presented for your information only.\n";
  } // detect_order

  //  check_data  ------------------------------------------------------------//

  void check_data()
  {
    big_8_t big_8;
    big_16_t big_16;
    big_24_t big_24;
    big_32_t big_32;
    big_40_t big_40;
    big_48_t big_48;
    big_56_t big_56;
    big_64_t big_64;

    big_u8_t big_u8;
    big_u16_t big_u16;
    big_u24_t big_u24;
    big_u32_t big_u32;
    big_u40_t big_u40;
    big_u48_t big_u48;
    big_u56_t big_u56;
    big_u64_t big_u64;

    little_8_t little_8;
    little_16_t little_16;
    little_24_t little_24;
    little_32_t little_32;
    little_40_t little_40;
    little_48_t little_48;
    little_56_t little_56;
    little_64_t little_64;

    little_u8_t little_u8;
    little_u16_t little_u16;
    little_u24_t little_u24;
    little_u32_t little_u32;
    little_u40_t little_u40;
    little_u48_t little_u48;
    little_u56_t little_u56;
    little_u64_t little_u64;

    native_8_t native_8;
    native_16_t native_16;
    native_24_t native_24;
    native_32_t native_32;
    native_40_t native_40;
    native_48_t native_48;
    native_56_t native_56;
    native_64_t native_64;

    native_u8_t native_u8;
    native_u16_t native_u16;
    native_u24_t native_u24;
    native_u32_t native_u32;
    native_u40_t native_u40;
    native_u48_t native_u48;
    native_u56_t native_u56;
    native_u64_t native_u64;

    big_int16_t  big_int16;
    big_int32_t  big_int32;
    big_int64_t  big_int64;

    big_uint16_t big_uint16;
    big_uint32_t big_uint32;
    big_uint64_t big_uint64;

    little_int16_t  little_int16;
    little_int32_t  little_int32;
    little_int64_t  little_int64;

    little_uint16_t little_uint16 ;
    little_uint32_t little_uint32 ;
    little_uint64_t little_uint64 ;

    big_float32_t big_float32;
    big_float64_t big_float64;
    little_float32_t little_float32;
    little_float64_t little_float64;
    
    VERIFY(big_float32.data() == reinterpret_cast<const char *>(&big_float32));
    VERIFY(big_float64.data() == reinterpret_cast<const char *>(&big_float64));

    VERIFY(little_float32.data() == reinterpret_cast<const char *>(&little_float32));
    VERIFY(little_float64.data() == reinterpret_cast<const char *>(&little_float64));

    big_float32un_t big_float32un;
    big_float64un_t big_float64un;
    little_float32un_t little_float32un;
    little_float64un_t little_float64un;
    
    VERIFY(big_float32un.data() == reinterpret_cast<const char *>(&big_float32un));
    VERIFY(big_float64un.data() == reinterpret_cast<const char *>(&big_float64un));

    VERIFY(little_float32un.data() == reinterpret_cast<const char *>(&little_float32un));
    VERIFY(little_float64un.data() == reinterpret_cast<const char *>(&little_float64un));

    VERIFY(big_8.data() == reinterpret_cast<const char *>(&big_8));
    VERIFY(big_16.data() == reinterpret_cast<const char *>(&big_16));
    VERIFY(big_24.data() == reinterpret_cast<const char *>(&big_24));
    VERIFY(big_32.data() == reinterpret_cast<const char *>(&big_32));
    VERIFY(big_40.data() == reinterpret_cast<const char *>(&big_40));
    VERIFY(big_48.data() == reinterpret_cast<const char *>(&big_48));
    VERIFY(big_56.data() == reinterpret_cast<const char *>(&big_56));
    VERIFY(big_64.data() == reinterpret_cast<const char *>(&big_64));

    VERIFY(big_u8.data() == reinterpret_cast<const char *>(&big_u8));
    VERIFY(big_u16.data() == reinterpret_cast<const char *>(&big_u16));
    VERIFY(big_u24.data() == reinterpret_cast<const char *>(&big_u24));
    VERIFY(big_u32.data() == reinterpret_cast<const char *>(&big_u32));
    VERIFY(big_u40.data() == reinterpret_cast<const char *>(&big_u40));
    VERIFY(big_u48.data() == reinterpret_cast<const char *>(&big_u48));
    VERIFY(big_u56.data() == reinterpret_cast<const char *>(&big_u56));
    VERIFY(big_u64.data() == reinterpret_cast<const char *>(&big_u64));

    VERIFY(little_8.data() == reinterpret_cast<const char *>(&little_8));
    VERIFY(little_16.data() == reinterpret_cast<const char *>(&little_16));
    VERIFY(little_24.data() == reinterpret_cast<const char *>(&little_24));
    VERIFY(little_32.data() == reinterpret_cast<const char *>(&little_32));
    VERIFY(little_40.data() == reinterpret_cast<const char *>(&little_40));
    VERIFY(little_48.data() == reinterpret_cast<const char *>(&little_48));
    VERIFY(little_56.data() == reinterpret_cast<const char *>(&little_56));
    VERIFY(little_64.data() == reinterpret_cast<const char *>(&little_64));

    VERIFY(little_u8.data() == reinterpret_cast<const char *>(&little_u8));
    VERIFY(little_u16.data() == reinterpret_cast<const char *>(&little_u16));
    VERIFY(little_u24.data() == reinterpret_cast<const char *>(&little_u24));
    VERIFY(little_u32.data() == reinterpret_cast<const char *>(&little_u32));
    VERIFY(little_u40.data() == reinterpret_cast<const char *>(&little_u40));
    VERIFY(little_u48.data() == reinterpret_cast<const char *>(&little_u48));
    VERIFY(little_u56.data() == reinterpret_cast<const char *>(&little_u56));
    VERIFY(little_u64.data() == reinterpret_cast<const char *>(&little_u64));

    VERIFY(native_8.data() == reinterpret_cast<const char *>(&native_8));
    VERIFY(native_16.data() == reinterpret_cast<const char *>(&native_16));
    VERIFY(native_24.data() == reinterpret_cast<const char *>(&native_24));
    VERIFY(native_32.data() == reinterpret_cast<const char *>(&native_32));
    VERIFY(native_40.data() == reinterpret_cast<const char *>(&native_40));
    VERIFY(native_48.data() == reinterpret_cast<const char *>(&native_48));
    VERIFY(native_56.data() == reinterpret_cast<const char *>(&native_56));
    VERIFY(native_64.data() == reinterpret_cast<const char *>(&native_64));

    VERIFY(native_u8.data() == reinterpret_cast<const char *>(&native_u8));
    VERIFY(native_u16.data() == reinterpret_cast<const char *>(&native_u16));
    VERIFY(native_u24.data() == reinterpret_cast<const char *>(&native_u24));
    VERIFY(native_u32.data() == reinterpret_cast<const char *>(&native_u32));
    VERIFY(native_u40.data() == reinterpret_cast<const char *>(&native_u40));
    VERIFY(native_u48.data() == reinterpret_cast<const char *>(&native_u48));
    VERIFY(native_u56.data() == reinterpret_cast<const char *>(&native_u56));
    VERIFY(native_u64.data() == reinterpret_cast<const char *>(&native_u64));

    VERIFY(big_int16.data() == reinterpret_cast<const char *>(&big_int16));
    VERIFY(big_int32.data() == reinterpret_cast<const char *>(&big_int32));
    VERIFY(big_int64.data() == reinterpret_cast<const char *>(&big_int64));

    VERIFY(big_uint16.data() == reinterpret_cast<const char *>(&big_uint16));
    VERIFY(big_uint32.data() == reinterpret_cast<const char *>(&big_uint32));
    VERIFY(big_uint64.data() == reinterpret_cast<const char *>(&big_uint64));

    VERIFY(little_int16.data() == reinterpret_cast<const char *>(&little_int16));
    VERIFY(little_int32.data() == reinterpret_cast<const char *>(&little_int32));
    VERIFY(little_int64.data() == reinterpret_cast<const char *>(&little_int64));

    VERIFY(little_uint16.data() == reinterpret_cast<const char *>(&little_uint16));
    VERIFY(little_uint32.data() == reinterpret_cast<const char *>(&little_uint32));
    VERIFY(little_uint64.data() == reinterpret_cast<const char *>(&little_uint64));
 
  }

  //  check_size  ------------------------------------------------------------//

  void check_size()
  {
    VERIFY( numeric_limits<signed char>::digits == 7 );
    VERIFY( numeric_limits<unsigned char>::digits == 8 );

    VERIFY_SIZE(sizeof( big_float32_t ), 4 );
    VERIFY_SIZE(sizeof( big_float64_t ), 8 );
    VERIFY_SIZE(sizeof( little_float32_t ), 4 );
    VERIFY_SIZE(sizeof( little_float64_t ), 8 );

    VERIFY_SIZE(sizeof( big_float32un_t ), 4 );
    VERIFY_SIZE(sizeof( big_float64un_t ), 8 );
    VERIFY_SIZE(sizeof( little_float32un_t ), 4 );
    VERIFY_SIZE(sizeof( little_float64un_t ), 8 );

    VERIFY_SIZE( sizeof( big_8_t ), 1 );
    VERIFY_SIZE( sizeof( big_16_t ), 2 );
    VERIFY_SIZE( sizeof( big_24_t ), 3 );
    VERIFY_SIZE( sizeof( big_32_t ), 4 );
    VERIFY_SIZE( sizeof( big_40_t ), 5 );
    VERIFY_SIZE( sizeof( big_48_t ), 6 );
    VERIFY_SIZE( sizeof( big_56_t ), 7 );
    VERIFY_SIZE( sizeof( big_64_t ), 8 );

    VERIFY_SIZE( sizeof( big_u8_t ), 1 );
    VERIFY_SIZE( sizeof( big_u16_t ), 2 );
    VERIFY_SIZE( sizeof( big_u24_t ), 3 );
    VERIFY_SIZE( sizeof( big_u32_t ), 4 );
    VERIFY_SIZE( sizeof( big_u40_t ), 5 );
    VERIFY_SIZE( sizeof( big_u48_t ), 6 );
    VERIFY_SIZE( sizeof( big_u56_t ), 7 );
    VERIFY_SIZE( sizeof( big_u64_t ), 8 );

    VERIFY_SIZE( sizeof( little_8_t ), 1 );
    VERIFY_SIZE( sizeof( little_16_t ), 2 );
    VERIFY_SIZE( sizeof( little_24_t ), 3 );
    VERIFY_SIZE( sizeof( little_32_t ), 4 );
    VERIFY_SIZE( sizeof( little_40_t ), 5 );
    VERIFY_SIZE( sizeof( little_48_t ), 6 );
    VERIFY_SIZE( sizeof( little_56_t ), 7 );
    VERIFY_SIZE( sizeof( little_64_t ), 8 );

    VERIFY_SIZE( sizeof( little_u8_t ), 1 );
    VERIFY_SIZE( sizeof( little_u16_t ), 2 );
    VERIFY_SIZE( sizeof( little_u24_t ), 3 );
    VERIFY_SIZE( sizeof( little_u32_t ), 4 );
    VERIFY_SIZE( sizeof( little_u40_t ), 5 );
    VERIFY_SIZE( sizeof( little_u48_t ), 6 );
    VERIFY_SIZE( sizeof( little_u56_t ), 7 );
    VERIFY_SIZE( sizeof( little_u64_t ), 8 );

    VERIFY_SIZE( sizeof( native_8_t ), 1 );
    VERIFY_SIZE( sizeof( native_16_t ), 2 );
    VERIFY_SIZE( sizeof( native_24_t ), 3 );
    VERIFY_SIZE( sizeof( native_32_t ), 4 );
    VERIFY_SIZE( sizeof( native_40_t ), 5 );
    VERIFY_SIZE( sizeof( native_48_t ), 6 );
    VERIFY_SIZE( sizeof( native_56_t ), 7 );
    VERIFY_SIZE( sizeof( native_64_t ), 8 );

    VERIFY_SIZE( sizeof( native_u8_t ), 1 );
    VERIFY_SIZE( sizeof( native_u16_t ), 2 );
    VERIFY_SIZE( sizeof( native_u24_t ), 3 );
    VERIFY_SIZE( sizeof( native_u32_t ), 4 );
    VERIFY_SIZE( sizeof( native_u40_t ), 5 );
    VERIFY_SIZE( sizeof( native_u48_t ), 6 );
    VERIFY_SIZE( sizeof( native_u56_t ), 7 );
    VERIFY_SIZE( sizeof( native_u64_t ), 8 );

    VERIFY_SIZE( sizeof( big_int16_t ), 2 );
    VERIFY_SIZE( sizeof( big_int32_t ), 4 );
    VERIFY_SIZE( sizeof( big_int64_t ), 8 );

    VERIFY_SIZE( sizeof( big_uint16_t ), 2 );
    VERIFY_SIZE( sizeof( big_uint32_t ), 4 );
    VERIFY_SIZE( sizeof( big_uint64_t ), 8 );

    VERIFY_SIZE( sizeof( little_int16_t ), 2 );
    VERIFY_SIZE( sizeof( little_int32_t ), 4 );
    VERIFY_SIZE( sizeof( little_int64_t ), 8 );

    VERIFY_SIZE( sizeof( little_uint16_t ), 2 );
    VERIFY_SIZE( sizeof( little_uint32_t ), 4 );
    VERIFY_SIZE( sizeof( little_uint64_t ), 8 );
  } // check_size

  //  check_alignment  -------------------------------------------------------//

  void check_alignment()
  {
    // structs with offsets % 2 == 1 for type of size > 1 to ensure no alignment
    // bytes added for any size > 1

    struct big_struct
    {
      big_8_t    v0;
      big_16_t    v1;
      big_24_t    v3;
      char      v6;
      big_32_t    v7;
      big_40_t    v11;
      char      v16;
      big_48_t    v17;
      big_56_t    v23;
      char      v30;
      big_64_t    v31;
    };

    struct big_u_struct
    {
      big_u8_t    v0;
      big_u16_t    v1;
      big_u24_t    v3;
      char       v6;
      big_u32_t    v7;
      big_u40_t    v11;
      char       v16;
      big_u48_t    v17;
      big_u56_t    v23;
      char       v30;
      big_u64_t    v31;
    };

    struct little_struct
    {
      little_8_t    v0;
      little_16_t    v1;
      little_24_t    v3;
      char         v6;
      little_32_t    v7;
      little_40_t    v11;
      char         v16;
      little_48_t    v17;
      little_56_t    v23;
      char         v30;
      little_64_t    v31;
    };

    struct little_u_struct
    {
      little_u8_t    v0;
      little_u16_t    v1;
      little_u24_t    v3;
      char          v6;
      little_u32_t    v7;
      little_u40_t    v11;
      char          v16;
      little_u48_t    v17;
      little_u56_t    v23;
      char          v30;
      little_u64_t    v31;
    };

    struct native_struct
    {
      native_8_t    v0;
      native_16_t    v1;
      native_24_t    v3;
      char         v6;
      native_32_t    v7;
      native_40_t    v11;
      char         v16;
      native_48_t    v17;
      native_56_t    v23;
      char         v30;
      native_64_t    v31;
    };

    struct native_u_struct
    {
      native_u8_t    v0;
      native_u16_t    v1;
      native_u24_t    v3;
      char          v6;
      native_u32_t    v7;
      native_u40_t    v11;
      char          v16;
      native_u48_t    v17;
      native_u56_t    v23;
      char          v30;
      native_u64_t    v31;
    };

    struct big_float_struct
    {
      int16_t v0;
      big_float32_t v1;
    };

    struct big_unaligned_float_struct
    {
      int16_t v0;
      big_float32un_t v1;
    };

    //  aligned test cases
  
    struct big_aligned_struct
    {
      big_int16_t    v0;
      big_int32_t    v1;
      char          v3;
      big_int64_t    v4;
    };
  
    struct little_aligned_struct
    {
      little_int16_t    v0;
      little_int32_t    v1;
      char          v3;
      little_int64_t    v4;
    };

    int saved_err_count = err_count;

    VERIFY_SIZE( sizeof(big_struct), 39 );
    VERIFY_SIZE( sizeof(big_u_struct), 39 );
    VERIFY_SIZE( sizeof(little_struct), 39 );
    VERIFY_SIZE( sizeof(little_u_struct), 39 );
    VERIFY_SIZE( sizeof(native_struct), 39 );
    VERIFY_SIZE( sizeof(native_u_struct), 39 );
    VERIFY_SIZE( sizeof(big_aligned_struct), 24 );
    VERIFY_SIZE( sizeof(little_aligned_struct), 24 );
    VERIFY_SIZE( sizeof(big_float_struct), 8 );
    VERIFY_SIZE( sizeof(big_unaligned_float_struct), 6 );

    if ( saved_err_count == err_count )
    { 
      cout <<
        "Size and alignment for structures of endian types are as expected.\n";
    }
  } // check_alignment

  //  check_representation_and_range_and_ops  --------------------------------//

  void check_representation_and_range_and_ops()
  {
    // aligned floating point types
    float big_float32_expected = std::numeric_limits<float>::max();
    boost::endian::big_endian(big_float32_expected);
    big_float32_t big_float32(std::numeric_limits<float>::max());
    VERIFY(std::memcmp(big_float32.data(),
      reinterpret_cast<const char*>(&big_float32_expected), sizeof(float)) == 0);

    float little_float32_expected = std::numeric_limits<float>::max();
    boost::endian::little_endian(little_float32_expected);
    little_float32_t little_float32(std::numeric_limits<float>::max());
    VERIFY(std::memcmp(little_float32.data(),
      reinterpret_cast<const char*>(&little_float32_expected), sizeof(float)) == 0);

    double big_float64_expected = std::numeric_limits<double>::max();
    boost::endian::big_endian(big_float64_expected);
    big_float64_t big_float64(std::numeric_limits<double>::max());
    VERIFY(std::memcmp(big_float64.data(),
      reinterpret_cast<const char*>(&big_float64_expected), sizeof(double)) == 0);

    double little_float64_expected = std::numeric_limits<double>::max();
    boost::endian::little_endian(little_float64_expected);
    little_float64_t little_float64(std::numeric_limits<double>::max());
    VERIFY(std::memcmp(little_float64.data(),
      reinterpret_cast<const char*>(&little_float64_expected), sizeof(double)) == 0);

    VERIFY_VALUE_AND_OPS( big_float32_t, float,  std::numeric_limits<float>::max() );
    VERIFY_VALUE_AND_OPS( big_float32_t, float, std::numeric_limits<float>::min() );
    VERIFY_VALUE_AND_OPS( big_float64_t, double,  std::numeric_limits<double>::max() );
    VERIFY_VALUE_AND_OPS( big_float64_t, double, std::numeric_limits<double>::min() );

    VERIFY_VALUE_AND_OPS( little_float32_t, float,  std::numeric_limits<float>::max() );
    VERIFY_VALUE_AND_OPS( little_float32_t, float, std::numeric_limits<float>::min() );
    VERIFY_VALUE_AND_OPS( little_float64_t, double,  std::numeric_limits<double>::max() );
    VERIFY_VALUE_AND_OPS( little_float64_t, double, std::numeric_limits<double>::min() );

    // unaligned floating point types
    float big_float32un_expected = std::numeric_limits<float>::max();
    boost::endian::big_endian(big_float32un_expected);
    big_float32un_t big_float32un(std::numeric_limits<float>::max());
    VERIFY(std::memcmp(big_float32un.data(),
      reinterpret_cast<const char*>(&big_float32un_expected), sizeof(float)) == 0);

    float little_float32un_expected = std::numeric_limits<float>::max();
    boost::endian::little_endian(little_float32un_expected);
    little_float32un_t little_float32un(std::numeric_limits<float>::max());
    VERIFY(std::memcmp(little_float32un.data(),
      reinterpret_cast<const char*>(&little_float32un_expected), sizeof(float)) == 0);

    double big_float64un_expected = std::numeric_limits<double>::max();
    boost::endian::big_endian(big_float64un_expected);
    big_float64un_t big_float64un(std::numeric_limits<double>::max());
    VERIFY(std::memcmp(big_float64un.data(),
      reinterpret_cast<const char*>(&big_float64un_expected), sizeof(double)) == 0);

    double little_float64un_expected = std::numeric_limits<double>::max();
    boost::endian::little_endian(little_float64un_expected);
    little_float64un_t little_float64un(std::numeric_limits<double>::max());
    VERIFY(std::memcmp(little_float64un.data(),
      reinterpret_cast<const char*>(&little_float64un_expected), sizeof(double)) == 0);

    VERIFY_VALUE_AND_OPS( big_float32un_t, float, std::numeric_limits<float>::max() );
    VERIFY_VALUE_AND_OPS( big_float32un_t, float, std::numeric_limits<float>::min() );
    VERIFY_VALUE_AND_OPS( big_float64un_t, double, std::numeric_limits<double>::max() );
    VERIFY_VALUE_AND_OPS( big_float64un_t, double, std::numeric_limits<double>::min() );

    VERIFY_VALUE_AND_OPS( little_float32un_t, float, std::numeric_limits<float>::max() );
    VERIFY_VALUE_AND_OPS( little_float32un_t, float, std::numeric_limits<float>::min() );
    VERIFY_VALUE_AND_OPS( little_float64un_t, double, std::numeric_limits<double>::max() );
    VERIFY_VALUE_AND_OPS( little_float64un_t, double, std::numeric_limits<double>::min() );

    float a = 1.0F;
    big_float32_t b(1.0F);
    big_float32un_t c(1.0F);
    little_float32_t d(1.0F);
    little_float32un_t e(1.0F);
    VERIFY(a==b);
    VERIFY(a==c);
    VERIFY(a==d);
    VERIFY(a==e);

    // unaligned integer types
    VERIFY_BIG_REPRESENTATION( big_8_t );
    VERIFY_VALUE_AND_OPS( big_8_t, int_least8_t,  0x7f );
    VERIFY_VALUE_AND_OPS( big_8_t, int_least8_t, -0x80 );

    VERIFY_BIG_REPRESENTATION( big_16_t );
    VERIFY_VALUE_AND_OPS( big_16_t, int_least16_t,  0x7fff );
    VERIFY_VALUE_AND_OPS( big_16_t, int_least16_t, -0x8000 );

    VERIFY_BIG_REPRESENTATION( big_24_t );
    VERIFY_VALUE_AND_OPS( big_24_t, int_least32_t,  0x7fffff );
    VERIFY_VALUE_AND_OPS( big_24_t, int_least32_t, -0x800000 );

    VERIFY_BIG_REPRESENTATION( big_32_t );
    VERIFY_VALUE_AND_OPS( big_32_t, int_least32_t,  0x7fffffff );
    VERIFY_VALUE_AND_OPS( big_32_t, int_least32_t, -0x7fffffff-1 );

    VERIFY_BIG_REPRESENTATION( big_40_t );
    VERIFY_VALUE_AND_OPS( big_40_t, int_least64_t,  0x7fffffffffLL );
    VERIFY_VALUE_AND_OPS( big_40_t, int_least64_t, -0x8000000000LL );

    VERIFY_BIG_REPRESENTATION( big_48_t );
    VERIFY_VALUE_AND_OPS( big_48_t, int_least64_t,  0x7fffffffffffLL );
    VERIFY_VALUE_AND_OPS( big_48_t, int_least64_t, -0x800000000000LL );

    VERIFY_BIG_REPRESENTATION( big_56_t );
    VERIFY_VALUE_AND_OPS( big_56_t, int_least64_t,  0x7fffffffffffffLL );
    VERIFY_VALUE_AND_OPS( big_56_t, int_least64_t, -0x80000000000000LL );

    VERIFY_BIG_REPRESENTATION( big_64_t );
    VERIFY_VALUE_AND_OPS( big_64_t, int_least64_t,  0x7fffffffffffffffLL );
    VERIFY_VALUE_AND_OPS( big_64_t, int_least64_t, -0x7fffffffffffffffLL-1 );

    VERIFY_BIG_REPRESENTATION( big_u8_t );
    VERIFY_VALUE_AND_OPS( big_u8_t, uint_least8_t,  0xff );

    VERIFY_BIG_REPRESENTATION( big_u16_t );
    VERIFY_VALUE_AND_OPS( big_u16_t, uint_least16_t, 0xffff );

    VERIFY_BIG_REPRESENTATION( big_u24_t );
    VERIFY_VALUE_AND_OPS( big_u24_t, uint_least32_t, 0xffffff );

    VERIFY_BIG_REPRESENTATION( big_u32_t );
    VERIFY_VALUE_AND_OPS( big_u32_t, uint_least32_t, 0xffffffff );

    VERIFY_BIG_REPRESENTATION( big_u40_t );
    VERIFY_VALUE_AND_OPS( big_u40_t, uint_least64_t, 0xffffffffffLL );

    VERIFY_BIG_REPRESENTATION( big_u48_t );
    VERIFY_VALUE_AND_OPS( big_u48_t, uint_least64_t, 0xffffffffffffLL );

    VERIFY_BIG_REPRESENTATION( big_u56_t );
    VERIFY_VALUE_AND_OPS( big_u56_t, uint_least64_t, 0xffffffffffffffLL );

    VERIFY_BIG_REPRESENTATION( big_u64_t );
    VERIFY_VALUE_AND_OPS( big_u64_t, uint_least64_t, 0xffffffffffffffffULL );

    VERIFY_LITTLE_REPRESENTATION( little_8_t );
    VERIFY_VALUE_AND_OPS( little_8_t, int_least8_t,   0x7f );
    VERIFY_VALUE_AND_OPS( little_8_t, int_least8_t,  -0x80 );

    VERIFY_LITTLE_REPRESENTATION( little_16_t );
    VERIFY_VALUE_AND_OPS( little_16_t, int_least16_t,  0x7fff );
    VERIFY_VALUE_AND_OPS( little_16_t, int_least16_t, -0x8000 );

    VERIFY_LITTLE_REPRESENTATION( little_24_t );
    VERIFY_VALUE_AND_OPS( little_24_t, int_least32_t,  0x7fffff );
    VERIFY_VALUE_AND_OPS( little_24_t, int_least32_t, -0x800000 );

    VERIFY_LITTLE_REPRESENTATION( little_32_t );
    VERIFY_VALUE_AND_OPS( little_32_t, int_least32_t,  0x7fffffff );
    VERIFY_VALUE_AND_OPS( little_32_t, int_least32_t, -0x7fffffff-1 );

    VERIFY_LITTLE_REPRESENTATION( little_40_t );
    VERIFY_VALUE_AND_OPS( little_40_t, int_least64_t,  0x7fffffffffLL );
    VERIFY_VALUE_AND_OPS( little_40_t, int_least64_t, -0x8000000000LL );

    VERIFY_LITTLE_REPRESENTATION( little_48_t );
    VERIFY_VALUE_AND_OPS( little_48_t, int_least64_t,  0x7fffffffffffLL );
    VERIFY_VALUE_AND_OPS( little_48_t, int_least64_t, -0x800000000000LL );

    VERIFY_LITTLE_REPRESENTATION( little_56_t );
    VERIFY_VALUE_AND_OPS( little_56_t, int_least64_t,  0x7fffffffffffffLL );
    VERIFY_VALUE_AND_OPS( little_56_t, int_least64_t, -0x80000000000000LL );

    VERIFY_LITTLE_REPRESENTATION( little_64_t );
    VERIFY_VALUE_AND_OPS( little_64_t, int_least64_t,  0x7fffffffffffffffLL );
    VERIFY_VALUE_AND_OPS( little_64_t, int_least64_t, -0x7fffffffffffffffLL-1 );

    VERIFY_LITTLE_REPRESENTATION( little_u8_t );
    VERIFY_VALUE_AND_OPS( little_u8_t, uint_least8_t, 0xff );

    VERIFY_LITTLE_REPRESENTATION( little_u16_t );
    VERIFY_VALUE_AND_OPS( little_u16_t, uint_least16_t, 0xffff );

    VERIFY_LITTLE_REPRESENTATION( little_u24_t );
    VERIFY_VALUE_AND_OPS( little_u24_t, uint_least32_t, 0xffffff );

    VERIFY_LITTLE_REPRESENTATION( little_u32_t );
    VERIFY_VALUE_AND_OPS( little_u32_t, uint_least32_t, 0xffffffff );

    VERIFY_LITTLE_REPRESENTATION( little_u40_t );
    VERIFY_VALUE_AND_OPS( little_u40_t, uint_least64_t, 0xffffffffffLL );

    VERIFY_LITTLE_REPRESENTATION( little_u48_t );
    VERIFY_VALUE_AND_OPS( little_u48_t, uint_least64_t, 0xffffffffffffLL );

    VERIFY_LITTLE_REPRESENTATION( little_u56_t );
    VERIFY_VALUE_AND_OPS( little_u56_t, uint_least64_t, 0xffffffffffffffLL );

    VERIFY_LITTLE_REPRESENTATION( little_u64_t );
    VERIFY_VALUE_AND_OPS( little_u64_t, uint_least64_t, 0xffffffffffffffffULL );

    VERIFY_NATIVE_REPRESENTATION( native_8_t );
    VERIFY_VALUE_AND_OPS( native_8_t, int_least8_t,   0x7f );
    VERIFY_VALUE_AND_OPS( native_8_t, int_least8_t,  -0x80 );

    VERIFY_NATIVE_REPRESENTATION( native_16_t );
    VERIFY_VALUE_AND_OPS( native_16_t, int_least16_t,  0x7fff );
    VERIFY_VALUE_AND_OPS( native_16_t, int_least16_t, -0x8000 );

    VERIFY_NATIVE_REPRESENTATION( native_24_t );
    VERIFY_VALUE_AND_OPS( native_24_t, int_least32_t,  0x7fffff );
    VERIFY_VALUE_AND_OPS( native_24_t, int_least32_t, -0x800000 );

    VERIFY_NATIVE_REPRESENTATION( native_32_t );
    VERIFY_VALUE_AND_OPS( native_32_t, int_least32_t,  0x7fffffff );
    VERIFY_VALUE_AND_OPS( native_32_t, int_least32_t, -0x7fffffff-1 );

    VERIFY_NATIVE_REPRESENTATION( native_40_t );
    VERIFY_VALUE_AND_OPS( native_40_t, int_least64_t,  0x7fffffffffLL );
    VERIFY_VALUE_AND_OPS( native_40_t, int_least64_t, -0x8000000000LL );

    VERIFY_NATIVE_REPRESENTATION( native_48_t );
    VERIFY_VALUE_AND_OPS( native_48_t, int_least64_t,  0x7fffffffffffLL );
    VERIFY_VALUE_AND_OPS( native_48_t, int_least64_t, -0x800000000000LL );

    VERIFY_NATIVE_REPRESENTATION( native_56_t );
    VERIFY_VALUE_AND_OPS( native_56_t, int_least64_t,  0x7fffffffffffffLL );
    VERIFY_VALUE_AND_OPS( native_56_t, int_least64_t, -0x80000000000000LL );

    VERIFY_NATIVE_REPRESENTATION( native_64_t );
    VERIFY_VALUE_AND_OPS( native_64_t, int_least64_t,  0x7fffffffffffffffLL );
    VERIFY_VALUE_AND_OPS( native_64_t, int_least64_t, -0x7fffffffffffffffLL-1 );

    VERIFY_NATIVE_REPRESENTATION( native_u8_t );
    VERIFY_VALUE_AND_OPS( native_u8_t, uint_least8_t, 0xff );

    VERIFY_NATIVE_REPRESENTATION( native_u16_t );
    VERIFY_VALUE_AND_OPS( native_u16_t, uint_least16_t, 0xffff );

    VERIFY_NATIVE_REPRESENTATION( native_u24_t );
    VERIFY_VALUE_AND_OPS( native_u24_t, uint_least32_t, 0xffffff );

    VERIFY_NATIVE_REPRESENTATION( native_u32_t );
    VERIFY_VALUE_AND_OPS( native_u32_t, uint_least32_t, 0xffffffff );

    VERIFY_NATIVE_REPRESENTATION( native_u40_t );
    VERIFY_VALUE_AND_OPS( native_u40_t, uint_least64_t, 0xffffffffffLL );

    VERIFY_NATIVE_REPRESENTATION( native_u48_t );
    VERIFY_VALUE_AND_OPS( native_u48_t, uint_least64_t, 0xffffffffffffLL );

    VERIFY_NATIVE_REPRESENTATION( native_u56_t );
    VERIFY_VALUE_AND_OPS( native_u56_t, uint_least64_t, 0xffffffffffffffLL );

    VERIFY_NATIVE_REPRESENTATION( native_u64_t );
    VERIFY_VALUE_AND_OPS( native_u64_t, uint_least64_t, 0xffffffffffffffffULL );

    // aligned integer types
    VERIFY_BIG_REPRESENTATION( big_int16_t );
    VERIFY_VALUE_AND_OPS( big_int16_t, int_least16_t,  0x7fff );
    VERIFY_VALUE_AND_OPS( big_int16_t, int_least16_t, -0x8000 );

    VERIFY_BIG_REPRESENTATION( big_int32_t );
    VERIFY_VALUE_AND_OPS( big_int32_t, int_least32_t,  0x7fffffff );
    VERIFY_VALUE_AND_OPS( big_int32_t, int_least32_t, -0x7fffffff-1 );

    VERIFY_BIG_REPRESENTATION( big_int64_t );
    VERIFY_VALUE_AND_OPS( big_int64_t, int_least64_t,  0x7fffffffffffffffLL );
    VERIFY_VALUE_AND_OPS( big_int64_t, int_least64_t, -0x7fffffffffffffffLL-1 );

    VERIFY_BIG_REPRESENTATION( big_uint16_t );
    VERIFY_VALUE_AND_OPS( big_uint16_t, uint_least16_t, 0xffff );

    VERIFY_BIG_REPRESENTATION( big_uint32_t );
    VERIFY_VALUE_AND_OPS( big_uint32_t, uint_least32_t, 0xffffffff );

    VERIFY_BIG_REPRESENTATION( big_uint64_t );
    VERIFY_VALUE_AND_OPS( big_uint64_t, uint_least64_t, 0xffffffffffffffffULL );

    VERIFY_LITTLE_REPRESENTATION( little_int16_t );
    VERIFY_VALUE_AND_OPS( little_int16_t, int_least16_t,  0x7fff );
    VERIFY_VALUE_AND_OPS( little_int16_t, int_least16_t, -0x8000 );

    VERIFY_LITTLE_REPRESENTATION( little_int32_t );
    VERIFY_VALUE_AND_OPS( little_int32_t, int_least32_t,  0x7fffffff );
    VERIFY_VALUE_AND_OPS( little_int32_t, int_least32_t, -0x7fffffff-1 );

    VERIFY_LITTLE_REPRESENTATION( little_int64_t );
    VERIFY_VALUE_AND_OPS( little_int64_t, int_least64_t,  0x7fffffffffffffffLL );
    VERIFY_VALUE_AND_OPS( little_int64_t, int_least64_t, -0x7fffffffffffffffLL-1 );

    VERIFY_LITTLE_REPRESENTATION( little_uint16_t );
    VERIFY_VALUE_AND_OPS( little_uint16_t, uint_least16_t, 0xffff );

    VERIFY_LITTLE_REPRESENTATION( little_uint32_t );
    VERIFY_VALUE_AND_OPS( little_uint32_t, uint_least32_t, 0xffffffff );

    VERIFY_LITTLE_REPRESENTATION( little_uint64_t );
    VERIFY_VALUE_AND_OPS( little_uint64_t, uint_least64_t, 0xffffffffffffffffULL );

  } // check_representation_and_range

  class MyInt
  {
    int32_t mx;
  public:
    MyInt(int32_t x) : mx(x) {}
    operator int32_t() const {return mx;}

    //friend int32_t operator+(const MyInt& x) {return x;}
  };

  void check_udt()
  {
    typedef boost::endian::endian< order::big, MyInt, 32 >  mybig_32_t;

    mybig_32_t v(10);
    cout << "+v is " << +v << endl;
    v += 1;
    cout << "v is " << +v << endl;
    v -= 2;
    cout << "v is " << +v << endl;
    v *= 2;
    cout << "v is " << +v << endl;
    ++v;
    cout << "v is " << +v << endl;
    --v;
    cout << "v is " << +v << endl;
//    cout << "v+v is " << +(v+v) << endl;
  }

  long iterations = 10000;
  
  template< class Endian >
  Endian timing_test( const char * s)
  {
    cout << s << " timing test, " << iterations << " iterations: ";
//    progress_timer t;

    Endian v = 1;
    for ( long i = 0; i < iterations; ++i )
    {
      v += 1;
      v *= 3;
      ++v;
      v *= i;
      if ( i == 0 ) VERIFY_VALUE_AND_OPS( Endian, typename Endian::value_type, 21 );
    }
    return v;
  }

} // unnamed namespace

//  main  ------------------------------------------------------------------------------//

int cpp_main( int argc, char * argv[] )
{
  cout << "Usage: "
       << argv[0] << " [#],\n where # specifies iteration count\n"
          " default iteration count is " << iterations << endl;

  if ( argc > 1 )
    iterations = atol( argv[1] );
  if ( iterations < 1 ) iterations = 1;

  detect_order();
  check_size();
  check_alignment();
  check_representation_and_range_and_ops();
  check_data();
  check_udt();

  //timing_test<big_32_t> ( "big_32_t" );
  //timing_test<big_int32_t>( "big_int32_t" );
  //timing_test<little_32_t> ( "little_32_t" );
  //timing_test<little_int32_t>( "little_int32_t" );

  cout << "\n" << err_count << " errors detected\nTest "
       << (err_count==0 ? "passed\n\n" : "failed\n\n");

  return err_count ? 1 : 0;
} // main
