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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <math.h>

#ଅନ୍ତର୍ଭାଵ "display.h"
#ଅନ୍ତର୍ଭାଵ "mathematics.h"

// fixed point to double
#define CONV_FP(x) ((ଦ୍ୱିଗୁଣ) (x)) / (1 << 16)

// double to fixed point
#define CONV_DB(x) (int32_t) ((x) * (1 << 16))

ଦ୍ୱିଗୁଣ av_display_rotation_get(ଅଚଳ int32_t matrix[9])
{
    ଦ୍ୱିଗୁଣ rotation, scale[2];

    scale[0] = hypot(CONV_FP(matrix[0]), CONV_FP(matrix[3]));
    scale[1] = hypot(CONV_FP(matrix[1]), CONV_FP(matrix[4]));

    ଯଦି (scale[0] == 0.0 || scale[1] == 0.0)
        ଫେରନ୍ତୁ NAN;

    rotation = atan2(CONV_FP(matrix[1]) / scale[1],
                     CONV_FP(matrix[0]) / scale[0]) * 180 / M_PI;

    ଫେରନ୍ତୁ -rotation;
}

ଶୂନ୍ୟ av_display_rotation_set(int32_t matrix[9], ଦ୍ୱିଗୁଣ angle)
{
    ଦ୍ୱିଗୁଣ radians = -angle * M_PI / 180.0f;
    ଦ୍ୱିଗୁଣ c = cos(radians);
    ଦ୍ୱିଗୁଣ s = sin(radians);

    memset(matrix, 0, 9 * ଆକାର(int32_t));

    matrix[0] = CONV_DB(c);
    matrix[1] = CONV_DB(-s);
    matrix[3] = CONV_DB(s);
    matrix[4] = CONV_DB(c);
    matrix[8] = 1 << 30;
}

ଶୂନ୍ୟ av_display_matrix_flip(int32_t matrix[9], ପୂର୍ଣ୍ଣସଂଖ୍ୟା hflip, ପୂର୍ଣ୍ଣସଂଖ୍ୟା vflip)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    ଯଦି (hflip || vflip)
        ପାଇଁ (i = 0; i < 9; i++)
            matrix[i] *= flip[i % 3];
}
