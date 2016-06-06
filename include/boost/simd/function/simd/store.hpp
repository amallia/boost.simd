//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SIMD_STORE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIMD_STORE_HPP_INCLUDED

#include <boost/simd/function/scalar/store.hpp>
#include <boost/simd/arch/common/simd/function/store.hpp>

#if defined(BOOST_HW_SIMD_X86)
# if BOOST_HW_SIMD_X86 >= BOOST_HW_SIMD_X86_SSE_VERSION
#  include <boost/simd/arch/x86/sse1/simd/function/store.hpp>
# endif
# if BOOST_HW_SIMD_X86 >= BOOST_HW_SIMD_X86_SSE2_VERSION
#  include <boost/simd/arch/x86/sse2/simd/function/store.hpp>
# endif
# if BOOST_HW_SIMD_X86 >= BOOST_HW_SIMD_X86_AVX_VERSION
#  include <boost/simd/arch/x86/avx/simd/function/store.hpp>
# endif
# if BOOST_HW_SIMD_X86 >= BOOST_HW_SIMD_X86_AVX2_VERSION
#  include <boost/simd/arch/x86/avx2/simd/function/store.hpp>
# endif
#endif

#if defined(BOOST_HW_SIMD_PPC)
#  if BOOST_HW_SIMD_PPC >= BOOST_HW_SIMD_PPC_VMX_VERSION
#    include <boost/simd/arch/ppc/vmx/simd/function/store.hpp>
#  endif
#endif

#endif