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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST 1
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/random_seed.c"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ N 256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ F 2
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t (*random_ਬੀਜ_ptr_t)(ਖਾਲੀ);

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਪੂਰਨ i, j, rsf, retry;
    uint32_t seeds[N];
    random_ਬੀਜ_ptr_t random_ਬੀਜ[F] = {av_get_random_ਬੀਜ, get_generic_ਬੀਜ};

    ਲਈ (rsf=0; rsf<F; ++rsf){
        ਲਈ (retry=0; retry<3; retry++){
            ਲਈ (i=0; i<N; i++){
                seeds[i] = random_ਬੀਜ[rsf]();
                ਲਈ (j=0; j<i; j++)
                    ਜੇ (seeds[j] == seeds[i])
                        ਜਾਓ retry;
            }
            ਲਿਖੋ("seeds OK\n");
            ਰੋਕੋ;
            retry:;
        }
        ਜੇ (retry >= 3) {
            ਲਿਖੋ("rsf %d: FAIL at %d with %"PRIX32"\n", rsf, j, seeds[j]);
            ਵਾਪਸ 1;
        }
    }
    ਵਾਪਸ 0;
}
