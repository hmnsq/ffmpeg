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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ಆಂತರಿಕ_H

#ಆದರೆ !defined(DEBUG) && !defined(NDEBUG)
#    define NDEBUG
#ಆದರೆ_ಅಂತ್ಯ

// This can be enabled to allow detection of additional integer overflows with ubsan
//#define CHECKED

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <math.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <assert.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "mathematics.h"
#ಅನ್ತರ್ಭಾವ "macros.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ attribute_align_arg
#ಆದರೆ ARCH_X86_32 && defined(__GNUC__)
#    define attribute_align_arg __attribute__((force_align_arg_ಸೂಚಕ))
#ಇಲ್ಲದಿದ್ದರೆ
#    define attribute_align_arg
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_MIPSFPU && HAVE_INLINE_ASM
#   include "mips/libm_mips.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_PRAGMA_DEPRECATED
#    ಆದರೆ defined(__ICL) || defined (__INTEL_COMPILER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ತಳ್ಳು)) __pragma(warning(disable:1478))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(ತೆಗೆ))
#    elif defined(_MSC_VER)
#        define FF_DISABLE_DEPRECATION_WARNINGS __pragma(warning(ತಳ್ಳು)) __pragma(warning(disable:4996))
#        define FF_ENABLE_DEPRECATION_WARNINGS  __pragma(warning(ತೆಗೆ))
#    ಇಲ್ಲದಿದ್ದರೆ
#        define FF_DISABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#        define FF_ENABLE_DEPRECATION_WARNINGS  _Pragma("GCC diagnostic pop")
#    endif
#ಇಲ್ಲದಿದ್ದರೆ
#    define FF_DISABLE_DEPRECATION_WARNINGS
#    define FF_ENABLE_DEPRECATION_WARNINGS
#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ANDROID__
#   include "compat/android/math.h"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು FF_ALLOC_TYPED_ARRAY(p, nelem)  (p = av_malloc_array(nelem, ಗಾತ್ರ(*p)))
#ವ್ಯಾಖ್ಯಾನಿಸು FF_ALLOCZ_TYPED_ARRAY(p, nelem) (p = av_calloc(nelem, ಗಾತ್ರ(*p)))

#ವ್ಯಾಖ್ಯಾನಿಸು FF_PTR_ಕೂಡಿಸು(ptr, off) ((off) ? (ptr) + (off) : (ptr))

/**
 * Access a field in a structure by its offset.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು FF_ಕ್ಷೇತ್ರ_AT(type, off, obj) (*(type *)((ಅಕ್ಷರ *)&(obj) + (off)))

/**
 * Return NULL if CONFIG_SMALL is true, otherwise the argument
 * without modification. Used to disable the definition of strings.
 */
#ಆದರೆ CONFIG_SMALL
#   define NULL_IF_CONFIG_SMALL(x) ಖಾಲಿ
#ಇಲ್ಲದಿದ್ದರೆ
#   define NULL_IF_CONFIG_SMALL(x) x
#ಆದರೆ_ಅಂತ್ಯ

/**
 * Log a generic warning message about a missing feature.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first
 *                field is a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
ಶೂನ್ಯ avpriv_report_missing_feature(ಶೂನ್ಯ *avc,
                                   ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ...) av_printf_format(2, 3);

/**
 * Log a generic warning message about a missing feature.
 * Additionally request that a sample showcasing the feature be uploaded.
 *
 * @param[in] avc a pointer to an arbitrary struct of which the first field is
 *                a pointer to an AVClass struct
 * @param[in] msg string containing the name of the missing feature
 */
ಶೂನ್ಯ avpriv_request_sample(ಶೂನ್ಯ *avc,
                           ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ...) av_printf_format(2, 3);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG
#   define ff_dlog(ctx, ...) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__)
#ಇಲ್ಲದಿದ್ದರೆ
#   define ff_dlog(ctx, ...) ಮಾಡು { ಆದರೆ (0) av_log(ctx, AV_LOG_DEBUG, __VA_ARGS__); } ಆಗ (0)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TRACE
#   define ff_tlog(ctx, ...) av_log(ctx, AV_LOG_TRACE, __VA_ARGS__)
#ಇಲ್ಲದಿದ್ದರೆ
#   define ff_tlog(ctx, ...) ಮಾಡು { } ಆಗ(0)
#ಆದರೆ_ಅಂತ್ಯ

// For debugging we use signed operations so overflows can be detected (by ubsan)
// For production we use unsigned so there are no undefined operations
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CHECKED
#ವ್ಯಾಖ್ಯಾನಿಸು SUINT   ಪೂರ್ಣಾಂಕ
#ವ್ಯಾಖ್ಯಾನಿಸು SUINT32 int32_t
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SUINT   ಚಿಹ್ನೆರಹಿತ
#ವ್ಯಾಖ್ಯಾನಿಸು SUINT32 uint32_t
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ av_always_inline av_const ಪೂರ್ಣಾಂಕ avpriv_mirror(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ w)
{
    ಆದರೆ (!w)
        ಹಿಂತಿರುಗಿ 0;

    ಆಗ ((ಚಿಹ್ನೆರಹಿತ)x > (ಚಿಹ್ನೆರಹಿತ)w) {
        x = -x;
        ಆದರೆ (x < 0)
            x += 2 * w;
    }
    ಹಿಂತಿರುಗಿ x;
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_INTERNAL_H */
