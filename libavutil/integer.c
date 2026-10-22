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

#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "integer.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "intmath.h"

ସ୍ଥିର ଅଚଳ AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, carry=0;

    ପାଇଁ(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    ଫେରନ୍ତୁ a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, carry=0;

    ପାଇଁ(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    ଫେରନ୍ତୁ a;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_log2_i(AVInteger a){
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ(i=AV_INTEGER_SIZE-1; i>=0; i--){
        ଯଦି(a.v[i])
            ଫେରନ୍ତୁ av_log2_16bit(a.v[i]) + 16*i;
    }
    ଫେରନ୍ତୁ -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା na= (av_log2_i(a)+16) >> 4;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, ଆକାର(out));

    ପାଇଁ(i=0; i<na; i++){
        unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା carry=0;

        ଯଦି(a.v[i])
            ପାଇଁ(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    ଫେରନ୍ତୁ out;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_cmp_i(AVInteger a, AVInteger b){
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    ଯଦି(v) ଫେରନ୍ତୁ (v>>16)|1;

    ପାଇଁ(i=AV_INTEGER_SIZE-2; i>=0; i--){
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା v= a.v[i] - b.v[i];
        ଯଦି(v) ଫେରନ୍ତୁ (v>>16)|1;
    }
    ଫେରନ୍ତୁ 0;
}

AVInteger av_shr_i(AVInteger a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା s){
    AVInteger out;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା index= i + (s>>4);
        unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା v=0;
        ଯଦି (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        ଯଦି (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    ଫେରନ୍ତୁ out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    ଯଦି(!quot) quot = &quot_temp;

    ଯଦି ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        ଫେରନ୍ତୁ av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    ଯଦି(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, ଆକାର(AVInteger));

    ଯେତେବେଳେ(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        ଯଦି(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    ଫେରନ୍ତୁ a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    ଫେରନ୍ତୁ quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    ଫେରନ୍ତୁ out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    ଫେରନ୍ତୁ out;
}
