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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_خاصيتون_H
#وصف_ڪريو AVUTIL_خاصيتون_H

#جيڪڏهن_وصف_ٿيل __GNUC__
#    define AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_نسخو_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#وإلا
#    define AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(x,y) 0
#    define AV_GCC_نسخو_AT_MOST(x,y)  0
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#وإلا
#    define AV_HAS_BUILTIN(x) 0
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#وإلا
#    define AV_HAS_ATTRIBUTE(x) 0
#جيڪڏهن_پورو

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
#جيڪڏهن_پورو

#إذا AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#وإلاإذا AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#وإلا
#    define av_fallthrough افعل {} طالما(0)
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل av_always_inline
#إذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) مضمن
#وإلاإذا defined(_MSC_VER)
#    define av_always_inline __forceinline
#وإلا
#    define av_always_inline مضمن
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل av_extern_inline
#إذا defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline خارجي مضمن
#وإلا
#    define av_extern_inline مضمن
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#إذا AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_اڻ_استعمال_ٿيل_نتيجو [[nodiscard]]
#وإلاإذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(3,4) || defined(__clang__)
#    define av_warn_اڻ_استعمال_ٿيل_نتيجو __attribute__((warn_اڻ_استعمال_ٿيل_نتيجو))
#وإلا
#    define av_warn_اڻ_استعمال_ٿيل_نتيجو
#جيڪڏهن_پورو

#إذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#وإلاإذا defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#وإلا
#    define av_noinline
#جيڪڏهن_پورو

#إذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(3,1) || defined(__clang__)
#    define av_خالص __attribute__((خالص))
#وإلا
#    define av_خالص
#جيڪڏهن_پورو

#إذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(2,6) || defined(__clang__)
#    define av_const __attribute__((ثابت))
#وإلا
#    define av_const
#جيڪڏهن_پورو

#إذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#وإلا
#    define av_cold
#جيڪڏهن_پورو

#إذا (AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#وإلا
#    define av_flatten
#جيڪڏهن_پورو

#إذا AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#وإلاإذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#وإلاإذا defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#وإلا
#    define attribute_deprecated
#جيڪڏهن_پورو

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#جيڪڏهن_وصف_نه_ٿيل AV_NOWARN_DEPRECATED
#إذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(ڪوڊ) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        ڪوڊ \
        _Pragma("GCC diagnostic pop")
#وإلاإذا defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(ڪوڊ) \
        __pragma(warning(ڌڪو)) \
        __pragma(warning(disable : 4996)) \
        ڪوڊ; \
        __pragma(warning(ڪڍو))
#وإلا
#    define AV_NOWARN_DEPRECATED(ڪوڊ) ڪوڊ
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#إذا AV_HAS_STD_ATTRIBUTE(maybe_اڻ_استعمال_ٿيل)
#    define av_اڻ_استعمال_ٿيل [[maybe_اڻ_استعمال_ٿيل]]
#وإلاإذا defined(__GNUC__) || defined(__clang__)
#    define av_اڻ_استعمال_ٿيل __attribute__((اڻ_استعمال_ٿيل))
#وإلا
#    define av_اڻ_استعمال_ٿيل
#جيڪڏهن_پورو

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#إذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(3,1) || defined(__clang__)
#    define av_استعمال_ٿيل __attribute__((استعمال_ٿيل))
#وإلا
#    define av_استعمال_ٿيل
#جيڪڏهن_پورو

#إذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#وإلا
#   define av_alias
#جيڪڏهن_پورو

#إذا (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#وإلا
#    define av_uninit(x) x
#جيڪڏهن_پورو

#إذا defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#وإلا
#    define av_builtin_constant_p(x) 0
#جيڪڏهن_پورو

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#جيڪڏهن_وصف_ٿيل __MINGW32__
#    include <stdio.h>
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#وإلاإذا AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#وإلاإذا AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#وإلا
#    define av_printf_format(fmtpos, attrpos)
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#وإلا
#    define av_scanf_format(fmtpos, attrpos)
#جيڪڏهن_پورو

#إذا AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#وإلاإذا AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#وإلا
#    define av_noreturn
#جيڪڏهن_پورو

#جيڪڏهن_پورو /* AVUTIL_ATTRIBUTES_H */
