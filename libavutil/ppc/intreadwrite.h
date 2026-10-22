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

#अगर_अघोषित AVUTIL_PPC_INTREADWRITE_H
#घोषणा AVUTIL_PPC_INTREADWRITE_H

#समावेश <stdint.h>
#समावेश "config.h"

#अगर HAVE_XFORM_ASM

#अगर HAVE_BIGENDIAN
#घोषणा AV_RL16 av_read_bswap16
#घोषणा AV_WL16 av_write_bswap16
#घोषणा AV_RL32 av_read_bswap32
#घोषणा AV_WL32 av_write_bswap32
#घोषणा AV_RL64 av_read_bswap64
#घोषणा AV_WL64 av_write_bswap64

#अन्यथा
#घोषणा AV_RB16 av_read_bswap16
#घोषणा AV_WB16 av_write_bswap16
#घोषणा AV_RB32 av_read_bswap32
#घोषणा AV_WB32 av_write_bswap32
#घोषणा AV_RB64 av_read_bswap64
#घोषणा AV_WB64 av_write_bswap64

#पूर्ण_अगर

अटल av_always_inline uint16_t av_read_bswap16(स्थिर व्योम *p)
{
    uint16_t v;
    __asm__ ("lhbrx   %0, %y1" : "=r"(v) : "Z"(*(स्थिर uint16_t*)p));
    वापस v;
}

अटल av_always_inline व्योम av_write_bswap16(व्योम *p, uint16_t v)
{
    __asm__ ("sthbrx  %1, %y0" : "=Z"(*(uint16_t*)p) : "r"(v));
}

अटल av_always_inline uint32_t av_read_bswap32(स्थिर व्योम *p)
{
    uint32_t v;
    __asm__ ("lwbrx   %0, %y1" : "=r"(v) : "Z"(*(स्थिर uint32_t*)p));
    वापस v;
}

अटल av_always_inline व्योम av_write_bswap32(व्योम *p, uint32_t v)
{
    __asm__ ("stwbrx  %1, %y0" : "=Z"(*(uint32_t*)p) : "r"(v));
}

#अगर HAVE_LDBRX

अटल av_always_inline uint64_t av_read_bswap64(स्थिर व्योम *p)
{
    uint64_t v;
    __asm__ ("ldbrx   %0, %y1" : "=r"(v) : "Z"(*(स्थिर uint64_t*)p));
    वापस v;
}

अटल av_always_inline व्योम av_write_bswap64(व्योम *p, uint64_t v)
{
    __asm__ ("stdbrx  %1, %y0" : "=Z"(*(uint64_t*)p) : "r"(v));
}

#अन्यथा

अटल av_always_inline uint64_t av_read_bswap64(स्थिर व्योम *p)
{
    जोड़ { uint64_t v; uint32_t hl[2]; } v;
    __asm__ ("lwbrx   %0, %y2  \n\t"
             "lwbrx   %1, %y3  \n\t"
             : "=&r"(v.hl[1]), "=r"(v.hl[0])
             : "Z"(*(स्थिर uint32_t*)p), "Z"(*((स्थिर uint32_t*)p+1)));
    वापस v.v;
}

अटल av_always_inline व्योम av_write_bswap64(व्योम *p, uint64_t v)
{
    जोड़ { uint64_t v; uint32_t hl[2]; } vv = { v };
    __asm__ ("stwbrx  %2, %y0  \n\t"
             "stwbrx  %3, %y1  \n\t"
             : "=Z"(*(uint32_t*)p), "=Z"(*((uint32_t*)p+1))
             : "r"(vv.hl[1]), "r"(vv.hl[0]));
}

#पूर्ण_अगर /* HAVE_LDBRX */

#पूर्ण_अगर /* HAVE_XFORM_ASM */

#पूर्ण_अगर /* AVUTIL_PPC_INTREADWRITE_H */
