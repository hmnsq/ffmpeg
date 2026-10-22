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
#وصف_ڪريو CONV_FP(x) ((مزدوج) (x)) / (1 << 16)

// double to fixed point
#وصف_ڪريو CONV_DB(x) (int32_t) ((x) * (1 << 16))

مزدوج av_display_rotation_get(ثابت int32_t ميٽرڪس[9])
{
    مزدوج rotation, scale[2];

    scale[0] = hypot(CONV_FP(ميٽرڪس[0]), CONV_FP(ميٽرڪس[3]));
    scale[1] = hypot(CONV_FP(ميٽرڪس[1]), CONV_FP(ميٽرڪس[4]));

    إذا (scale[0] == 0.0 || scale[1] == 0.0)
        أرجع NAN;

    rotation = atan2(CONV_FP(ميٽرڪس[1]) / scale[1],
                     CONV_FP(ميٽرڪس[0]) / scale[0]) * 180 / M_PI;

    أرجع -rotation;
}

فراغ av_display_rotation_سيٽ(int32_t ميٽرڪس[9], مزدوج angle)
{
    مزدوج radians = -angle * M_PI / 180.0f;
    مزدوج c = جيب_تمام(radians);
    مزدوج s = جيب(radians);

    memset(ميٽرڪس, 0, 9 * حجم(int32_t));

    ميٽرڪس[0] = CONV_DB(c);
    ميٽرڪس[1] = CONV_DB(-s);
    ميٽرڪس[3] = CONV_DB(s);
    ميٽرڪس[4] = CONV_DB(c);
    ميٽرڪس[8] = 1 << 30;
}

فراغ av_display_ميٽرڪس_flip(int32_t ميٽرڪس[9], صحيح hflip, صحيح vflip)
{
    صحيح i;
    ثابت صحيح flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    إذا (hflip || vflip)
        لكل (i = 0; i < 9; i++)
            ميٽرڪس[i] *= flip[i % 3];
}
