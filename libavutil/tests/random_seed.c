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
#ಅನ್ತರ್ಭಾವ "libavutil/random_seed.c"

#define N 256
#define F 2
#ಅನ್ತರ್ಭಾವ <stdio.h>

ಪ್ರಕಾರನಿರ್ದೇಶ uint32_t (*random_seed_ptr_t)(ಶೂನ್ಯ);

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ i, j, rsf, retry;
    uint32_t seeds[N];
    random_seed_ptr_t random_seed[F] = {av_get_random_seed, get_generic_seed};

    ಪ್ರತಿ (rsf=0; rsf<F; ++rsf){
        ಪ್ರತಿ (retry=0; retry<3; retry++){
            ಪ್ರತಿ (i=0; i<N; i++){
                seeds[i] = random_seed[rsf]();
                ಪ್ರತಿ (j=0; j<i; j++)
                    ಯದಿ (seeds[j] == seeds[i])
                        ಗಚ್ಛ retry;
            }
            printf("seeds OK\n");
            ಭಙ್ಗ;
            retry:;
        }
        ಯದಿ (retry >= 3) {
            printf("rsf %d: FAIL at %d with %"PRIX32"\n", rsf, j, seeds[j]);
            ಪ್ರತ್ಯಾಗಮ 1;
        }
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}
