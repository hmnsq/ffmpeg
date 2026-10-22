/*
 * linear least squares model
 *
 * Copyright (c) 2013 Loren Merritt
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

#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/lls.h"
#అన్తర్భావ "libavutil/x86/cpu.h"

శూన్య ff_update_lls_sse2(LLSModel *m, స్థిరరాశి ద్విగుణ *var);
శూన్య ff_update_lls_avx(LLSModel *m, స్థిరరాశి ద్విగుణ *var);
శూన్య ff_update_lls_fma3(LLSModel *m, స్థిరరాశి ద్విగుణ *var);
ద్విగుణ ff_evaluate_lls_sse2(LLSModel *m, స్థిరరాశి ద్విగుణ *var, పూర్ణాంకం క్రమం);

av_cold శూన్య ff_init_lls_x86(LLSModel *m)
{
    పూర్ణాంకం cpu_flags = av_get_cpu_flags();
    ఒకవేళ (EXTERNAL_SSE2(cpu_flags)) {
        m->update_lls = ff_update_lls_sse2;
        ఒకవేళ (m->indep_లెక్క >= 4)
            m->evaluate_lls = ff_evaluate_lls_sse2;
    }
    ఒకవేళ (EXTERNAL_AVX_FAST(cpu_flags)) {
        m->update_lls = ff_update_lls_avx;
    }
    ఒకవేళ (EXTERNAL_FMA3_FAST(cpu_flags)) {
        m->update_lls = ff_update_lls_fma3;
    }
}
