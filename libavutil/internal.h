/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
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

/**
 * @file
 * common internal API header
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ਅੰਦਰੂਨੀ_H

#ਜੇ !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#ਜੇ_ਅੰਤ

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mathematics.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ attribute_align_arg
#ਜੇ ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_ਸੂਚਕ))
#ਨਹੀਂਤਾਂ
#    define attribute_align_arg
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_PRAGMA_DEPRECATED
#    ਜੇ defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ਧੱਕੋ)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(ਕੱਢੋ))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ਧੱਕੋ)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(ਕੱਢੋ))
#    ਨਹੀਂਤਾਂ
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#ਨਹੀਂਤਾਂ
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#ਜੇ_ਅੰਤ


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ANDROID__
#   include "compat/android/math.h"
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, ਆਕਾਰ(*p)))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, ਆਕਾਰ(*p)))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_PTR_ਜੋੜੋ(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ਖੇਤਰ_AT(type, off, obj) (*(type *)((ਅੱਖਰ *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#ਜੇ CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) ਨਿਰਾ
#ਨਹੀਂਤਾਂ
#   define NULL_IF_CONFIG_SMALL(x) x
#ਜੇ_ਅੰਤ

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
ਖਾਲੀ avpriv_report_missing_feature(ਖਾਲੀ *avc,
                                   ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
ਖਾਲੀ avpriv_request_sample(ਖਾਲੀ *avc,
                           ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ...) av_printf_format(2, 3);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#ਨਹੀਂਤਾਂ
#   define ff_dlog(ctx, ...) ਕਰੋ { ਜੇ (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } ਜਦੋਂ (0)
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#ਨਹੀਂਤਾਂ
#   define ff_tlog(ctx, ...) ਕਰੋ { } ਜਦੋਂ(0)
#ਜੇ_ਅੰਤ

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CHECKED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUINT   ਪੂਰਨ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUINT32 int32_t
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUINT   ਬਿਨਾਨਿਸ਼ਾਨੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUINT32 uint32_t
#ਜੇ_ਅੰਤ

ਸਥਿਰ av_always_inline av_const ਪੂਰਨ avpriv_mirror(ਪੂਰਨ x, ਪੂਰਨ w)
{
    ਜੇ (!w)
        ਵਾਪਸ 0;

    ਜਦੋਂ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)x > (ਬਿਨਾਨਿਸ਼ਾਨੀ)w) {
        x = -x;
        ਜੇ (x < 0)
            x += 2 * w;
    }
    ਵਾਪਸ x;
}

#ਜੇ_ਅੰਤ /* AVUTIL_INTERNAL_H */
