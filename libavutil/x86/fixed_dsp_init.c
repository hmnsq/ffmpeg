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

#અન્તર્ભાવ "libavutil/attributes.h"
#અન્તર્ભાવ "libavutil/cpu.h"
#અન્તર્ભાવ "libavutil/fixed_dsp.h"
#અન્તર્ભાવ "cpu.h"

શૂન્ય ff_butterflies_fixed_sse2(પૂર્ણાંક *restrict src0, પૂર્ણાંક *restrict src1, પૂર્ણાંક len);

av_cold શૂન્ય ff_fixed_dsp_init_x86(AVFixedDSPContext *fdsp)
{
    પૂર્ણાંક cpu_flags = av_get_cpu_flags();

    જો (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->butterflies_fixed = ff_butterflies_fixed_sse2;
    }
}
