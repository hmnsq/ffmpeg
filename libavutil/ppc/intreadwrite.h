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

#నిర్వచితం_కాకపోతే AVUTIL_PPC_INTREADWRITE_H
#నిర్వచించు AVUTIL_PPC_INTREADWRITE_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_XFORM_ASM

#ఒకవేళ HAVE_BIGENDIAN
#నిర్వచించు AV_RL16 av_read_bswap16
#నిర్వచించు AV_WL16 av_write_bswap16
#నిర్వచించు AV_RL32 av_read_bswap32
#నిర్వచించు AV_WL32 av_write_bswap32
#నిర్వచించు AV_RL64 av_read_bswap64
#నిర్వచించు AV_WL64 av_write_bswap64

#లేకపోతే
#నిర్వచించు AV_RB16 av_read_bswap16
#నిర్వచించు AV_WB16 av_write_bswap16
#నిర్వచించు AV_RB32 av_read_bswap32
#నిర్వచించు AV_WB32 av_write_bswap32
#నిర్వచించు AV_RB64 av_read_bswap64
#నిర్వచించు AV_WB64 av_write_bswap64

#అయితే_ముగింపు

స్థిర av_always_inline uint16_t av_read_bswap16(స్థిరరాశి శూన్య *p)
{
    uint16_t v;
    __asm__ ("lhbrx   %0, %y1" : "=r"(v) : "Z"(*(స్థిరరాశి uint16_t*)p));
    తిరిగి v;
}

స్థిర av_always_inline శూన్య av_write_bswap16(శూన్య *p, uint16_t v)
{
    __asm__ ("sthbrx  %1, %y0" : "=Z"(*(uint16_t*)p) : "r"(v));
}

స్థిర av_always_inline uint32_t av_read_bswap32(స్థిరరాశి శూన్య *p)
{
    uint32_t v;
    __asm__ ("lwbrx   %0, %y1" : "=r"(v) : "Z"(*(స్థిరరాశి uint32_t*)p));
    తిరిగి v;
}

స్థిర av_always_inline శూన్య av_write_bswap32(శూన్య *p, uint32_t v)
{
    __asm__ ("stwbrx  %1, %y0" : "=Z"(*(uint32_t*)p) : "r"(v));
}

#ఒకవేళ HAVE_LDBRX

స్థిర av_always_inline uint64_t av_read_bswap64(స్థిరరాశి శూన్య *p)
{
    uint64_t v;
    __asm__ ("ldbrx   %0, %y1" : "=r"(v) : "Z"(*(స్థిరరాశి uint64_t*)p));
    తిరిగి v;
}

స్థిర av_always_inline శూన్య av_write_bswap64(శూన్య *p, uint64_t v)
{
    __asm__ ("stdbrx  %1, %y0" : "=Z"(*(uint64_t*)p) : "r"(v));
}

#లేకపోతే

స్థిర av_always_inline uint64_t av_read_bswap64(స్థిరరాశి శూన్య *p)
{
    సంఘం { uint64_t v; uint32_t hl[2]; } v;
    __asm__ ("lwbrx   %0, %y2  \n\t"
             "lwbrx   %1, %y3  \n\t"
             : "=&r"(v.hl[1]), "=r"(v.hl[0])
             : "Z"(*(స్థిరరాశి uint32_t*)p), "Z"(*((స్థిరరాశి uint32_t*)p+1)));
    తిరిగి v.v;
}

స్థిర av_always_inline శూన్య av_write_bswap64(శూన్య *p, uint64_t v)
{
    సంఘం { uint64_t v; uint32_t hl[2]; } vv = { v };
    __asm__ ("stwbrx  %2, %y0  \n\t"
             "stwbrx  %3, %y1  \n\t"
             : "=Z"(*(uint32_t*)p), "=Z"(*((uint32_t*)p+1))
             : "r"(vv.hl[1]), "r"(vv.hl[0]));
}

#అయితే_ముగింపు /* HAVE_LDBRX */

#అయితే_ముగింపు /* HAVE_XFORM_ASM */

#అయితే_ముగింపు /* AVUTIL_PPC_INTREADWRITE_H */
