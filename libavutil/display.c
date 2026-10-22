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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "display.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mathematics.h"

// fixed point to double
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONV_FP(x) ((ਦੁੱਗਣਾ) (x)) / (1 << 16)

// double to fixed point
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONV_DB(x) (int32_t) ((x) * (1 << 16))

ਦੁੱਗਣਾ av_display_rotation_get(ਅਚਲ int32_t ਮੈਟ੍ਰਿਕਸ[9])
{
    ਦੁੱਗਣਾ rotation, scale[2];

    scale[0] = hypot(CONV_FP(ਮੈਟ੍ਰਿਕਸ[0]), CONV_FP(ਮੈਟ੍ਰਿਕਸ[3]));
    scale[1] = hypot(CONV_FP(ਮੈਟ੍ਰਿਕਸ[1]), CONV_FP(ਮੈਟ੍ਰਿਕਸ[4]));

    ਜੇ (scale[0] == 0.0 || scale[1] == 0.0)
        ਵਾਪਸ NAN;

    rotation = atan2(CONV_FP(ਮੈਟ੍ਰਿਕਸ[1]) / scale[1],
                     CONV_FP(ਮੈਟ੍ਰਿਕਸ[0]) / scale[0]) * 180 / M_PI;

    ਵਾਪਸ -rotation;
}

ਖਾਲੀ av_display_rotation_ਸੈੱਟ(int32_t ਮੈਟ੍ਰਿਕਸ[9], ਦੁੱਗਣਾ angle)
{
    ਦੁੱਗਣਾ radians = -angle * M_PI / 180.0f;
    ਦੁੱਗਣਾ c = ਕੋਜੀਵਾ(radians);
    ਦੁੱਗਣਾ s = ਜੀਵਾ(radians);

    memset(ਮੈਟ੍ਰਿਕਸ, 0, 9 * ਆਕਾਰ(int32_t));

    ਮੈਟ੍ਰਿਕਸ[0] = CONV_DB(c);
    ਮੈਟ੍ਰਿਕਸ[1] = CONV_DB(-s);
    ਮੈਟ੍ਰਿਕਸ[3] = CONV_DB(s);
    ਮੈਟ੍ਰਿਕਸ[4] = CONV_DB(c);
    ਮੈਟ੍ਰਿਕਸ[8] = 1 << 30;
}

ਖਾਲੀ av_display_ਮੈਟ੍ਰਿਕਸ_flip(int32_t ਮੈਟ੍ਰਿਕਸ[9], ਪੂਰਨ hflip, ਪੂਰਨ vflip)
{
    ਪੂਰਨ i;
    ਅਚਲ ਪੂਰਨ flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    ਜੇ (hflip || vflip)
        ਲਈ (i = 0; i < 9; i++)
            ਮੈਟ੍ਰਿਕਸ[i] *= flip[i % 3];
}
