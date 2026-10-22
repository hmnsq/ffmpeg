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

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "libavutil/cpu_internal.h"

ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_wasm(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ flags = 0;
#ಯದಿ HAVE_SIMD128
    flags |= AV_CPU_FLAG_SIMD128;
#endif
    ಪ್ರತ್ಯಾಗಮ flags;
}

size_t ff_get_cpu_max_align_wasm(ಶೂನ್ಯ)
{
#ಯದಿ HAVE_SIMD128
    ಪ್ರತ್ಯಾಗಮ 16;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ 8;
#endif
}
