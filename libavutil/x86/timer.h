/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_X86_TIMER_H
#وصف_ڪريو AVUTIL_X86_TIMER_H

#ضمن <stdint.h>

#إذا HAVE_INLINE_ASM

#وصف_ڪريو FF_TIMER_UNITS "decicycles"
#وصف_ڪريو AV_READ_وقت read_وقت

ساكن مضمن uint64_t read_وقت(فراغ)
{
    uint32_t a, d;
    __asm__ متطاير(
#إذا ARCH_X86_64 || defined(__SSE2__)
                     "lfence \n\t"
#جيڪڏهن_پورو
                     "rdtsc  \n\t"
                     : "=a" (a), "=d" (d));
    أرجع ((uint64_t)d << 32) + a;
}

#وإلاإذا HAVE_RDTSC

#ضمن <intrin.h>
#وصف_ڪريو AV_READ_وقت __rdtsc

#جيڪڏهن_پورو /* HAVE_INLINE_ASM */

#جيڪڏهن_پورو /* AVUTIL_X86_TIMER_H */
