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

#اگر_غیر_تعریف_شدہ AVUTIL_X86_TIMER_H
#تعریف_کرو AVUTIL_X86_TIMER_H

#شامل <stdint.h>

#اگر HAVE_INLINE_ASM

#تعریف_کرو FF_TIMER_UNITS "decicycles"
#تعریف_کرو AV_READ_وقت read_وقت

ساکن اندرونی uint64_t read_وقت(خالی)
{
    uint32_t a, d;
    __asm__ متلون(
#اگر ARCH_X86_64 || defined(__SSE2__)
                     "lfence \n\t"
#اگر_ختم
                     "rdtsc  \n\t"
                     : "=a" (a), "=d" (d));
    واپس ((uint64_t)d << 32) + a;
}

#وگرنہ_اگر HAVE_RDTSC

#شامل <intrin.h>
#تعریف_کرو AV_READ_وقت __rdtsc

#اگر_ختم /* HAVE_INLINE_ASM */

#اگر_ختم /* AVUTIL_X86_TIMER_H */
