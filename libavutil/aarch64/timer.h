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

#यदि_अपरिभाषितम् AVUTIL_AARCH64_TIMER_H
#परिभाषय AVUTIL_AARCH64_TIMER_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "config.h"

#यदि HAVE_INLINE_ASM

#परिभाषय AV_READ_TIME read_time

स्थिर अन्तःस्थ uint64_t read_time(शून्य)
{
    uint64_t आवृत्तिः_गणक;
    __asm__ चञ्चल(
        "isb                   \t\n"
        // cntvct_el0 has lower resolution than pmccntr_el0, but is usually
        // accessible from user space by default.
        "mrs %0, cntvct_el0        "
        : "=r"(आवृत्तिः_गणक) :: "memory" );

    प्रत्यागम आवृत्तिः_गणक;
}

#यदि_अन्तः /* HAVE_INLINE_ASM */

#यदि_अन्तः /* AVUTIL_AARCH64_TIMER_H */
