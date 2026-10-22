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

#अगर_अघोषित AVUTIL_ATTRIBUTES_H
#घोषणा AVUTIL_ATTRIBUTES_H

#अगर_घोषित __GNUC__
#    define AV_GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#    define AV_GCC_VERSION_AT_MOST(x,y)  (__GNUC__ < (x) || __GNUC__ == (x) && __GNUC_MINOR__ <= (y))
#अन्यथा
#    define AV_GCC_VERSION_AT_LEAST(x,y) 0
#    define AV_GCC_VERSION_AT_MOST(x,y)  0
#पूर्ण_अगर

#अगर_घोषित __has_builtin
#    define AV_HAS_BUILTIN(x) __has_builtin(x)
#अन्यथा
#    define AV_HAS_BUILTIN(x) 0
#पूर्ण_अगर

#अगर_घोषित __has_attribute
#    define AV_HAS_ATTRIBUTE(x) __has_attribute(x)
#अन्यथा
#    define AV_HAS_ATTRIBUTE(x) 0
#पूर्ण_अगर

#अगर defined(__cplusplus) && \
    defined(__has_cpp_attribute) && \
    __cplusplus >= 201103L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_cpp_attribute(x)
#या_अगर !defined(__cplusplus) && \
      defined(__has_c_attribute) && \
      defined(__STDC_VERSION__) && \
      __STDC_VERSION__ >= 202311L
#    define AV_HAS_STD_ATTRIBUTE(x) __has_c_attribute(x)
#अन्यथा
#    define AV_HAS_STD_ATTRIBUTE(x) 0
#पूर्ण_अगर

#अगर AV_HAS_STD_ATTRIBUTE(fallthrough)
#    define av_fallthrough [[fallthrough]]
#या_अगर AV_HAS_ATTRIBUTE(fallthrough)
#    define av_fallthrough __attribute__((fallthrough))
#अन्यथा
#    define av_fallthrough करो {} जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित av_always_inline
#अगर AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_always_inline __attribute__((always_inline)) अंतरभूत
#या_अगर defined(_MSC_VER)
#    define av_always_inline __forceinline
#अन्यथा
#    define av_always_inline अंतरभूत
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित av_extern_inline
#अगर defined(__ICL) && __ICL >= 1210 || defined(__GNUC_STDC_INLINE__)
#    define av_extern_inline बाह्य अंतरभूत
#अन्यथा
#    define av_extern_inline अंतरभूत
#पूर्ण_अगर
#पूर्ण_अगर

#अगर AV_HAS_STD_ATTRIBUTE(nodiscard)
#    define av_warn_unused_परिणाम [[nodiscard]]
#या_अगर AV_GCC_VERSION_AT_LEAST(3,4) || defined(__clang__)
#    define av_warn_unused_परिणाम __attribute__((warn_unused_परिणाम))
#अन्यथा
#    define av_warn_unused_परिणाम
#पूर्ण_अगर

#अगर AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_noinline __attribute__((noinline))
#या_अगर defined(_MSC_VER)
#    define av_noinline __declspec(noinline)
#अन्यथा
#    define av_noinline
#पूर्ण_अगर

#अगर AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_pure __attribute__((pure))
#अन्यथा
#    define av_pure
#पूर्ण_अगर

#अगर AV_GCC_VERSION_AT_LEAST(2,6) || defined(__clang__)
#    define av_const __attribute__((स्थिर))
#अन्यथा
#    define av_const
#पूर्ण_अगर

#अगर AV_GCC_VERSION_AT_LEAST(4,3) || defined(__clang__)
#    define av_cold __attribute__((cold))
#अन्यथा
#    define av_cold
#पूर्ण_अगर

#अगर (AV_GCC_VERSION_AT_LEAST(4,1) && !defined(__clang__ )) || AV_HAS_ATTRIBUTE(flatten)
#    define av_flatten __attribute__((flatten))
#अन्यथा
#    define av_flatten
#पूर्ण_अगर

