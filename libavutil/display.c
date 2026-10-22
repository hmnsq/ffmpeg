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

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <math.h>

#અન્તર્ભાવ "display.h"
#અન્તર્ભાવ "mathematics.h"

// fixed point to double
#define CONV_FP(x) ((દ્વિગુણ) (x)) / (1 << 16)

// double to fixed point
#define CONV_DB(x) (int32_t) ((x) * (1 << 16))

દ્વિગુણ av_display_rotation_get(અચલ int32_t matrix[9])
{
    દ્વિગુણ rotation, scale[2];

    scale[0] = hypot(CONV_FP(matrix[0]), CONV_FP(matrix[3]));
    scale[1] = hypot(CONV_FP(matrix[1]), CONV_FP(matrix[4]));

    જો (scale[0] == 0.0 || scale[1] == 0.0)
        પાછા NAN;

    rotation = atan2(CONV_FP(matrix[1]) / scale[1],
                     CONV_FP(matrix[0]) / scale[0]) * 180 / M_PI;

    પાછા -rotation;
}

શૂન્ય av_display_rotation_set(int32_t matrix[9], દ્વિગુણ angle)
{
    દ્વિગુણ radians = -angle * M_PI / 180.0f;
    દ્વિગુણ c = cos(radians);
    દ્વિગુણ s = sin(radians);

    memset(matrix, 0, 9 * કદ(int32_t));

    matrix[0] = CONV_DB(c);
    matrix[1] = CONV_DB(-s);
    matrix[3] = CONV_DB(s);
    matrix[4] = CONV_DB(c);
    matrix[8] = 1 << 30;
}

શૂન્ય av_display_matrix_flip(int32_t matrix[9], પૂર્ણાંક hflip, પૂર્ણાંક vflip)
{
    પૂર્ણાંક i;
    અચલ પૂર્ણાંક flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    જો (hflip || vflip)
        માટે (i = 0; i < 9; i++)
            matrix[i] *= flip[i % 3];
}
