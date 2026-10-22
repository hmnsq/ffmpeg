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

#ifndef AVUTIL_X86_W64XMMTEST_H
#define AVUTIL_X86_W64XMMTEST_H

#अन्तर्भाव <inttypes.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/bswap.h"

#define storexmmregs(mem)               \
    __asm__ चञ्चल(                   \
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

#define testxmmclobbers(func, ctx, ...)                         \
    uint64_t xmm[2][10][2];                                     \
    पूर्णाङ्क ret;                                                    \
    storexmmregs(xmm[0]);                                       \
    ret = __real_ ## func(ctx, __VA_ARGS__);                    \
    storexmmregs(xmm[1]);                                       \
    सचे (memcmp(xmm[0], xmm[1], परिमाण(xmm[0]))) {               \
        पूर्णाङ्क i;                                                  \
        av_log(ctx, AV_LOG_ERROR,                               \
               "XMM REGS CLOBBERED IN %s!\n", #func);           \
        अत्थाय (i = 0; i < 10; i ++)                               \
            सचे (xmm[0][i][0] != xmm[1][i][0] ||                 \
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
    पटिनिवत्त ret

#define wrap(func)      \
पूर्णाङ्क __real_ ## func;    \
पूर्णाङ्क __wrap_ ## func;    \
पूर्णाङ्क __wrap_ ## func

#endif /* AVUTIL_X86_W64XMMTEST_H */
