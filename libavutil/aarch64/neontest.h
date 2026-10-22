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

#ifndef AVUTIL_AARCH64_NEONTEST_H
#define AVUTIL_AARCH64_NEONTEST_H

#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/bswap.h"

#define storeneonregs(mem)                \
    __asm__ ಚಞ್ಚಲ(                     \
        "stp d8,  d9,  [%0]\n\t"          \
        "stp d10, d11, [%0, #16]\n\t"     \
        "stp d12, d13, [%0, #32]\n\t"     \
        "stp d14, d15, [%0, #48]\n\t"     \
        :: "r"(mem) : "memory")

#define testneonclobbers(func, ctx, ...)                        \
    uint64_t neon[2][8];                                        \
    ಪೂರ್ಣಾಙ್ಕ ret;                                                    \
    storeneonregs(neon[0]);                                     \
    ret = __real_ ## func(ctx, __VA_ARGS__);                    \
    storeneonregs(neon[1]);                                     \
    ಯದಿ (memcmp(neon[0], neon[1], ಪರಿಮಾಣ(neon[0]))) {            \
        ಪೂರ್ಣಾಙ್ಕ i;                                                  \
        av_log(ctx, AV_LOG_ERROR,                               \
               "NEON REGS CLOBBERED IN %s!\n", #func);          \
        ಪ್ರತಿ (i = 0; i < 8; i ++)                                \
            ಯದಿ (neon[0][i] != neon[1][i]) {                     \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "d%-2d = %016"PRIx64"\n",                \
                       8 + i, av_bswap64(neon[0][i]));          \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "   -> %016"PRIx64"\n",                  \
                       av_bswap64(neon[1][i]));                 \
            }                                                   \
        abort();                                                \
    }                                                           \
    ಪ್ರತ್ಯಾಗಮ ret

#define wrap(func)      \
ಪೂರ್ಣಾಙ್ಕ __real_ ## func;    \
ಪೂರ್ಣಾಙ್ಕ __wrap_ ## func;    \
ಪೂರ್ಣಾಙ್ಕ __wrap_ ## func

#endif /* AVUTIL_AARCH64_NEONTEST_H */
