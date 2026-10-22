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

#अगर_अघोषित AVUTIL_AARCH64_TIMER_H
#घोषणा AVUTIL_AARCH64_TIMER_H

#समावेश <stdint.h>
#समावेश "config.h"

#अगर HAVE_INLINE_ASM

#घोषणा AV_READ_TIME read_time

अटल अंतरभूत uint64_t read_time(व्योम)
{
    uint64_t cycle_गणक;
    __asm__ अस्थिर(
        "isb                   \t\n"
        // cntvct_el0 has lower resolution than pmccntr_el0, but is usually
        // accessible from user space by default.
        "mrs %0, cntvct_el0        "
        : "=r"(cycle_गणक) :: "memory" );

    वापस cycle_गणक;
}

#पूर्ण_अगर /* HAVE_INLINE_ASM */

#पूर्ण_अगर /* AVUTIL_AARCH64_TIMER_H */
