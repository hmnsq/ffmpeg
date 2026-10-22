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

#నిర్వచితం_కాకపోతే AVUTIL_AVASSERT_H
#నిర్వచించు AVUTIL_AVASSERT_H

#అన్తర్భావ <stdlib.h>
#నిర్వచితమైతే HAVE_AV_CONFIG_H
#   include "config.h"
#అయితే_ముగింపు
#అన్తర్భావ "attributes.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "version.h"

/**
 * assert() equivalent, that is always enabled.
 */
#నిర్వచించు av_assert0(cond) చేయి {                                           \
    ఒకవేళ (!(cond)) {                                                      \
        av_log(ఖాళీ, AV_LOG_PANIC, "Assertion %s failed at %s:%d\n",    \
               AV_STRINGIFY(cond), __FILE__, __LINE__);                 \
        abort();                                                        \
    }                                                                   \
} అయితే (0)


/**
 * assert() equivalent, that does not lie in speed critical code.
 * These asserts() thus can be enabled without fearing speed loss.
 */
#ఒకవేళ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 0
#నిర్వచించు av_assert1(cond) av_assert0(cond)
#లేకపోతే
#నిర్వచించు av_assert1(cond) ((శూన్య)0)
#అయితే_ముగింపు


/**
 * assert() equivalent, that does lie in speed critical code.
 */
#ఒకవేళ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#నిర్వచించు av_assert2(cond) av_assert0(cond)
#లేకపోతే
#నిర్వచించు av_assert2(cond) ((శూన్య)0)
#అయితే_ముగింపు

#ఒకవేళ FF_API_ASSERT_FPU
#ఒకవేళ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#నిర్వచించు av_assert2_fpu() av_assert0_fpu()
#లేకపోతే
#నిర్వచించు av_assert2_fpu() ((శూన్య)0)
#అయితే_ముగింపు
/**
 * Assert that floating point operations can be executed.
 *
 * This will av_assert0() that the cpu is not in MMX state on X86
 * @deprecated without replacement
 */
attribute_deprecated
శూన్య av_assert0_fpu(శూన్య);
#అయితే_ముగింపు

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
#ఒకవేళ defined(ASSERT_LEVEL) ? ASSERT_LEVEL > 0 : !defined(HAVE_AV_CONFIG_H) && !defined(NDEBUG)
#నిర్వచించు av_unreachable(సందేశం)                                             \
చేయి {                                                                    \
    av_log(ఖాళీ, AV_LOG_PANIC,                                          \
           "Reached supposedly unreachable code at %s:%d: %s\n",        \
           __FILE__, __LINE__, సందేశం);                                    \
    abort();                                                            \
} అయితే (0)
#నిర్వచించు av_assume(cond) av_assert0(cond)
#లేకపోతే
#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(4, 5) || AV_HAS_BUILTIN(__builtin_unreachable)
#నిర్వచించు av_unreachable(సందేశం) __builtin_unreachable()
#లేదావేళ  defined(_MSC_VER)
#నిర్వచించు av_unreachable(సందేశం) __assume(0)
#లేదావేళ __STDC_VERSION__ >= 202311L
#అన్తర్భావ <stddef.h>
#నిర్వచించు av_unreachable(సందేశం) unreachable()
#లేకపోతే
#నిర్వచించు av_unreachable(సందేశం) ((శూన్య)0)
#అయితే_ముగింపు

#నిర్వచించు av_assume(cond) చేయి { \
    ఒకవేళ (!(cond))             \
        av_unreachable();    \
} అయితే (0)
#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_AVASSERT_H */
