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

#اگر_غیر_تعریف_شدہ AVUTIL_اندرونی_H
#تعریف_کرو AVUTIL_اندرونی_H

#اگر !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#اگر_ختم

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#شامل <limits.h>
#شامل <math.h>
#شامل <stdint.h>
#شامل <stddef.h>
#شامل <assert.h>
#شامل <stdio.h>
#شامل "config.h"
#شامل "attributes.h"
#شامل "mathematics.h"
#شامل "macros.h"

#اگر_غیر_تعریف_شدہ attribute_align_arg
#اگر ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_اشارہ_گر))
#ورنہ
#    define attribute_align_arg
#اگر_ختم
#اگر_ختم

#اگر HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#اگر_ختم

#اگر HAVE_PRAGMA_DEPRECATED
#    اگر defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ڈالو)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(نکالو))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ڈالو)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(نکالو))
#    ورنہ
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#ورنہ
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#اگر_ختم


#اگر_تعریف_شدہ __ANDROID__
#   include "compat/android/math.h"
#اگر_ختم

#تعریف_کرو FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, حجم(*p)))
#تعریف_کرو FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, حجم(*p)))

#تعریف_کرو FF_PTR_جوڑو(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#تعریف_کرو FF_میدان_AT(type, off, obj) (*(type *)((حرف *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#اگر CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) تہی
#ورنہ
#   define NULL_IF_CONFIG_SMALL(x) x
#اگر_ختم

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
خالی avpriv_report_missing_feature(خالی *avc,
                                   ثابت حرف *پیغام, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
خالی avpriv_request_sample(خالی *avc,
                           ثابت حرف *پیغام, ...) av_printf_format(2, 3);

#اگر_تعریف_شدہ DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#ورنہ
#   define ff_dlog(ctx, ...) کرو { اگر (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } جب (0)
#اگر_ختم

#اگر_تعریف_شدہ TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#ورنہ
#   define ff_tlog(ctx, ...) کرو { } جب(0)
#اگر_ختم

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#اگر_تعریف_شدہ CHECKED
#تعریف_کرو SUINT   صحیح
#تعریف_کرو SUINT32 int32_t
#ورنہ
#تعریف_کرو SUINT   غیرعلامتی
#تعریف_کرو SUINT32 uint32_t
#اگر_ختم

ساکن av_always_inline av_const صحیح avpriv_mirror(صحیح x, صحیح w)
{
    اگر (!w)
        واپس 0;

    جب ((غیرعلامتی)x > (غیرعلامتی)w) {
        x = -x;
        اگر (x < 0)
            x += 2 * w;
    }
    واپس x;
}

#اگر_ختم /* AVUTIL_INTERNAL_H */
