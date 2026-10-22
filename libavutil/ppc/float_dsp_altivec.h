/*
 * Copyright (c) 2006 Luca Barbato <lu_zero@gentoo.org>
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

#ifndef AVUTIL_PPC_FLOAT_DSP_ALTIVEC_H
#define AVUTIL_PPC_FLOAT_DSP_ALTIVEC_H

ശൂന്യം ff_vector_fmul_altivec(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                            സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_window_altivec(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                   സ്ഥിരം ദശാംശം *src1, സ്ഥിരം ദശാംശം *win,
                                   പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_add_altivec(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                സ്ഥിരം ദശാംശം *src1, സ്ഥിരം ദശാംശം *src2,
                                പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_reverse_altivec(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                    സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len);

#endif /* AVUTIL_PPC_FLOAT_DSP_ALTIVEC_H */
