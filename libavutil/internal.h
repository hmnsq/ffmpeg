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

#എങ്കിൽ !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#endif

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <math.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <assert.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "mathematics.h"
#അന്തര്ഭാവ "macros.h"

#ifndef attribute_align_arg
#എങ്കിൽ ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_pointer))
#അല്ലെങ്കിൽ
#    define attribute_align_arg
#endif
#endif

#എങ്കിൽ HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#endif

#എങ്കിൽ HAVE_PRAGMA_DEPRECATED
#    എങ്കിൽ defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(തള്ളുക)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(എടുക്കുക))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(തള്ളുക)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(എടുക്കുക))
#    അല്ലെങ്കിൽ
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#അല്ലെങ്കിൽ
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#endif


#ifdef __ANDROID__
#   include "compat/android/math.h"
#endif

#define FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, വലുപ്പം(*p)))
#define FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, വലുപ്പം(*p)))

#define FF_PTR_ADD(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#define FF_FIELD_AT(type, off, obj) (*(type *)((അക്ഷരം *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#എങ്കിൽ CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) ശൂന്യ
#അല്ലെങ്കിൽ
#   define NULL_IF_CONFIG_SMALL(x) x
#endif

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
ശൂന്യം avpriv_report_missing_feature(ശൂന്യം *avc,
                                   സ്ഥിരം അക്ഷരം *സന്ദേശം, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
ശൂന്യം avpriv_request_sample(ശൂന്യം *avc,
                           സ്ഥിരം അക്ഷരം *സന്ദേശം, ...) av_printf_format(2, 3);

#ifdef DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#അല്ലെങ്കിൽ
#   define ff_dlog(ctx, ...) ചെയ്യുക { എങ്കിൽ (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } ആകുമ്പോൾ (0)
#endif

#ifdef TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#അല്ലെങ്കിൽ
#   define ff_tlog(ctx, ...) ചെയ്യുക { } ആകുമ്പോൾ(0)
#endif

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#ifdef CHECKED
#define SUINT   പൂർണ്ണസംഖ്യ
#define SUINT32 int32_t
#അല്ലെങ്കിൽ
#define SUINT   unsigned
#define SUINT32 uint32_t
#endif

സ്ഥിതം av_always_inline av_const പൂർണ്ണസംഖ്യ avpriv_mirror(പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ w)
{
    എങ്കിൽ (!w)
        തിരികെ 0;

    ആകുമ്പോൾ ((unsigned)x > (unsigned)w) {
        x = -x;
        എങ്കിൽ (x < 0)
            x += 2 * w;
    }
    തിരികെ x;
}

#endif /* AVUTIL_INTERNAL_H */
