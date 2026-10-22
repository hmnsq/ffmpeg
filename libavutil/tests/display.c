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

#అన్తర్భావ <stdio.h>
#అన్తర్భావ "libavutil/display.c"

స్థిర శూన్య print_మాతృక(int32_t మాతృక[9])
{
    పూర్ణాంకం i, j;

    కొరకు (i = 0; i < 3; ++i) {
        కొరకు (j = 0; j < 3 - 1; ++j)
            రాయి("%d ", మాతృక[i*3 + j]);

        రాయి("%d\n", మాతృక[i*3 + j]);
    }
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    int32_t మాతృక[9];

    // Set the matrix to 90 degrees
    av_display_rotation_సమితి(మాతృక, 90);
    print_మాతృక(మాతృక);
    రాయి("degrees: %f\n", av_display_rotation_get(మాతృక));

    // Set the matrix to -45 degrees
    av_display_rotation_సమితి(మాతృక, -45);
    print_మాతృక(మాతృక);
    రాయి("degrees: %f\n", av_display_rotation_get(మాతృక));

    // flip horizontal
    av_display_మాతృక_flip(మాతృక, 1, 0);
    print_మాతృక(మాతృక);
    రాయి("degrees: %f\n", av_display_rotation_get(మాతృక));

    // flip vertical
    av_display_మాతృక_flip(మాతృక, 0, 1);
    print_మాతృక(మాతృక);
    రాయి("degrees: %f\n", av_display_rotation_get(మాతృక));

    తిరిగి 0;

}
