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

#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "integer.h"
#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "intmath.h"

સ્થિર અચલ AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    પૂર્ણાંક i, carry=0;

    માટે(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    પાછા a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    પૂર્ણાંક i, carry=0;

    માટે(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    પાછા a;
}

પૂર્ણાંક av_log2_i(AVInteger a){
    પૂર્ણાંક i;

    માટે(i=AV_INTEGER_SIZE-1; i>=0; i--){
        જો(a.v[i])
            પાછા av_log2_16bit(a.v[i]) + 16*i;
    }
    પાછા -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    પૂર્ણાંક i, j;
    પૂર્ણાંક na= (av_log2_i(a)+16) >> 4;
    પૂર્ણાંક nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, કદ(out));

    માટે(i=0; i<na; i++){
        unsigned પૂર્ણાંક carry=0;

        જો(a.v[i])
            માટે(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    પાછા out;
}

પૂર્ણાંક av_cmp_i(AVInteger a, AVInteger b){
    પૂર્ણાંક i;
    પૂર્ણાંક v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    જો(v) પાછા (v>>16)|1;

    માટે(i=AV_INTEGER_SIZE-2; i>=0; i--){
        પૂર્ણાંક v= a.v[i] - b.v[i];
        જો(v) પાછા (v>>16)|1;
    }
    પાછા 0;
}

AVInteger av_shr_i(AVInteger a, પૂર્ણાંક s){
    AVInteger out;
    પૂર્ણાંક i;

    માટે(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned પૂર્ણાંક index= i + (s>>4);
        unsigned પૂર્ણાંક v=0;
        જો (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        જો (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    પાછા out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    પૂર્ણાંક i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    જો(!quot) quot = &quot_temp;

    જો ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        પાછા av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    જો(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, કદ(AVInteger));

    જ્યારે(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        જો(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    પાછા a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    પાછા quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    પૂર્ણાંક i;

    માટે(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    પાછા out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    માટે (પૂર્ણાંક i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    પાછા out;
}
