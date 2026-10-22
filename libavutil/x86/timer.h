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

#यदि_अपरिभाषितम् AVUTIL_X86_TIMER_H
#परिभाषय AVUTIL_X86_TIMER_H

#अन्तर्भाव <stdint.h>

#यदि HAVE_INLINE_ASM

#परिभाषय FF_TIMER_UNITS "decicycles"
#परिभाषय AV_READ_TIME read_time

स्थिर अन्तःस्थ uint64_t read_time(शून्य)
{
    uint32_t a, d;
    __asm__ चञ्चल(
#यदि ARCH_X86_64 || defined(__SSE2__)
                     "lfence \n\t"
#यदि_अन्तः
                     "rdtsc  \n\t"
                     : "=a" (a), "=d" (d));
    प्रत्यागम ((uint64_t)d << 32) + a;
}

#नोचेद्यदि HAVE_RDTSC

#अन्तर्भाव <intrin.h>
#परिभाषय AV_READ_TIME __rdtsc

#यदि_अन्तः /* HAVE_INLINE_ASM */

#यदि_अन्तः /* AVUTIL_X86_TIMER_H */
