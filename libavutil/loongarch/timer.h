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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_LOONGARCH_TIMER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_LOONGARCH_TIMER_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_INLINE_ASM

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_READ_ਸਮਾਂ read_ਸਮਾਂ

ਸਥਿਰ ਸਤਰਅੰਦਰ uint64_t read_ਸਮਾਂ(ਖਾਲੀ)
{

#ਜੇ ARCH_LOONGARCH64
    uint64_t a, id;
    __asm__ ਅਸਥਿਰ ( "rdtime.d  %0, %1" : "=r"(a), "=r"(id) :: );
    ਵਾਪਸ a;
#ਨਹੀਂਤਾਂ
    uint32_t a, id;
    __asm__ ਅਸਥਿਰ ( "rdtimel.w  %0, %1" : "=r"(a), "=r"(id) :: );
    ਵਾਪਸ (uint64_t)a;
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਅੰਤ /* HAVE_INLINE_ASM */

#ਜੇ_ਅੰਤ /* AVUTIL_LOONGARCH_TIMER_H */
