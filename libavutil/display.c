/*
 * Copyright (c) 2014 Vittorio Giovara <vittorio.giovara@gmail.com>
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
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <math.h>

#അന്തര്ഭാവ "display.h"
#അന്തര്ഭാവ "mathematics.h"

// fixed point to double
#define CONV_FP(x) ((ഇരട്ട) (x)) / (1 << 16)

// double to fixed point
#define CONV_DB(x) (int32_t) ((x) * (1 << 16))

ഇരട്ട av_display_rotation_get(സ്ഥിരം int32_t matrix[9])
{
    ഇരട്ട rotation, scale[2];

    scale[0] = hypot(CONV_FP(matrix[0]), CONV_FP(matrix[3]));
    scale[1] = hypot(CONV_FP(matrix[1]), CONV_FP(matrix[4]));

    എങ്കിൽ (scale[0] == 0.0 || scale[1] == 0.0)
        തിരികെ NAN;

    rotation = atan2(CONV_FP(matrix[1]) / scale[1],
                     CONV_FP(matrix[0]) / scale[0]) * 180 / M_PI;

    തിരികെ -rotation;
}

ശൂന്യം av_display_rotation_set(int32_t matrix[9], ഇരട്ട angle)
{
    ഇരട്ട radians = -angle * M_PI / 180.0f;
    ഇരട്ട c = cos(radians);
    ഇരട്ട s = sin(radians);

    memset(matrix, 0, 9 * വലുപ്പം(int32_t));

    matrix[0] = CONV_DB(c);
    matrix[1] = CONV_DB(-s);
    matrix[3] = CONV_DB(s);
    matrix[4] = CONV_DB(c);
    matrix[8] = 1 << 30;
}

ശൂന്യം av_display_matrix_flip(int32_t matrix[9], പൂർണ്ണസംഖ്യ hflip, പൂർണ്ണസംഖ്യ vflip)
{
    പൂർണ്ണസംഖ്യ i;
    സ്ഥിരം പൂർണ്ണസംഖ്യ flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    എങ്കിൽ (hflip || vflip)
        വേണ്ടി (i = 0; i < 9; i++)
            matrix[i] *= flip[i % 3];
}
