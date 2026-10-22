/*
 * Copyright (c) 2002 Fabrice Bellard
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_MEM_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_MEM_ਅੰਦਰੂਨੀ_H

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਅਨ੍ਤਰ੍ਭਾਵ <stdalign.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"

/**
 * @def DECLARE_ALIGNED(n,t,v)
 * Declare a variable that is aligned in memory.
 *
 * @code{.c}
 * DECLARE_ALIGNED(16, uint16_t, aligned_int) = 42;
 * DECLARE_ALIGNED(32, uint8_t, aligned_array)[128];
 *
 * // The default-alignment equivalent would be
 * uint16_t aligned_int = 42;
 * uint8_t aligned_array[128];
 * @endcode
 *
 * @param n Minimum alignment in bytes
 * @param t Type of the variable (or array element)
 * @param v Name of the variable
 */

/**
 * @def DECLARE_ASM_ALIGNED(n,t,v)
 * Declare an aligned variable appropriate for use in inline assembly code.
 *
 * @code{.c}
 * DECLARE_ASM_ALIGNED(16, uint64_t, pw_08) = UINT64_C(0x0008000800080008);
 * @endcode
 *
 * @param n Minimum alignment in bytes
 * @param t Type of the variable (or array element)
 * @param v Name of the variable
 */

/**
 * @def DECLARE_ASM_CONST(n,t,v)
 * Declare a static constant aligned variable appropriate for use in inline
 * assembly code.
 *
 * @code{.c}
 * DECLARE_ASM_CONST(16, uint64_t, pw_08) = UINT64_C(0x0008000800080008);
 * @endcode
 *
 * @param n Minimum alignment in bytes
 * @param t Type of the variable (or array element)
 * @param v Name of the variable
 */

#ਜੇ defined(__DJGPP__)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED_T(n,t,v)    alignas(FFMIN(n, 16)) t v
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ASM_ALIGNED(n,t,v)  alignas(FFMIN(n, 16)) t av_ਵਰਤਿਆ v
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ASM_CONST(n,t,v)    alignas(FFMIN(n, 16)) ਸਥਿਰ ਅਚਲ t av_ਵਰਤਿਆ v
#ਜਾਂਜੇ defined(_MSC_VER)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED_T(n,t,v)    __declspec(align(n)) t v
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ASM_ALIGNED(n,t,v)  __declspec(align(n)) t av_ਵਰਤਿਆ v
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ASM_CONST(n,t,v)    __declspec(align(n)) ਸਥਿਰ ਅਚਲ t av_ਵਰਤਿਆ v
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED_T(n,t,v)    alignas(n) t v
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ASM_ALIGNED(n,t,v)  alignas(n) t av_ਵਰਤਿਆ v
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ASM_CONST(n,t,v)    alignas(n) ਸਥਿਰ ਅਚਲ t av_ਵਰਤਿਆ v
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_SIMD_ALIGN_64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGN_64 64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGN_32 32
#ਜਾਂਜੇ HAVE_SIMD_ALIGN_32
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGN_64 32
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGN_32 32
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGN_64 16
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGN_32 16
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED(n,t,v) DECLARE_ALIGNED_V(n,t,v)

// Macro needs to be double-wrapped in order to expand
// possible other macros being passed for n.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED_V(n,t,v) DECLARE_ALIGNED_##n(t,v)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED_4(t,v)  DECLARE_ALIGNED_T(       4, t, v)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED_8(t,v)  DECLARE_ALIGNED_T(       8, t, v)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED_16(t,v) DECLARE_ALIGNED_T(      16, t, v)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED_32(t,v) DECLARE_ALIGNED_T(ALIGN_32, t, v)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ALIGNED_64(t,v) DECLARE_ALIGNED_T(ALIGN_64, t, v)

// Some broken preprocessors need a second expansion
// to be forced to tokenize __VA_ARGS__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ E1(x) x

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOCAL_ALIGNED_D(a, t, v, s, o, ...)             \
    DECLARE_ALIGNED(a, t, la_##v) s o;                  \
    t (*v) o = la_##v

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOCAL_ALIGNED(a, t, v, ...) LOCAL_ALIGNED_##a(t, v, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOCAL_ALIGNED_4(t, v, ...) E1(LOCAL_ALIGNED_D(4, t, v, __VA_ARGS__,,))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOCAL_ALIGNED_8(t, v, ...) E1(LOCAL_ALIGNED_D(8, t, v, __VA_ARGS__,,))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOCAL_ALIGNED_16(t, v, ...) E1(LOCAL_ALIGNED_D(16, t, v, __VA_ARGS__,,))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOCAL_ALIGNED_32(t, v, ...) E1(LOCAL_ALIGNED_D(32, t, v, __VA_ARGS__,,))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOCAL_ALIGNED_64(t, v, ...) E1(LOCAL_ALIGNED_D(64, t, v, __VA_ARGS__,,))

#ਜੇ_ਅੰਤ /* AVUTIL_MEM_INTERNAL_H */
