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

#تعریف_کرو TEST 1
#ضمن "libavutil/random_seed.c"

#تعریف_کرو N 256
#تعریف_کرو F 2
#ضمن <stdio.h>

تعريفنوع uint32_t (*random_بیج_ptr_t)(فراغ);

صحيح مکھ(فراغ)
{
    صحيح i, j, rsf, retry;
    uint32_t seeds[N];
    random_بیج_ptr_t random_بیج[F] = {av_get_random_بیج, get_generic_بیج};

    لكل (rsf=0; rsf<F; ++rsf){
        لكل (retry=0; retry<3; retry++){
            لكل (i=0; i<N; i++){
                seeds[i] = random_بیج[rsf]();
                لكل (j=0; j<i; j++)
                    إذا (seeds[j] == seeds[i])
                        اذهب retry;
            }
            لکھو("seeds OK\n");
            اكسر;
            retry:;
        }
        إذا (retry >= 3) {
            لکھو("rsf %d: FAIL at %d with %"PRIX32"\n", rsf, j, seeds[j]);
            أرجع 1;
        }
    }
    أرجع 0;
}
