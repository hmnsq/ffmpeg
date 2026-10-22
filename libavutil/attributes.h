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
 * Macro definitions for various function/variable attributes
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ಗುಣಲಕ್ಷಣಗಳು_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ಗುಣಲಕ್ಷಣಗಳು_H

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __GNUC__
#    define AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_ಆವೃತ್ತಿ_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#ಇಲ್ಲದಿದ್ದರೆ
#    define AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(x,y) 0
#    define AV_GCC_ಆವೃತ್ತಿ_AT_MOST(x,y)  0
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#ಇಲ್ಲದಿದ್ದರೆ
#    define AV_HAS_BUILTIN(x) 0
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#ಇಲ್ಲದಿದ್ದರೆ
#    define AV_HAS_ATTRIBUTE(x) 0
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#ಅಥವಾಆದರೆ !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#ಇಲ್ಲದಿದ್ದರೆ
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#ಅಥವಾಆದರೆ AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_fallthrough ಮಾಡು {} ಆಗ(0)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ av_always_inline
#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) ಸಾಲೊಳಗೆ
#ಅಥವಾಆದರೆ defined(_MSC_VER)
#    define av_always_inline __forceinline
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_always_inline ಸಾಲೊಳಗೆ
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ av_extern_inline
#ಆದರೆ defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline ಬಾಹ್ಯ ಸಾಲೊಳಗೆ
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_extern_inline ಸಾಲೊಳಗೆ
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_ಬಳಸದ_ಫಲಿತಾಂಶ [[nodiscard]]
#ಅಥವಾಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(3,4) || defined(__clang__)
#    define av_warn_ಬಳಸದ_ಫಲಿತಾಂಶ __attribute__((warn_ಬಳಸದ_ಫಲಿತಾಂಶ))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_warn_ಬಳಸದ_ಫಲಿತಾಂಶ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#ಅಥವಾಆದರೆ defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_noinline
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(3,1) || defined(__clang__)
#    define av_ಶುದ್ಧ __attribute__((ಶುದ್ಧ))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_ಶುದ್ಧ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(2,6) || defined(__clang__)
#    define av_const __attribute__((ಸ್ಥಿರಾಂಕ))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_const
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_cold
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ (AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_flatten
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#ಅಥವಾಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#ಅಥವಾಆದರೆ defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#ಇಲ್ಲದಿದ್ದರೆ
#    define attribute_deprecated
#ಆದರೆ_ಅಂತ್ಯ

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AV_NOWARN_DEPRECATED
#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(ಸಂಕೇತ_2) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        ಸಂಕೇತ_2 \
        _Pragma("GCC diagnostic pop")
#ಅಥವಾಆದರೆ defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(ಸಂಕೇತ_2) \
        __pragma(warning(ತಳ್ಳು)) \
        __pragma(warning(disable : 4996)) \
        ಸಂಕೇತ_2; \
        __pragma(warning(ತೆಗೆ))
#ಇಲ್ಲದಿದ್ದರೆ
#    define AV_NOWARN_DEPRECATED(ಸಂಕೇತ_2) ಸಂಕೇತ_2
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_HAS_STD_ATTRIBUTE(maybe_ಬಳಸದ)
#    define av_ಬಳಸದ [[maybe_ಬಳಸದ]]
#ಅಥವಾಆದರೆ defined(__GNUC__) || defined(__clang__)
#    define av_ಬಳಸದ __attribute__((ಬಳಸದ))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_ಬಳಸದ
#ಆದರೆ_ಅಂತ್ಯ

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(3,1) || defined(__clang__)
#    define av_ಬಳಸಿದ __attribute__((ಬಳಸಿದ))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_ಬಳಸಿದ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#ಇಲ್ಲದಿದ್ದರೆ
#   define av_alias
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_uninit(x) x
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_builtin_constant_p(x) 0
#ಆದರೆ_ಅಂತ್ಯ

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __MINGW32__
#    include <stdio.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#ಅಥವಾಆದರೆ AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#ಅಥವಾಆದರೆ AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_printf_format(fmtpos, attrpos)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_scanf_format(fmtpos, attrpos)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#ಅಥವಾಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#ಇಲ್ಲದಿದ್ದರೆ
#    define av_noreturn
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_ATTRIBUTES_H */
