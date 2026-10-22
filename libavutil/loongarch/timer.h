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

#ifndef AVUTIL_LOONGARCH_TIMER_H
#define AVUTIL_LOONGARCH_TIMER_H

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব "config.h"

#যদি HAVE_INLINE_ASM

#define AV_READ_TIME read_time

স্থির অন্তঃস্থ uint64_t read_time(শূন্য)
{

#যদি ARCH_LOONGARCH64
    uint64_t a, id;
    __asm__ চঞ্চল ( "rdtime.d  %0, %1" : "=r"(a), "=r"(id) :: );
    প্রত্যাগম a;
#অন্যথা
    uint32_t a, id;
    __asm__ চঞ্চল ( "rdtimel.w  %0, %1" : "=r"(a), "=r"(id) :: );
    প্রত্যাগম (uint64_t)a;
#endif
}

#endif /* HAVE_INLINE_ASM */

#endif /* AVUTIL_LOONGARCH_TIMER_H */
