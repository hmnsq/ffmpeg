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
    ціле i, carry=0;

    для(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    повернути a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    ціле i, carry=0;

    для(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    повернути a;
}

ціле av_log2_i(AVInteger a){
    ціле i;

    для(i=AV_INTEGER_SIZE-1; i>=0; i--){
        якщо(a.v[i])
            повернути av_log2_16bit(a.v[i]) + 16*i;
    }
    повернути -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    ціле i, j;
    ціле na= (av_log2_i(a)+16) >> 4;
    ціле nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, sizeof(out));

    для(i=0; i<na; i++){
        unsigned ціле carry=0;

        якщо(a.v[i])
            для(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    повернути out;
}

ціле av_cmp_i(AVInteger a, AVInteger b){
    ціле i;
    ціле v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    якщо(v) повернути (v>>16)|1;

    для(i=AV_INTEGER_SIZE-2; i>=0; i--){
        ціле v= a.v[i] - b.v[i];
        якщо(v) повернути (v>>16)|1;
    }
    повернути 0;
}

AVInteger av_shr_i(AVInteger a, ціле s){
    AVInteger out;
    ціле i;

    для(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned ціле index= i + (s>>4);
        unsigned ціле v=0;
        якщо (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        якщо (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    повернути out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    ціле i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    якщо(!quot) quot = &quot_temp;

    якщо ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        повернути av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    якщо(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, sizeof(AVInteger));

    поки(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        якщо(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    повернути a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    повернути quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    ціле i;

    для(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    повернути out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    для (ціле i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    повернути out;
}
