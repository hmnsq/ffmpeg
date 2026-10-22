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

#घोषणा TEST 1
#समावेश "libavutil/random_seed.c"

#घोषणा N 256
#घोषणा F 2
#समावेश <stdio.h>

प्रकार uint32_t (*random_seed_ptr_t)(व्योम);

पूर्णांक मुख्य(व्योम)
{
    पूर्णांक i, j, rsf, retry;
    uint32_t seeds[N];
    random_seed_ptr_t random_seed[F] = {av_get_random_seed, get_generic_seed};

    क्रम (rsf=0; rsf<F; ++rsf){
        क्रम (retry=0; retry<3; retry++){
            क्रम (i=0; i<N; i++){
                seeds[i] = random_seed[rsf]();
                क्रम (j=0; j<i; j++)
                    अगर (seeds[j] == seeds[i])
                        जाओ retry;
            }
            म_लिखो("seeds OK\n");
            अवरोध;
            retry:;
        }
        अगर (retry >= 3) {
            म_लिखो("rsf %d: FAIL at %d with %"PRIX32"\n", rsf, j, seeds[j]);
            वापस 1;
        }
    }
    वापस 0;
}
