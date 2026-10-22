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

#నిర్వచితం_కాకపోతే AVUTIL_RISCV_CPU_H
#నిర్వచించు AVUTIL_RISCV_CPU_H

#అన్తర్భావ "config.h"
#అన్తర్భావ <stdbool.h>
#అన్తర్భావ <stddef.h>
#అన్తర్భావ "libavutil/attributes_internal.h"
#అన్తర్భావ "libavutil/cpu.h"

#నిర్వచితం_కాకపోతే __riscv_zbb
బాహ్య attribute_visibility_hidden bool ff_rv_zbb_supported;
#అయితే_ముగింపు

స్థిర అంతఃవరుస av_const bool ff_rv_zbb_support(శూన్య)
{
#నిర్వచితం_కాకపోతే __riscv_zbb
    తిరిగి ff_rv_zbb_supported;
#లేకపోతే
    తిరిగి true;
#అయితే_ముగింపు
}

#ఒకవేళ HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
స్థిర అంతఃవరుస av_const size_t ff_get_rv_vlenb(శూన్య)
{
    size_t vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    తిరిగి vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
స్థిర అంతఃవరుస av_const bool ff_rv_vlen_కనిష్ఠ(గుర్తులేని పూర్ణాంకం బిట్లు)
{
#నిర్వచితమైతే __riscv_v_min_vlen
    ఒకవేళ (బిట్లు <= __riscv_v_min_vlen)
        తిరిగి true;
#లేకపోతే
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    ఒకవేళ (బిట్లు <= 128)
        తిరిగి true;
#అయితే_ముగింపు
    తిరిగి బిట్లు <= (8 * ff_get_rv_vlenb());
}
#అయితే_ముగింపు
#అయితే_ముగింపు /* HAVE_RVV */
