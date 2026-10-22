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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <math.h>

#అన్తర్భావ "display.h"
#అన్తర్భావ "mathematics.h"

// fixed point to double
#నిర్వచించు CONV_FP(x) ((ద్విగుణ) (x)) / (1 << 16)

// double to fixed point
#నిర్వచించు CONV_DB(x) (int32_t) ((x) * (1 << 16))

ద్విగుణ av_display_rotation_get(స్థిరరాశి int32_t మాతృక[9])
{
    ద్విగుణ rotation, scale[2];

    scale[0] = hypot(CONV_FP(మాతృక[0]), CONV_FP(మాతృక[3]));
    scale[1] = hypot(CONV_FP(మాతృక[1]), CONV_FP(మాతృక[4]));

    ఒకవేళ (scale[0] == 0.0 || scale[1] == 0.0)
        తిరిగి NAN;

    rotation = atan2(CONV_FP(మాతృక[1]) / scale[1],
                     CONV_FP(మాతృక[0]) / scale[0]) * 180 / M_PI;

    తిరిగి -rotation;
}

శూన్య av_display_rotation_సమితి(int32_t మాతృక[9], ద్విగుణ angle)
{
    ద్విగుణ radians = -angle * M_PI / 180.0f;
    ద్విగుణ c = కోజ్యా(radians);
    ద్విగుణ s = జ్యా(radians);

    memset(మాతృక, 0, 9 * పరిమాణం(int32_t));

    మాతృక[0] = CONV_DB(c);
    మాతృక[1] = CONV_DB(-s);
    మాతృక[3] = CONV_DB(s);
    మాతృక[4] = CONV_DB(c);
    మాతృక[8] = 1 << 30;
}

శూన్య av_display_మాతృక_flip(int32_t మాతృక[9], పూర్ణాంకం hflip, పూర్ణాంకం vflip)
{
    పూర్ణాంకం i;
    స్థిరరాశి పూర్ణాంకం flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    ఒకవేళ (hflip || vflip)
        కొరకు (i = 0; i < 9; i++)
            మాతృక[i] *= flip[i % 3];
}
