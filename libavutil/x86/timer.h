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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_X86_TIMER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_X86_TIMER_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਜੇ HAVE_INLINE_ASM

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_TIMER_UNITS "decicycles"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_READ_ਸਮਾਂ read_ਸਮਾਂ

ਸਥਿਰ ਸਤਰਅੰਦਰ uint64_t read_ਸਮਾਂ(ਖਾਲੀ)
{
    uint32_t a, d;
    __asm__ ਅਸਥਿਰ(
#ਜੇ ARCH_X86_64 || defined(__SSE2__)
                     "lfence \n\t"
#ਜੇ_ਅੰਤ
                     "rdtsc  \n\t"
                     : "=a" (a), "=d" (d));
    ਵਾਪਸ ((uint64_t)d << 32) + a;
}

#ਜਾਂਜੇ HAVE_RDTSC

#ਅਨ੍ਤਰ੍ਭਾਵ <intrin.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_READ_ਸਮਾਂ __rdtsc

#ਜੇ_ਅੰਤ /* HAVE_INLINE_ASM */

#ਜੇ_ਅੰਤ /* AVUTIL_X86_TIMER_H */
