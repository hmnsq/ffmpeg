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

#যদি !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#endif

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <math.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <assert.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব "config.h"
#অন্তর্ভাব "attributes.h"
#অন্তর্ভাব "mathematics.h"
#অন্তর্ভাব "macros.h"

#ifndef attribute_align_arg
#যদি ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_pointer))
#অন্যথা
#    define attribute_align_arg
#endif
#endif

#যদি HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#endif

#যদি HAVE_PRAGMA_DEPRECATED
#    যদি defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ঠেলো)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(বের_করো))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ঠেলো)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(বের_করো))
#    অন্যথা
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#অন্যথা
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#endif


#ifdef __ANDROID__
#   include "compat/android/math.h"
#endif

#define FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, পরিমাণ(*p)))
#define FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, পরিমাণ(*p)))

#define FF_PTR_ADD(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#define FF_FIELD_AT(type, off, obj) (*(type *)((বর্ণ *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#যদি CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) রিক্ত
#অন্যথা
#   define NULL_IF_CONFIG_SMALL(x) x
#endif

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
শূন্য avpriv_report_missing_feature(শূন্য *avc,
                                   ধ্রুব বর্ণ *বার্তা, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
শূন্য avpriv_request_sample(শূন্য *avc,
                           ধ্রুব বর্ণ *বার্তা, ...) av_printf_format(2, 3);

#ifdef DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#অন্যথা
#   define ff_dlog(ctx, ...) কুরু { যদি (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } যাবত্ (0)
#endif

#ifdef TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#অন্যথা
#   define ff_tlog(ctx, ...) কুরু { } যাবত্(0)
#endif

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#ifdef CHECKED
#define SUINT   পূর্ণাঙ্ক
#define SUINT32 int32_t
#অন্যথা
#define SUINT   unsigned
#define SUINT32 uint32_t
#endif

স্থির av_always_inline av_const পূর্ণাঙ্ক avpriv_mirror(পূর্ণাঙ্ক x, পূর্ণাঙ্ক w)
{
    যদি (!w)
        প্রত্যাগম 0;

    যাবত্ ((unsigned)x > (unsigned)w) {
        x = -x;
        যদি (x < 0)
            x += 2 * w;
    }
    প্রত্যাগম x;
}

#endif /* AVUTIL_INTERNAL_H */
