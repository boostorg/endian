#ifndef BOOST_ENDIAN_DETAIL_ENDIAN_LOAD_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ENDIAN_LOAD_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/endian/conversion.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <cstddef>
#include <cstring>

namespace boost
{
namespace endian
{

namespace detail
{

template<class T, std::size_t N1, BOOST_SCOPED_ENUM(order) O1, std::size_t N2, BOOST_SCOPED_ENUM(order) O2> struct endian_load_impl
{
};

} // namespace detail

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) Order>
inline T endian_load( unsigned char const * p ) BOOST_NOEXCEPT
{
    return detail::endian_load_impl<T, sizeof(T), endian::order::native, N, Order>()( p );
}

namespace detail
{

template<std::size_t N> struct integral_by_size
{
};

template<> struct integral_by_size<1>
{
    typedef uint8_t type;
};

template<> struct integral_by_size<2>
{
    typedef uint16_t type;
};

template<> struct integral_by_size<4>
{
    typedef uint32_t type;
};

template<> struct integral_by_size<8>
{
    typedef uint64_t type;
};

// same endianness, same size

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O> struct endian_load_impl<T, N, O, N, O>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        T t;
        std::memcpy( &t, p, N );
        return t;
    }
};

// same size, reverse endianness

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O1, BOOST_SCOPED_ENUM(order) O2> struct endian_load_impl<T, N, O1, N, O2>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        typename integral_by_size<N>::type tmp;
        std::memcpy( &tmp, p, N );

        endian_reverse_inplace( tmp );

        T t;
        std::memcpy( &t, &tmp, N );
        return t;
    }
};

// expanding load 3 -> 4

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 4, Order, 3, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 4 ];

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];
        tmp[3] = boost::is_signed<T>::value && ( p[2] & 0x80 )? 0xFF: 0x00;

        return endian::endian_load<T, 4, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 4, Order, 3, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 4 ];

        tmp[0] = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;
        tmp[1] = p[0];
        tmp[2] = p[1];
        tmp[3] = p[2];

        return endian::endian_load<T, 4, order::big>( tmp );
    }
};

// expanding load 5 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 5, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[4] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];
        tmp[3] = p[3];
        tmp[4] = p[4];

        tmp[5] = fill;
        tmp[6] = fill;
        tmp[7] = fill;

        return endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 5, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;
        tmp[2] = fill;

        tmp[3] = p[0];
        tmp[4] = p[1];
        tmp[5] = p[2];
        tmp[6] = p[3];
        tmp[7] = p[4];

        return endian::endian_load<T, 8, order::big>( tmp );
    }
};

// expanding load 6 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 6, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[5] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];
        tmp[3] = p[3];
        tmp[4] = p[4];
        tmp[5] = p[5];

        tmp[6] = fill;
        tmp[7] = fill;

        return endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 6, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;

        tmp[2] = p[0];
        tmp[3] = p[1];
        tmp[4] = p[2];
        tmp[5] = p[3];
        tmp[6] = p[4];
        tmp[7] = p[5];

        return endian::endian_load<T, 8, order::big>( tmp );
    }
};

// expanding load 7 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 7, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[6] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];
        tmp[3] = p[3];
        tmp[4] = p[4];
        tmp[5] = p[5];
        tmp[6] = p[6];

        tmp[7] = fill;

        return endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 7, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;

        tmp[1] = p[0];
        tmp[2] = p[1];
        tmp[3] = p[2];
        tmp[4] = p[3];
        tmp[5] = p[4];
        tmp[6] = p[5];
        tmp[7] = p[6];

        return endian::endian_load<T, 8, order::big>( tmp );
    }
};

} // namespace detail

} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_ENDIAN_LOAD_HPP_INCLUDED
