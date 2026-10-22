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

#که_نه_تعریف_شوی AVUTIL_دننی_H
#تعریف_کړه AVUTIL_دننی_H

#إذا !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#د_که_پای

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

#که_نه_تعریف_شوی attribute_align_arg
#إذا ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_اشاره_ګر))
#وإلا
#    define attribute_align_arg
#د_که_پای
#د_که_پای

#إذا HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#د_که_پای

#إذا HAVE_PRAGMA_DEPRECATED
#    إذا defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ټېل)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(راوباسه))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ټېل)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(راوباسه))
#    وإلا
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#وإلا
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#د_که_پای


#که_تعریف_شوی __ANDROID__
#   include "compat/android/math.h"
#د_که_پای

#تعریف_کړه FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, حجم(*p)))
#تعریف_کړه FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, حجم(*p)))

#تعریف_کړه FF_PTR_جمع_کړه(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#تعریف_کړه FF_ډګر_AT(type, off, obj) (*(type *)((حرف *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#إذا CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) عدم
#وإلا
#   define NULL_IF_CONFIG_SMALL(x) x
#د_که_پای

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
فراغ avpriv_report_missing_feature(فراغ *avc,
                                   ثابت حرف *پیغام, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
فراغ avpriv_request_sample(فراغ *avc,
                           ثابت حرف *پیغام, ...) av_printf_format(2, 3);

#که_تعریف_شوی DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#وإلا
#   define ff_dlog(ctx, ...) افعل { إذا (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } طالما (0)
#د_که_پای

#که_تعریف_شوی TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#وإلا
#   define ff_tlog(ctx, ...) افعل { } طالما(0)
#د_که_پای

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#که_تعریف_شوی CHECKED
#تعریف_کړه SUINT   صحيح
#تعریف_کړه SUINT32 int32_t
#وإلا
#تعریف_کړه SUINT   بینښه
#تعریف_کړه SUINT32 uint32_t
#د_که_پای

ساكن av_always_inline av_const صحيح avpriv_mirror(صحيح x, صحيح w)
{
    إذا (!w)
        أرجع 0;

    طالما ((بینښه)x > (بینښه)w) {
        x = -x;
        إذا (x < 0)
            x += 2 * w;
    }
    أرجع x;
}

#د_که_پای /* AVUTIL_INTERNAL_H */
