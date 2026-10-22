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
#অন্তর্ভাব "libavutil/random_seed.c"

#define N 256
#define F 2
#অন্তর্ভাব <stdio.h>

প্রকারলেখ uint32_t (*random_seed_ptr_t)(শূন্য);

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    পূর্ণসংখ্যা i, j, rsf, retry;
    uint32_t seeds[N];
    random_seed_ptr_t random_seed[F] = {av_get_random_seed, get_generic_seed};

    জন্য (rsf=0; rsf<F; ++rsf){
        জন্য (retry=0; retry<3; retry++){
            জন্য (i=0; i<N; i++){
                seeds[i] = random_seed[rsf]();
                জন্য (j=0; j<i; j++)
                    যদি (seeds[j] == seeds[i])
                        যাও retry;
            }
            printf("seeds OK\n");
            বিরতি;
            retry:;
        }
        যদি (retry >= 3) {
            printf("rsf %d: FAIL at %d with %"PRIX32"\n", rsf, j, seeds[j]);
            ফেরত 1;
        }
    }
    ফেরত 0;
}
