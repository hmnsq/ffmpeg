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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ "libavutil/display.c"

ಸ್ಥಿರ ಶೂನ್ಯ print_ಮಾತೃಕೆ(int32_t ಮಾತೃಕೆ[9])
{
    ಪೂರ್ಣಾಂಕ i, j;

    ಗಾಗಿ (i = 0; i < 3; ++i) {
        ಗಾಗಿ (j = 0; j < 3 - 1; ++j)
            ಬರೆ("%d ", ಮಾತೃಕೆ[i*3 + j]);

        ಬರೆ("%d\n", ಮಾತೃಕೆ[i*3 + j]);
    }
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    int32_t ಮಾತೃಕೆ[9];

    // Set the matrix to 90 degrees
    av_display_rotation_ಗಣ(ಮಾತೃಕೆ, 90);
    print_ಮಾತೃಕೆ(ಮಾತೃಕೆ);
    ಬರೆ("degrees: %f\n", av_display_rotation_get(ಮಾತೃಕೆ));

    // Set the matrix to -45 degrees
    av_display_rotation_ಗಣ(ಮಾತೃಕೆ, -45);
    print_ಮಾತೃಕೆ(ಮಾತೃಕೆ);
    ಬರೆ("degrees: %f\n", av_display_rotation_get(ಮಾತೃಕೆ));

    // flip horizontal
    av_display_ಮಾತೃಕೆ_flip(ಮಾತೃಕೆ, 1, 0);
    print_ಮಾತೃಕೆ(ಮಾತೃಕೆ);
    ಬರೆ("degrees: %f\n", av_display_rotation_get(ಮಾತೃಕೆ));

    // flip vertical
    av_display_ಮಾತೃಕೆ_flip(ಮಾತೃಕೆ, 0, 1);
    print_ಮಾತೃಕೆ(ಮಾತೃಕೆ);
    ಬರೆ("degrees: %f\n", av_display_rotation_get(ಮಾತೃಕೆ));

    ಹಿಂತಿರುಗಿ 0;

}
