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

#ifndef AVUTIL_AARCH64_TIMER_H
#define AVUTIL_AARCH64_TIMER_H

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব "config.h"

#যদি HAVE_INLINE_ASM

#define AV_READ_TIME read_time

স্থির অন্তঃরেখ uint64_t read_time(শূন্য)
{
    uint64_t cycle_গণক;
    __asm__ অস্থির(
        "isb                   \t\n"
        // cntvct_el0 has lower resolution than pmccntr_el0, but is usually
        // accessible from user space by default.
        "mrs %0, cntvct_el0        "
        : "=r"(cycle_গণক) :: "memory" );

    ফেরত cycle_গণক;
}

#endif /* HAVE_INLINE_ASM */

#endif /* AVUTIL_AARCH64_TIMER_H */
