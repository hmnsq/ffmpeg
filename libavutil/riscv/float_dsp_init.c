/*
 * Copyright © 2022 Rémi Denis-Courmont.
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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/float_dsp.h"

ಶೂನ್ಯ ff_vector_fmul_rvv(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                         ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmac_scalar_rvv(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                                ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_scalar_rvv(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                                ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_window_rvv(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                                ಧ್ರುವ ಭಿನ್ನ *src1, ಧ್ರುವ ಭಿನ್ನ *win, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_add_rvv(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                             ಧ್ರುವ ಭಿನ್ನ *src2, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_reverse_rvv(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                                 ಧ್ರುವ ಭಿನ್ನ *src1, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_butterflies_float_rvv(ಭಿನ್ನ *v1, ಭಿನ್ನ *v2, ಪೂರ್ಣಾಙ್ಕ len);
ಭಿನ್ನ ff_scalarproduct_float_rvv(ಧ್ರುವ ಭಿನ್ನ *v1, ಧ್ರುವ ಭಿನ್ನ *v2, ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_dmul_rvv(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src0, ಧ್ರುವ ದ್ವಿಗುಣ *src1,
                         ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_dmac_scalar_rvv(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_dmul_scalar_rvv(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                ಪೂರ್ಣಾಙ್ಕ len);
ದ್ವಿಗುಣ ff_scalarproduct_double_rvv(ಧ್ರುವ ದ್ವಿಗುಣ *v1, ಧ್ರುವ ದ್ವಿಗುಣ *v2,
                                   size_t len);

av_cold ಶೂನ್ಯ ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#ಯದಿ HAVE_RVV
    ಪೂರ್ಣಾಙ್ಕ flags = av_get_cpu_flags();

    ಯದಿ (flags & AV_CPU_FLAG_RVB) {
        ಯದಿ (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->vector_fmul = ff_vector_fmul_rvv;
            fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_rvv;
            fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_rvv;
            fdsp->vector_fmul_add = ff_vector_fmul_add_rvv;
            fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        ಯದಿ (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->vector_dmul = ff_vector_dmul_rvv;
            fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_rvv;
            fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#endif
}
