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

#ಅನ್ತರ್ಭಾವ "float_dsp.h"

ದಶಮಾಂಶ ff_scalarproduct_float_c(ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v2, ಪೂರ್ಣಾಂಕ len)
{
    ದಶಮಾಂಶ p = 0.0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++)
        p += v1[i] * v2[i];

    ಹಿಂತಿರುಗಿ p;
}
