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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_MIPS_INTREADWRITE_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_MIPS_INTREADWRITE_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ ARCH_MIPS64 && HAVE_INLINE_ASM && !HAVE_MIPS64R6

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_RN32 AV_RN32
ਸਥਿਰ av_always_inline uint32_t AV_RN32(ਅਚਲ ਖਾਲੀ *p)
{
    ਬਣਤਰ __attribute__((packed)) u32 { uint32_t v; };
    ਅਚਲ uint8_t *q = p;
    ਅਚਲ ਬਣਤਰ u32 *pl = (ਅਚਲ ਬਣਤਰ u32 *)(q + 3 * !HAVE_BIGENDIAN);
    ਅਚਲ ਬਣਤਰ u32 *pr = (ਅਚਲ ਬਣਤਰ u32 *)(q + 3 *  HAVE_BIGENDIAN);
    uint32_t v;
    __asm__ ("lwl %0, %1  \n\t"
             "lwr %0, %2  \n\t"
             : "=&r"(v)
             : "m"(*pl), "m"(*pr));
    ਵਾਪਸ v;
}

#ਜੇ_ਅੰਤ /* ARCH_MIPS64 && HAVE_INLINE_ASM && !HAVE_MIPS64R6 */

#ਜੇ_ਅੰਤ /* AVUTIL_MIPS_INTREADWRITE_H */
