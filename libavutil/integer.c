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

#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "integer.h"
#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "intmath.h"

স্থির ধ্রুৱ AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    পূর্ণাঙ্ক i, carry=0;

    বাবে(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    ঘূৰাই a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    পূর্ণাঙ্ক i, carry=0;

    বাবে(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    ঘূৰাই a;
}

পূর্ণাঙ্ক av_log2_i(AVInteger a){
    পূর্ণাঙ্ক i;

    বাবে(i=AV_INTEGER_SIZE-1; i>=0; i--){
        যদি(a.v[i])
            ঘূৰাই av_log2_16bit(a.v[i]) + 16*i;
    }
    ঘূৰাই -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    পূর্ণাঙ্ক i, j;
    পূর্ণাঙ্ক na= (av_log2_i(a)+16) >> 4;
    পূর্ণাঙ্ক nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, পরিমাণ(out));

    বাবে(i=0; i<na; i++){
        unsigned পূর্ণাঙ্ক carry=0;

        যদি(a.v[i])
            বাবে(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    ঘূৰাই out;
}

পূর্ণাঙ্ক av_cmp_i(AVInteger a, AVInteger b){
    পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    যদি(v) ঘূৰাই (v>>16)|1;

    বাবে(i=AV_INTEGER_SIZE-2; i>=0; i--){
        পূর্ণাঙ্ক v= a.v[i] - b.v[i];
        যদি(v) ঘূৰাই (v>>16)|1;
    }
    ঘূৰাই 0;
}

AVInteger av_shr_i(AVInteger a, পূর্ণাঙ্ক s){
    AVInteger out;
    পূর্ণাঙ্ক i;

    বাবে(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned পূর্ণাঙ্ক index= i + (s>>4);
        unsigned পূর্ণাঙ্ক v=0;
        যদি (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        যদি (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    ঘূৰাই out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    পূর্ণাঙ্ক i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    যদি(!quot) quot = &quot_temp;

    যদি ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        ঘূৰাই av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    যদি(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, পরিমাণ(AVInteger));

    যেতিয়ালৈ(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        যদি(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    ঘূৰাই a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    ঘূৰাই quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    পূর্ণাঙ্ক i;

    বাবে(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    ঘূৰাই out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    বাবে (পূর্ণাঙ্ক i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    ঘূৰাই out;
}
