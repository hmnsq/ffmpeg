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

#ifndef AVUTIL_RISCV_CPU_H
#define AVUTIL_RISCV_CPU_H

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ <stdbool.h>
#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ "libavutil/attributes_internal.h"
#અન્તર્ભાવ "libavutil/cpu.h"

#ifndef __riscv_zbb
બાહ્ય attribute_visibility_hidden bool ff_rv_zbb_supported;
#endif

સ્થિર અંતઃરેખ av_const bool ff_rv_zbb_support(શૂન્ય)
{
#ifndef __riscv_zbb
    પાછા ff_rv_zbb_supported;
#નહીંતર
    પાછા true;
#endif
}

#જો HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
સ્થિર અંતઃરેખ av_const size_t ff_get_rv_vlenb(શૂન્ય)
{
    size_t vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    પાછા vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
સ્થિર અંતઃરેખ av_const bool ff_rv_vlen_least(unsigned પૂર્ણાંક bits)
{
#ifdef __riscv_v_min_vlen
    જો (bits <= __riscv_v_min_vlen)
        પાછા true;
#નહીંતર
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    જો (bits <= 128)
        પાછા true;
#endif
    પાછા bits <= (8 * ff_get_rv_vlenb());
}
#endif
#endif /* HAVE_RVV */
