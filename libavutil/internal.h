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

#अगर_अघोषित AVUTIL_INTERNAL_H
#घोषणा AVUTIL_INTERNAL_H

#अगर !defined(DEBUG) && !defined(न_संशोधन)
#    define न_संशोधन
#पूर्ण_अगर

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#समावेश <limits.h>
#समावेश <math.h>
#समावेश <stdint.h>
#समावेश <stddef.h>
#समावेश <assert.h>
#समावेश <stdio.h>
#समावेश "config.h"
#समावेश "attributes.h"
#समावेश "mathematics.h"
#समावेश "macros.h"

#अगर_अघोषित attribute_align_arg
#अगर ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_pointer))
#अन्यथा
#    define attribute_align_arg
#पूर्ण_अगर
#पूर्ण_अगर

#अगर HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#पूर्ण_अगर

#अगर HAVE_PRAGMA_DEPRECATED
#    अगर defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(धकेलो)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(निकालो))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(धकेलो)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(निकालो))
#    अन्यथा
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#अन्यथा
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#पूर्ण_अगर


#अगर_घोषित __ANDROID__
#   include "compat/android/math.h"
#पूर्ण_अगर

#घोषणा FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, माप(*p)))
#घोषणा FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, माप(*p)))

#घोषणा FF_PTR_ADD(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#घोषणा FF_FIELD_AT(type, off, obj) (*(type *)((अक्षर *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#अगर CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) शून्य
#अन्यथा
#   define NULL_IF_CONFIG_SMALL(x) x
#पूर्ण_अगर

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
व्योम avpriv_report_missing_feature(व्योम *avc,
                                   स्थिर अक्षर *संदेश, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
व्योम avpriv_request_sample(व्योम *avc,
                           स्थिर अक्षर *संदेश, ...) av_printf_format(2, 3);

#अगर_घोषित DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#अन्यथा
#   define ff_dlog(ctx, ...) करो { अगर (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } जबतक (0)
#पूर्ण_अगर

#अगर_घोषित TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#अन्यथा
#   define ff_tlog(ctx, ...) करो { } जबतक(0)
#पूर्ण_अगर

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#अगर_घोषित CHECKED
#घोषणा SUINT   पूर्णांक
#घोषणा SUINT32 int32_t
#अन्यथा
#घोषणा SUINT   अचिन्हित
#घोषणा SUINT32 uint32_t
#पूर्ण_अगर

अटल av_always_inline av_const पूर्णांक avpriv_mirror(पूर्णांक x, पूर्णांक w)
{
    अगर (!w)
        वापस 0;

    जबतक ((अचिन्हित)x > (अचिन्हित)w) {
        x = -x;
        अगर (x < 0)
            x += 2 * w;
    }
    वापस x;
}

#पूर्ण_अगर /* AVUTIL_INTERNAL_H */
