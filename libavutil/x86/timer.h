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

#که_نه_تعریف_شوی AVUTIL_X86_TIMER_H
#تعریف_کړه AVUTIL_X86_TIMER_H

#ضمن <stdint.h>

#إذا HAVE_INLINE_ASM

#تعریف_کړه FF_TIMER_UNITS "decicycles"
#تعریف_کړه AV_READ_وخت read_وخت

ساكن مضمن uint64_t read_وخت(فراغ)
{
    uint32_t a, d;
    __asm__ متطاير(
#إذا ARCH_X86_64 || defined(__SSE2__)
                     "lfence \n\t"
#د_که_پای
                     "rdtsc  \n\t"
                     : "=a" (a), "=d" (d));
    أرجع ((uint64_t)d << 32) + a;
}

#وإلاإذا HAVE_RDTSC

#ضمن <intrin.h>
#تعریف_کړه AV_READ_وخت __rdtsc

#د_که_پای /* HAVE_INLINE_ASM */

#د_که_پای /* AVUTIL_X86_TIMER_H */
