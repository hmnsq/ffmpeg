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

#अगर_अघोषित AVUTIL_AVASSERT_H
#घोषणा AVUTIL_AVASSERT_H

#समावेश <stdlib.h>
#अगर_घोषित HAVE_AV_CONFIG_H
#   include "config.h"
#पूर्ण_अगर
#समावेश "attributes.h"
#समावेश "log.h"
#समावेश "macros.h"
#समावेश "version.h"

/**
 * assert() equivalent, that is always enabled.
 */
#घोषणा av_assert0(cond) करो {                                           \
    अगर (!(cond)) {                                                      \
        av_log(शून्य, AV_LOG_PANIC, "Assertion %s failed at %s:%d\n",    \
               AV_STRINGIFY(cond), __खाता__, __LINE__);                 \
        पात();                                                        \
    }                                                                   \
} जबतक (0)


/**
 * assert() equivalent, that does not lie in speed critical code.
 * These asserts() thus can be enabled without fearing speed loss.
 */
#अगर defined(ASSERT_LEVEL) && ASSERT_LEVEL > 0
#घोषणा av_assert1(cond) av_assert0(cond)
#अन्यथा
#घोषणा av_assert1(cond) ((व्योम)0)
#पूर्ण_अगर


/**
 * assert() equivalent, that does lie in speed critical code.
 */
#अगर defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#घोषणा av_assert2(cond) av_assert0(cond)
#अन्यथा
#घोषणा av_assert2(cond) ((व्योम)0)
#पूर्ण_अगर

#अगर FF_API_ASSERT_FPU
#अगर defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#घोषणा av_assert2_fpu() av_assert0_fpu()
#अन्यथा
#घोषणा av_assert2_fpu() ((व्योम)0)
#पूर्ण_अगर
/**
 * Assert that floating point operations can be executed.
 *
 * This will av_assert0() that the cpu is not in MMX state on X86
 * @deprecated without replacement
 */
attribute_deprecated
व्योम av_assert0_fpu(व्योम);
#पूर्ण_अगर

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
#अगर defined(ASSERT_LEVEL) ? ASSERT_LEVEL > 0 : !defined(HAVE_AV_CONFIG_H) && !defined(न_संशोधन)
#घोषणा av_unreachable(संदेश)                                             \
करो {                                                                    \
    av_log(शून्य, AV_LOG_PANIC,                                          \
           "Reached supposedly unreachable code at %s:%d: %s\n",        \
           __खाता__, __LINE__, संदेश);                                    \
    पात();                                                            \
} जबतक (0)
#घोषणा av_assume(cond) av_assert0(cond)
#अन्यथा
#अगर AV_GCC_VERSION_AT_LEAST(4, 5) || AV_HAS_BUILTIN(__builtin_unreachable)
#घोषणा av_unreachable(संदेश) __builtin_unreachable()
#या_अगर  defined(_MSC_VER)
#घोषणा av_unreachable(संदेश) __assume(0)
#या_अगर __STDC_VERSION__ >= 202311L
#समावेश <stddef.h>
#घोषणा av_unreachable(संदेश) unreachable()
#अन्यथा
#घोषणा av_unreachable(संदेश) ((व्योम)0)
#पूर्ण_अगर

#घोषणा av_assume(cond) करो { \
    अगर (!(cond))             \
        av_unreachable();    \
} जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* AVUTIL_AVASSERT_H */
