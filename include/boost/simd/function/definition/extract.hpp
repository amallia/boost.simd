//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS
  @copyright 2016 J.T.Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_EXTRACT_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/dispatch/function/make_callable.hpp>
#include <boost/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, extract_, boost::dispatch::elementwise_<extract_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, extract_);
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::extract_,extract);
  }

  template <class T,  class I> BOOST_FORCEINLINE auto extract(const T & a, const I& i) BOOST_NOEXCEPT
  -> decltype(detail::extract(a, i))
  {
    return detail::extract(a, i);
  }
  template <class T,  class I> BOOST_FORCEINLINE auto extract( T & a, const I& i) BOOST_NOEXCEPT
  -> decltype(detail::extract(a, i))
  {
    return detail::extract(a, i);
  }
  template < size_t N, class T> BOOST_FORCEINLINE dispatch::scalar_of_t<T> extract(const T & a) BOOST_NOEXCEPT
  {
    brigand::size_t<N> n;
    return detail::extract(a, n);
  }

} }

#endif
