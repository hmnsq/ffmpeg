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

#समावेश <stdint.h>

#समावेश "libavutil/cpu_internal.h"

पूर्णांक ff_get_cpu_flags_wasm(व्योम)
{
    पूर्णांक flags = 0;
#अगर HAVE_SIMD128
    flags |= AV_CPU_FLAG_SIMD128;
#पूर्ण_अगर
    वापस flags;
}

माप_प्रकार ff_get_cpu_max_align_wasm(व्योम)
{
#अगर HAVE_SIMD128
    वापस 16;
#अन्यथा
    वापस 8;
#पूर्ण_अगर
}
