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

#شامل <string.h>

#شامل "integer.h"
#شامل "avassert.h"
#شامل "intmath.h"

ایستا ثابت AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    صحیح i, carry=0;

    برای(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    بازگشت a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    صحیح i, carry=0;

    برای(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    بازگشت a;
}

صحیح av_log2_i(AVInteger a){
    صحیح i;

    برای(i=AV_INTEGER_SIZE-1; i>=0; i--){
        اگر(a.v[i])
            بازگشت av_log2_16bit(a.v[i]) + 16*i;
    }
    بازگشت -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    صحیح i, j;
    صحیح na= (av_log2_i(a)+16) >> 4;
    صحیح nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, اندازه(out));

    برای(i=0; i<na; i++){
        unsigned صحیح carry=0;

        اگر(a.v[i])
            برای(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    بازگشت out;
}

صحیح av_cmp_i(AVInteger a, AVInteger b){
    صحیح i;
    صحیح v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    اگر(v) بازگشت (v>>16)|1;

    برای(i=AV_INTEGER_SIZE-2; i>=0; i--){
        صحیح v= a.v[i] - b.v[i];
        اگر(v) بازگشت (v>>16)|1;
    }
    بازگشت 0;
}

AVInteger av_shr_i(AVInteger a, صحیح s){
    AVInteger out;
    صحیح i;

    برای(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned صحیح index= i + (s>>4);
        unsigned صحیح v=0;
        اگر (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        اگر (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    بازگشت out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    صحیح i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    اگر(!quot) quot = &quot_temp;

    اگر ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        بازگشت av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    اگر(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, اندازه(AVInteger));

    وقتی(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        اگر(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    بازگشت a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    بازگشت quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    صحیح i;

    برای(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    بازگشت out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    برای (صحیح i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    بازگشت out;
}
