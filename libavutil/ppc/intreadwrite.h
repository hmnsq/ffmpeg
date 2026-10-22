/*
 * Copyright (c) 2008 Mans Rullgard <mans@mansr.com>
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_PPC_INTREADWRITE_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_PPC_INTREADWRITE_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ HAVE_XFORM_ASM

#ಆದರೆ HAVE_BIGENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು AV_RL16 av_read_bswap16
#ವ್ಯಾಖ್ಯಾನಿಸು AV_WL16 av_write_bswap16
#ವ್ಯಾಖ್ಯಾನಿಸು AV_RL32 av_read_bswap32
#ವ್ಯಾಖ್ಯಾನಿಸು AV_WL32 av_write_bswap32
#ವ್ಯಾಖ್ಯಾನಿಸು AV_RL64 av_read_bswap64
#ವ್ಯಾಖ್ಯಾನಿಸು AV_WL64 av_write_bswap64

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು AV_RB16 av_read_bswap16
#ವ್ಯಾಖ್ಯಾನಿಸು AV_WB16 av_write_bswap16
#ವ್ಯಾಖ್ಯಾನಿಸು AV_RB32 av_read_bswap32
#ವ್ಯಾಖ್ಯಾನಿಸು AV_WB32 av_write_bswap32
#ವ್ಯಾಖ್ಯಾನಿಸು AV_RB64 av_read_bswap64
#ವ್ಯಾಖ್ಯಾನಿಸು AV_WB64 av_write_bswap64

#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ av_always_inline uint16_t av_read_bswap16(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p)
{
    uint16_t v;
    __asm__ ("lhbrx   %0, %y1" : "=r"(v) : "Z"(*(ಸ್ಥಿರಾಂಕ uint16_t*)p));
    ಹಿಂತಿರುಗಿ v;
}

ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ av_write_bswap16(ಶೂನ್ಯ *p, uint16_t v)
{
    __asm__ ("sthbrx  %1, %y0" : "=Z"(*(uint16_t*)p) : "r"(v));
}

ಸ್ಥಿರ av_always_inline uint32_t av_read_bswap32(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p)
{
    uint32_t v;
    __asm__ ("lwbrx   %0, %y1" : "=r"(v) : "Z"(*(ಸ್ಥಿರಾಂಕ uint32_t*)p));
    ಹಿಂತಿರುಗಿ v;
}

ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ av_write_bswap32(ಶೂನ್ಯ *p, uint32_t v)
{
    __asm__ ("stwbrx  %1, %y0" : "=Z"(*(uint32_t*)p) : "r"(v));
}

#ಆದರೆ HAVE_LDBRX

ಸ್ಥಿರ av_always_inline uint64_t av_read_bswap64(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p)
{
    uint64_t v;
    __asm__ ("ldbrx   %0, %y1" : "=r"(v) : "Z"(*(ಸ್ಥಿರಾಂಕ uint64_t*)p));
    ಹಿಂತಿರುಗಿ v;
}

ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ av_write_bswap64(ಶೂನ್ಯ *p, uint64_t v)
{
    __asm__ ("stdbrx  %1, %y0" : "=Z"(*(uint64_t*)p) : "r"(v));
}

#ಇಲ್ಲದಿದ್ದರೆ

ಸ್ಥಿರ av_always_inline uint64_t av_read_bswap64(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p)
{
    ಒಕ್ಕೂಟ { uint64_t v; uint32_t hl[2]; } v;
    __asm__ ("lwbrx   %0, %y2  \n\t"
             "lwbrx   %1, %y3  \n\t"
             : "=&r"(v.hl[1]), "=r"(v.hl[0])
             : "Z"(*(ಸ್ಥಿರಾಂಕ uint32_t*)p), "Z"(*((ಸ್ಥಿರಾಂಕ uint32_t*)p+1)));
    ಹಿಂತಿರುಗಿ v.v;
}

ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ av_write_bswap64(ಶೂನ್ಯ *p, uint64_t v)
{
    ಒಕ್ಕೂಟ { uint64_t v; uint32_t hl[2]; } vv = { v };
    __asm__ ("stwbrx  %2, %y0  \n\t"
             "stwbrx  %3, %y1  \n\t"
             : "=Z"(*(uint32_t*)p), "=Z"(*((uint32_t*)p+1))
             : "r"(vv.hl[1]), "r"(vv.hl[0]));
}

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_LDBRX */

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_XFORM_ASM */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_PPC_INTREADWRITE_H */
