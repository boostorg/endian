#ifndef BOOST_ENDIAN_DETAIL_ENDIAN_STORE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ENDIAN_STORE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/endian/detail/integral_by_size.hpp>
#include <boost/endian/conversion.hpp>
#include <cstddef>
#include <cstring>

namespace boost
{
namespace endian
{

namespace detail
{

template<class T, std::size_t N1, BOOST_SCOPED_ENUM(order) O1, std::size_t N2, BOOST_SCOPED_ENUM(order) O2> struct endian_store_impl
{
};

} // namespace detail

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) Order>
inline void endian_store( T const & v, unsigned char * p ) BOOST_NOEXCEPT
{
    return detail::endian_store_impl<T, sizeof(T), endian::order::native, N, Order>()( v, p );
}

namespace detail
{

// same endianness, same size

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O> struct endian_store_impl<T, N, O, N, O>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        std::memcpy( p, &v, N );
    }
};

// same size, reverse endianness

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O1, BOOST_SCOPED_ENUM(order) O2> struct endian_store_impl<T, N, O1, N, O2>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        typename integral_by_size<N>::type tmp;
        std::memcpy( &tmp, &v, N );

        endian_reverse_inplace( tmp );

        std::memcpy( p, &tmp, N );
    }
};

// truncating store 4 -> 3

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 3, order::little>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 4 ];
        endian::endian_store<T, 4, order::little>( v, tmp );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 3, order::big>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 4 ];
        endian::endian_store<T, 4, order::big>( v, tmp );

        p[0] = tmp[1];
        p[1] = tmp[2];
        p[2] = tmp[3];
    }
};

// truncating store 8 -> 5

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 5, order::little>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];
        endian::endian_store<T, 8, order::little>( v, tmp );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
        p[4] = tmp[4];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 5, order::big>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];
        endian::endian_store<T, 8, order::big>( v, tmp );

        p[0] = tmp[3];
        p[1] = tmp[4];
        p[2] = tmp[5];
        p[3] = tmp[6];
        p[4] = tmp[7];
    }
};

// truncating store 8 -> 6

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 6, order::little>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];
        endian::endian_store<T, 8, order::little>( v, tmp );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
        p[4] = tmp[4];
        p[5] = tmp[5];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 6, order::big>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];
        endian::endian_store<T, 8, order::big>( v, tmp );

        p[0] = tmp[2];
        p[1] = tmp[3];
        p[2] = tmp[4];
        p[3] = tmp[5];
        p[4] = tmp[6];
        p[5] = tmp[7];
    }
};

// truncating store 8 -> 7

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 7, order::little>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];
        endian::endian_store<T, 8, order::little>( v, tmp );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
        p[4] = tmp[4];
        p[5] = tmp[5];
        p[6] = tmp[6];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 7, order::big>
{
    inline void operator()( T const & v, unsigned char * p ) const BOOST_NOEXCEPT
    {
        unsigned char tmp[ 8 ];
        endian::endian_store<T, 8, order::big>( v, tmp );

        p[0] = tmp[1];
        p[1] = tmp[2];
        p[2] = tmp[3];
        p[3] = tmp[4];
        p[4] = tmp[5];
        p[5] = tmp[6];
        p[6] = tmp[7];
    }
};

} // namespace detail

} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_ENDIAN_STORE_HPP_INCLUDED
