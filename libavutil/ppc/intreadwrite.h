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

#اگر_تعریف_نشده AVUTIL_PPC_INTREADWRITE_H
#تعریف_کن AVUTIL_PPC_INTREADWRITE_H

#ضمن <stdint.h>
#ضمن "config.h"

#إذا HAVE_XFORM_ASM

#إذا HAVE_BIGENDIAN
#تعریف_کن AV_RL16 av_read_bswap16
#تعریف_کن AV_WL16 av_write_bswap16
#تعریف_کن AV_RL32 av_read_bswap32
#تعریف_کن AV_WL32 av_write_bswap32
#تعریف_کن AV_RL64 av_read_bswap64
#تعریف_کن AV_WL64 av_write_bswap64

#وإلا
#تعریف_کن AV_RB16 av_read_bswap16
#تعریف_کن AV_WB16 av_write_bswap16
#تعریف_کن AV_RB32 av_read_bswap32
#تعریف_کن AV_WB32 av_write_bswap32
#تعریف_کن AV_RB64 av_read_bswap64
#تعریف_کن AV_WB64 av_write_bswap64

#پایان_اگر

ساكن av_always_inline uint16_t av_read_bswap16(ثابت فراغ *p)
{
    uint16_t v;
    __asm__ ("lhbrx   %0, %y1" : "=r"(v) : "Z"(*(ثابت uint16_t*)p));
    أرجع v;
}

ساكن av_always_inline فراغ av_write_bswap16(فراغ *p, uint16_t v)
{
    __asm__ ("sthbrx  %1, %y0" : "=Z"(*(uint16_t*)p) : "r"(v));
}

ساكن av_always_inline uint32_t av_read_bswap32(ثابت فراغ *p)
{
    uint32_t v;
    __asm__ ("lwbrx   %0, %y1" : "=r"(v) : "Z"(*(ثابت uint32_t*)p));
    أرجع v;
}

ساكن av_always_inline فراغ av_write_bswap32(فراغ *p, uint32_t v)
{
    __asm__ ("stwbrx  %1, %y0" : "=Z"(*(uint32_t*)p) : "r"(v));
}

#إذا HAVE_LDBRX

ساكن av_always_inline uint64_t av_read_bswap64(ثابت فراغ *p)
{
    uint64_t v;
    __asm__ ("ldbrx   %0, %y1" : "=r"(v) : "Z"(*(ثابت uint64_t*)p));
    أرجع v;
}

ساكن av_always_inline فراغ av_write_bswap64(فراغ *p, uint64_t v)
{
    __asm__ ("stdbrx  %1, %y0" : "=Z"(*(uint64_t*)p) : "r"(v));
}

#وإلا

ساكن av_always_inline uint64_t av_read_bswap64(ثابت فراغ *p)
{
    اتحاد { uint64_t v; uint32_t hl[2]; } v;
    __asm__ ("lwbrx   %0, %y2  \n\t"
             "lwbrx   %1, %y3  \n\t"
             : "=&r"(v.hl[1]), "=r"(v.hl[0])
             : "Z"(*(ثابت uint32_t*)p), "Z"(*((ثابت uint32_t*)p+1)));
    أرجع v.v;
}

ساكن av_always_inline فراغ av_write_bswap64(فراغ *p, uint64_t v)
{
    اتحاد { uint64_t v; uint32_t hl[2]; } vv = { v };
    __asm__ ("stwbrx  %2, %y0  \n\t"
             "stwbrx  %3, %y1  \n\t"
             : "=Z"(*(uint32_t*)p), "=Z"(*((uint32_t*)p+1))
             : "r"(vv.hl[1]), "r"(vv.hl[0]));
}

#پایان_اگر /* HAVE_LDBRX */

#پایان_اگر /* HAVE_XFORM_ASM */

#پایان_اگر /* AVUTIL_PPC_INTREADWRITE_H */
