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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ਗੁਣ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ਗੁਣ_H

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __GNUC__
#    define AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_ਸੰਸਕਰਣ_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#ਨਹੀਂਤਾਂ
#    define AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(x,y) 0
#    define AV_GCC_ਸੰਸਕਰਣ_AT_MOST(x,y)  0
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#ਨਹੀਂਤਾਂ
#    define AV_HAS_BUILTIN(x) 0
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#ਨਹੀਂਤਾਂ
#    define AV_HAS_ATTRIBUTE(x) 0
#ਜੇ_ਅੰਤ

#ਜੇ defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#ਜਾਂਜੇ !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#ਨਹੀਂਤਾਂ
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#ਜੇ_ਅੰਤ

#ਜੇ AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#ਜਾਂਜੇ AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#ਨਹੀਂਤਾਂ
#    define av_fallthrough ਕਰੋ {} ਜਦੋਂ(0)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_always_inline
#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) ਸਤਰਅੰਦਰ
#ਜਾਂਜੇ defined(_MSC_VER)
#    define av_always_inline __forceinline
#ਨਹੀਂਤਾਂ
#    define av_always_inline ਸਤਰਅੰਦਰ
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_extern_inline
#ਜੇ defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline ਬਾਹਰੀ ਸਤਰਅੰਦਰ
#ਨਹੀਂਤਾਂ
#    define av_extern_inline ਸਤਰਅੰਦਰ
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ [[nodiscard]]
#ਜਾਂਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(3,4) || defined(__clang__)
#    define av_warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ __attribute__((warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ))
#ਨਹੀਂਤਾਂ
#    define av_warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ
#ਜੇ_ਅੰਤ

#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#ਜਾਂਜੇ defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#ਨਹੀਂਤਾਂ
#    define av_noinline
#ਜੇ_ਅੰਤ

#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(3,1) || defined(__clang__)
#    define av_ਸ਼ੁੱਧ __attribute__((ਸ਼ੁੱਧ))
#ਨਹੀਂਤਾਂ
#    define av_ਸ਼ੁੱਧ
#ਜੇ_ਅੰਤ

#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(2,6) || defined(__clang__)
#    define av_const __attribute__((ਅਚਲ))
#ਨਹੀਂਤਾਂ
#    define av_const
#ਜੇ_ਅੰਤ

#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#ਨਹੀਂਤਾਂ
#    define av_cold
#ਜੇ_ਅੰਤ

#ਜੇ (AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#ਨਹੀਂਤਾਂ
#    define av_flatten
#ਜੇ_ਅੰਤ

#ਜੇ AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#ਜਾਂਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#ਜਾਂਜੇ defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#ਨਹੀਂਤਾਂ
#    define attribute_deprecated
#ਜੇ_ਅੰਤ

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AV_NOWARN_DEPRECATED
#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(ਕੋਡ) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        ਕੋਡ \
        _Pragma("GCC diagnostic pop")
#ਜਾਂਜੇ defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(ਕੋਡ) \
        __pragma(warning(ਧੱਕੋ)) \
        __pragma(warning(disable : 4996)) \
        ਕੋਡ; \
        __pragma(warning(ਕੱਢੋ))
#ਨਹੀਂਤਾਂ
#    define AV_NOWARN_DEPRECATED(ਕੋਡ) ਕੋਡ
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ AV_HAS_STD_ATTRIBUTE(maybe_ਅਣਵਰਤਿਆ)
#    define av_ਅਣਵਰਤਿਆ [[maybe_ਅਣਵਰਤਿਆ]]
#ਜਾਂਜੇ defined(__GNUC__) || defined(__clang__)
#    define av_ਅਣਵਰਤਿਆ __attribute__((ਅਣਵਰਤਿਆ))
#ਨਹੀਂਤਾਂ
#    define av_ਅਣਵਰਤਿਆ
#ਜੇ_ਅੰਤ

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(3,1) || defined(__clang__)
#    define av_ਵਰਤਿਆ __attribute__((ਵਰਤਿਆ))
#ਨਹੀਂਤਾਂ
#    define av_ਵਰਤਿਆ
#ਜੇ_ਅੰਤ

#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#ਨਹੀਂਤਾਂ
#   define av_alias
#ਜੇ_ਅੰਤ

#ਜੇ (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#ਨਹੀਂਤਾਂ
#    define av_uninit(x) x
#ਜੇ_ਅੰਤ

#ਜੇ defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#ਨਹੀਂਤਾਂ
#    define av_builtin_constant_p(x) 0
#ਜੇ_ਅੰਤ

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __MINGW32__
#    include <stdio.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#ਜਾਂਜੇ AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#ਜਾਂਜੇ AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#ਨਹੀਂਤਾਂ
#    define av_printf_format(fmtpos, attrpos)
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#ਨਹੀਂਤਾਂ
#    define av_scanf_format(fmtpos, attrpos)
#ਜੇ_ਅੰਤ

#ਜੇ AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#ਜਾਂਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#ਨਹੀਂਤਾਂ
#    define av_noreturn
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_ATTRIBUTES_H */
