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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_RISCV_CPU_H
#وصف_ڪريو AVUTIL_RISCV_CPU_H

#ضمن "config.h"
#ضمن <stdbool.h>
#ضمن <stddef.h>
#ضمن "libavutil/attributes_internal.h"
#ضمن "libavutil/cpu.h"

#جيڪڏهن_وصف_نه_ٿيل __riscv_zbb
خارجي attribute_visibility_hidden bool ff_rv_zbb_supported;
#جيڪڏهن_پورو

ساكن مضمن av_const bool ff_rv_zbb_support(فراغ)
{
#جيڪڏهن_وصف_نه_ٿيل __riscv_zbb
    أرجع ff_rv_zbb_supported;
#وإلا
    أرجع true;
#جيڪڏهن_پورو
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
ساكن مضمن av_const bool ff_rv_vlen_گهٽ_کان_گهٽ(بنانشان صحيح بٽ)
{
#جيڪڏهن_وصف_ٿيل __riscv_v_min_vlen
    إذا (بٽ <= __riscv_v_min_vlen)
        أرجع true;
#وإلا
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    إذا (بٽ <= 128)
        أرجع true;
#جيڪڏهن_پورو
    أرجع بٽ <= (8 * ff_get_rv_vlenb());
}
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* HAVE_RVV */
