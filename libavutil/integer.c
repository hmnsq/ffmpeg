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

#include <string.h>

#include "integer.h"
#include "avassert.h"
#include "intmath.h"

static const AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    số_nguyên i, carry=0;

    cho(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    trả_về a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    số_nguyên i, carry=0;

    cho(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    trả_về a;
}

số_nguyên av_log2_i(AVInteger a){
    số_nguyên i;

    cho(i=AV_INTEGER_SIZE-1; i>=0; i--){
        nếu(a.v[i])
            trả_về av_log2_16bit(a.v[i]) + 16*i;
    }
    trả_về -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    số_nguyên i, j;
    số_nguyên na= (av_log2_i(a)+16) >> 4;
    số_nguyên nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, sizeof(out));

    cho(i=0; i<na; i++){
        unsigned số_nguyên carry=0;

        nếu(a.v[i])
            cho(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    trả_về out;
}

số_nguyên av_cmp_i(AVInteger a, AVInteger b){
    số_nguyên i;
    số_nguyên v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    nếu(v) trả_về (v>>16)|1;

    cho(i=AV_INTEGER_SIZE-2; i>=0; i--){
        số_nguyên v= a.v[i] - b.v[i];
        nếu(v) trả_về (v>>16)|1;
    }
    trả_về 0;
}

AVInteger av_shr_i(AVInteger a, số_nguyên s){
    AVInteger out;
    số_nguyên i;

    cho(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned số_nguyên index= i + (s>>4);
        unsigned số_nguyên v=0;
        nếu (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        nếu (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    trả_về out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    số_nguyên i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    nếu(!quot) quot = &quot_temp;

    nếu ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        trả_về av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    nếu(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, sizeof(AVInteger));

    trong_khi(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        nếu(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    trả_về a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    trả_về quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    số_nguyên i;

    cho(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    trả_về out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    cho (số_nguyên i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    trả_về out;
}
