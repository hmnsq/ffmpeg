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

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ "libavutil/display.c"

સ્થિર શૂન્ય print_matrix(int32_t matrix[9])
{
    પૂર્ણાંક i, j;

    માટે (i = 0; i < 3; ++i) {
        માટે (j = 0; j < 3 - 1; ++j)
            printf("%d ", matrix[i*3 + j]);

        printf("%d\n", matrix[i*3 + j]);
    }
}

પૂર્ણાંક મુખ્ય(શૂન્ય)
{
    int32_t matrix[9];

    // Set the matrix to 90 degrees
    av_display_rotation_set(matrix, 90);
    print_matrix(matrix);
    printf("degrees: %f\n", av_display_rotation_get(matrix));

    // Set the matrix to -45 degrees
    av_display_rotation_set(matrix, -45);
    print_matrix(matrix);
    printf("degrees: %f\n", av_display_rotation_get(matrix));

    // flip horizontal
    av_display_matrix_flip(matrix, 1, 0);
    print_matrix(matrix);
    printf("degrees: %f\n", av_display_rotation_get(matrix));

    // flip vertical
    av_display_matrix_flip(matrix, 0, 1);
    print_matrix(matrix);
    printf("degrees: %f\n", av_display_rotation_get(matrix));

    પાછા 0;

}
