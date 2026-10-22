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

#నిర్వచితం_కాకపోతే AVUTIL_X86_TIMER_H
#నిర్వచించు AVUTIL_X86_TIMER_H

#అన్తర్భావ <stdint.h>

#ఒకవేళ HAVE_INLINE_ASM

#నిర్వచించు FF_TIMER_UNITS "decicycles"
#నిర్వచించు AV_READ_సమయం read_సమయం

స్థిర అంతఃవరుస uint64_t read_సమయం(శూన్య)
{
    uint32_t a, d;
    __asm__ అస్థిర(
#ఒకవేళ ARCH_X86_64 || defined(__SSE2__)
                     "lfence \n\t"
#అయితే_ముగింపు
                     "rdtsc  \n\t"
                     : "=a" (a), "=d" (d));
    తిరిగి ((uint64_t)d << 32) + a;
}

#లేదావేళ HAVE_RDTSC

#అన్తర్భావ <intrin.h>
#నిర్వచించు AV_READ_సమయం __rdtsc

#అయితే_ముగింపు /* HAVE_INLINE_ASM */

#అయితే_ముగింపు /* AVUTIL_X86_TIMER_H */
