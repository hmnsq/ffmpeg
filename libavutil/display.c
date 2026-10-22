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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <math.h>

#अन्तर्भाव "display.h"
#अन्तर्भाव "mathematics.h"

// fixed point to double
#परिभाषय CONV_FP(x) ((द्विगुण) (x)) / (1 << 16)

// double to fixed point
#परिभाषय CONV_DB(x) (int32_t) ((x) * (1 << 16))

द्विगुण av_display_rotation_get(ध्रुव int32_t matrix[9])
{
    द्विगुण rotation, scale[2];

    scale[0] = hypot(CONV_FP(matrix[0]), CONV_FP(matrix[3]));
    scale[1] = hypot(CONV_FP(matrix[1]), CONV_FP(matrix[4]));

    यदि (scale[0] == 0.0 || scale[1] == 0.0)
        प्रत्यागम NAN;

    rotation = atan2(CONV_FP(matrix[1]) / scale[1],
                     CONV_FP(matrix[0]) / scale[0]) * 180 / M_PI;

    प्रत्यागम -rotation;
}

शून्य av_display_rotation_समुच्चयः(int32_t matrix[9], द्विगुण angle)
{
    द्विगुण radians = -angle * M_PI / 180.0f;
    द्विगुण c = कोटिज्या(radians);
    द्विगुण s = ज्या(radians);

    स्मृतिं_पूरय(matrix, 0, 9 * परिमाण(int32_t));

    matrix[0] = CONV_DB(c);
    matrix[1] = CONV_DB(-s);
    matrix[3] = CONV_DB(s);
    matrix[4] = CONV_DB(c);
    matrix[8] = 1 << 30;
}

शून्य av_display_matrix_flip(int32_t matrix[9], पूर्णाङ्क hflip, पूर्णाङ्क vflip)
{
    पूर्णाङ्क i;
    ध्रुव पूर्णाङ्क flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    यदि (hflip || vflip)
        प्रति (i = 0; i < 9; i++)
            matrix[i] *= flip[i % 3];
}
