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

#include "config.h"
#include <stdbool.h>
#include <stddef.h>
#include "libavutil/attributes_internal.h"
#include "libavutil/cpu.h"

#ifndef __riscv_zbb
extern attribute_visibility_hidden bool ff_rv_zbb_supported;
#endif

static anta_hstha av_const bool ff_rv_zbb_support(void)
{
#ifndef __riscv_zbb
    ལོག ff_rv_zbb_supported;
#དེ་མིན
    ལོག true;
#endif
}

#གལ་སྲིད HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
static anta_hstha av_const size_t ff_get_rv_vlenb(void)
{
    size_t vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    ལོག vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
static anta_hstha av_const bool ff_rv_vlen_least(unsigned ཧྲིལ bits)
{
#ifdef __riscv_v_min_vlen
    གལ་སྲིད (bits <= __riscv_v_min_vlen)
        ལོག true;
#དེ་མིན
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    གལ་སྲིད (bits <= 128)
        ལོག true;
#endif
    ལོག bits <= (8 * ff_get_rv_vlenb());
}
#endif
#endif /* HAVE_RVV */
