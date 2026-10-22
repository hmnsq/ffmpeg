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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_اندروني_H
#وصف_ڪريو AVUTIL_اندروني_H

#إذا !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#جيڪڏهن_پورو

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#ضمن <limits.h>
#ضمن <math.h>
#ضمن <stdint.h>
#ضمن <stddef.h>
#ضمن <assert.h>
#ضمن <stdio.h>
#ضمن "config.h"
#ضمن "attributes.h"
#ضمن "mathematics.h"
#ضمن "macros.h"

#جيڪڏهن_وصف_نه_ٿيل attribute_align_arg
#إذا ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_اشارو))
#وإلا
#    define attribute_align_arg
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#إذا HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#جيڪڏهن_پورو

#إذا HAVE_PRAGMA_DEPRECATED
#    إذا defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ڌڪو)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(ڪڍو))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ڌڪو)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(ڪڍو))
#    وإلا
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#وإلا
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل __ANDROID__
#   include "compat/android/math.h"
#جيڪڏهن_پورو

#وصف_ڪريو FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, حجم(*p)))
#وصف_ڪريو FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, حجم(*p)))

#وصف_ڪريو FF_PTR_جوڙيو(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#وصف_ڪريو FF_ميدان_AT(type, off, obj) (*(type *)((حرف *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#إذا CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) عدم
#وإلا
#   define NULL_IF_CONFIG_SMALL(x) x
#جيڪڏهن_پورو

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
فراغ avpriv_report_missing_feature(فراغ *avc,
                                   ثابت حرف *نياپو, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
فراغ avpriv_request_sample(فراغ *avc,
                           ثابت حرف *نياپو, ...) av_printf_format(2, 3);

#جيڪڏهن_وصف_ٿيل DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#وإلا
#   define ff_dlog(ctx, ...) افعل { إذا (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } طالما (0)
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#وإلا
#   define ff_tlog(ctx, ...) افعل { } طالما(0)
#جيڪڏهن_پورو

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#جيڪڏهن_وصف_ٿيل CHECKED
#وصف_ڪريو SUINT   صحيح
#وصف_ڪريو SUINT32 int32_t
#وإلا
#وصف_ڪريو SUINT   بنانشان
#وصف_ڪريو SUINT32 uint32_t
#جيڪڏهن_پورو

ساكن av_always_inline av_const صحيح avpriv_mirror(صحيح x, صحيح w)
{
    إذا (!w)
        أرجع 0;

    طالما ((بنانشان)x > (بنانشان)w) {
        x = -x;
        إذا (x < 0)
            x += 2 * w;
    }
    أرجع x;
}

#جيڪڏهن_پورو /* AVUTIL_INTERNAL_H */
