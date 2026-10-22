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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST 1
#ಅನ್ತರ್ಭಾವ "libavutil/random_seed.c"

#ವ್ಯಾಖ್ಯಾನಿಸು N 256
#ವ್ಯಾಖ್ಯಾನಿಸು F 2
#ಅನ್ತರ್ಭಾವ <stdio.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t (*random_ಬೀಜ_ptr_t)(ಶೂನ್ಯ);

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i, j, rsf, retry;
    uint32_t seeds[N];
    random_ಬೀಜ_ptr_t random_ಬೀಜ[F] = {av_get_random_ಬೀಜ, get_generic_ಬೀಜ};

    ಗಾಗಿ (rsf=0; rsf<F; ++rsf){
        ಗಾಗಿ (retry=0; retry<3; retry++){
            ಗಾಗಿ (i=0; i<N; i++){
                seeds[i] = random_ಬೀಜ[rsf]();
                ಗಾಗಿ (j=0; j<i; j++)
                    ಆದರೆ (seeds[j] == seeds[i])
                        ಹೋಗು retry;
            }
            ಬರೆ("seeds OK\n");
            ನಿಲ್ಲಿಸು;
            retry:;
        }
        ಆದರೆ (retry >= 3) {
            ಬರೆ("rsf %d: FAIL at %d with %"PRIX32"\n", rsf, j, seeds[j]);
            ಹಿಂತಿರುಗಿ 1;
        }
    }
    ಹಿಂತಿರುಗಿ 0;
}
