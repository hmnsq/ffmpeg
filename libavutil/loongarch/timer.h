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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ "config.h"

#எனில் HAVE_INLINE_ASM

#define AV_READ_TIME read_time

நிலையான உள்வரி uint64_t read_time(வெறுமை)
{

#எனில் ARCH_LOONGARCH64
    uint64_t a, id;
    __asm__ நிலையற்ற ( "rdtime.d  %0, %1" : "=r"(a), "=r"(id) :: );
    திரும்பு a;
#இல்லையெனில்
    uint32_t a, id;
    __asm__ நிலையற்ற ( "rdtimel.w  %0, %1" : "=r"(a), "=r"(id) :: );
    திரும்பு (uint64_t)a;
#endif
}

#endif /* HAVE_INLINE_ASM */

#endif /* AVUTIL_LOONGARCH_TIMER_H */