#अगर AV_HAS_STD_ATTRIBUTE(deprecated)
#    define attribute_deprecated [[deprecated]]
#या_अगर AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define attribute_deprecated __attribute__((deprecated))
#या_अगर defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#अन्यथा
#    define attribute_deprecated
#पूर्ण_अगर

/**
 * Disable warnings about deprecated features
 * This is useful for sections of code kept for backward compatibility and
 * scheduled for removal.
 */
#अगर_अघोषित AV_NOWARN_DEPRECATED
#अगर AV_GCC_VERSION_AT_LEAST(4,6) || defined(__clang__)
#    define AV_NOWARN_DEPRECATED(code) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        code \
        _Pragma("GCC diagnostic pop")
#या_अगर defined(_MSC_VER)
#    define AV_NOWARN_DEPRECATED(code) \
        __pragma(warning(धकेलो)) \
        __pragma(warning(disable : 4996)) \
        code; \
        __pragma(warning(निकालो))
#अन्यथा
#    define AV_NOWARN_DEPRECATED(code) code
#पूर्ण_अगर
#पूर्ण_अगर

#अगर AV_HAS_STD_ATTRIBUTE(maybe_unused)
#    define av_unused [[maybe_unused]]
#या_अगर defined(__GNUC__) || defined(__clang__)
#    define av_unused __attribute__((unused))
#अन्यथा
#    define av_unused
#पूर्ण_अगर

/**
 * Mark a variable as used and prevent the compiler from optimizing it
 * away.  This is useful for variables accessed only from inline
 * assembler without the compiler being aware.
 */
#अगर AV_GCC_VERSION_AT_LEAST(3,1) || defined(__clang__)
#    define av_used __attribute__((used))
#अन्यथा
#    define av_used
#पूर्ण_अगर

#अगर AV_GCC_VERSION_AT_LEAST(3,3) || defined(__clang__)
#   define av_alias __attribute__((may_alias))
#अन्यथा
#   define av_alias
#पूर्ण_अगर

#अगर (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
#    define av_uninit(x) x=x
#अन्यथा
#    define av_uninit(x) x
#पूर्ण_अगर

#अगर defined(__GNUC__) || defined(__clang__)
#    define av_builtin_constant_p __builtin_constant_p
#अन्यथा
#    define av_builtin_constant_p(x) 0
#पूर्ण_अगर

// for __MINGW_PRINTF_FORMAT and __MINGW_SCANF_FORMAT
#अगर_घोषित __MINGW32__
#    include <stdio.h>
#पूर्ण_अगर

#अगर_घोषित __MINGW_PRINTF_FORMAT
#    define AV_PRINTF_FMT __MINGW_PRINTF_FORMAT
#या_अगर AV_HAS_ATTRIBUTE(format)
#    define AV_PRINTF_FMT __printf__
#पूर्ण_अगर

#अगर_घोषित __MINGW_SCANF_FORMAT
#    define AV_SCANF_FMT __MINGW_SCANF_FORMAT
#या_अगर AV_HAS_ATTRIBUTE(format)
#    define AV_SCANF_FMT __scanf__
#पूर्ण_अगर

#अगर_घोषित AV_PRINTF_FMT
#    define av_printf_format(fmtpos, attrpos) __attribute__((format(AV_PRINTF_FMT, fmtpos, attrpos)))
#अन्यथा
#    define av_printf_format(fmtpos, attrpos)
#पूर्ण_अगर

#अगर_घोषित AV_SCANF_FMT
#    define av_scanf_format(fmtpos, attrpos) __attribute__((format(AV_SCANF_FMT, fmtpos, attrpos)))
#अन्यथा
#    define av_scanf_format(fmtpos, attrpos)
#पूर्ण_अगर

#अगर AV_HAS_STD_ATTRIBUTE(noreturn)
#    define av_noreturn [[noreturn]]
#या_अगर AV_GCC_VERSION_AT_LEAST(2,5) || defined(__clang__)
#    define av_noreturn __attribute__((noreturn))
#अन्यथा
#    define av_noreturn
#पूर्ण_अगर

#पूर्ण_अगर /* AVUTIL_ATTRIBUTES_H */
