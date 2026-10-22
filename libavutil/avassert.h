/*
 * copyright (c) 2010 Michael Niedermayer <michaelni@gmx.at>
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
 * simple assert() macros that are a bit more flexible than ISO C assert().
 * @author Michael Niedermayer <michaelni@gmx.at>
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_AVASSERT_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_AVASSERT_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_AV_CONFIG_H
#   include "config.h"
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "version.h"

/**
 * assert() equivalent, that is always enabled.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_assert0(cond) ਕਰੋ {                                           \
    ਜੇ (!(cond)) {                                                      \
        av_log(ਨਿਰਾ, AV_LOG_PANIC, "Assertion %s failed at %s:%d\n",    \
               AV_STRINGIFY(cond), __FILE__, __LINE__);                 \
        abort();                                                        \
    }                                                                   \
} ਜਦੋਂ (0)


/**
 * assert() equivalent, that does not lie in speed critical code.
 * These asserts() thus can be enabled without fearing speed loss.
 */
#ਜੇ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_assert1(cond) av_assert0(cond)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_assert1(cond) ((ਖਾਲੀ)0)
#ਜੇ_ਅੰਤ


/**
 * assert() equivalent, that does lie in speed critical code.
 */
#ਜੇ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_assert2(cond) av_assert0(cond)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_assert2(cond) ((ਖਾਲੀ)0)
#ਜੇ_ਅੰਤ

#ਜੇ FF_API_ASSERT_FPU
#ਜੇ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_assert2_fpu() av_assert0_fpu()
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_assert2_fpu() ((ਖਾਲੀ)0)
#ਜੇ_ਅੰਤ
/**
 * Assert that floating point operations can be executed.
 *
 * This will av_assert0() that the cpu is not in MMX state on X86
 * @deprecated without replacement
 */
attribute_deprecated
ਖਾਲੀ av_assert0_fpu(ਖਾਲੀ);
#ਜੇ_ਅੰਤ

/**
 * Asserts that are used as compiler optimization hints depending
 * upon ASSERT_LEVEL and NBDEBUG.
 *
 * Undefined behaviour occurs if execution reaches a point marked
 * with av_unreachable() or if a condition used with av_assume()
 * is false.
 *
 * The condition used with av_assume() should not have side-effects
 * and should be visible to the compiler.
 */
#ਜੇ defined(ASSERT_LEVEL) ? ASSERT_LEVEL > 0 : !defined(HAVE_AV_CONFIG_H) && !defined(NDEBUG)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_unreachable(ਸੁਨੇਹਾ)                                             \
ਕਰੋ {                                                                    \
    av_log(ਨਿਰਾ, AV_LOG_PANIC,                                          \
           "Reached supposedly unreachable code at %s:%d: %s\n",        \
           __FILE__, __LINE__, ਸੁਨੇਹਾ);                                    \
    abort();                                                            \
} ਜਦੋਂ (0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_assume(cond) av_assert0(cond)
#ਨਹੀਂਤਾਂ
#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(4, 5) || AV_HAS_BUILTIN(__builtin_unreachable)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_unreachable(ਸੁਨੇਹਾ) __builtin_unreachable()
#ਜਾਂਜੇ  defined(_MSC_VER)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_unreachable(ਸੁਨੇਹਾ) __assume(0)
#ਜਾਂਜੇ __STDC_VERSION__ >= 202311L
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_unreachable(ਸੁਨੇਹਾ) unreachable()
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_unreachable(ਸੁਨੇਹਾ) ((ਖਾਲੀ)0)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_assume(cond) ਕਰੋ { \
    ਜੇ (!(cond))             \
        av_unreachable();    \
} ਜਦੋਂ (0)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_AVASSERT_H */
