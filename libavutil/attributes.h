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
#अण्णहा
#    define AV_GCC_VERSION_AT_LEAST(x,y) 0
#    define AV_GCC_VERSION_AT_MOST(x,y)  0
#endif

#ifdef __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#अण्णहा
#    define AV_HAS_BUILTIN(x) 0
#endif

#ifdef __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#अण्णहा
#    define AV_HAS_ATTRIBUTE(x) 0
#endif

#जइ defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#नोचेद्यदि !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#अण्णहा
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#endif

#जइ AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#नोचेद्यदि AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#अण्णहा
#    define av_fallthrough करेहि {} जाव(0)
#endif

#ifndef av_always_inline
#जइ AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) अन्तःस्थ
#नोचेद्यदि defined(_MSC_VER)
#    define av_always_inline __forceinline
#अण्णहा
#    define av_always_inline अन्तःस्थ
#endif
#endif

#ifndef av_extern_inline
#जइ defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline बाह्य अन्तःस्थ
#अण्णहा
#    define av_extern_inline अन्तःस्थ
#endif
#endif

#जइ AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_unused_result [[nodiscard]]
#नोचेद्यदि AV_GCC_VERSION_AT_LEAST(3,4) || defined(__clang__)
#    define av_warn_unused_result __attribute__((warn_unused_result))
#अण्णहा
#    define av_warn_unused_result
#endif

#जइ AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#नोचेद्यदि defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#अण्णहा
#    define av_noinline
#endif

#जइ AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_pure __attribute__((pure))
#अण्णहा
#    define av_pure
#endif

#जइ AV_GCC_VERSION_AT_LEAST(2,6) || defined(__clang__)
#    define av_const __attribute__((ध्रुव))
#अण्णहा
#    define av_const
#endif

#जइ AV_GCC_VERSION_AT_LEAST(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#अण्णहा
#    define av_cold
#endif

#जइ (AV_GCC_VERSION_AT_LEAST(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#अण्णहा
#    define av_flatten
#endif

#जइ AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#नोचेद्यदि AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#नोचेद्यदि defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#अण्णहा
#    define attribute_deprecated
#endif

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#ifndef AV_NOWARN_DEPRECATED
#जइ AV_GCC_VERSION_AT_LEAST(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(code) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        code \
        _Pragma("GCC diagnostic pop")
#नोचेद्यदि defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(code) \
        __pragma(warning(प्रक्षिप)) \
        __pragma(warning(disable : 4996)) \
        code; \
        __pragma(warning(निष्कासय))
#अण्णहा
#    define AV_NOWARN_DEPRECATED(code) code
#endif
#endif

#जइ AV_HAS_STD_ATTRIBUTE(maybe_unused)
#    define av_unused [[maybe_unused]]
#नोचेद्यदि defined(__GNUC__) || defined(__clang__)
#    define av_unused __attribute__((unused))
#अण्णहा
#    define av_unused
#endif

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#जइ AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_used __attribute__((used))
#अण्णहा
#    define av_used
#endif

#जइ AV_GCC_VERSION_AT_LEAST(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#अण्णहा
#   define av_alias
#endif

#जइ (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#अण्णहा
#    define av_uninit(x) x
#endif

#जइ defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#अण्णहा
#    define av_builtin_constant_p(x) 0
#endif

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#ifdef __MINGW32__
#    include <stdio.h>
#endif

#ifdef __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#नोचेद्यदि AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#endif

#ifdef __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#नोचेद्यदि AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#endif

#ifdef AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#अण्णहा
#    define av_printf_format(fmtpos, attrpos)
#endif

#ifdef AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#अण्णहा
#    define av_scanf_format(fmtpos, attrpos)
#endif

#जइ AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#नोचेद्यदि AV_GCC_VERSION_AT_LEAST(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#अण्णहा
#    define av_noreturn
#endif

#endif /* AVUTIL_ATTRIBUTES_H */
