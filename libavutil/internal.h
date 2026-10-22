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

#यदि_अपरिभाषितम् AVUTIL_आन्तरिकम्_H
#परिभाषय AVUTIL_आन्तरिकम्_H

#यदि !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#यदि_अन्तः

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#अन्तर्भाव <limits.h>
#अन्तर्भाव <math.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stddef.h>
#अन्तर्भाव <assert.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव "config.h"
#अन्तर्भाव "attributes.h"
#अन्तर्भाव "mathematics.h"
#अन्तर्भाव "macros.h"

#यदि_अपरिभाषितम् attribute_align_arg
#यदि ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_pointer))
#अन्यथा
#    define attribute_align_arg
#यदि_अन्तः
#यदि_अन्तः

#यदि HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#यदि_अन्तः

#यदि HAVE_PRAGMA_DEPRECATED
#    यदि defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(प्रक्षिप)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(निष्कासय))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(प्रक्षिप)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(निष्कासय))
#    अन्यथा
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#अन्यथा
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#यदि_अन्तः


#यदि_परिभाषितम् __ANDROID__
#   include "compat/android/math.h"
#यदि_अन्तः

#परिभाषय FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, परिमाण(*p)))
#परिभाषय FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, परिमाण(*p)))

#परिभाषय FF_PTR_सङ्कलय(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#परिभाषय FF_क्षेत्रम्_AT(type, off, obj) (*(type *)((वर्ण *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#यदि CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) रिक्त
#अन्यथा
#   define NULL_IF_CONFIG_SMALL(x) x
#यदि_अन्तः

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
शून्य avpriv_report_missing_feature(शून्य *avc,
                                   ध्रुव वर्ण *सन्देशः, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
शून्य avpriv_request_sample(शून्य *avc,
                           ध्रुव वर्ण *सन्देशः, ...) av_printf_format(2, 3);

#यदि_परिभाषितम् DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#अन्यथा
#   define ff_dlog(ctx, ...) कुरु { यदि (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } यावत् (0)
#यदि_अन्तः

#यदि_परिभाषितम् TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#अन्यथा
#   define ff_tlog(ctx, ...) कुरु { } यावत्(0)
#यदि_अन्तः

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#यदि_परिभाषितम् CHECKED
#परिभाषय SUINT   पूर्णाङ्क
#परिभाषय SUINT32 int32_t
#अन्यथा
#परिभाषय SUINT   अचिह्नित
#परिभाषय SUINT32 uint32_t
#यदि_अन्तः

स्थिर av_always_inline av_const पूर्णाङ्क avpriv_mirror(पूर्णाङ्क x, पूर्णाङ्क w)
{
    यदि (!w)
        प्रत्यागम 0;

    यावत् ((अचिह्नित)x > (अचिह्नित)w) {
        x = -x;
        यदि (x < 0)
            x += 2 * w;
    }
    प्रत्यागम x;
}

#यदि_अन्तः /* AVUTIL_INTERNAL_H */
