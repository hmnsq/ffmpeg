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

#جے_بنا_تعریف AVUTIL_LOONGARCH_TIMER_H
#تعریف_کرو AVUTIL_LOONGARCH_TIMER_H

#ضمن <stdint.h>
#ضمن "config.h"

#إذا HAVE_INLINE_ASM

#تعریف_کرو AV_READ_ویلا read_ویلا

ساكن مضمن uint64_t read_ویلا(فراغ)
{

#إذا ARCH_LOONGARCH64
    uint64_t a, id;
    __asm__ متطاير ( "rdtime.d  %0, %1" : "=r"(a), "=r"(id) :: );
    أرجع a;
#وإلا
    uint32_t a, id;
    __asm__ متطاير ( "rdtimel.w  %0, %1" : "=r"(a), "=r"(id) :: );
    أرجع (uint64_t)a;
#جے_انت
}

#جے_انت /* HAVE_INLINE_ASM */

#جے_انت /* AVUTIL_LOONGARCH_TIMER_H */
