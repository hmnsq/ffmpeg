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

#నిర్వచించు TEST 1
#అన్తర్భావ "libavutil/random_seed.c"

#నిర్వచించు N 256
#నిర్వచించు F 2
#అన్తర్భావ <stdio.h>

రకనిర్వచనం uint32_t (*random_విత్తనం_ptr_t)(శూన్య);

పూర్ణాంకం ప్రధాన(శూన్య)
{
    పూర్ణాంకం i, j, rsf, retry;
    uint32_t seeds[N];
    random_విత్తనం_ptr_t random_విత్తనం[F] = {av_get_random_విత్తనం, get_generic_విత్తనం};

    కొరకు (rsf=0; rsf<F; ++rsf){
        కొరకు (retry=0; retry<3; retry++){
            కొరకు (i=0; i<N; i++){
                seeds[i] = random_విత్తనం[rsf]();
                కొరకు (j=0; j<i; j++)
                    ఒకవేళ (seeds[j] == seeds[i])
                        వెళ్ళు retry;
            }
            రాయి("seeds OK\n");
            ఆపు;
            retry:;
        }
        ఒకవేళ (retry >= 3) {
            రాయి("rsf %d: FAIL at %d with %"PRIX32"\n", rsf, j, seeds[j]);
            తిరిగి 1;
        }
    }
    తిరిగి 0;
}
