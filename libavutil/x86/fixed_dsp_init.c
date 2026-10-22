/*
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

#समावेश "libavutil/attributes.h"
#समावेश "libavutil/cpu.h"
#समावेश "libavutil/fixed_dsp.h"
#समावेश "cpu.h"

व्योम ff_butterflies_fixed_sse2(पूर्णांक *restrict src0, पूर्णांक *restrict src1, पूर्णांक len);

av_cold व्योम ff_fixed_dsp_init_x86(AVFixedDSPContext *fdsp)
{
    पूर्णांक cpu_flags = av_get_cpu_flags();

    अगर (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->butterflies_fixed = ff_butterflies_fixed_sse2;
    }
}
