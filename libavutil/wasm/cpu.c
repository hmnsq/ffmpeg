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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu_internal.h"

ਪੂਰਨ ff_get_cpu_flags_wasm(ਖਾਲੀ)
{
    ਪੂਰਨ flags = 0;
#ਜੇ HAVE_SIMD128
    flags |= AV_CPU_FLAG_SIMD128;
#ਜੇ_ਅੰਤ
    ਵਾਪਸ flags;
}

size_t ff_get_cpu_max_align_wasm(ਖਾਲੀ)
{
#ਜੇ HAVE_SIMD128
    ਵਾਪਸ 16;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ 8;
#ਜੇ_ਅੰਤ
}
