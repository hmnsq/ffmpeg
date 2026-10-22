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

#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/lls.h"
#ಅನ್ತರ್ಭಾವ "libavutil/x86/cpu.h"

ಶೂನ್ಯ ff_update_lls_sse2(LLSModel *m, ಧ್ರುವ ದ್ವಿಗುಣ *var);
ಶೂನ್ಯ ff_update_lls_avx(LLSModel *m, ಧ್ರುವ ದ್ವಿಗುಣ *var);
ಶೂನ್ಯ ff_update_lls_fma3(LLSModel *m, ಧ್ರುವ ದ್ವಿಗುಣ *var);
ದ್ವಿಗುಣ ff_evaluate_lls_sse2(LLSModel *m, ಧ್ರುವ ದ್ವಿಗುಣ *var, ಪೂರ್ಣಾಙ್ಕ order);

av_cold ಶೂನ್ಯ ff_init_lls_x86(LLSModel *m)
{
    ಪೂರ್ಣಾಙ್ಕ cpu_flags = av_get_cpu_flags();
    ಯದಿ (EXTERNAL_SSE2(cpu_flags)) {
        m->update_lls = ff_update_lls_sse2;
        ಯದಿ (m->indep_ಎಣಿಕೆ >= 4)
            m->evaluate_lls = ff_evaluate_lls_sse2;
    }
    ಯದಿ (EXTERNAL_AVX_FAST(cpu_flags)) {
        m->update_lls = ff_update_lls_avx;
    }
    ಯದಿ (EXTERNAL_FMA3_FAST(cpu_flags)) {
        m->update_lls = ff_update_lls_fma3;
    }
}
