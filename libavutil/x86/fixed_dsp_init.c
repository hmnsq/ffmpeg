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

#شامل "libavutil/attributes.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/fixed_dsp.h"
#شامل "cpu.h"

خالی ff_butterflies_fixed_sse2(صحیح *محدود src0, صحیح *محدود src1, صحیح len);

av_cold خالی ff_fixed_dsp_init_x86(AVFixedDSPContext *fdsp)
{
    صحیح cpu_flags = av_get_cpu_flags();

    اگر (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->butterflies_fixed = ff_butterflies_fixed_sse2;
    }
}
