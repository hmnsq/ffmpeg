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

#اگر_تعریف_نشده AVUTIL_صفات_H
#تعریف_کن AVUTIL_صفات_H

#اگر_تعریف_شده __GNUC__
#    define AV_GCC_نسخه_AT_کمترین(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_نسخه_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#وإلا
#    define AV_GCC_نسخه_AT_کمترین(x,y) 0
#    define AV_GCC_نسخه_AT_MOST(x,y)  0
#پایان_اگر

#اگر_تعریف_شده __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#وإلا
#    define AV_HAS_BUILTIN(x) 0
#پایان_اگر

#اگر_تعریف_شده __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#وإلا
#    define AV_HAS_ATTRIBUTE(x) 0
#پایان_اگر

#إذا defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#وإلاإذا !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#وإلا
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#پایان_اگر

#إذا AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#وإلاإذا AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#وإلا
#    define av_fallthrough افعل {} طالما(0)
#پایان_اگر

#اگر_تعریف_نشده av_always_inline
#إذا AV_GCC_نسخه_AT_کمترین(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) مضمن
#وإلاإذا defined(_MSC_VER)
#    define av_always_inline __forceinline
#وإلا
#    define av_always_inline مضمن
#پایان_اگر
#پایان_اگر

#اگر_تعریف_نشده av_extern_inline
#إذا defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline خارجي مضمن
#وإلا
#    define av_extern_inline مضمن
#پایان_اگر
#پایان_اگر

#إذا AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_استفادهنشده_نتیجه [[nodiscard]]
#وإلاإذا AV_GCC_نسخه_AT_کمترین(3,4) || defined(__clang__)
#    define av_warn_استفادهنشده_نتیجه __attribute__((warn_استفادهنشده_نتیجه))
#وإلا
#    define av_warn_استفادهنشده_نتیجه
#پایان_اگر

#إذا AV_GCC_نسخه_AT_کمترین(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#وإلاإذا defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#وإلا
#    define av_noinline
#پایان_اگر

#إذا AV_GCC_نسخه_AT_کمترین(3,1) || defined(__clang__)
#    define av_خالص __attribute__((خالص))
#وإلا
#    define av_خالص
#پایان_اگر

#إذا AV_GCC_نسخه_AT_کمترین(2,6) || defined(__clang__)
#    define av_const __attribute__((ثابت))
#وإلا
#    define av_const
#پایان_اگر

#إذا AV_GCC_نسخه_AT_کمترین(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#وإلا
#    define av_cold
#پایان_اگر

#إذا (AV_GCC_نسخه_AT_کمترین(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#وإلا
#    define av_flatten
#پایان_اگر

#إذا AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#وإلاإذا AV_GCC_نسخه_AT_کمترین(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#وإلاإذا defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#وإلا
#    define attribute_deprecated
#پایان_اگر

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#اگر_تعریف_نشده AV_NOWARN_DEPRECATED
#إذا AV_GCC_نسخه_AT_کمترین(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(کد) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        کد \
        _Pragma("GCC diagnostic pop")
#وإلاإذا defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(کد) \
        __pragma(warning(افزودن)) \
        __pragma(warning(disable : 4996)) \
        کد; \
        __pragma(warning(برداشت))
#وإلا
#    define AV_NOWARN_DEPRECATED(کد) کد
#پایان_اگر
#پایان_اگر

#إذا AV_HAS_STD_ATTRIBUTE(maybe_استفادهنشده)
#    define av_استفادهنشده [[maybe_استفادهنشده]]
#وإلاإذا defined(__GNUC__) || defined(__clang__)
#    define av_استفادهنشده __attribute__((استفادهنشده))
#وإلا
#    define av_استفادهنشده
#پایان_اگر

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#إذا AV_GCC_نسخه_AT_کمترین(3,1) || defined(__clang__)
#    define av_استفاده_شده __attribute__((استفاده_شده))
#وإلا
#    define av_استفاده_شده
#پایان_اگر

#إذا AV_GCC_نسخه_AT_کمترین(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#وإلا
#   define av_alias
#پایان_اگر

#إذا (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#وإلا
#    define av_uninit(x) x
#پایان_اگر

#إذا defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#وإلا
#    define av_builtin_constant_p(x) 0
#پایان_اگر

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#اگر_تعریف_شده __MINGW32__
#    include <stdio.h>
#پایان_اگر

#اگر_تعریف_شده __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#وإلاإذا AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#پایان_اگر

#اگر_تعریف_شده __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#وإلاإذا AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#پایان_اگر

#اگر_تعریف_شده AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#وإلا
#    define av_printf_format(fmtpos, attrpos)
#پایان_اگر

#اگر_تعریف_شده AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#وإلا
#    define av_scanf_format(fmtpos, attrpos)
#پایان_اگر

#إذا AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#وإلاإذا AV_GCC_نسخه_AT_کمترین(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#وإلا
#    define av_noreturn
#پایان_اگر

#پایان_اگر /* AVUTIL_ATTRIBUTES_H */
