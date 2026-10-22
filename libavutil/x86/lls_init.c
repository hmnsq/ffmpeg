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

#समावेश "libavutil/attributes.h"
#समावेश "libavutil/lls.h"
#समावेश "libavutil/x86/cpu.h"

व्योम ff_update_lls_sse2(LLSModel *m, स्थिर द्विगुन *var);
व्योम ff_update_lls_avx(LLSModel *m, स्थिर द्विगुन *var);
व्योम ff_update_lls_fma3(LLSModel *m, स्थिर द्विगुन *var);
द्विगुन ff_evaluate_lls_sse2(LLSModel *m, स्थिर द्विगुन *var, पूर्णांक order);

av_cold व्योम ff_init_lls_x86(LLSModel *m)
{
    पूर्णांक cpu_flags = av_get_cpu_flags();
    अगर (EXTERNAL_SSE2(cpu_flags)) {
        m->update_lls = ff_update_lls_sse2;
        अगर (m->indep_गिनती >= 4)
            m->evaluate_lls = ff_evaluate_lls_sse2;
    }
    अगर (EXTERNAL_AVX_FAST(cpu_flags)) {
        m->update_lls = ff_update_lls_avx;
    }
    अगर (EXTERNAL_FMA3_FAST(cpu_flags)) {
        m->update_lls = ff_update_lls_fma3;
    }
}
