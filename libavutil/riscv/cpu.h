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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_RISCV_CPU_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_RISCV_CPU_H

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <stdbool.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __riscv_zbb
ਬਾਹਰੀ attribute_visibility_hidden bool ff_rv_zbb_supported;
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਸਤਰਅੰਦਰ av_const bool ff_rv_zbb_support(ਖਾਲੀ)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __riscv_zbb
    ਵਾਪਸ ff_rv_zbb_supported;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ true;
#ਜੇ_ਅੰਤ
}

#ਜੇ HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const size_t ff_get_rv_vlenb(ਖਾਲੀ)
{
    size_t vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    ਵਾਪਸ vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const bool ff_rv_vlen_ਘੱਟ_ਤੋਂ_ਘੱਟ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਿੱਟ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __riscv_v_min_vlen
    ਜੇ (ਬਿੱਟ <= __riscv_v_min_vlen)
        ਵਾਪਸ true;
#ਨਹੀਂਤਾਂ
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    ਜੇ (ਬਿੱਟ <= 128)
        ਵਾਪਸ true;
#ਜੇ_ਅੰਤ
    ਵਾਪਸ ਬਿੱਟ <= (8 * ff_get_rv_vlenb());
}
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* HAVE_RVV */
