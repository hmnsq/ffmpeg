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

#اگر_غیر_تعریف_شدہ AVUTIL_PPC_INTREADWRITE_H
#تعریف_کرو AVUTIL_PPC_INTREADWRITE_H

#شامل <stdint.h>
#شامل "config.h"

#اگر HAVE_XFORM_ASM

#اگر HAVE_BIGENDIAN
#تعریف_کرو AV_RL16 av_read_bswap16
#تعریف_کرو AV_WL16 av_write_bswap16
#تعریف_کرو AV_RL32 av_read_bswap32
#تعریف_کرو AV_WL32 av_write_bswap32
#تعریف_کرو AV_RL64 av_read_bswap64
#تعریف_کرو AV_WL64 av_write_bswap64

#ورنہ
#تعریف_کرو AV_RB16 av_read_bswap16
#تعریف_کرو AV_WB16 av_write_bswap16
#تعریف_کرو AV_RB32 av_read_bswap32
#تعریف_کرو AV_WB32 av_write_bswap32
#تعریف_کرو AV_RB64 av_read_bswap64
#تعریف_کرو AV_WB64 av_write_bswap64

#اگر_ختم

ساکن av_always_inline uint16_t av_read_bswap16(ثابت خالی *p)
{
    uint16_t v;
    __asm__ ("lhbrx   %0, %y1" : "=r"(v) : "Z"(*(ثابت uint16_t*)p));
    واپس v;
}

ساکن av_always_inline خالی av_write_bswap16(خالی *p, uint16_t v)
{
    __asm__ ("sthbrx  %1, %y0" : "=Z"(*(uint16_t*)p) : "r"(v));
}

ساکن av_always_inline uint32_t av_read_bswap32(ثابت خالی *p)
{
    uint32_t v;
    __asm__ ("lwbrx   %0, %y1" : "=r"(v) : "Z"(*(ثابت uint32_t*)p));
    واپس v;
}

ساکن av_always_inline خالی av_write_bswap32(خالی *p, uint32_t v)
{
    __asm__ ("stwbrx  %1, %y0" : "=Z"(*(uint32_t*)p) : "r"(v));
}

#اگر HAVE_LDBRX

ساکن av_always_inline uint64_t av_read_bswap64(ثابت خالی *p)
{
    uint64_t v;
    __asm__ ("ldbrx   %0, %y1" : "=r"(v) : "Z"(*(ثابت uint64_t*)p));
    واپس v;
}

ساکن av_always_inline خالی av_write_bswap64(خالی *p, uint64_t v)
{
    __asm__ ("stdbrx  %1, %y0" : "=Z"(*(uint64_t*)p) : "r"(v));
}

#ورنہ

ساکن av_always_inline uint64_t av_read_bswap64(ثابت خالی *p)
{
    اتحاد { uint64_t v; uint32_t hl[2]; } v;
    __asm__ ("lwbrx   %0, %y2  \n\t"
             "lwbrx   %1, %y3  \n\t"
             : "=&r"(v.hl[1]), "=r"(v.hl[0])
             : "Z"(*(ثابت uint32_t*)p), "Z"(*((ثابت uint32_t*)p+1)));
    واپس v.v;
}

ساکن av_always_inline خالی av_write_bswap64(خالی *p, uint64_t v)
{
    اتحاد { uint64_t v; uint32_t hl[2]; } vv = { v };
    __asm__ ("stwbrx  %2, %y0  \n\t"
             "stwbrx  %3, %y1  \n\t"
             : "=Z"(*(uint32_t*)p), "=Z"(*((uint32_t*)p+1))
             : "r"(vv.hl[1]), "r"(vv.hl[0]));
}

#اگر_ختم /* HAVE_LDBRX */

#اگر_ختم /* HAVE_XFORM_ASM */

#اگر_ختم /* AVUTIL_PPC_INTREADWRITE_H */
