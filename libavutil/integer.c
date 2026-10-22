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

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "integer.h"
#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "intmath.h"

স্থির ধ্রুবক AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    পূর্ণসংখ্যা i, carry=0;

    জন্য(i=0; i<AV_INTEGER_আকার; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    ফেরত a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    পূর্ণসংখ্যা i, carry=0;

    জন্য(i=0; i<AV_INTEGER_আকার; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    ফেরত a;
}

পূর্ণসংখ্যা av_log2_i(AVInteger a){
    পূর্ণসংখ্যা i;

    জন্য(i=AV_INTEGER_আকার-1; i>=0; i--){
        যদি(a.v[i])
            ফেরত av_log2_16bit(a.v[i]) + 16*i;
    }
    ফেরত -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    পূর্ণসংখ্যা i, j;
    পূর্ণসংখ্যা na= (av_log2_i(a)+16) >> 4;
    পূর্ণসংখ্যা nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, আকার(out));

    জন্য(i=0; i<na; i++){
        unsigned পূর্ণসংখ্যা carry=0;

        যদি(a.v[i])
            জন্য(j=i; j<AV_INTEGER_আকার && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    ফেরত out;
}

পূর্ণসংখ্যা av_cmp_i(AVInteger a, AVInteger b){
    পূর্ণসংখ্যা i;
    পূর্ণসংখ্যা v= (int16_t)a.v[AV_INTEGER_আকার-1] - (int16_t)b.v[AV_INTEGER_আকার-1];
    যদি(v) ফেরত (v>>16)|1;

    জন্য(i=AV_INTEGER_আকার-2; i>=0; i--){
        পূর্ণসংখ্যা v= a.v[i] - b.v[i];
        যদি(v) ফেরত (v>>16)|1;
    }
    ফেরত 0;
}

AVInteger av_shr_i(AVInteger a, পূর্ণসংখ্যা s){
    AVInteger out;
    পূর্ণসংখ্যা i;

    জন্য(i=0; i<AV_INTEGER_আকার; i++){
        unsigned পূর্ণসংখ্যা সূচক= i + (s>>4);
        unsigned পূর্ণসংখ্যা v=0;
        যদি (সূচক + 1 < AV_INTEGER_আকার) v  = a.v[সূচক + 1] * (1U << 16);
        যদি (সূচক     < AV_INTEGER_আকার) v |= a.v[সূচক];
        out.v[i]= v >> (s&15);
    }
    ফেরত out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    পূর্ণসংখ্যা i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_অস্থায়ী;
    যদি(!quot) quot = &quot_অস্থায়ী;

    যদি ((int16_t)a.v[AV_INTEGER_আকার-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        ফেরত av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_আকার-1] >= 0 && (int16_t)b.v[AV_INTEGER_আকার-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    যদি(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, আকার(AVInteger));

    যখন(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        যদি(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    ফেরত a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    ফেরত quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    পূর্ণসংখ্যা i;

    জন্য(i=0; i<AV_INTEGER_আকার; i++){
        out.v[i]= a;
        a>>=16;
    }
    ফেরত out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    জন্য (পূর্ণসংখ্যা i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    ফেরত out;
}
