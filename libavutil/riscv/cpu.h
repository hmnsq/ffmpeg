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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব <stdbool.h>
#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব "libavutil/attributes_internal.h"
#অন্তর্ভাব "libavutil/cpu.h"

#ifndef __riscv_zbb
বাহ্য attribute_visibility_hidden bool ff_rv_zbb_supported;
#endif

স্থির অন্তঃস্থ av_const bool ff_rv_zbb_support(শূন্য)
{
#ifndef __riscv_zbb
    প্রত্যাগম ff_rv_zbb_supported;
#অন্যথা
    প্রত্যাগম true;
#endif
}

#যদি HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
স্থির অন্তঃস্থ av_const size_t ff_get_rv_vlenb(শূন্য)
{
    size_t vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    প্রত্যাগম vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
স্থির অন্তঃস্থ av_const bool ff_rv_vlen_least(unsigned পূর্ণাঙ্ক bits)
{
#ifdef __riscv_v_min_vlen
    যদি (bits <= __riscv_v_min_vlen)
        প্রত্যাগম true;
#অন্যথা
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    যদি (bits <= 128)
        প্রত্যাগম true;
#endif
    প্রত্যাগম bits <= (8 * ff_get_rv_vlenb());
}
#endif
#endif /* HAVE_RVV */
