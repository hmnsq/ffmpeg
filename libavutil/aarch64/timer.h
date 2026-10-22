/*
 * Copyright (c) 2015 Janne Grunau <janne-libav@jannau.net>
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_AARCH64_TIMER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_AARCH64_TIMER_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_INLINE_ASM

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_READ_ਸਮਾਂ read_ਸਮਾਂ

ਸਥਿਰ ਸਤਰਅੰਦਰ uint64_t read_ਸਮਾਂ(ਖਾਲੀ)
{
    uint64_t ਚੱਕਰ_counter;
    __asm__ ਅਸਥਿਰ(
        "isb                   \t\n"
        // cntvct_el0 has lower resolution than pmccntr_el0, but is usually
        // accessible from user space by default.
        "mrs %0, cntvct_el0        "
        : "=r"(ਚੱਕਰ_counter) :: "memory" );

    ਵਾਪਸ ਚੱਕਰ_counter;
}

#ਜੇ_ਅੰਤ /* HAVE_INLINE_ASM */

#ਜੇ_ਅੰਤ /* AVUTIL_AARCH64_TIMER_H */
