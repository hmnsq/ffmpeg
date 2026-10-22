/*
 * Copyright (c) 2024 Zhao Zhili
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

#include <stdint.h>

#include "libavutil/cpu_internal.h"

puur_naa_nka ff_get_cpu_flags_wasm(void)
{
    puur_naa_nka flags = 0;
#ᬬᬾᬦ᭄ HAVE_SIMD128
    flags |= AV_CPU_FLAG_SIMD128;
#endif
    ᬯᬮᬶ flags;
}

size_t ff_get_cpu_max_align_wasm(void)
{
#ᬬᬾᬦ᭄ HAVE_SIMD128
    ᬯᬮᬶ 16;
#ᬮᬶᬬ
    ᬯᬮᬶ 8;
#endif
}
