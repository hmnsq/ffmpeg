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

#اگر_تعریف_نشده AVUTIL_AVASSERT_H
#تعریف_کن AVUTIL_AVASSERT_H

#ضمن <stdlib.h>
#اگر_تعریف_شده HAVE_AV_CONFIG_H
#   include "config.h"
#پایان_اگر
#ضمن "attributes.h"
#ضمن "log.h"
#ضمن "macros.h"
#ضمن "version.h"

/**
 * assert() equivalent, that is always enabled.
 */
#تعریف_کن av_assert0(cond) افعل {                                           \
    إذا (!(cond)) {                                                      \
        av_log(عدم, AV_LOG_PANIC, "Assertion %s failed at %s:%d\n",    \
               AV_STRINGIFY(cond), __FILE__, __LINE__);                 \
        abort();                                                        \
    }                                                                   \
} طالما (0)


/**
 * assert() equivalent, that does not lie in speed critical code.
 * These asserts() thus can be enabled without fearing speed loss.
 */
#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL > 0
#تعریف_کن av_assert1(cond) av_assert0(cond)
#وإلا
#تعریف_کن av_assert1(cond) ((فراغ)0)
#پایان_اگر


/**
 * assert() equivalent, that does lie in speed critical code.
 */
#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#تعریف_کن av_assert2(cond) av_assert0(cond)
#وإلا
#تعریف_کن av_assert2(cond) ((فراغ)0)
#پایان_اگر

#إذا FF_API_ASSERT_FPU
#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#تعریف_کن av_assert2_fpu() av_assert0_fpu()
#وإلا
#تعریف_کن av_assert2_fpu() ((فراغ)0)
#پایان_اگر
/**
 * Assert that floating point operations can be executed.
 *
 * This will av_assert0() that the cpu is not in MMX state on X86
 * @deprecated without replacement
 */
attribute_deprecated
فراغ av_assert0_fpu(فراغ);
#پایان_اگر

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
#إذا defined(ASSERT_LEVEL) ? ASSERT_LEVEL > 0 : !defined(HAVE_AV_CONFIG_H) && !defined(NDEBUG)
#تعریف_کن av_unreachable(پیام)                                             \
افعل {                                                                    \
    av_log(عدم, AV_LOG_PANIC,                                          \
           "Reached supposedly unreachable code at %s:%d: %s\n",        \
           __FILE__, __LINE__, پیام);                                    \
    abort();                                                            \
} طالما (0)
#تعریف_کن av_assume(cond) av_assert0(cond)
#وإلا
#إذا AV_GCC_نسخه_AT_کمترین(4, 5) || AV_HAS_BUILTIN(__builtin_unreachable)
#تعریف_کن av_unreachable(پیام) __builtin_unreachable()
#وإلاإذا  defined(_MSC_VER)
#تعریف_کن av_unreachable(پیام) __assume(0)
#وإلاإذا __STDC_VERSION__ >= 202311L
#ضمن <stddef.h>
#تعریف_کن av_unreachable(پیام) unreachable()
#وإلا
#تعریف_کن av_unreachable(پیام) ((فراغ)0)
#پایان_اگر

#تعریف_کن av_assume(cond) افعل { \
    إذا (!(cond))             \
        av_unreachable();    \
} طالما (0)
#پایان_اگر

#پایان_اگر /* AVUTIL_AVASSERT_H */
