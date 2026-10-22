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

#ضمن <stdio.h>
#ضمن "libavutil/display.c"

ساكن فراغ print_ميٽرڪس(int32_t ميٽرڪس[9])
{
    صحيح i, j;

    لكل (i = 0; i < 3; ++i) {
        لكل (j = 0; j < 3 - 1; ++j)
            لکو("%d ", ميٽرڪس[i*3 + j]);

        لکو("%d\n", ميٽرڪس[i*3 + j]);
    }
}

صحيح مکيه(فراغ)
{
    int32_t ميٽرڪس[9];

    // Set the matrix to 90 degrees
    av_display_rotation_سيٽ(ميٽرڪس, 90);
    print_ميٽرڪس(ميٽرڪس);
    لکو("degrees: %f\n", av_display_rotation_get(ميٽرڪس));

    // Set the matrix to -45 degrees
    av_display_rotation_سيٽ(ميٽرڪس, -45);
    print_ميٽرڪس(ميٽرڪس);
    لکو("degrees: %f\n", av_display_rotation_get(ميٽرڪس));

    // flip horizontal
    av_display_ميٽرڪس_flip(ميٽرڪس, 1, 0);
    print_ميٽرڪس(ميٽرڪس);
    لکو("degrees: %f\n", av_display_rotation_get(ميٽرڪس));

    // flip vertical
    av_display_ميٽرڪس_flip(ميٽرڪس, 0, 1);
    print_ميٽرڪس(ميٽرڪس);
    لکو("degrees: %f\n", av_display_rotation_get(ميٽرڪس));

    أرجع 0;

}
