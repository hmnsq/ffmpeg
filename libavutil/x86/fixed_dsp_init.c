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

#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/fixed_dsp.h"
#అన్తర్భావ "cpu.h"

శూన్య ff_butterflies_fixed_sse2(పూర్ణాంకం *పరిమిత src0, పూర్ణాంకం *పరిమిత src1, పూర్ణాంకం len);

av_cold శూన్య ff_fixed_dsp_init_x86(AVFixedDSPContext *fdsp)
{
    పూర్ణాంకం cpu_flags = av_get_cpu_flags();

    ఒకవేళ (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->butterflies_fixed = ff_butterflies_fixed_sse2;
    }
}
