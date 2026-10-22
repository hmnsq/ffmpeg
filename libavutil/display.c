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

#شامل <stdint.h>
#شامل <string.h>
#شامل <math.h>

#شامل "display.h"
#شامل "mathematics.h"

// fixed point to double
#define CONV_FP(x) ((دوگانه) (x)) / (1 << 16)

// double to fixed point
#define CONV_DB(x) (int32_t) ((x) * (1 << 16))

دوگانه av_display_rotation_get(ثابت int32_t matrix[9])
{
    دوگانه rotation, scale[2];

    scale[0] = hypot(CONV_FP(matrix[0]), CONV_FP(matrix[3]));
    scale[1] = hypot(CONV_FP(matrix[1]), CONV_FP(matrix[4]));

    اگر (scale[0] == 0.0 || scale[1] == 0.0)
        بازگشت NAN;

    rotation = atan2(CONV_FP(matrix[1]) / scale[1],
                     CONV_FP(matrix[0]) / scale[0]) * 180 / M_PI;

    بازگشت -rotation;
}

تهی av_display_rotation_set(int32_t matrix[9], دوگانه angle)
{
    دوگانه radians = -angle * M_PI / 180.0f;
    دوگانه c = cos(radians);
    دوگانه s = sin(radians);

    memset(matrix, 0, 9 * اندازه(int32_t));

    matrix[0] = CONV_DB(c);
    matrix[1] = CONV_DB(-s);
    matrix[3] = CONV_DB(s);
    matrix[4] = CONV_DB(c);
    matrix[8] = 1 << 30;
}

تهی av_display_matrix_flip(int32_t matrix[9], صحیح hflip, صحیح vflip)
{
    صحیح i;
    ثابت صحیح flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    اگر (hflip || vflip)
        برای (i = 0; i < 9; i++)
            matrix[i] *= flip[i % 3];
}
