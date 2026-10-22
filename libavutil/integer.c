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

ಸ್ಥಿರ ಧ್ರುವ AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    ಪೂರ್ಣಾಙ್ಕ i, carry=0;

    ಪ್ರತಿ(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    ಪ್ರತ್ಯಾಗಮ a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    ಪೂರ್ಣಾಙ್ಕ i, carry=0;

    ಪ್ರತಿ(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    ಪ್ರತ್ಯಾಗಮ a;
}

ಪೂರ್ಣಾಙ್ಕ av_log2_i(AVInteger a){
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ(i=AV_INTEGER_SIZE-1; i>=0; i--){
        ಯದಿ(a.v[i])
            ಪ್ರತ್ಯಾಗಮ av_log2_16bit(a.v[i]) + 16*i;
    }
    ಪ್ರತ್ಯಾಗಮ -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    ಪೂರ್ಣಾಙ್ಕ i, j;
    ಪೂರ್ಣಾಙ್ಕ na= (av_log2_i(a)+16) >> 4;
    ಪೂರ್ಣಾಙ್ಕ nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, ಪರಿಮಾಣ(out));

    ಪ್ರತಿ(i=0; i<na; i++){
        unsigned ಪೂರ್ಣಾಙ್ಕ carry=0;

        ಯದಿ(a.v[i])
            ಪ್ರತಿ(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    ಪ್ರತ್ಯಾಗಮ out;
}

ಪೂರ್ಣಾಙ್ಕ av_cmp_i(AVInteger a, AVInteger b){
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪೂರ್ಣಾಙ್ಕ v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    ಯದಿ(v) ಪ್ರತ್ಯಾಗಮ (v>>16)|1;

    ಪ್ರತಿ(i=AV_INTEGER_SIZE-2; i>=0; i--){
        ಪೂರ್ಣಾಙ್ಕ v= a.v[i] - b.v[i];
        ಯದಿ(v) ಪ್ರತ್ಯಾಗಮ (v>>16)|1;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

AVInteger av_shr_i(AVInteger a, ಪೂರ್ಣಾಙ್ಕ s){
    AVInteger out;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned ಪೂರ್ಣಾಙ್ಕ index= i + (s>>4);
        unsigned ಪೂರ್ಣಾಙ್ಕ v=0;
        ಯದಿ (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        ಯದಿ (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    ಪ್ರತ್ಯಾಗಮ out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    ಪೂರ್ಣಾಙ್ಕ i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    ಯದಿ(!quot) quot = &quot_temp;

    ಯದಿ ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        ಪ್ರತ್ಯಾಗಮ av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    ಯದಿ(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, ಪರಿಮಾಣ(AVInteger));

    ಯಾವತ್(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        ಯದಿ(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    ಪ್ರತ್ಯಾಗಮ a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    ಪ್ರತ್ಯಾಗಮ quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    ಪ್ರತ್ಯಾಗಮ out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    ಪ್ರತ್ಯಾಗಮ out;
}
