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

#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/fixed_dsp.h"
#அந்தர்பாவ "cpu.h"

வெறுமை ff_butterflies_fixed_sse2(முழு *restrict src0, முழு *restrict src1, முழு len);

av_cold வெறுமை ff_fixed_dsp_init_x86(AVFixedDSPContext *fdsp)
{
    முழு cpu_flags = av_get_cpu_flags();

    எனில் (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->butterflies_fixed = ff_butterflies_fixed_sse2;
    }
}
