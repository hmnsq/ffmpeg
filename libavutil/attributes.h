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
#אחרת
#    define AV_GCC_VERSION_AT_LEAST(x,y) 0
#    define AV_GCC_VERSION_AT_MOST(x,y)  0
#endif

#ifdef __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#אחרת
#    define AV_HAS_BUILTIN(x) 0
#endif

#ifdef __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#אחרת
#    define AV_HAS_ATTRIBUTE(x) 0
#endif

#אם defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#وإلاإذا !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#אחרת
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#endif

#אם AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#وإلاإذا AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#אחרת
#    define av_fallthrough עשה {} כלעוד(0)
#endif

#ifndef av_always_inline
#אם AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) مضمن
#وإلاإذا defined(_MSC_VER)
#    define av_always_inline __forceinline
#אחרת
#    define av_always_inline مضمن
#endif
#endif

#ifndef av_extern_inline
#אם defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline خارجي مضمن
#אחרת
#    define av_extern_inline مضمن
#endif
#endif

#אם AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_unused_result [[nodiscard]]
#وإلاإذا AV_GCC_VERSION_AT_LEAST(3,4) || defined(__clang__)
#    define av_warn_unused_result __attribute__((warn_unused_result))
#אחרת
#    define av_warn_unused_result
#endif

#אם AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#وإلاإذا defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#אחרת
#    define av_noinline
#endif

#אם AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_pure __attribute__((pure))
#אחרת
#    define av_pure
#endif

#אם AV_GCC_VERSION_AT_LEAST(2,6) || defined(__clang__)
#    define av_const __attribute__((ثابت))
#אחרת
#    define av_const
#endif

#אם AV_GCC_VERSION_AT_LEAST(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#אחרת
#    define av_cold
#endif

#אם (AV_GCC_VERSION_AT_LEAST(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#אחרת
#    define av_flatten
#endif

#אם AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#وإلاإذا AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#وإلاإذا defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#אחרת
#    define attribute_deprecated
#endif

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#ifndef AV_NOWARN_DEPRECATED
#אם AV_GCC_VERSION_AT_LEAST(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(code) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        code \
        _Pragma("GCC diagnostic pop")
#وإلاإذا defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(code) \
        __pragma(warning(push)) \
        __pragma(warning(disable : 4996)) \
        code; \
        __pragma(warning(pop))
#אחרת
#    define AV_NOWARN_DEPRECATED(code) code
#endif
#endif

#אם AV_HAS_STD_ATTRIBUTE(maybe_unused)
#    define av_unused [[maybe_unused]]
#وإلاإذا defined(__GNUC__) || defined(__clang__)
#    define av_unused __attribute__((unused))
#אחרת
#    define av_unused
#endif

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#אם AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_used __attribute__((used))
#אחרת
#    define av_used
#endif

#אם AV_GCC_VERSION_AT_LEAST(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#אחרת
#   define av_alias
#endif

#אם (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#אחרת
#    define av_uninit(x) x
#endif

#אם defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#אחרת
#    define av_builtin_constant_p(x) 0
#endif

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#ifdef __MINGW32__
#    include <stdio.h>
#endif

#ifdef __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#وإلاإذا AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#endif

#ifdef __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#وإلاإذا AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#endif

#ifdef AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#אחרת
#    define av_printf_format(fmtpos, attrpos)
#endif

#ifdef AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#אחרת
#    define av_scanf_format(fmtpos, attrpos)
#endif

#אם AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#وإلاإذا AV_GCC_VERSION_AT_LEAST(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#אחרת
#    define av_noreturn
#endif

#endif /* AVUTIL_ATTRIBUTES_H */
