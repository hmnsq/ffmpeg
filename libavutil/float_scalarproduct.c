/*
 * Copyright 2005 Balatoni Denes
 * Copyright 2006 Loren Merritt
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

#അന്തര്ഭാവ "float_dsp.h"

ദശാംശം ff_scalarproduct_float_c(സ്ഥിരം ദശാംശം *v1, സ്ഥിരം ദശാംശം *v2, പൂർണ്ണസംഖ്യ len)
{
    ദശാംശം p = 0.0;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < len; i++)
        p += v1[i] * v2[i];

    തിരികെ p;
}
