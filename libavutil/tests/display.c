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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/display.c"

ਸਥਿਰ ਖਾਲੀ print_ਮੈਟ੍ਰਿਕਸ(int32_t ਮੈਟ੍ਰਿਕਸ[9])
{
    ਪੂਰਨ i, j;

    ਲਈ (i = 0; i < 3; ++i) {
        ਲਈ (j = 0; j < 3 - 1; ++j)
            ਲਿਖੋ("%d ", ਮੈਟ੍ਰਿਕਸ[i*3 + j]);

        ਲਿਖੋ("%d\n", ਮੈਟ੍ਰਿਕਸ[i*3 + j]);
    }
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    int32_t ਮੈਟ੍ਰਿਕਸ[9];

    // Set the matrix to 90 degrees
    av_display_rotation_ਸੈੱਟ(ਮੈਟ੍ਰਿਕਸ, 90);
    print_ਮੈਟ੍ਰਿਕਸ(ਮੈਟ੍ਰਿਕਸ);
    ਲਿਖੋ("degrees: %f\n", av_display_rotation_get(ਮੈਟ੍ਰਿਕਸ));

    // Set the matrix to -45 degrees
    av_display_rotation_ਸੈੱਟ(ਮੈਟ੍ਰਿਕਸ, -45);
    print_ਮੈਟ੍ਰਿਕਸ(ਮੈਟ੍ਰਿਕਸ);
    ਲਿਖੋ("degrees: %f\n", av_display_rotation_get(ਮੈਟ੍ਰਿਕਸ));

    // flip horizontal
    av_display_ਮੈਟ੍ਰਿਕਸ_flip(ਮੈਟ੍ਰਿਕਸ, 1, 0);
    print_ਮੈਟ੍ਰਿਕਸ(ਮੈਟ੍ਰਿਕਸ);
    ਲਿਖੋ("degrees: %f\n", av_display_rotation_get(ਮੈਟ੍ਰਿਕਸ));

    // flip vertical
    av_display_ਮੈਟ੍ਰਿਕਸ_flip(ਮੈਟ੍ਰਿਕਸ, 0, 1);
    print_ਮੈਟ੍ਰਿਕਸ(ਮੈਟ੍ਰਿਕਸ);
    ਲਿਖੋ("degrees: %f\n", av_display_rotation_get(ਮੈਟ੍ਰਿਕਸ));

    ਵਾਪਸ 0;

}
