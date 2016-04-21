//==================================================================================================
/*!

  Copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#include <boost/simd/function/scalar/abs_s.hpp>
#include <simd_test.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>


STF_CASE_TPL( "Check abs_s behavior with floating", STF_IEEE_TYPES )
{
  namespace bs = boost::simd;
  using bs::abs_s;
  using r_t = decltype(abs_s(T()));
  STF_TYPE_IS(r_t, T);

#ifndef BOOST_SIMD_NO_INVALIDS
  STF_EQUAL(abs_s(bs::Inf<T>()),  bs::Inf<r_t>());
  STF_EQUAL(abs_s(bs::Minf<T>()), bs::Inf<r_t>());
  STF_IEEE_EQUAL(abs_s(bs::Nan<T>()),  bs::Nan<r_t>());
#endif
  STF_EQUAL(abs_s(bs::Mone<T>()), bs::One<T>());
  STF_EQUAL(abs_s(bs::One<T>()), bs::One<T>());
  STF_EQUAL(abs_s(bs::Valmax<T>()), bs::Valmax<T>());
  STF_EQUAL(abs_s(bs::Valmin<T>()), bs::Valmax<T>());
  STF_EQUAL(abs_s(bs::Zero<T>()), bs::Zero<T>());
}



