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
#ವ್ಯಾಖ್ಯಾನಿಸು CONV_FP(x) ((ದ್ವಿಗುಣ) (x)) / (1 << 16)

// double to fixed point
#ವ್ಯಾಖ್ಯಾನಿಸು CONV_DB(x) (int32_t) ((x) * (1 << 16))

ದ್ವಿಗುಣ av_display_rotation_get(ಸ್ಥಿರಾಂಕ int32_t ಮಾತೃಕೆ[9])
{
    ದ್ವಿಗುಣ rotation, scale[2];

    scale[0] = hypot(CONV_FP(ಮಾತೃಕೆ[0]), CONV_FP(ಮಾತೃಕೆ[3]));
    scale[1] = hypot(CONV_FP(ಮಾತೃಕೆ[1]), CONV_FP(ಮಾತೃಕೆ[4]));

    ಆದರೆ (scale[0] == 0.0 || scale[1] == 0.0)
        ಹಿಂತಿರುಗಿ NAN;

    rotation = atan2(CONV_FP(ಮಾತೃಕೆ[1]) / scale[1],
                     CONV_FP(ಮಾತೃಕೆ[0]) / scale[0]) * 180 / M_PI;

    ಹಿಂತಿರುಗಿ -rotation;
}

ಶೂನ್ಯ av_display_rotation_ಗಣ(int32_t ಮಾತೃಕೆ[9], ದ್ವಿಗುಣ angle)
{
    ದ್ವಿಗುಣ radians = -angle * M_PI / 180.0f;
    ದ್ವಿಗುಣ c = ಕೋಜ್ಯಾ(radians);
    ದ್ವಿಗುಣ s = ಜ್ಯಾ(radians);

    memset(ಮಾತೃಕೆ, 0, 9 * ಗಾತ್ರ(int32_t));

    ಮಾತೃಕೆ[0] = CONV_DB(c);
    ಮಾತೃಕೆ[1] = CONV_DB(-s);
    ಮಾತೃಕೆ[3] = CONV_DB(s);
    ಮಾತೃಕೆ[4] = CONV_DB(c);
    ಮಾತೃಕೆ[8] = 1 << 30;
}

ಶೂನ್ಯ av_display_ಮಾತೃಕೆ_flip(int32_t ಮಾತೃಕೆ[9], ಪೂರ್ಣಾಂಕ hflip, ಪೂರ್ಣಾಂಕ vflip)
{
    ಪೂರ್ಣಾಂಕ i;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ flip[] = { 1 - 2 * (!!hflip), 1 - 2 * (!!vflip), 1 };

    ಆದರೆ (hflip || vflip)
        ಗಾಗಿ (i = 0; i < 9; i++)
            ಮಾತೃಕೆ[i] *= flip[i % 3];
}
