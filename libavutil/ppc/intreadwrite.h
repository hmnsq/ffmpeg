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

#ifndef AVUTIL_PPC_INTREADWRITE_H
#define AVUTIL_PPC_INTREADWRITE_H

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ "config.h"

#எனில் HAVE_XFORM_ASM

#எனில் HAVE_BIGENDIAN
#define AV_RL16 av_read_bswap16
#define AV_WL16 av_write_bswap16
#define AV_RL32 av_read_bswap32
#define AV_WL32 av_write_bswap32
#define AV_RL64 av_read_bswap64
#define AV_WL64 av_write_bswap64

#இல்லையெனில்
#define AV_RB16 av_read_bswap16
#define AV_WB16 av_write_bswap16
#define AV_RB32 av_read_bswap32
#define AV_WB32 av_write_bswap32
#define AV_RB64 av_read_bswap64
#define AV_WB64 av_write_bswap64

#endif

நிலையான av_always_inline uint16_t av_read_bswap16(மாறிலி வெறுமை *p)
{
    uint16_t v;
    __asm__ ("lhbrx   %0, %y1" : "=r"(v) : "Z"(*(மாறிலி uint16_t*)p));
    திரும்பு v;
}

நிலையான av_always_inline வெறுமை av_write_bswap16(வெறுமை *p, uint16_t v)
{
    __asm__ ("sthbrx  %1, %y0" : "=Z"(*(uint16_t*)p) : "r"(v));
}

நிலையான av_always_inline uint32_t av_read_bswap32(மாறிலி வெறுமை *p)
{
    uint32_t v;
    __asm__ ("lwbrx   %0, %y1" : "=r"(v) : "Z"(*(மாறிலி uint32_t*)p));
    திரும்பு v;
}

நிலையான av_always_inline வெறுமை av_write_bswap32(வெறுமை *p, uint32_t v)
{
    __asm__ ("stwbrx  %1, %y0" : "=Z"(*(uint32_t*)p) : "r"(v));
}

#எனில் HAVE_LDBRX

நிலையான av_always_inline uint64_t av_read_bswap64(மாறிலி வெறுமை *p)
{
    uint64_t v;
    __asm__ ("ldbrx   %0, %y1" : "=r"(v) : "Z"(*(மாறிலி uint64_t*)p));
    திரும்பு v;
}

நிலையான av_always_inline வெறுமை av_write_bswap64(வெறுமை *p, uint64_t v)
{
    __asm__ ("stdbrx  %1, %y0" : "=Z"(*(uint64_t*)p) : "r"(v));
}

#இல்லையெனில்

நிலையான av_always_inline uint64_t av_read_bswap64(மாறிலி வெறுமை *p)
{
    ஒன்றிப்பு { uint64_t v; uint32_t hl[2]; } v;
    __asm__ ("lwbrx   %0, %y2  \n\t"
             "lwbrx   %1, %y3  \n\t"
             : "=&r"(v.hl[1]), "=r"(v.hl[0])
             : "Z"(*(மாறிலி uint32_t*)p), "Z"(*((மாறிலி uint32_t*)p+1)));
    திரும்பு v.v;
}

நிலையான av_always_inline வெறுமை av_write_bswap64(வெறுமை *p, uint64_t v)
{
    ஒன்றிப்பு { uint64_t v; uint32_t hl[2]; } vv = { v };
    __asm__ ("stwbrx  %2, %y0  \n\t"
             "stwbrx  %3, %y1  \n\t"
             : "=Z"(*(uint32_t*)p), "=Z"(*((uint32_t*)p+1))
             : "r"(vv.hl[1]), "r"(vv.hl[0]));
}

#endif /* HAVE_LDBRX */

#endif /* HAVE_XFORM_ASM */

#endif /* AVUTIL_PPC_INTREADWRITE_H */
