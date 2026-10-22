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

#ifndef AVUTIL_ARM_NEONTEST_H
#define AVUTIL_ARM_NEONTEST_H

#شامل <inttypes.h>
#شامل <stdint.h>
#شامل <stdlib.h>
#شامل <stdarg.h>
#شامل <string.h>

#شامل "libavutil/bswap.h"

#define storeneonregs(mem)                \
    __asm__ فرار(                     \
        "vstm %0, {d8-d15}\n\t"           \
        :: "r"(mem) : "memory")

#define testneonclobbers(func, ctx, ...)                        \
    uint64_t neon[2][8];                                        \
    صحیح ret;                                                    \
    storeneonregs(neon[0]);                                     \
    ret = __real_ ## func(ctx, __VA_ARGS__);                    \
    storeneonregs(neon[1]);                                     \
    اگر (memcmp(neon[0], neon[1], اندازه(neon[0]))) {            \
        صحیح i;                                                  \
        av_log(ctx, AV_LOG_ERROR,                               \
               "NEON REGS CLOBBERED IN %s!\n", #func);          \
        برای (i = 0; i < 8; i ++)                                \
            اگر (neon[0][i] != neon[1][i]) {                     \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "d%-2d = %016"PRIx64"\n",                \
                       8 + i, av_bswap64(neon[0][i]));          \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "   -> %016"PRIx64"\n",                  \
                       av_bswap64(neon[1][i]));                 \
            }                                                   \
        abort();                                                \
    }                                                           \
    بازگشت ret

#define wrap(func)      \
صحیح __real_ ## func;    \
صحیح __wrap_ ## func;    \
صحیح __wrap_ ## func

#endif /* AVUTIL_ARM_NEONTEST_H */
