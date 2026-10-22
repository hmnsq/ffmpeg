/*
 * check XMM registers for clobbers on Win64
 * Copyright (c) 2008 Ramiro Polla <ramiro.polla@gmail.com>
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_X86_W64XMMTEST_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_X86_W64XMMTEST_H

#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/bswap.h"

#ವ್ಯಾಖ್ಯಾನಿಸು storexmmregs(mem)               \
    __asm__ ಅಸ್ಥಿರ(                   \
        "movups %%xmm6 , 0x00(%0)\n\t"  \
        "movups %%xmm7 , 0x10(%0)\n\t"  \
        "movups %%xmm8 , 0x20(%0)\n\t"  \
        "movups %%xmm9 , 0x30(%0)\n\t"  \
        "movups %%xmm10, 0x40(%0)\n\t"  \
        "movups %%xmm11, 0x50(%0)\n\t"  \
        "movups %%xmm12, 0x60(%0)\n\t"  \
        "movups %%xmm13, 0x70(%0)\n\t"  \
        "movups %%xmm14, 0x80(%0)\n\t"  \
        "movups %%xmm15, 0x90(%0)\n\t"  \
        :: "r"(mem) : "memory")

#ವ್ಯಾಖ್ಯಾನಿಸು testxmmclobbers(func, ctx, ...)                         \
    uint64_t xmm[2][10][2];                                     \
    ಪೂರ್ಣಾಂಕ ret;                                                    \
    storexmmregs(xmm[0]);                                       \
    ret = __real_ ## func(ctx, __VA_ARGS__);                    \
    storexmmregs(xmm[1]);                                       \
    ಆದರೆ (memcmp(xmm[0], xmm[1], ಗಾತ್ರ(xmm[0]))) {               \
        ಪೂರ್ಣಾಂಕ i;                                                  \
        av_log(ctx, AV_LOG_ERROR,                               \
               "XMM REGS CLOBBERED IN %s!\n", #func);           \
        ಗಾಗಿ (i = 0; i < 10; i ++)                               \
            ಆದರೆ (xmm[0][i][0] != xmm[1][i][0] ||                 \
                xmm[0][i][1] != xmm[1][i][1]) {                 \
                av_log(ctx, AV_LOG_ERROR,                       \
                       "xmm%-2d = %016"PRIx64"%016"PRIx64"\n",  \
                       6 + i, av_bswap64(xmm[0][i][0]),         \
                       av_bswap64(xmm[0][i][1]));               \
                av_log(ctx, AV_LOG_ERROR,                       \
                         "     -> %016"PRIx64"%016"PRIx64"\n",  \
                       av_bswap64(xmm[1][i][0]),                \
                       av_bswap64(xmm[1][i][1]));               \
            }                                                   \
        abort();                                                \
    }                                                           \
    ಹಿಂತಿರುಗಿ ret

#ವ್ಯಾಖ್ಯಾನಿಸು wrap(func)      \
ಪೂರ್ಣಾಂಕ __real_ ## func;    \
ಪೂರ್ಣಾಂಕ __wrap_ ## func;    \
ಪೂರ್ಣಾಂಕ __wrap_ ## func

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_X86_W64XMMTEST_H */
