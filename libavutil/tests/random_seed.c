/*
 * Copyright (c) 2009 Baptiste Coudurier <baptiste.coudurier@gmail.com>
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

#define TEST 1
#अन्तर्भाव "libavutil/random_seed.c"

#define N 256
#define F 2
#अन्तर्भाव <stdio.h>

प्रकारनिर्देश uint32_t (*random_seed_ptr_t)(शून्य);

पूर्णाङ्क main(शून्य)
{
    पूर्णाङ्क i, j, rsf, retry;
    uint32_t seeds[N];
    random_seed_ptr_t random_seed[F] = {av_get_random_seed, get_generic_seed};

    अत्थाय (rsf=0; rsf<F; ++rsf){
        अत्थाय (retry=0; retry<3; retry++){
            अत्थाय (i=0; i<N; i++){
                seeds[i] = random_seed[rsf]();
                अत्थाय (j=0; j<i; j++)
                    सचे (seeds[j] == seeds[i])
                        गच्छ retry;
            }
            printf("seeds OK\n");
            भङ्ग;
            retry:;
        }
        सचे (retry >= 3) {
            printf("rsf %d: FAIL at %d with %"PRIX32"\n", rsf, j, seeds[j]);
            पटिनिवत्त 1;
        }
    }
    पटिनिवत्त 0;
}
