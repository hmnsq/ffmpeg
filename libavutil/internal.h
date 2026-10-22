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

#ifndef AVUTIL_INTERNAL_H
#define AVUTIL_INTERNAL_H

#எனில் !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#endif

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <math.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <assert.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ "config.h"
#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "mathematics.h"
#அந்தர்பாவ "macros.h"

#ifndef attribute_align_arg
#எனில் ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_pointer))
#இல்லையெனில்
#    define attribute_align_arg
#endif
#endif

#எனில் HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#endif

#எனில் HAVE_PRAGMA_DEPRECATED
#    எனில் defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(தள்ளு)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(எடு))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(தள்ளு)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(எடு))
#    இல்லையெனில்
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#இல்லையெனில்
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#endif


#ifdef __ANDROID__
#   include "compat/android/math.h"
#endif

#define FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, அளவு(*p)))
#define FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, அளவு(*p)))

#define FF_PTR_ADD(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#define FF_FIELD_AT(type, off, obj) (*(type *)((எழுத்து *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#எனில் CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) வெற்று
#இல்லையெனில்
#   define NULL_IF_CONFIG_SMALL(x) x
#endif

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
வெறுமை avpriv_report_missing_feature(வெறுமை *avc,
                                   மாறிலி எழுத்து *செய்தி, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
வெறுமை avpriv_request_sample(வெறுமை *avc,
                           மாறிலி எழுத்து *செய்தி, ...) av_printf_format(2, 3);

#ifdef DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#இல்லையெனில்
#   define ff_dlog(ctx, ...) செய் { எனில் (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } போது (0)
#endif

#ifdef TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#இல்லையெனில்
#   define ff_tlog(ctx, ...) செய் { } போது(0)
#endif

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#ifdef CHECKED
#define SUINT   முழு
#define SUINT32 int32_t
#இல்லையெனில்
#define SUINT   unsigned
#define SUINT32 uint32_t
#endif

நிலையான av_always_inline av_const முழு avpriv_mirror(முழு x, முழு w)
{
    எனில் (!w)
        திரும்பு 0;

    போது ((unsigned)x > (unsigned)w) {
        x = -x;
        எனில் (x < 0)
            x += 2 * w;
    }
    திரும்பு x;
}

#endif /* AVUTIL_INTERNAL_H */
