/*
 * Copyright © 2022 Rémi Denis-Courmont.
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

#اگر_غیر_تعریف_شدہ AVUTIL_RISCV_CPU_H
#تعریف_کرو AVUTIL_RISCV_CPU_H

#شامل "config.h"
#شامل <stdbool.h>
#شامل <stddef.h>
#شامل "libavutil/attributes_internal.h"
#شامل "libavutil/cpu.h"

#اگر_غیر_تعریف_شدہ __riscv_zbb
خارجی attribute_visibility_hidden bool ff_rv_zbb_supported;
#اگر_ختم

ساکن اندرونی av_const bool ff_rv_zbb_support(خالی)
{
#اگر_غیر_تعریف_شدہ __riscv_zbb
    واپس ff_rv_zbb_supported;
#ورنہ
    واپس true;
#اگر_ختم
}

#اگر HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
ساکن اندرونی av_const size_t ff_get_rv_vlenb(خالی)
{
    size_t vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    واپس vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
ساکن اندرونی av_const bool ff_rv_vlen_کم_سے_کم(غیرعلامتی صحیح بٹ)
{
#اگر_تعریف_شدہ __riscv_v_min_vlen
    اگر (بٹ <= __riscv_v_min_vlen)
        واپس true;
#ورنہ
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    اگر (بٹ <= 128)
        واپس true;
#اگر_ختم
    واپس بٹ <= (8 * ff_get_rv_vlenb());
}
#اگر_ختم
#اگر_ختم /* HAVE_RVV */
