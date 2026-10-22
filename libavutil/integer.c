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

স্থির ধ্রুব AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    পূর্ণাঙ্ক i, carry=0;

    প্রতি(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    প্রত্যাগম a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    পূর্ণাঙ্ক i, carry=0;

    প্রতি(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    প্রত্যাগম a;
}

পূর্ণাঙ্ক av_log2_i(AVInteger a){
    পূর্ণাঙ্ক i;

    প্রতি(i=AV_INTEGER_SIZE-1; i>=0; i--){
        যদি(a.v[i])
            প্রত্যাগম av_log2_16bit(a.v[i]) + 16*i;
    }
    প্রত্যাগম -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    পূর্ণাঙ্ক i, j;
    পূর্ণাঙ্ক na= (av_log2_i(a)+16) >> 4;
    পূর্ণাঙ্ক nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, পরিমাণ(out));

    প্রতি(i=0; i<na; i++){
        unsigned পূর্ণাঙ্ক carry=0;

        যদি(a.v[i])
            প্রতি(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    প্রত্যাগম out;
}

পূর্ণাঙ্ক av_cmp_i(AVInteger a, AVInteger b){
    পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    যদি(v) প্রত্যাগম (v>>16)|1;

    প্রতি(i=AV_INTEGER_SIZE-2; i>=0; i--){
        পূর্ণাঙ্ক v= a.v[i] - b.v[i];
        যদি(v) প্রত্যাগম (v>>16)|1;
    }
    প্রত্যাগম 0;
}

AVInteger av_shr_i(AVInteger a, পূর্ণাঙ্ক s){
    AVInteger out;
    পূর্ণাঙ্ক i;

    প্রতি(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned পূর্ণাঙ্ক index= i + (s>>4);
        unsigned পূর্ণাঙ্ক v=0;
        যদি (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        যদি (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    প্রত্যাগম out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    পূর্ণাঙ্ক i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    যদি(!quot) quot = &quot_temp;

    যদি ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        প্রত্যাগম av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    যদি(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, পরিমাণ(AVInteger));

    যাবত্(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        যদি(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    প্রত্যাগম a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    প্রত্যাগম quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    পূর্ণাঙ্ক i;

    প্রতি(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    প্রত্যাগম out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    প্রতি (পূর্ণাঙ্ক i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    প্রত্যাগম out;
}
