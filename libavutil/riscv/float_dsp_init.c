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

#ଅନ୍ତର୍ଭାଵ <stdint.h>

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/float_dsp.h"

ଶୂନ୍ୟ ff_vector_fmul_rvv(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmac_scalar_rvv(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_scalar_rvv(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_window_rvv(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                ଅଚଳ ଦଶମିକ *src1, ଅଚଳ ଦଶମିକ *win, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_add_rvv(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                             ଅଚଳ ଦଶମିକ *src2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_reverse_rvv(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                 ଅଚଳ ଦଶମିକ *src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_butterflies_float_rvv(ଦଶମିକ *v1, ଦଶମିକ *v2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଦଶମିକ ff_scalarproduct_float_rvv(ଅଚଳ ଦଶମିକ *v1, ଅଚଳ ଦଶମିକ *v2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_dmul_rvv(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src0, ଅଚଳ ଦ୍ୱିଗୁଣ *src1,
                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_dmac_scalar_rvv(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src, ଦ୍ୱିଗୁଣ mul,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_dmul_scalar_rvv(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src, ଦ୍ୱିଗୁଣ mul,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଦ୍ୱିଗୁଣ ff_scalarproduct_double_rvv(ଅଚଳ ଦ୍ୱିଗୁଣ *v1, ଅଚଳ ଦ୍ୱିଗୁଣ *v2,
                                   size_t len);

av_cold ଶୂନ୍ୟ ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#ଯଦି HAVE_RVV
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = av_get_cpu_flags();

    ଯଦି (flags & AV_CPU_FLAG_RVB) {
        ଯଦି (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->vector_fmul = ff_vector_fmul_rvv;
            fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_rvv;
            fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_rvv;
            fdsp->vector_fmul_add = ff_vector_fmul_add_rvv;
            fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        ଯଦି (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->vector_dmul = ff_vector_dmul_rvv;
            fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_rvv;
            fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#endif
}
