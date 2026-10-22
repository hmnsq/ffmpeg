/*
 * Copyright (c) 2009 Mans Rullgard <mans@mansr.com>
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

#यदि_अपरिभाषितम् AVUTIL_MIPS_INTREADWRITE_H
#परिभाषय AVUTIL_MIPS_INTREADWRITE_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "config.h"

#यदि ARCH_MIPS64 && HAVE_INLINE_ASM && !HAVE_MIPS64R6

#परिभाषय AV_RN32 AV_RN32
स्थिर av_always_inline uint32_t AV_RN32(ध्रुव शून्य *p)
{
    संरचना __attribute__((packed)) u32 { uint32_t v; };
    ध्रुव uint8_t *q = p;
    ध्रुव संरचना u32 *pl = (ध्रुव संरचना u32 *)(q + 3 * !HAVE_BIGENDIAN);
    ध्रुव संरचना u32 *pr = (ध्रुव संरचना u32 *)(q + 3 *  HAVE_BIGENDIAN);
    uint32_t v;
    __asm__ ("lwl %0, %1  \n\t"
             "lwr %0, %2  \n\t"
             : "=&r"(v)
             : "m"(*pl), "m"(*pr));
    प्रत्यागम v;
}

#यदि_अन्तः /* ARCH_MIPS64 && HAVE_INLINE_ASM && !HAVE_MIPS64R6 */

#यदि_अन्तः /* AVUTIL_MIPS_INTREADWRITE_H */
