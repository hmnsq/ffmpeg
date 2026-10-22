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

#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/fixed_dsp.h"

ശൂന്യം ff_vector_fmul_window_scaled_rvv(int16_t *dst, സ്ഥിരം int32_t *src0,
                                      സ്ഥിരം int32_t *src1, സ്ഥിരം int32_t *win,
                                      പൂർണ്ണസംഖ്യ len, uint8_t bits);
ശൂന്യം ff_vector_fmul_window_fixed_rvv(int32_t *dst, സ്ഥിരം int32_t *src0,
                                     സ്ഥിരം int32_t *src1, സ്ഥിരം int32_t *win,
                                     പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_fixed_rvv(പൂർണ്ണസംഖ്യ *dst, സ്ഥിരം പൂർണ്ണസംഖ്യ *src0, സ്ഥിരം പൂർണ്ണസംഖ്യ *src1,
                              പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_reverse_fixed_rvv(പൂർണ്ണസംഖ്യ *dst, സ്ഥിരം പൂർണ്ണസംഖ്യ *src0,
                                      സ്ഥിരം പൂർണ്ണസംഖ്യ *src1, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_add_fixed_rvv(പൂർണ്ണസംഖ്യ *dst, സ്ഥിരം പൂർണ്ണസംഖ്യ *src0, സ്ഥിരം പൂർണ്ണസംഖ്യ *src1,
                                  സ്ഥിരം പൂർണ്ണസംഖ്യ *src2, പൂർണ്ണസംഖ്യ len);
പൂർണ്ണസംഖ്യ ff_scalarproduct_fixed_rvv(സ്ഥിരം പൂർണ്ണസംഖ്യ *v1, സ്ഥിരം പൂർണ്ണസംഖ്യ *v2, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_butterflies_fixed_rvv(പൂർണ്ണസംഖ്യ *v1, പൂർണ്ണസംഖ്യ *v2, പൂർണ്ണസംഖ്യ len);

av_cold ശൂന്യം ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#എങ്കിൽ HAVE_RVV
    പൂർണ്ണസംഖ്യ flags = av_get_cpu_flags();

    എങ്കിൽ ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        എങ്കിൽ (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->vector_fmul_window_scaled = ff_vector_fmul_window_scaled_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_fixed_rvv;
        }

        fdsp->vector_fmul = ff_vector_fmul_fixed_rvv;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_fixed_rvv;
        fdsp->vector_fmul_add = ff_vector_fmul_add_fixed_rvv;

        എങ്കിൽ (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#endif
}
