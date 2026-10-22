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

#ضمن <stdint.h>
#ضمن <string.h>
#ضمن <math.h>

#ضمن "display.h"
#ضمن "mathematics.h"

// fixed point to double
#تعریف_کړه CONV_FP(x) ((مزدوج) (x)) / (1 << 16)

// double to fixed point
#تعریف_کړه CONV_DB(x) (int32_t) ((x) * (1 << 16))

مزدوج av_display_rotation_get(ثابت int32_t ماتریکس[9])
{
    مزدوج rotation, scale[2];

    scale[0] = hypot(CONV_FP(ماتریکس[0]), CONV_FP(ماتریکس[3]));
    scale[1] = hypot(CONV_FP(ماتریکس[1]), CONV_FP(ماتریکس[4]));

    إذا (scale[0] == 0.0 || scale[1] == 0.0)
        أرجع NAN;

    rotation = atan2(CONV_FP(ماتریکس[1]) / scale[1],
                     CONV_FP(ماتریکس[0]) / scale[0]) * 180 / M_PI;

    أرجع -rotation;
}

فراغ av_display_rotation_سېټ(int32_t ماتریکس[9], مزدوج angle)
{
    مزدوج radians = -angle * M_PI / 180.0f;
    مزدوج c = کوساین(radians);
    مزدوج s = ساین(radians);

    memset(ماتریکس, 0, 9 * حجم(int32_t));

    ماتریکس[0] = CONV_DB(c);
    ماتریکس[1] = CONV_DB(-s);
    ماتریکس[3] = CONV_DB(s);
    ماتریکس[4] = CONV_DB(c);
    ماتریکس[8] = 1 << 30;
}

فراغ av_display_ماتریکس_flip(int32_t ماتریکس[9], صحيح hflip, صحيح vflip)
{
    صحيح i;
    ثابت صحيح flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    إذا (hflip || vflip)
        لكل (i = 0; i < 9; i++)
            ماتریکس[i] *= flip[i % 3];
}
