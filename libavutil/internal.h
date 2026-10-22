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

#నిర్వచితం_కాకపోతే AVUTIL_అంతర్గత_H
#నిర్వచించు AVUTIL_అంతర్గత_H

#ఒకవేళ !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#అయితే_ముగింపు

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#అన్తర్భావ <limits.h>
#అన్తర్భావ <math.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stddef.h>
#అన్తర్భావ <assert.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ "config.h"
#అన్తర్భావ "attributes.h"
#అన్తర్భావ "mathematics.h"
#అన్తర్భావ "macros.h"

#నిర్వచితం_కాకపోతే attribute_align_arg
#ఒకవేళ ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_సూచిక))
#లేకపోతే
#    define attribute_align_arg
#అయితే_ముగింపు
#అయితే_ముగింపు

#ఒకవేళ HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_PRAGMA_DEPRECATED
#    ఒకవేళ defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(నెట్టు)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(తీయి))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(నెట్టు)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(తీయి))
#    లేకపోతే
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#లేకపోతే
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#అయితే_ముగింపు


#నిర్వచితమైతే __ANDROID__
#   include "compat/android/math.h"
#అయితే_ముగింపు

#నిర్వచించు FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, పరిమాణం(*p)))
#నిర్వచించు FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, పరిమాణం(*p)))

#నిర్వచించు FF_PTR_కూడు(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#నిర్వచించు FF_క్షేత్రం_AT(type, off, obj) (*(type *)((అక్షరం *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#ఒకవేళ CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) ఖాళీ
#లేకపోతే
#   define NULL_IF_CONFIG_SMALL(x) x
#అయితే_ముగింపు

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
శూన్య avpriv_report_missing_feature(శూన్య *avc,
                                   స్థిరరాశి అక్షరం *సందేశం, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
శూన్య avpriv_request_sample(శూన్య *avc,
                           స్థిరరాశి అక్షరం *సందేశం, ...) av_printf_format(2, 3);

#నిర్వచితమైతే DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#లేకపోతే
#   define ff_dlog(ctx, ...) చేయి { ఒకవేళ (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } అయితే (0)
#అయితే_ముగింపు

#నిర్వచితమైతే TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#లేకపోతే
#   define ff_tlog(ctx, ...) చేయి { } అయితే(0)
#అయితే_ముగింపు

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#నిర్వచితమైతే CHECKED
#నిర్వచించు SUINT   పూర్ణాంకం
#నిర్వచించు SUINT32 int32_t
#లేకపోతే
#నిర్వచించు SUINT   గుర్తులేని
#నిర్వచించు SUINT32 uint32_t
#అయితే_ముగింపు

స్థిర av_always_inline av_const పూర్ణాంకం avpriv_mirror(పూర్ణాంకం x, పూర్ణాంకం w)
{
    ఒకవేళ (!w)
        తిరిగి 0;

    అయితే ((గుర్తులేని)x > (గుర్తులేని)w) {
        x = -x;
        ఒకవేళ (x < 0)
            x += 2 * w;
    }
    తిరిగి x;
}

#అయితే_ముగింపు /* AVUTIL_INTERNAL_H */
