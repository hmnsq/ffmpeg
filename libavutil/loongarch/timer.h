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

#अगर_अघोषित AVUTIL_LOONGARCH_TIMER_H
#घोषणा AVUTIL_LOONGARCH_TIMER_H

#समावेश <stdint.h>
#समावेश "config.h"

#अगर HAVE_INLINE_ASM

#घोषणा AV_READ_TIME read_time

अटल अंतरभूत uint64_t read_time(व्योम)
{

#अगर ARCH_LOONGARCH64
    uint64_t a, id;
    __asm__ अस्थिर ( "rdtime.d  %0, %1" : "=r"(a), "=r"(id) :: );
    वापस a;
#अन्यथा
    uint32_t a, id;
    __asm__ अस्थिर ( "rdtimel.w  %0, %1" : "=r"(a), "=r"(id) :: );
    वापस (uint64_t)a;
#पूर्ण_अगर
}

#पूर्ण_अगर /* HAVE_INLINE_ASM */

#पूर्ण_अगर /* AVUTIL_LOONGARCH_TIMER_H */
