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

#समावेश <stdint.h>
#समावेश <string.h>
#समावेश <math.h>

#समावेश "display.h"
#समावेश "mathematics.h"

// fixed point to double
#घोषणा CONV_FP(x) ((द्विगुन) (x)) / (1 << 16)

// double to fixed point
#घोषणा CONV_DB(x) (int32_t) ((x) * (1 << 16))

द्विगुन av_display_rotation_get(स्थिर int32_t matrix[9])
{
    द्विगुन rotation, scale[2];

    scale[0] = hypot(CONV_FP(matrix[0]), CONV_FP(matrix[3]));
    scale[1] = hypot(CONV_FP(matrix[1]), CONV_FP(matrix[4]));

    अगर (scale[0] == 0.0 || scale[1] == 0.0)
        वापस न_अंक;

    rotation = atan2(CONV_FP(matrix[1]) / scale[1],
                     CONV_FP(matrix[0]) / scale[0]) * 180 / M_PI;

    वापस -rotation;
}

व्योम av_display_rotation_set(int32_t matrix[9], द्विगुन angle)
{
    द्विगुन radians = -angle * M_PI / 180.0f;
    द्विगुन c = cos(radians);
    द्विगुन s = sin(radians);

    स_रखो(matrix, 0, 9 * माप(int32_t));

    matrix[0] = CONV_DB(c);
    matrix[1] = CONV_DB(-s);
    matrix[3] = CONV_DB(s);
    matrix[4] = CONV_DB(c);
    matrix[8] = 1 << 30;
}

व्योम av_display_matrix_flip(int32_t matrix[9], पूर्णांक hflip, पूर्णांक vflip)
{
    पूर्णांक i;
    स्थिर पूर्णांक flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    अगर (hflip || vflip)
        क्रम (i = 0; i < 9; i++)
            matrix[i] *= flip[i % 3];
}
