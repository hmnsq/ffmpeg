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
    ကိန်းပြည့် i, carry=0;

    အတွက်(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    ပြန်ပေး a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    ကိန်းပြည့် i, carry=0;

    အတွက်(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    ပြန်ပေး a;
}

ကိန်းပြည့် av_log2_i(AVInteger a){
    ကိန်းပြည့် i;

    အတွက်(i=AV_INTEGER_SIZE-1; i>=0; i--){
        အကယ်၍(a.v[i])
            ပြန်ပေး av_log2_16bit(a.v[i]) + 16*i;
    }
    ပြန်ပေး -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    ကိန်းပြည့် i, j;
    ကိန်းပြည့် na= (av_log2_i(a)+16) >> 4;
    ကိန်းပြည့် nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, parimaa_na(out));

    အတွက်(i=0; i<na; i++){
        unsigned ကိန်းပြည့် carry=0;

        အကယ်၍(a.v[i])
            အတွက်(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    ပြန်ပေး out;
}

ကိန်းပြည့် av_cmp_i(AVInteger a, AVInteger b){
    ကိန်းပြည့် i;
    ကိန်းပြည့် v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    အကယ်၍(v) ပြန်ပေး (v>>16)|1;

    အတွက်(i=AV_INTEGER_SIZE-2; i>=0; i--){
        ကိန်းပြည့် v= a.v[i] - b.v[i];
        အကယ်၍(v) ပြန်ပေး (v>>16)|1;
    }
    ပြန်ပေး 0;
}

AVInteger av_shr_i(AVInteger a, ကိန်းပြည့် s){
    AVInteger out;
    ကိန်းပြည့် i;

    အတွက်(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned ကိန်းပြည့် index= i + (s>>4);
        unsigned ကိန်းပြည့် v=0;
        အကယ်၍ (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        အကယ်၍ (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    ပြန်ပေး out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    ကိန်းပြည့် i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    အကယ်၍(!quot) quot = &quot_temp;

    အကယ်၍ ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        ပြန်ပေး av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    အကယ်၍(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, parimaa_na(AVInteger));

    နေစဉ်(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        အကယ်၍(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    ပြန်ပေး a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    ပြန်ပေး quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    ကိန်းပြည့် i;

    အတွက်(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    ပြန်ပေး out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    အတွက် (ကိန်းပြည့် i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    ပြန်ပေး out;
}
