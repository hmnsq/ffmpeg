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

#اگر_تعریف_نشده AVUTIL_X86_TIMER_H
#تعریف_کن AVUTIL_X86_TIMER_H

#ضمن <stdint.h>

#إذا HAVE_INLINE_ASM

#تعریف_کن FF_TIMER_UNITS "decicycles"
#تعریف_کن AV_READ_زمان read_زمان

ساكن مضمن uint64_t read_زمان(فراغ)
{
    uint32_t a, d;
    __asm__ متطاير(
#إذا ARCH_X86_64 || defined(__SSE2__)
                     "lfence \n\t"
#پایان_اگر
                     "rdtsc  \n\t"
                     : "=a" (a), "=d" (d));
    أرجع ((uint64_t)d << 32) + a;
}

#وإلاإذا HAVE_RDTSC

#ضمن <intrin.h>
#تعریف_کن AV_READ_زمان __rdtsc

#پایان_اگر /* HAVE_INLINE_ASM */

#پایان_اگر /* AVUTIL_X86_TIMER_H */
