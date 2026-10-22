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

#ifndef AVUTIL_AVASSERT_H
#define AVUTIL_AVASSERT_H

#ضمن <stdlib.h>
#ifdef HAVE_AV_CONFIG_H
#   include "config.h"
#endif
#ضمن "attributes.h"
#ضمن "log.h"
#ضمن "macros.h"
#ضمن "version.h"

/**
 * assert() equivalent, that is always enabled.
 */
#define av_assert0(cond) افعل {                                           \
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
#define av_assert1(cond) av_assert0(cond)
#وإلا
#define av_assert1(cond) ((فراغ)0)
#endif


/**
 * assert() equivalent, that does lie in speed critical code.
 */
#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#define av_assert2(cond) av_assert0(cond)
#وإلا
#define av_assert2(cond) ((فراغ)0)
#endif

#إذا FF_API_ASSERT_FPU
#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#define av_assert2_fpu() av_assert0_fpu()
#وإلا
#define av_assert2_fpu() ((فراغ)0)
#endif
/**
 * Assert that floating point operations can be executed.
 *
 * This will av_assert0() that the cpu is not in MMX state on X86
 * @deprecated without replacement
 */
attribute_deprecated
فراغ av_assert0_fpu(فراغ);
#endif

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
#define av_unreachable(ئۇچۇر)                                             \
افعل {                                                                    \
    av_log(عدم, AV_LOG_PANIC,                                          \
           "Reached supposedly unreachable code at %s:%d: %s\n",        \
           __FILE__, __LINE__, ئۇچۇر);                                    \
    abort();                                                            \
} طالما (0)
#define av_assume(cond) av_assert0(cond)
#وإلا
#إذا AV_GCC_VERSION_AT_LEAST(4, 5) || AV_HAS_BUILTIN(__builtin_unreachable)
#define av_unreachable(ئۇچۇر) __builtin_unreachable()
#وإلاإذا  defined(_MSC_VER)
#define av_unreachable(ئۇچۇر) __assume(0)
#وإلاإذا __STDC_VERSION__ >= 202311L
#ضمن <stddef.h>
#define av_unreachable(ئۇچۇر) unreachable()
#وإلا
#define av_unreachable(ئۇچۇر) ((فراغ)0)
#endif

#define av_assume(cond) افعل { \
    إذا (!(cond))             \
        av_unreachable();    \
} طالما (0)
#endif

#endif /* AVUTIL_AVASSERT_H */
