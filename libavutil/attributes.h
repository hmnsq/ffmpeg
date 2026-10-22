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

#నిర్వచితం_కాకపోతే AVUTIL_లక్షణాలు_H
#నిర్వచించు AVUTIL_లక్షణాలు_H

#నిర్వచితమైతే __GNUC__
#    define AV_GCC_సంస్కరణ_AT_కనిష్ఠ(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_సంస్కరణ_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#లేకపోతే
#    define AV_GCC_సంస్కరణ_AT_కనిష్ఠ(x,y) 0
#    define AV_GCC_సంస్కరణ_AT_MOST(x,y)  0
#అయితే_ముగింపు

#నిర్వచితమైతే __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#లేకపోతే
#    define AV_HAS_BUILTIN(x) 0
#అయితే_ముగింపు

#నిర్వచితమైతే __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#లేకపోతే
#    define AV_HAS_ATTRIBUTE(x) 0
#అయితే_ముగింపు

#ఒకవేళ defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#లేదావేళ !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#లేకపోతే
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#అయితే_ముగింపు

#ఒకవేళ AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#లేదావేళ AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#లేకపోతే
#    define av_fallthrough చేయి {} అయితే(0)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే av_always_inline
#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) అంతఃవరుస
#లేదావేళ defined(_MSC_VER)
#    define av_always_inline __forceinline
#లేకపోతే
#    define av_always_inline అంతఃవరుస
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే av_extern_inline
#ఒకవేళ defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline బాహ్య అంతఃవరుస
#లేకపోతే
#    define av_extern_inline అంతఃవరుస
#అయితే_ముగింపు
#అయితే_ముగింపు

#ఒకవేళ AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_వాడని_ఫలితం [[nodiscard]]
#లేదావేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(3,4) || defined(__clang__)
#    define av_warn_వాడని_ఫలితం __attribute__((warn_వాడని_ఫలితం))
#లేకపోతే
#    define av_warn_వాడని_ఫలితం
#అయితే_ముగింపు

#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#లేదావేళ defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#లేకపోతే
#    define av_noinline
#అయితే_ముగింపు

#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(3,1) || defined(__clang__)
#    define av_శుద్ధ __attribute__((శుద్ధ))
#లేకపోతే
#    define av_శుద్ధ
#అయితే_ముగింపు

#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(2,6) || defined(__clang__)
#    define av_const __attribute__((స్థిరరాశి))
#లేకపోతే
#    define av_const
#అయితే_ముగింపు

#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#లేకపోతే
#    define av_cold
#అయితే_ముగింపు

#ఒకవేళ (AV_GCC_సంస్కరణ_AT_కనిష్ఠ(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#లేకపోతే
#    define av_flatten
#అయితే_ముగింపు

#ఒకవేళ AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#లేదావేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#లేదావేళ defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#లేకపోతే
#    define attribute_deprecated
#అయితే_ముగింపు

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#నిర్వచితం_కాకపోతే AV_NOWARN_DEPRECATED
#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(సంకేతం_2) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        సంకేతం_2 \
        _Pragma("GCC diagnostic pop")
#లేదావేళ defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(సంకేతం_2) \
        __pragma(warning(నెట్టు)) \
        __pragma(warning(disable : 4996)) \
        సంకేతం_2; \
        __pragma(warning(తీయి))
#లేకపోతే
#    define AV_NOWARN_DEPRECATED(సంకేతం_2) సంకేతం_2
#అయితే_ముగింపు
#అయితే_ముగింపు

#ఒకవేళ AV_HAS_STD_ATTRIBUTE(maybe_వాడని)
#    define av_వాడని [[maybe_వాడని]]
#లేదావేళ defined(__GNUC__) || defined(__clang__)
#    define av_వాడని __attribute__((వాడని))
#లేకపోతే
#    define av_వాడని
#అయితే_ముగింపు

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(3,1) || defined(__clang__)
#    define av_వాడిన __attribute__((వాడిన))
#లేకపోతే
#    define av_వాడిన
#అయితే_ముగింపు

#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#లేకపోతే
#   define av_alias
#అయితే_ముగింపు

#ఒకవేళ (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#లేకపోతే
#    define av_uninit(x) x
#అయితే_ముగింపు

#ఒకవేళ defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#లేకపోతే
#    define av_builtin_constant_p(x) 0
#అయితే_ముగింపు

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#నిర్వచితమైతే __MINGW32__
#    include <stdio.h>
#అయితే_ముగింపు

#నిర్వచితమైతే __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#లేదావేళ AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#అయితే_ముగింపు

#నిర్వచితమైతే __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#లేదావేళ AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#అయితే_ముగింపు

#నిర్వచితమైతే AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#లేకపోతే
#    define av_printf_format(fmtpos, attrpos)
#అయితే_ముగింపు

#నిర్వచితమైతే AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#లేకపోతే
#    define av_scanf_format(fmtpos, attrpos)
#అయితే_ముగింపు

#ఒకవేళ AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#లేదావేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#లేకపోతే
#    define av_noreturn
#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_ATTRIBUTES_H */
