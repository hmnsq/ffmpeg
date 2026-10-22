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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_X86_TIMER_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_X86_TIMER_H

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಆದರೆ HAVE_INLINE_ASM

#ವ್ಯಾಖ್ಯಾನಿಸು FF_TIMER_UNITS "decicycles"
#ವ್ಯಾಖ್ಯಾನಿಸು AV_READ_ಸಮಯ read_ಸಮಯ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint64_t read_ಸಮಯ(ಶೂನ್ಯ)
{
    uint32_t a, d;
    __asm__ ಅಸ್ಥಿರ(
#ಆದರೆ ARCH_X86_64 || defined(__SSE2__)
                     "lfence \n\t"
#ಆದರೆ_ಅಂತ್ಯ
                     "rdtsc  \n\t"
                     : "=a" (a), "=d" (d));
    ಹಿಂತಿರುಗಿ ((uint64_t)d << 32) + a;
}

#ಅಥವಾಆದರೆ HAVE_RDTSC

#ಅನ್ತರ್ಭಾವ <intrin.h>
#ವ್ಯಾಖ್ಯಾನಿಸು AV_READ_ಸಮಯ __rdtsc

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_INLINE_ASM */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_X86_TIMER_H */
