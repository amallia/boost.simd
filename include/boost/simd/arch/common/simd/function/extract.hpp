//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_EXTRACT_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/aliasing.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/hierarchy/logical.hpp>
#include <boost/dispatch/function/overload.hpp>
#include <boost/dispatch/adapted/std/integral_constant.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  // -----------------------------------------------------------------------------------------------
  // extract get the value out of the storage
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename Ext, typename A1)
                          , bs::simd_
                          , bs::pack_<bd::arithmetic_<A0>,Ext>
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    using result_t = typename A0::value_type;
    BOOST_FORCEINLINE result_t operator() ( A0 const& a0, A1 i) const BOOST_NOEXCEPT
    {
      return result_t(reinterpret_cast<detail::may_alias_t<result_t const>*>( &(a0.storage()) )[i]);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // extract on logical pack potentially use bitwise cast
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename Ext, typename A1)
                          , bs::simd_
                          , bs::pack_<bs::logical_<A0>,Ext>
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    using result_t = typename A0::value_type;

    template<typename K>
    static BOOST_FORCEINLINE result_t do_( A0 const& a0, A1 i, K const&) BOOST_NOEXCEPT
    {
      auto bits = bitwise_cast<as_arithmetic_t<A0>>(a0);
      return result_t( boost::simd::extract(bits,i));
    }

    static BOOST_FORCEINLINE result_t do_( A0 const& a0, A1 i, aggregate_storage const&) BOOST_NOEXCEPT
    {
      return A0::traits::at(a0,i);
    }

    BOOST_FORCEINLINE result_t operator() ( A0 const& a0, A1 i) const BOOST_NOEXCEPT
    {
      return do_(a0,i, typename A0::storage_kind{});
    }
  };

  // -----------------------------------------------------------------------------------------------
  // extract on logical pack potentially use bitwise cast but still optimizes static indexing
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename Ext, typename A1)
                          , bs::simd_
                          , bs::pack_<bs::logical_<A0>,Ext>
                          , bd::constant_< bd::integer_<A1> >
                          )
  {
    using result_t = typename A0::value_type;

    static BOOST_FORCEINLINE
    result_t do_( A0 const& a0, A1 const&, native_storage const&) BOOST_NOEXCEPT
    {
      auto bits = bitwise_cast<as_arithmetic_t<A0>>(a0);
      return result_t( boost::simd::extract<A1::value>(bits));
    }

    template<typename K>
    static BOOST_FORCEINLINE result_t do_( A0 const& a0, A1 const&, K const&) BOOST_NOEXCEPT
    {
      return A0::traits::at(a0,A1::value);
    }

    BOOST_FORCEINLINE result_t operator() ( A0 const& a0, A1 const& i) const BOOST_NOEXCEPT
    {
      return do_(a0,i, typename A0::storage_kind{});
    }
  };
} } }

#endif
