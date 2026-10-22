/*
 * Copyright (c) 2023 Loongson Technology Corporation Limited
 * Contributed by Hecai Yuan <yuanhecai@loongson.cn>
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

#اگر_غیر_تعریف_شدہ AVUTIL_LOONGARCH_TIMER_H
#تعریف_کرو AVUTIL_LOONGARCH_TIMER_H

#شامل <stdint.h>
#شامل "config.h"

#اگر HAVE_INLINE_ASM

#تعریف_کرو AV_READ_وقت read_وقت

ساکن اندرونی uint64_t read_وقت(خالی)
{

#اگر ARCH_LOONGARCH64
    uint64_t a, id;
    __asm__ متلون ( "rdtime.d  %0, %1" : "=r"(a), "=r"(id) :: );
    واپس a;
#ورنہ
    uint32_t a, id;
    __asm__ متلون ( "rdtimel.w  %0, %1" : "=r"(a), "=r"(id) :: );
    واپس (uint64_t)a;
#اگر_ختم
}

#اگر_ختم /* HAVE_INLINE_ASM */

#اگر_ختم /* AVUTIL_LOONGARCH_TIMER_H */
