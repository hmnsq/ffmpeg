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

#ifndef AVUTIL_ATTRIBUTES_H
#define AVUTIL_ATTRIBUTES_H

#ifdef __GNUC__
#    define AV_GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_VERSION_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#وگرنه
#    define AV_GCC_VERSION_AT_LEAST(x,y) 0
#    define AV_GCC_VERSION_AT_MOST(x,y)  0
#endif

#ifdef __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#وگرنه
#    define AV_HAS_BUILTIN(x) 0
#endif

#ifdef __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#وگرنه
#    define AV_HAS_ATTRIBUTE(x) 0
#endif

#اگر defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#وگرنهاگر !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#وگرنه
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#endif

#اگر AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#وگرنهاگر AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#وگرنه
#    define av_fallthrough انجامبده {} وقتی(0)
#endif

#ifndef av_always_inline
#اگر AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) درونخطی
#وگرنهاگر defined(_MSC_VER)
#    define av_always_inline __forceinline
#وگرنه
#    define av_always_inline درونخطی
#endif
#endif

#ifndef av_extern_inline
#اگر defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline بیرونی درونخطی
#وگرنه
#    define av_extern_inline درونخطی
#endif
#endif

#اگر AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_unused_result [[nodiscard]]
#وگرنهاگر AV_GCC_VERSION_AT_LEAST(3,4) || defined(__clang__)
#    define av_warn_unused_result __attribute__((warn_unused_result))
#وگرنه
#    define av_warn_unused_result
#endif

#اگر AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#وگرنهاگر defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#وگرنه
#    define av_noinline
#endif

#اگر AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_pure __attribute__((pure))
#وگرنه
#    define av_pure
#endif

#اگر AV_GCC_VERSION_AT_LEAST(2,6) || defined(__clang__)
#    define av_const __attribute__((ثابت))
#وگرنه
#    define av_const
#endif

#اگر AV_GCC_VERSION_AT_LEAST(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#وگرنه
#    define av_cold
#endif

#اگر (AV_GCC_VERSION_AT_LEAST(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#وگرنه
#    define av_flatten
#endif

#اگر AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#وگرنهاگر AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#وگرنهاگر defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#وگرنه
#    define attribute_deprecated
#endif

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#ifndef AV_NOWARN_DEPRECATED
#اگر AV_GCC_VERSION_AT_LEAST(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(code) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        code \
        _Pragma("GCC diagnostic pop")
#وگرنهاگر defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(code) \
        __pragma(warning(افزودن)) \
        __pragma(warning(disable : 4996)) \
        code; \
        __pragma(warning(برداشت))
#وگرنه
#    define AV_NOWARN_DEPRECATED(code) code
#endif
#endif

#اگر AV_HAS_STD_ATTRIBUTE(maybe_unused)
#    define av_unused [[maybe_unused]]
#وگرنهاگر defined(__GNUC__) || defined(__clang__)
#    define av_unused __attribute__((unused))
#وگرنه
#    define av_unused
#endif

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#اگر AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_used __attribute__((used))
#وگرنه
#    define av_used
#endif

#اگر AV_GCC_VERSION_AT_LEAST(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#وگرنه
#   define av_alias
#endif

#اگر (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#وگرنه
#    define av_uninit(x) x
#endif

#اگر defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#وگرنه
#    define av_builtin_constant_p(x) 0
#endif

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#ifdef __MINGW32__
#    include <stdio.h>
#endif

#ifdef __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#وگرنهاگر AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#endif

#ifdef __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#وگرنهاگر AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#endif

#ifdef AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#وگرنه
#    define av_printf_format(fmtpos, attrpos)
#endif

#ifdef AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#وگرنه
#    define av_scanf_format(fmtpos, attrpos)
#endif

#اگر AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#وگرنهاگر AV_GCC_VERSION_AT_LEAST(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#وگرنه
#    define av_noreturn
#endif

#endif /* AVUTIL_ATTRIBUTES_H */
