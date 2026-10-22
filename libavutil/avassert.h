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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_AVASSERT_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_AVASSERT_H

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_AV_CONFIG_H
#   include "config.h"
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "version.h"

/**
 * assert() equivalent, that is always enabled.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು av_assert0(cond) ಮಾಡು {                                           \
    ಆದರೆ (!(cond)) {                                                      \
        av_log(ಖಾಲಿ, AV_LOG_PANIC, "Assertion %s failed at %s:%d\n",    \
               AV_STRINGIFY(cond), __FILE__, __LINE__);                 \
        abort();                                                        \
    }                                                                   \
} ಆಗ (0)


/**
 * assert() equivalent, that does not lie in speed critical code.
 * These asserts() thus can be enabled without fearing speed loss.
 */
#ಆದರೆ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 0
#ವ್ಯಾಖ್ಯಾನಿಸು av_assert1(cond) av_assert0(cond)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು av_assert1(cond) ((ಶೂನ್ಯ)0)
#ಆದರೆ_ಅಂತ್ಯ


/**
 * assert() equivalent, that does lie in speed critical code.
 */
#ಆದರೆ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#ವ್ಯಾಖ್ಯಾನಿಸು av_assert2(cond) av_assert0(cond)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು av_assert2(cond) ((ಶೂನ್ಯ)0)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ FF_API_ASSERT_FPU
#ಆದರೆ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1
#ವ್ಯಾಖ್ಯಾನಿಸು av_assert2_fpu() av_assert0_fpu()
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು av_assert2_fpu() ((ಶೂನ್ಯ)0)
#ಆದರೆ_ಅಂತ್ಯ
/**
 * Assert that floating point operations can be executed.
 *
 * This will av_assert0() that the cpu is not in MMX state on X86
 * @deprecated without replacement
 */
attribute_deprecated
ಶೂನ್ಯ av_assert0_fpu(ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ

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
#ಆದರೆ defined(ASSERT_LEVEL) ? ASSERT_LEVEL > 0 : !defined(HAVE_AV_CONFIG_H) && !defined(NDEBUG)
#ವ್ಯಾಖ್ಯಾನಿಸು av_unreachable(ಸಂದೇಶ)                                             \
ಮಾಡು {                                                                    \
    av_log(ಖಾಲಿ, AV_LOG_PANIC,                                          \
           "Reached supposedly unreachable code at %s:%d: %s\n",        \
           __FILE__, __LINE__, ಸಂದೇಶ);                                    \
    abort();                                                            \
} ಆಗ (0)
#ವ್ಯಾಖ್ಯಾನಿಸು av_assume(cond) av_assert0(cond)
#ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(4, 5) || AV_HAS_BUILTIN(__builtin_unreachable)
#ವ್ಯಾಖ್ಯಾನಿಸು av_unreachable(ಸಂದೇಶ) __builtin_unreachable()
#ಅಥವಾಆದರೆ  defined(_MSC_VER)
#ವ್ಯಾಖ್ಯಾನಿಸು av_unreachable(ಸಂದೇಶ) __assume(0)
#ಅಥವಾಆದರೆ __STDC_VERSION__ >= 202311L
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ವ್ಯಾಖ್ಯಾನಿಸು av_unreachable(ಸಂದೇಶ) unreachable()
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು av_unreachable(ಸಂದೇಶ) ((ಶೂನ್ಯ)0)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು av_assume(cond) ಮಾಡು { \
    ಆದರೆ (!(cond))             \
        av_unreachable();    \
} ಆಗ (0)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_AVASSERT_H */
