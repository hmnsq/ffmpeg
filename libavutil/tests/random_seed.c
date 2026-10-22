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
#અન્તર્ભાવ "libavutil/random_seed.c"

#define N 256
#define F 2
#અન્તર્ભાવ <stdio.h>

પ્રકારવ્યાખ્યા uint32_t (*random_seed_ptr_t)(શૂન્ય);

પૂર્ણાંક મુખ્ય(શૂન્ય)
{
    પૂર્ણાંક i, j, rsf, retry;
    uint32_t seeds[N];
    random_seed_ptr_t random_seed[F] = {av_get_random_seed, get_generic_seed};

    માટે (rsf=0; rsf<F; ++rsf){
        માટે (retry=0; retry<3; retry++){
            માટે (i=0; i<N; i++){
                seeds[i] = random_seed[rsf]();
                માટે (j=0; j<i; j++)
                    જો (seeds[j] == seeds[i])
                        જાઓ retry;
            }
            printf("seeds OK\n");
            તોડો;
            retry:;
        }
        જો (retry >= 3) {
            printf("rsf %d: FAIL at %d with %"PRIX32"\n", rsf, j, seeds[j]);
            પાછા 1;
        }
    }
    પાછા 0;
}
