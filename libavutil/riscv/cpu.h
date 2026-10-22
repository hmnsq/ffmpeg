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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ <stdbool.h>
#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ "libavutil/attributes_internal.h"
#അന്തര്ഭാവ "libavutil/cpu.h"

#ifndef __riscv_zbb
ബാഹ്യ attribute_visibility_hidden bool ff_rv_zbb_supported;
#endif

സ്ഥിതം വരിയിൽ av_const bool ff_rv_zbb_support(ശൂന്യം)
{
#ifndef __riscv_zbb
    തിരികെ ff_rv_zbb_supported;
#അല്ലെങ്കിൽ
    തിരികെ true;
#endif
}

#എങ്കിൽ HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
സ്ഥിതം വരിയിൽ av_const size_t ff_get_rv_vlenb(ശൂന്യം)
{
    size_t vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    തിരികെ vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
സ്ഥിതം വരിയിൽ av_const bool ff_rv_vlen_least(unsigned പൂർണ്ണസംഖ്യ bits)
{
#ifdef __riscv_v_min_vlen
    എങ്കിൽ (bits <= __riscv_v_min_vlen)
        തിരികെ true;
#അല്ലെങ്കിൽ
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    എങ്കിൽ (bits <= 128)
        തിരികെ true;
#endif
    തിരികെ bits <= (8 * ff_get_rv_vlenb());
}
#endif
#endif /* HAVE_RVV */
