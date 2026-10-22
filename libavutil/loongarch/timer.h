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

#నిర్వచితం_కాకపోతే AVUTIL_LOONGARCH_TIMER_H
#నిర్వచించు AVUTIL_LOONGARCH_TIMER_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_INLINE_ASM

#నిర్వచించు AV_READ_సమయం read_సమయం

స్థిర అంతఃవరుస uint64_t read_సమయం(శూన్య)
{

#ఒకవేళ ARCH_LOONGARCH64
    uint64_t a, id;
    __asm__ అస్థిర ( "rdtime.d  %0, %1" : "=r"(a), "=r"(id) :: );
    తిరిగి a;
#లేకపోతే
    uint32_t a, id;
    __asm__ అస్థిర ( "rdtimel.w  %0, %1" : "=r"(a), "=r"(id) :: );
    తిరిగి (uint64_t)a;
#అయితే_ముగింపు
}

#అయితే_ముగింపు /* HAVE_INLINE_ASM */

#అయితే_ముగింపు /* AVUTIL_LOONGARCH_TIMER_H */
