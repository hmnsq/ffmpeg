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
#تعریف_کرو CONV_FP(x) ((مزدوج) (x)) / (1 << 16)

// double to fixed point
#تعریف_کرو CONV_DB(x) (int32_t) ((x) * (1 << 16))

مزدوج av_display_rotation_get(ثابت int32_t میٹرکس[9])
{
    مزدوج rotation, scale[2];

    scale[0] = hypot(CONV_FP(میٹرکس[0]), CONV_FP(میٹرکس[3]));
    scale[1] = hypot(CONV_FP(میٹرکس[1]), CONV_FP(میٹرکس[4]));

    إذا (scale[0] == 0.0 || scale[1] == 0.0)
        أرجع NAN;

    rotation = atan2(CONV_FP(میٹرکس[1]) / scale[1],
                     CONV_FP(میٹرکس[0]) / scale[0]) * 180 / M_PI;

    أرجع -rotation;
}

فراغ av_display_rotation_سیٹ(int32_t میٹرکس[9], مزدوج angle)
{
    مزدوج radians = -angle * M_PI / 180.0f;
    مزدوج c = جیب_تمام(radians);
    مزدوج s = جیب(radians);

    memset(میٹرکس, 0, 9 * حجم(int32_t));

    میٹرکس[0] = CONV_DB(c);
    میٹرکس[1] = CONV_DB(-s);
    میٹرکس[3] = CONV_DB(s);
    میٹرکس[4] = CONV_DB(c);
    میٹرکس[8] = 1 << 30;
}

فراغ av_display_میٹرکس_flip(int32_t میٹرکس[9], صحيح hflip, صحيح vflip)
{
    صحيح i;
    ثابت صحيح flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    إذا (hflip || vflip)
        لكل (i = 0; i < 9; i++)
            میٹرکس[i] *= flip[i % 3];
}
