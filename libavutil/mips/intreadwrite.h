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

#ifndef AVUTIL_MIPS_INTREADWRITE_H
#define AVUTIL_MIPS_INTREADWRITE_H

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব "config.h"

#যদি ARCH_MIPS64 && HAVE_INLINE_ASM && !HAVE_MIPS64R6

#define AV_RN32 AV_RN32
স্থির av_always_inline uint32_t AV_RN32(ধ্রুবক শূন্য *p)
{
    কাঠামো __attribute__((packed)) u32 { uint32_t v; };
    ধ্রুবক uint8_t *q = p;
    ধ্রুবক কাঠামো u32 *pl = (ধ্রুবক কাঠামো u32 *)(q + 3 * !HAVE_BIGENDIAN);
    ধ্রুবক কাঠামো u32 *pr = (ধ্রুবক কাঠামো u32 *)(q + 3 *  HAVE_BIGENDIAN);
    uint32_t v;
    __asm__ ("lwl %0, %1  \n\t"
             "lwr %0, %2  \n\t"
             : "=&r"(v)
             : "m"(*pl), "m"(*pr));
    ফেরত v;
}

#endif /* ARCH_MIPS64 && HAVE_INLINE_ASM && !HAVE_MIPS64R6 */

#endif /* AVUTIL_MIPS_INTREADWRITE_H */
