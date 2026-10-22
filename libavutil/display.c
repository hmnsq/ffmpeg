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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <math.h>

#অন্তর্ভাব "display.h"
#অন্তর্ভাব "mathematics.h"

// fixed point to double
#define CONV_FP(x) ((দ্বিগুণ) (x)) / (1 << 16)

// double to fixed point
#define CONV_DB(x) (int32_t) ((x) * (1 << 16))

দ্বিগুণ av_display_rotation_get(ধ্রুবক int32_t matrix[9])
{
    দ্বিগুণ rotation, scale[2];

    scale[0] = hypot(CONV_FP(matrix[0]), CONV_FP(matrix[3]));
    scale[1] = hypot(CONV_FP(matrix[1]), CONV_FP(matrix[4]));

    যদি (scale[0] == 0.0 || scale[1] == 0.0)
        ফেরত NAN;

    rotation = atan2(CONV_FP(matrix[1]) / scale[1],
                     CONV_FP(matrix[0]) / scale[0]) * 180 / M_PI;

    ফেরত -rotation;
}

শূন্য av_display_rotation_set(int32_t matrix[9], দ্বিগুণ angle)
{
    দ্বিগুণ radians = -angle * M_PI / 180.0f;
    দ্বিগুণ c = cos(radians);
    দ্বিগুণ s = sin(radians);

    memset(matrix, 0, 9 * আকার(int32_t));

    matrix[0] = CONV_DB(c);
    matrix[1] = CONV_DB(-s);
    matrix[3] = CONV_DB(s);
    matrix[4] = CONV_DB(c);
    matrix[8] = 1 << 30;
}

শূন্য av_display_matrix_flip(int32_t matrix[9], পূর্ণসংখ্যা hflip, পূর্ণসংখ্যা vflip)
{
    পূর্ণসংখ্যা i;
    ধ্রুবক পূর্ণসংখ্যা flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    যদি (hflip || vflip)
        জন্য (i = 0; i < 9; i++)
            matrix[i] *= flip[i % 3];
}
