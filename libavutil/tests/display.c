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

#شامل <stdio.h>
#شامل "libavutil/display.c"

ساکن خالی print_میٹرکس(int32_t میٹرکس[9])
{
    صحیح i, j;

    برائے (i = 0; i < 3; ++i) {
        برائے (j = 0; j < 3 - 1; ++j)
            لکھو("%d ", میٹرکس[i*3 + j]);

        لکھو("%d\n", میٹرکس[i*3 + j]);
    }
}

صحیح مین(خالی)
{
    int32_t میٹرکس[9];

    // Set the matrix to 90 degrees
    av_display_rotation_سیٹ(میٹرکس, 90);
    print_میٹرکس(میٹرکس);
    لکھو("degrees: %f\n", av_display_rotation_get(میٹرکس));

    // Set the matrix to -45 degrees
    av_display_rotation_سیٹ(میٹرکس, -45);
    print_میٹرکس(میٹرکس);
    لکھو("degrees: %f\n", av_display_rotation_get(میٹرکس));

    // flip horizontal
    av_display_میٹرکس_flip(میٹرکس, 1, 0);
    print_میٹرکس(میٹرکس);
    لکھو("degrees: %f\n", av_display_rotation_get(میٹرکس));

    // flip vertical
    av_display_میٹرکس_flip(میٹرکس, 0, 1);
    print_میٹرکس(میٹرکس);
    لکھو("degrees: %f\n", av_display_rotation_get(میٹرکس));

    واپس 0;

}
