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
    ចំនួនគត់ i, carry=0;

    សម្រាប់(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    ត្រឡប់ a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    ចំនួនគត់ i, carry=0;

    សម្រាប់(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    ត្រឡប់ a;
}

ចំនួនគត់ av_log2_i(AVInteger a){
    ចំនួនគត់ i;

    សម្រាប់(i=AV_INTEGER_SIZE-1; i>=0; i--){
        ប្រសិនបើ(a.v[i])
            ត្រឡប់ av_log2_16bit(a.v[i]) + 16*i;
    }
    ត្រឡប់ -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    ចំនួនគត់ i, j;
    ចំនួនគត់ na= (av_log2_i(a)+16) >> 4;
    ចំនួនគត់ nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, parimaa_na(out));

    សម្រាប់(i=0; i<na; i++){
        unsigned ចំនួនគត់ carry=0;

        ប្រសិនបើ(a.v[i])
            សម្រាប់(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    ត្រឡប់ out;
}

ចំនួនគត់ av_cmp_i(AVInteger a, AVInteger b){
    ចំនួនគត់ i;
    ចំនួនគត់ v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    ប្រសិនបើ(v) ត្រឡប់ (v>>16)|1;

    សម្រាប់(i=AV_INTEGER_SIZE-2; i>=0; i--){
        ចំនួនគត់ v= a.v[i] - b.v[i];
        ប្រសិនបើ(v) ត្រឡប់ (v>>16)|1;
    }
    ត្រឡប់ 0;
}

AVInteger av_shr_i(AVInteger a, ចំនួនគត់ s){
    AVInteger out;
    ចំនួនគត់ i;

    សម្រាប់(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned ចំនួនគត់ index= i + (s>>4);
        unsigned ចំនួនគត់ v=0;
        ប្រសិនបើ (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        ប្រសិនបើ (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    ត្រឡប់ out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    ចំនួនគត់ i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    ប្រសិនបើ(!quot) quot = &quot_temp;

    ប្រសិនបើ ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        ត្រឡប់ av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    ប្រសិនបើ(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, parimaa_na(AVInteger));

    ខណៈពេល(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        ប្រសិនបើ(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    ត្រឡប់ a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    ត្រឡប់ quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    ចំនួនគត់ i;

    សម្រាប់(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    ត្រឡប់ out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    សម្រាប់ (ចំនួនគត់ i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    ត្រឡប់ out;
}
