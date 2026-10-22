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

#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ifdef HAVE_AV_CONFIG_H
#   include "config.h"
#endif
#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "version.h"

/**
 * assert() equivalent, that is always enabled.
 */
#define av_assert0(cond) କର {                                           \
    ଯଦି (!(cond)) {                                                      \
        av_log(ଖାଲି, AV_LOG_PANIC, "Assertion %s failed at %s:%d\n",    \
               AV_STRINGIFY(cond), __FILE__, __LINE__);                 \
        abort();                                                        \
    }                                                                   \
} ଯେତେବେଳେ (0)


/**
 * assert() equivalent, that does not lie in speed critical code.
 * These asserts() thus can be enabled without fearing speed loss.
 */
#ଯଦି defined(ASSERT_LEVEL) && ASSERT_LEVEL > 0
#define av_assert1(cond) av_assert0(cond)
#ଅନ୍ୟଥା
#define av_assert1(cond) ((ଶୂନ୍ୟ)0)
#endif


/**
 * assert() equivalent, that does lie in speed critical code.
 */
#ଯଦି defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#define av_assert2(cond) av_assert0(cond)
#ଅନ୍ୟଥା
#define av_assert2(cond) ((ଶୂନ୍ୟ)0)
#endif

#ଯଦି FF_API_ASSERT_FPU
#ଯଦି defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#define av_assert2_fpu() av_assert0_fpu()
#ଅନ୍ୟଥା
#define av_assert2_fpu() ((ଶୂନ୍ୟ)0)
#endif
/**
 * Assert that floating point operations can be executed.
 *
 * This will av_assert0() that the cpu is not in MMX state on X86
 * @deprecated without replacement
 */
attribute_deprecated
ଶୂନ୍ୟ av_assert0_fpu(ଶୂନ୍ୟ);
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
#ଯଦି defined(ASSERT_LEVEL) ? ASSERT_LEVEL > 0 : !defined(HAVE_AV_CONFIG_H) && !defined(NDEBUG)
#define av_unreachable(ସନ୍ଦେଶ)                                             \
କର {                                                                    \
    av_log(ଖାଲି, AV_LOG_PANIC,                                          \
           "Reached supposedly unreachable code at %s:%d: %s\n",        \
           __FILE__, __LINE__, ସନ୍ଦେଶ);                                    \
    abort();                                                            \
} ଯେତେବେଳେ (0)
#define av_assume(cond) av_assert0(cond)
#ଅନ୍ୟଥା
#ଯଦି AV_GCC_VERSION_AT_LEAST(4, 5) || AV_HAS_BUILTIN(__builtin_unreachable)
#define av_unreachable(ସନ୍ଦେଶ) __builtin_unreachable()
#ନଚେତଯଦି  defined(_MSC_VER)
#define av_unreachable(ସନ୍ଦେଶ) __assume(0)
#ନଚେତଯଦି __STDC_VERSION__ >= 202311L
#ଅନ୍ତର୍ଭାଵ <stddef.h>
#define av_unreachable(ସନ୍ଦେଶ) unreachable()
#ଅନ୍ୟଥା
#define av_unreachable(ସନ୍ଦେଶ) ((ଶୂନ୍ୟ)0)
#endif

#define av_assume(cond) କର { \
    ଯଦି (!(cond))             \
        av_unreachable();    \
} ଯେତେବେଳେ (0)
#endif

#endif /* AVUTIL_AVASSERT_H */
