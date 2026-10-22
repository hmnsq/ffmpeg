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

#اگر_غیر_تعریف_شدہ AVUTIL_اوصاف_H
#تعریف_کرو AVUTIL_اوصاف_H

#اگر_تعریف_شدہ __GNUC__
#    define AV_GCC_نسخہ_AT_کم_سے_کم(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_نسخہ_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#ورنہ
#    define AV_GCC_نسخہ_AT_کم_سے_کم(x,y) 0
#    define AV_GCC_نسخہ_AT_MOST(x,y)  0
#اگر_ختم

#اگر_تعریف_شدہ __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#ورنہ
#    define AV_HAS_BUILTIN(x) 0
#اگر_ختم

#اگر_تعریف_شدہ __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#ورنہ
#    define AV_HAS_ATTRIBUTE(x) 0
#اگر_ختم

#اگر defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#وگرنہ_اگر !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#ورنہ
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#اگر_ختم

#اگر AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#وگرنہ_اگر AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#ورنہ
#    define av_fallthrough کرو {} جب(0)
#اگر_ختم

#اگر_غیر_تعریف_شدہ av_always_inline
#اگر AV_GCC_نسخہ_AT_کم_سے_کم(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) اندرونی
#وگرنہ_اگر defined(_MSC_VER)
#    define av_always_inline __forceinline
#ورنہ
#    define av_always_inline اندرونی
#اگر_ختم
#اگر_ختم

#اگر_غیر_تعریف_شدہ av_extern_inline
#اگر defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline خارجی اندرونی
#ورنہ
#    define av_extern_inline اندرونی
#اگر_ختم
#اگر_ختم

#اگر AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_غیر_مستعمل_نتیجہ [[nodiscard]]
#وگرنہ_اگر AV_GCC_نسخہ_AT_کم_سے_کم(3,4) || defined(__clang__)
#    define av_warn_غیر_مستعمل_نتیجہ __attribute__((warn_غیر_مستعمل_نتیجہ))
#ورنہ
#    define av_warn_غیر_مستعمل_نتیجہ
#اگر_ختم

#اگر AV_GCC_نسخہ_AT_کم_سے_کم(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#وگرنہ_اگر defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#ورنہ
#    define av_noinline
#اگر_ختم

#اگر AV_GCC_نسخہ_AT_کم_سے_کم(3,1) || defined(__clang__)
#    define av_خالص __attribute__((خالص))
#ورنہ
#    define av_خالص
#اگر_ختم

#اگر AV_GCC_نسخہ_AT_کم_سے_کم(2,6) || defined(__clang__)
#    define av_const __attribute__((ثابت))
#ورنہ
#    define av_const
#اگر_ختم

#اگر AV_GCC_نسخہ_AT_کم_سے_کم(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#ورنہ
#    define av_cold
#اگر_ختم

#اگر (AV_GCC_نسخہ_AT_کم_سے_کم(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#ورنہ
#    define av_flatten
#اگر_ختم

#اگر AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#وگرنہ_اگر AV_GCC_نسخہ_AT_کم_سے_کم(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#وگرنہ_اگر defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#ورنہ
#    define attribute_deprecated
#اگر_ختم

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#اگر_غیر_تعریف_شدہ AV_NOWARN_DEPRECATED
#اگر AV_GCC_نسخہ_AT_کم_سے_کم(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(رمز) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        رمز \
        _Pragma("GCC diagnostic pop")
#وگرنہ_اگر defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(رمز) \
        __pragma(warning(ڈالو)) \
        __pragma(warning(disable : 4996)) \
        رمز; \
        __pragma(warning(نکالو))
#ورنہ
#    define AV_NOWARN_DEPRECATED(رمز) رمز
#اگر_ختم
#اگر_ختم

#اگر AV_HAS_STD_ATTRIBUTE(maybe_غیر_مستعمل)
#    define av_غیر_مستعمل [[maybe_غیر_مستعمل]]
#وگرنہ_اگر defined(__GNUC__) || defined(__clang__)
#    define av_غیر_مستعمل __attribute__((غیر_مستعمل))
#ورنہ
#    define av_غیر_مستعمل
#اگر_ختم

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#اگر AV_GCC_نسخہ_AT_کم_سے_کم(3,1) || defined(__clang__)
#    define av_مستعمل __attribute__((مستعمل))
#ورنہ
#    define av_مستعمل
#اگر_ختم

#اگر AV_GCC_نسخہ_AT_کم_سے_کم(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#ورنہ
#   define av_alias
#اگر_ختم

#اگر (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#ورنہ
#    define av_uninit(x) x
#اگر_ختم

#اگر defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#ورنہ
#    define av_builtin_constant_p(x) 0
#اگر_ختم

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#اگر_تعریف_شدہ __MINGW32__
#    include <stdio.h>
#اگر_ختم

#اگر_تعریف_شدہ __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#وگرنہ_اگر AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#اگر_ختم

#اگر_تعریف_شدہ __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#وگرنہ_اگر AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#اگر_ختم

#اگر_تعریف_شدہ AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#ورنہ
#    define av_printf_format(fmtpos, attrpos)
#اگر_ختم

#اگر_تعریف_شدہ AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#ورنہ
#    define av_scanf_format(fmtpos, attrpos)
#اگر_ختم

#اگر AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#وگرنہ_اگر AV_GCC_نسخہ_AT_کم_سے_کم(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#ورنہ
#    define av_noreturn
#اگر_ختم

#اگر_ختم /* AVUTIL_ATTRIBUTES_H */
