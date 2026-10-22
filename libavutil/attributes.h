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

#که_نه_تعریف_شوی AVUTIL_ځانګړتیاوې_H
#تعریف_کړه AVUTIL_ځانګړتیاوې_H

#که_تعریف_شوی __GNUC__
#    define AV_GCC_نسخه_AT_لږترلږه(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_نسخه_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#وإلا
#    define AV_GCC_نسخه_AT_لږترلږه(x,y) 0
#    define AV_GCC_نسخه_AT_MOST(x,y)  0
#د_که_پای

#که_تعریف_شوی __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#وإلا
#    define AV_HAS_BUILTIN(x) 0
#د_که_پای

#که_تعریف_شوی __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#وإلا
#    define AV_HAS_ATTRIBUTE(x) 0
#د_که_پای

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
#د_که_پای

#إذا AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#وإلاإذا AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#وإلا
#    define av_fallthrough افعل {} طالما(0)
#د_که_پای

#که_نه_تعریف_شوی av_always_inline
#إذا AV_GCC_نسخه_AT_لږترلږه(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) مضمن
#وإلاإذا defined(_MSC_VER)
#    define av_always_inline __forceinline
#وإلا
#    define av_always_inline مضمن
#د_که_پای
#د_که_پای

#که_نه_تعریف_شوی av_extern_inline
#إذا defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline خارجي مضمن
#وإلا
#    define av_extern_inline مضمن
#د_که_پای
#د_که_پای

#إذا AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_ناکارول_شوی_پایله [[nodiscard]]
#وإلاإذا AV_GCC_نسخه_AT_لږترلږه(3,4) || defined(__clang__)
#    define av_warn_ناکارول_شوی_پایله __attribute__((warn_ناکارول_شوی_پایله))
#وإلا
#    define av_warn_ناکارول_شوی_پایله
#د_که_پای

#إذا AV_GCC_نسخه_AT_لږترلږه(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#وإلاإذا defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#وإلا
#    define av_noinline
#د_که_پای

#إذا AV_GCC_نسخه_AT_لږترلږه(3,1) || defined(__clang__)
#    define av_خالص __attribute__((خالص))
#وإلا
#    define av_خالص
#د_که_پای

#إذا AV_GCC_نسخه_AT_لږترلږه(2,6) || defined(__clang__)
#    define av_const __attribute__((ثابت))
#وإلا
#    define av_const
#د_که_پای

#إذا AV_GCC_نسخه_AT_لږترلږه(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#وإلا
#    define av_cold
#د_که_پای

#إذا (AV_GCC_نسخه_AT_لږترلږه(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#وإلا
#    define av_flatten
#د_که_پای

#إذا AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#وإلاإذا AV_GCC_نسخه_AT_لږترلږه(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#وإلاإذا defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#وإلا
#    define attribute_deprecated
#د_که_پای

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#که_نه_تعریف_شوی AV_NOWARN_DEPRECATED
#إذا AV_GCC_نسخه_AT_لږترلږه(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(کوډ) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        کوډ \
        _Pragma("GCC diagnostic pop")
#وإلاإذا defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(کوډ) \
        __pragma(warning(ټېل)) \
        __pragma(warning(disable : 4996)) \
        کوډ; \
        __pragma(warning(راوباسه))
#وإلا
#    define AV_NOWARN_DEPRECATED(کوډ) کوډ
#د_که_پای
#د_که_پای

#إذا AV_HAS_STD_ATTRIBUTE(maybe_ناکارول_شوی)
#    define av_ناکارول_شوی [[maybe_ناکارول_شوی]]
#وإلاإذا defined(__GNUC__) || defined(__clang__)
#    define av_ناکارول_شوی __attribute__((ناکارول_شوی))
#وإلا
#    define av_ناکارول_شوی
#د_که_پای

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#إذا AV_GCC_نسخه_AT_لږترلږه(3,1) || defined(__clang__)
#    define av_کارول_شوی __attribute__((کارول_شوی))
#وإلا
#    define av_کارول_شوی
#د_که_پای

#إذا AV_GCC_نسخه_AT_لږترلږه(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#وإلا
#   define av_alias
#د_که_پای

#إذا (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#وإلا
#    define av_uninit(x) x
#د_که_پای

#إذا defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#وإلا
#    define av_builtin_constant_p(x) 0
#د_که_پای

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#که_تعریف_شوی __MINGW32__
#    include <stdio.h>
#د_که_پای

#که_تعریف_شوی __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#وإلاإذا AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#د_که_پای

#که_تعریف_شوی __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#وإلاإذا AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#د_که_پای

#که_تعریف_شوی AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#وإلا
#    define av_printf_format(fmtpos, attrpos)
#د_که_پای

#که_تعریف_شوی AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#وإلا
#    define av_scanf_format(fmtpos, attrpos)
#د_که_پای

#إذا AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#وإلاإذا AV_GCC_نسخه_AT_لږترلږه(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#وإلا
#    define av_noreturn
#د_که_پای

#د_که_پای /* AVUTIL_ATTRIBUTES_H */
