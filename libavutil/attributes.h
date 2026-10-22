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

#यदि_अपरिभाषितम् AVUTIL_गुणाः_H
#परिभाषय AVUTIL_गुणाः_H

#यदि_परिभाषितम् __GNUC__
#    define AV_GCC_संस्करणम्_AT_न्यूनतमम्(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_संस्करणम्_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#अन्यथा
#    define AV_GCC_संस्करणम्_AT_न्यूनतमम्(x,y) 0
#    define AV_GCC_संस्करणम्_AT_MOST(x,y)  0
#यदि_अन्तः

#यदि_परिभाषितम् __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#अन्यथा
#    define AV_HAS_BUILTIN(x) 0
#यदि_अन्तः

#यदि_परिभाषितम् __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#अन्यथा
#    define AV_HAS_ATTRIBUTE(x) 0
#यदि_अन्तः

#यदि defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#नोचेद्यदि !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#अन्यथा
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#यदि_अन्तः

#यदि AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#नोचेद्यदि AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#अन्यथा
#    define av_fallthrough कुरु {} यावत्(0)
#यदि_अन्तः

#यदि_अपरिभाषितम् av_always_inline
#यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) अन्तःस्थ
#नोचेद्यदि defined(_MSC_VER)
#    define av_always_inline __forceinline
#अन्यथा
#    define av_always_inline अन्तःस्थ
#यदि_अन्तः
#यदि_अन्तः

#यदि_अपरिभाषितम् av_extern_inline
#यदि defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline बाह्य अन्तःस्थ
#अन्यथा
#    define av_extern_inline अन्तःस्थ
#यदि_अन्तः
#यदि_अन्तः

#यदि AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_अप्रयुक्तम्_परिणाम [[nodiscard]]
#नोचेद्यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(3,4) || defined(__clang__)
#    define av_warn_अप्रयुक्तम्_परिणाम __attribute__((warn_अप्रयुक्तम्_परिणाम))
#अन्यथा
#    define av_warn_अप्रयुक्तम्_परिणाम
#यदि_अन्तः

#यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#नोचेद्यदि defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#अन्यथा
#    define av_noinline
#यदि_अन्तः

#यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(3,1) || defined(__clang__)
#    define av_विशुद्धम् __attribute__((विशुद्धम्))
#अन्यथा
#    define av_विशुद्धम्
#यदि_अन्तः

#यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(2,6) || defined(__clang__)
#    define av_const __attribute__((ध्रुव))
#अन्यथा
#    define av_const
#यदि_अन्तः

#यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#अन्यथा
#    define av_cold
#यदि_अन्तः

#यदि (AV_GCC_संस्करणम्_AT_न्यूनतमम्(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#अन्यथा
#    define av_flatten
#यदि_अन्तः

#यदि AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#नोचेद्यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#नोचेद्यदि defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#अन्यथा
#    define attribute_deprecated
#यदि_अन्तः

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#यदि_अपरिभाषितम् AV_NOWARN_DEPRECATED
#यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(संहिता) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        संहिता \
        _Pragma("GCC diagnostic pop")
#नोचेद्यदि defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(संहिता) \
        __pragma(warning(प्रक्षिप)) \
        __pragma(warning(disable : 4996)) \
        संहिता; \
        __pragma(warning(निष्कासय))
#अन्यथा
#    define AV_NOWARN_DEPRECATED(संहिता) संहिता
#यदि_अन्तः
#यदि_अन्तः

#यदि AV_HAS_STD_ATTRIBUTE(maybe_अप्रयुक्तम्)
#    define av_अप्रयुक्तम् [[maybe_अप्रयुक्तम्]]
#नोचेद्यदि defined(__GNUC__) || defined(__clang__)
#    define av_अप्रयुक्तम् __attribute__((अप्रयुक्तम्))
#अन्यथा
#    define av_अप्रयुक्तम्
#यदि_अन्तः

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(3,1) || defined(__clang__)
#    define av_प्रयुक्तम् __attribute__((प्रयुक्तम्))
#अन्यथा
#    define av_प्रयुक्तम्
#यदि_अन्तः

#यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#अन्यथा
#   define av_alias
#यदि_अन्तः

#यदि (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#अन्यथा
#    define av_uninit(x) x
#यदि_अन्तः

#यदि defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#अन्यथा
#    define av_builtin_constant_p(x) 0
#यदि_अन्तः

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#यदि_परिभाषितम् __MINGW32__
#    include <stdio.h>
#यदि_अन्तः

#यदि_परिभाषितम् __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#नोचेद्यदि AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#यदि_अन्तः

#यदि_परिभाषितम् __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#नोचेद्यदि AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#यदि_अन्तः

#यदि_परिभाषितम् AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#अन्यथा
#    define av_printf_format(fmtpos, attrpos)
#यदि_अन्तः

#यदि_परिभाषितम् AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#अन्यथा
#    define av_scanf_format(fmtpos, attrpos)
#यदि_अन्तः

#यदि AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#नोचेद्यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#अन्यथा
#    define av_noreturn
#यदि_अन्तः

#यदि_अन्तः /* AVUTIL_ATTRIBUTES_H */
