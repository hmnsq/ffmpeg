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

#अगर_अघोषित AVUTIL_X86_TIMER_H
#घोषणा AVUTIL_X86_TIMER_H

#समावेश <stdint.h>

#अगर HAVE_INLINE_ASM

#घोषणा FF_TIMER_UNITS "decicycles"
#घोषणा AV_READ_TIME read_time

अटल अंतरभूत uint64_t read_time(व्योम)
{
    uint32_t a, d;
    __asm__ अस्थिर(
#अगर ARCH_X86_64 || defined(__SSE2__)
                     "lfence \n\t"
#पूर्ण_अगर
                     "rdtsc  \n\t"
                     : "=a" (a), "=d" (d));
    वापस ((uint64_t)d << 32) + a;
}

#या_अगर HAVE_RDTSC

#समावेश <intrin.h>
#घोषणा AV_READ_TIME __rdtsc

#पूर्ण_अगर /* HAVE_INLINE_ASM */

#पूर्ण_अगर /* AVUTIL_X86_TIMER_H */
