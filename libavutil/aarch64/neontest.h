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

#నిర్వచితం_కాకపోతే AVUTIL_AARCH64_NEONTEST_H
#నిర్వచించు AVUTIL_AARCH64_NEONTEST_H

#అన్తర్భావ <inttypes.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <stdarg.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/bswap.h"

#నిర్వచించు storeneonregs(mem)                \
    __asm__ అస్థిర(                     \
        "stp d8,  d9,  [%0]\n\t"          \
        "stp d10, d11, [%0, #16]\n\t"     \
        "stp d12, d13, [%0, #32]\n\t"     \
        "stp d14, d15, [%0, #48]\n\t"     \
        :: "r"(mem) : "memory")

#నిర్వచించు testneonclobbers(func, ctx, ...)                        \
    uint64_t neon[2][8];                                        \
    పూర్ణాంకం ret;                                                    \
    storeneonregs(neon[0]);                                     \
    ret = __real_ ## func(ctx, __VA_ARGS__);                    \
    storeneonregs(neon[1]);                                     \
    ఒకవేళ (memcmp(neon[0], neon[1], పరిమాణం(neon[0]))) {            \
        పూర్ణాంకం i;                                                  \
        av_log(ctx, AV_LOG_ERROR,                               \
               "NEON REGS CLOBBERED IN %s!\n", #func);          \
        కొరకు (i = 0; i < 8; i ++)                                \
            ఒకవేళ (neon[0][i] != neon[1][i]) {                     \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "d%-2d = %016"PRIx64"\n",                \
                       8 + i, av_bswap64(neon[0][i]));          \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "   -> %016"PRIx64"\n",                  \
                       av_bswap64(neon[1][i]));                 \
            }                                                   \
        abort();                                                \
    }                                                           \
    తిరిగి ret

#నిర్వచించు wrap(func)      \
పూర్ణాంకం __real_ ## func;    \
పూర్ణాంకం __wrap_ ## func;    \
పూర్ణాంకం __wrap_ ## func

#అయితే_ముగింపు /* AVUTIL_AARCH64_NEONTEST_H */
