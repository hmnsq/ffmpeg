/*
 * arbitrary precision integers
 * Copyright (c) 2004 Michael Niedermayer <michaelni@gmx.at>
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

/**
 * @file
 * arbitrary precision integers
 * @author Michael Niedermayer <michaelni@gmx.at>
 */

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "integer.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "intmath.h"

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVInteger zero_i;

AVInteger av_ಕೂಡಿಸು_i(AVInteger a, AVInteger b){
    ಪೂರ್ಣಾಂಕ i, ವಾಹಕ=0;

    ಗಾಗಿ(i=0; i<AV_INTEGER_ಗಾತ್ರ; i++){
        ವಾಹಕ= (ವಾಹಕ>>16) + a.v[i] + b.v[i];
        a.v[i]= ವಾಹಕ;
    }
    ಹಿಂತಿರುಗಿ a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    ಪೂರ್ಣಾಂಕ i, ವಾಹಕ=0;

    ಗಾಗಿ(i=0; i<AV_INTEGER_ಗಾತ್ರ; i++){
        ವಾಹಕ= (ವಾಹಕ>>16) + a.v[i] - b.v[i];
        a.v[i]= ವಾಹಕ;
    }
    ಹಿಂತಿರುಗಿ a;
}

ಪೂರ್ಣಾಂಕ av_log2_i(AVInteger a){
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ(i=AV_INTEGER_ಗಾತ್ರ-1; i>=0; i--){
        ಆದರೆ(a.v[i])
            ಹಿಂತಿರುಗಿ av_log2_16bit(a.v[i]) + 16*i;
    }
    ಹಿಂತಿರುಗಿ -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger ಹೊರಹೋಗು;
    ಪೂರ್ಣಾಂಕ i, j;
    ಪೂರ್ಣಾಂಕ na= (av_log2_i(a)+16) >> 4;
    ಪೂರ್ಣಾಂಕ nb= (av_log2_i(b)+16) >> 4;

    memset(&ಹೊರಹೋಗು, 0, ಗಾತ್ರ(ಹೊರಹೋಗು));

    ಗಾಗಿ(i=0; i<na; i++){
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ವಾಹಕ=0;

        ಆದರೆ(a.v[i])
            ಗಾಗಿ(j=i; j<AV_INTEGER_ಗಾತ್ರ && j-i<=nb; j++){
                ವಾಹಕ= (ವಾಹಕ>>16) + ಹೊರಹೋಗು.v[j] + a.v[i]*(ಚಿಹ್ನೆರಹಿತ)b.v[j-i];
                ಹೊರಹೋಗು.v[j]= ವಾಹಕ;
            }
    }

    ಹಿಂತಿರುಗಿ ಹೊರಹೋಗು;
}

ಪೂರ್ಣಾಂಕ av_cmp_i(AVInteger a, AVInteger b){
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ v= (int16_t)a.v[AV_INTEGER_ಗಾತ್ರ-1] - (int16_t)b.v[AV_INTEGER_ಗಾತ್ರ-1];
    ಆದರೆ(v) ಹಿಂತಿರುಗಿ (v>>16)|1;

    ಗಾಗಿ(i=AV_INTEGER_ಗಾತ್ರ-2; i>=0; i--){
        ಪೂರ್ಣಾಂಕ v= a.v[i] - b.v[i];
        ಆದರೆ(v) ಹಿಂತಿರುಗಿ (v>>16)|1;
    }
    ಹಿಂತಿರುಗಿ 0;
}

AVInteger av_shr_i(AVInteger a, ಪೂರ್ಣಾಂಕ s){
    AVInteger ಹೊರಹೋಗು;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ(i=0; i<AV_INTEGER_ಗಾತ್ರ; i++){
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ= i + (s>>4);
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ v=0;
        ಆದರೆ (ಸೂಚ್ಯಂಕ + 1 < AV_INTEGER_ಗಾತ್ರ) v  = a.v[ಸೂಚ್ಯಂಕ + 1] * (1U << 16);
        ಆದರೆ (ಸೂಚ್ಯಂಕ     < AV_INTEGER_ಗಾತ್ರ) v |= a.v[ಸೂಚ್ಯಂಕ];
        ಹೊರಹೋಗು.v[i]= v >> (s&15);
    }
    ಹಿಂತಿರುಗಿ ಹೊರಹೋಗು;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    ಪೂರ್ಣಾಂಕ i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_ತಾತ್ಕಾಲಿಕ;
    ಆದರೆ(!quot) quot = &quot_ತಾತ್ಕಾಲಿಕ;

    ಆದರೆ ((int16_t)a.v[AV_INTEGER_ಗಾತ್ರ-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        ಹಿಂತಿರುಗಿ av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_ಗಾತ್ರ-1] >= 0 && (int16_t)b.v[AV_INTEGER_ಗಾತ್ರ-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    ಆದರೆ(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, ಗಾತ್ರ(AVInteger));

    ಆಗ(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        ಆದರೆ(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    ಹಿಂತಿರುಗಿ a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    ಹಿಂತಿರುಗಿ quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger ಹೊರಹೋಗು;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ(i=0; i<AV_INTEGER_ಗಾತ್ರ; i++){
        ಹೊರಹೋಗು.v[i]= a;
        a>>=16;
    }
    ಹಿಂತಿರುಗಿ ಹೊರಹೋಗು;
}

int64_t av_i2int(AVInteger a){
    uint64_t ಹೊರಹೋಗು = a.v[3];

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 2; i >= 0; i--)
        ಹೊರಹೋಗು = (ಹೊರಹೋಗು << 16) | a.v[i];
    ಹಿಂತಿರುಗಿ ಹೊರಹೋಗು;
}
