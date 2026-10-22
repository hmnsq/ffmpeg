/*
 * check NEON registers for clobbering
 * Copyright (c) 2008 Ramiro Polla <ramiro.polla@gmail.com>
 * Copyright (c) 2013 Martin Storsjo
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

#که_نه_تعریف_شوی AVUTIL_AARCH64_NEONTEST_H
#تعریف_کړه AVUTIL_AARCH64_NEONTEST_H

#ضمن <inttypes.h>
#ضمن <stdint.h>
#ضمن <stdlib.h>
#ضمن <stdarg.h>
#ضمن <string.h>

#ضمن "libavutil/bswap.h"

#تعریف_کړه storeneonregs(mem)                \
    __asm__ متطاير(                     \
        "stp d8,  d9,  [%0]\n\t"          \
        "stp d10, d11, [%0, #16]\n\t"     \
        "stp d12, d13, [%0, #32]\n\t"     \
        "stp d14, d15, [%0, #48]\n\t"     \
        :: "r"(mem) : "memory")

#تعریف_کړه testneonclobbers(func, ctx, ...)                        \
    uint64_t neon[2][8];                                        \
    صحيح ret;                                                    \
    storeneonregs(neon[0]);                                     \
    ret = __real_ ## func(ctx, __VA_ARGS__);                    \
    storeneonregs(neon[1]);                                     \
    إذا (memcmp(neon[0], neon[1], حجم(neon[0]))) {            \
        صحيح i;                                                  \
        av_log(ctx, AV_LOG_ERROR,                               \
               "NEON REGS CLOBBERED IN %s!\n", #func);          \
        لكل (i = 0; i < 8; i ++)                                \
            إذا (neon[0][i] != neon[1][i]) {                     \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "d%-2d = %016"PRIx64"\n",                \
                       8 + i, av_bswap64(neon[0][i]));          \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "   -> %016"PRIx64"\n",                  \
                       av_bswap64(neon[1][i]));                 \
            }                                                   \
        abort();                                                \
    }                                                           \
    أرجع ret

#تعریف_کړه wrap(func)      \
صحيح __real_ ## func;    \
صحيح __wrap_ ## func;    \
صحيح __wrap_ ## func

#د_که_پای /* AVUTIL_AARCH64_NEONTEST_H */
