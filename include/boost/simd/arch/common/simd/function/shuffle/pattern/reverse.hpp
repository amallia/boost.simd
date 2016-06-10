//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_PATTERN_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_PATTERN_REVERSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/detail/shuffle.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    // ---------------------------------------------------------------------------------------------
    // Check if pattern is [B B+1 ... B+C]
    template<int B, int... Ps> struct is_reverse
    {
      using type = brigand::all < brigand::transform< brigand::range<int,B,B+sizeof...(Ps)>
                                                    , brigand::reverse<brigand::integral_list<int,Ps...>>
                                                    , brigand::equal_to<brigand::_1,brigand::_2>
                                                    >
                                >;
    };

    template<int B, int P> struct is_reverse<B,P> : std::false_type {};
  }

  // -----------------------------------------------------------------------------------------------
  // Identity pattern hierarchy
  template<int B, typename P> struct reverse_pattern : detail::any_pattern_<reverse_pattern<B,P>>
  {
    static const std::size_t static_size = P::static_size;
    using parent = detail::any_pattern_<reverse_pattern<B,P>>;
  };
} }

// -------------------------------------------------------------------------------------------------
// Hierarchize reverse patterns
namespace boost { namespace dispatch { namespace ext
{
  template<int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<Ps...>,Origin
                          , typename std::enable_if < simd::detail
                                                          ::is_reverse<0,Ps...>::type::value
                                                    >::type
                          >
  {
    using type = boost::simd::reverse_pattern<0,bsd::pattern_<Ps...>>;
  };

  template<int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<Ps...>,Origin
                          , typename std::enable_if < simd::detail::is_reverse < sizeof...(Ps)
                                                                                , Ps...
                                                                                >::type::value
                                                    >::type
                          >
  {
    using type = boost::simd::reverse_pattern<1,bsd::pattern_<Ps...>>;
  };
} } }

#endif
