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

#اگر_تعریف_نشده AVUTIL_RISCV_CPU_H
#تعریف_کن AVUTIL_RISCV_CPU_H

#ضمن "config.h"
#ضمن <stdbool.h>
#ضمن <stddef.h>
#ضمن "libavutil/attributes_internal.h"
#ضمن "libavutil/cpu.h"

#اگر_تعریف_نشده __riscv_zbb
خارجي attribute_visibility_hidden bool ff_rv_zbb_supported;
#پایان_اگر

ساكن مضمن av_const bool ff_rv_zbb_support(فراغ)
{
#اگر_تعریف_نشده __riscv_zbb
    أرجع ff_rv_zbb_supported;
#وإلا
    أرجع true;
#پایان_اگر
}

#إذا HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
ساكن مضمن av_const size_t ff_get_rv_vlenb(فراغ)
{
    size_t vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    أرجع vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
ساكن مضمن av_const bool ff_rv_vlen_کمترین(بیعلامت صحيح بیتها)
{
#اگر_تعریف_شده __riscv_v_min_vlen
    إذا (بیتها <= __riscv_v_min_vlen)
        أرجع true;
#وإلا
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    إذا (بیتها <= 128)
        أرجع true;
#پایان_اگر
    أرجع بیتها <= (8 * ff_get_rv_vlenb());
}
#پایان_اگر
#پایان_اگر /* HAVE_RVV */
