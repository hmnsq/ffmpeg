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

#که_نه_تعریف_شوی AVUTIL_AARCH64_TIMER_H
#تعریف_کړه AVUTIL_AARCH64_TIMER_H

#ضمن <stdint.h>
#ضمن "config.h"

#إذا HAVE_INLINE_ASM

#تعریف_کړه AV_READ_وخت read_وخت

ساكن مضمن uint64_t read_وخت(فراغ)
{
    uint64_t دوره_counter;
    __asm__ متطاير(
        "isb                   \t\n"
        // cntvct_el0 has lower resolution than pmccntr_el0, but is usually
        // accessible from user space by default.
        "mrs %0, cntvct_el0        "
        : "=r"(دوره_counter) :: "memory" );

    أرجع دوره_counter;
}

#د_که_پای /* HAVE_INLINE_ASM */

#د_که_پای /* AVUTIL_AARCH64_TIMER_H */
