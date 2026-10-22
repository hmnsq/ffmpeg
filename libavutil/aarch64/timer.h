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

#اگر_تعریف_نشده AVUTIL_AARCH64_TIMER_H
#تعریف_کن AVUTIL_AARCH64_TIMER_H

#ضمن <stdint.h>
#ضمن "config.h"

#إذا HAVE_INLINE_ASM

#تعریف_کن AV_READ_زمان read_زمان

ساكن مضمن uint64_t read_زمان(فراغ)
{
    uint64_t چرخه_counter;
    __asm__ متطاير(
        "isb                   \t\n"
        // cntvct_el0 has lower resolution than pmccntr_el0, but is usually
        // accessible from user space by default.
        "mrs %0, cntvct_el0        "
        : "=r"(چرخه_counter) :: "memory" );

    أرجع چرخه_counter;
}

#پایان_اگر /* HAVE_INLINE_ASM */

#پایان_اگر /* AVUTIL_AARCH64_TIMER_H */
