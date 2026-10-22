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
    ຈຳນວນເຕັມ i, carry=0;

    ສຳລັບ(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    ສົ່ງຄືນ a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    ຈຳນວນເຕັມ i, carry=0;

    ສຳລັບ(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    ສົ່ງຄືນ a;
}

ຈຳນວນເຕັມ av_log2_i(AVInteger a){
    ຈຳນວນເຕັມ i;

    ສຳລັບ(i=AV_INTEGER_SIZE-1; i>=0; i--){
        ຖ້າ(a.v[i])
            ສົ່ງຄືນ av_log2_16bit(a.v[i]) + 16*i;
    }
    ສົ່ງຄືນ -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    ຈຳນວນເຕັມ i, j;
    ຈຳນວນເຕັມ na= (av_log2_i(a)+16) >> 4;
    ຈຳນວນເຕັມ nb= (av_log2_i(b)+16) >> 4;

    memset(&out, 0, parimaa_na(out));

    ສຳລັບ(i=0; i<na; i++){
        unsigned ຈຳນວນເຕັມ carry=0;

        ຖ້າ(a.v[i])
            ສຳລັບ(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(unsigned)b.v[j-i];
                out.v[j]= carry;
            }
    }

    ສົ່ງຄືນ out;
}

ຈຳນວນເຕັມ av_cmp_i(AVInteger a, AVInteger b){
    ຈຳນວນເຕັມ i;
    ຈຳນວນເຕັມ v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    ຖ້າ(v) ສົ່ງຄືນ (v>>16)|1;

    ສຳລັບ(i=AV_INTEGER_SIZE-2; i>=0; i--){
        ຈຳນວນເຕັມ v= a.v[i] - b.v[i];
        ຖ້າ(v) ສົ່ງຄືນ (v>>16)|1;
    }
    ສົ່ງຄືນ 0;
}

AVInteger av_shr_i(AVInteger a, ຈຳນວນເຕັມ s){
    AVInteger out;
    ຈຳນວນເຕັມ i;

    ສຳລັບ(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned ຈຳນວນເຕັມ index= i + (s>>4);
        unsigned ຈຳນວນເຕັມ v=0;
        ຖ້າ (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        ຖ້າ (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    ສົ່ງຄືນ out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    ຈຳນວນເຕັມ i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    ຖ້າ(!quot) quot = &quot_temp;

    ຖ້າ ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        ສົ່ງຄືນ av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    ຖ້າ(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, parimaa_na(AVInteger));

    ໃນຂະນະທີ່(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        ຖ້າ(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    ສົ່ງຄືນ a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    ສົ່ງຄືນ quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    ຈຳນວນເຕັມ i;

    ສຳລັບ(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    ສົ່ງຄືນ out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    ສຳລັບ (ຈຳນວນເຕັມ i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    ສົ່ງຄືນ out;
}
