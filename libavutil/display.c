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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <math.h>

#ಅನ್ತರ್ಭಾವ "display.h"
#ಅನ್ತರ್ಭಾವ "mathematics.h"

// fixed point to double
#define CONV_FP(x) ((ದ್ವಿಗುಣ) (x)) / (1 << 16)

// double to fixed point
#define CONV_DB(x) (int32_t) ((x) * (1 << 16))

ದ್ವಿಗುಣ av_display_rotation_get(ಧ್ರುವ int32_t matrix[9])
{
    ದ್ವಿಗುಣ rotation, scale[2];

    scale[0] = hypot(CONV_FP(matrix[0]), CONV_FP(matrix[3]));
    scale[1] = hypot(CONV_FP(matrix[1]), CONV_FP(matrix[4]));

    ಯದಿ (scale[0] == 0.0 || scale[1] == 0.0)
        ಪ್ರತ್ಯಾಗಮ NAN;

    rotation = atan2(CONV_FP(matrix[1]) / scale[1],
                     CONV_FP(matrix[0]) / scale[0]) * 180 / M_PI;

    ಪ್ರತ್ಯಾಗಮ -rotation;
}

ಶೂನ್ಯ av_display_rotation_set(int32_t matrix[9], ದ್ವಿಗುಣ angle)
{
    ದ್ವಿಗುಣ radians = -angle * M_PI / 180.0f;
    ದ್ವಿಗುಣ c = cos(radians);
    ದ್ವಿಗುಣ s = sin(radians);

    memset(matrix, 0, 9 * ಪರಿಮಾಣ(int32_t));

    matrix[0] = CONV_DB(c);
    matrix[1] = CONV_DB(-s);
    matrix[3] = CONV_DB(s);
    matrix[4] = CONV_DB(c);
    matrix[8] = 1 << 30;
}

ಶೂನ್ಯ av_display_matrix_flip(int32_t matrix[9], ಪೂರ್ಣಾಙ್ಕ hflip, ಪೂರ್ಣಾಙ್ಕ vflip)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    ಯದಿ (hflip || vflip)
        ಪ್ರತಿ (i = 0; i < 9; i++)
            matrix[i] *= flip[i % 3];
}
