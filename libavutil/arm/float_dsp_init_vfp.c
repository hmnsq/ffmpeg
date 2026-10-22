/*
 * Copyright (c) 2008 Siarhei Siamashka <ssvb@users.sourceforge.net>
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

#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/float_dsp.h"
#അന്തര്ഭാവ "cpu.h"
#അന്തര്ഭാവ "float_dsp_arm.h"

ശൂന്യം ff_vector_fmul_vfp(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                        പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_window_vfp(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                               സ്ഥിരം ദശാംശം *src1, സ്ഥിരം ദശാംശം *win, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_reverse_vfp(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_butterflies_float_vfp(ദശാംശം *restrict v1, ദശാംശം *restrict v2, പൂർണ്ണസംഖ്യ len);

av_cold ശൂന്യം ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, പൂർണ്ണസംഖ്യ cpu_flags)
{
    എങ്കിൽ (have_vfp_vm(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_vfp;
        fdsp->vector_fmul_window = ff_vector_fmul_window_vfp;
    }
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vfp;
    എങ്കിൽ (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
