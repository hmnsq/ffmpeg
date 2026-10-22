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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ARM_NEONTEST_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ARM_NEONTEST_H

#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/bswap.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ storeneonregs(mem)                \
    __asm__ ਅਸਥਿਰ(                     \
        "vstm %0, {d8-d15}\n\t"           \
        :: "r"(mem) : "memory")

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ testneonclobbers(func, ctx, ...)                        \
    uint64_t neon[2][8];                                        \
    ਪੂਰਨ ret;                                                    \
    storeneonregs(neon[0]);                                     \
    ret = __real_ ## func(ctx, __VA_ARGS__);                    \
    storeneonregs(neon[1]);                                     \
    ਜੇ (memcmp(neon[0], neon[1], ਆਕਾਰ(neon[0]))) {            \
        ਪੂਰਨ i;                                                  \
        av_log(ctx, AV_LOG_ERROR,                               \
               "NEON REGS CLOBBERED IN %s!\n", #func);          \
        ਲਈ (i = 0; i < 8; i ++)                                \
            ਜੇ (neon[0][i] != neon[1][i]) {                     \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "d%-2d = %016"PRIx64"\n",                \
                       8 + i, av_bswap64(neon[0][i]));          \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "   -> %016"PRIx64"\n",                  \
                       av_bswap64(neon[1][i]));                 \
            }                                                   \
        abort();                                                \
    }                                                           \
    ਵਾਪਸ ret

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wrap(func)      \
ਪੂਰਨ __real_ ## func;    \
ਪੂਰਨ __wrap_ ## func;    \
ਪੂਰਨ __wrap_ ## func

#ਜੇ_ਅੰਤ /* AVUTIL_ARM_NEONTEST_H */
