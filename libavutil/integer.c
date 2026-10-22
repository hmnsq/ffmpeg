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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "integer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intmath.h"

ਸਥਿਰ ਅਚਲ AVInteger zero_i;

AVInteger av_ਜੋੜੋ_i(AVInteger a, AVInteger b){
    ਪੂਰਨ i, ਹਾਸਲ=0;

    ਲਈ(i=0; i<AV_INTEGER_ਮਾਪ; i++){
        ਹਾਸਲ= (ਹਾਸਲ>>16) + a.v[i] + b.v[i];
        a.v[i]= ਹਾਸਲ;
    }
    ਵਾਪਸ a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    ਪੂਰਨ i, ਹਾਸਲ=0;

    ਲਈ(i=0; i<AV_INTEGER_ਮਾਪ; i++){
        ਹਾਸਲ= (ਹਾਸਲ>>16) + a.v[i] - b.v[i];
        a.v[i]= ਹਾਸਲ;
    }
    ਵਾਪਸ a;
}

ਪੂਰਨ av_log2_i(AVInteger a){
    ਪੂਰਨ i;

    ਲਈ(i=AV_INTEGER_ਮਾਪ-1; i>=0; i--){
        ਜੇ(a.v[i])
            ਵਾਪਸ av_log2_16bit(a.v[i]) + 16*i;
    }
    ਵਾਪਸ -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger ਬਾਹਰਲਾ;
    ਪੂਰਨ i, j;
    ਪੂਰਨ na= (av_log2_i(a)+16) >> 4;
    ਪੂਰਨ nb= (av_log2_i(b)+16) >> 4;

    memset(&ਬਾਹਰਲਾ, 0, ਆਕਾਰ(ਬਾਹਰਲਾ));

    ਲਈ(i=0; i<na; i++){
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਹਾਸਲ=0;

        ਜੇ(a.v[i])
            ਲਈ(j=i; j<AV_INTEGER_ਮਾਪ && j-i<=nb; j++){
                ਹਾਸਲ= (ਹਾਸਲ>>16) + ਬਾਹਰਲਾ.v[j] + a.v[i]*(ਬਿਨਾਨਿਸ਼ਾਨੀ)b.v[j-i];
                ਬਾਹਰਲਾ.v[j]= ਹਾਸਲ;
            }
    }

    ਵਾਪਸ ਬਾਹਰਲਾ;
}

ਪੂਰਨ av_cmp_i(AVInteger a, AVInteger b){
    ਪੂਰਨ i;
    ਪੂਰਨ v= (int16_t)a.v[AV_INTEGER_ਮਾਪ-1] - (int16_t)b.v[AV_INTEGER_ਮਾਪ-1];
    ਜੇ(v) ਵਾਪਸ (v>>16)|1;

    ਲਈ(i=AV_INTEGER_ਮਾਪ-2; i>=0; i--){
        ਪੂਰਨ v= a.v[i] - b.v[i];
        ਜੇ(v) ਵਾਪਸ (v>>16)|1;
    }
    ਵਾਪਸ 0;
}

AVInteger av_shr_i(AVInteger a, ਪੂਰਨ s){
    AVInteger ਬਾਹਰਲਾ;
    ਪੂਰਨ i;

    ਲਈ(i=0; i<AV_INTEGER_ਮਾਪ; i++){
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਸੂਚਕਾਂਕ= i + (s>>4);
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ v=0;
        ਜੇ (ਸੂਚਕਾਂਕ + 1 < AV_INTEGER_ਮਾਪ) v  = a.v[ਸੂਚਕਾਂਕ + 1] * (1U << 16);
        ਜੇ (ਸੂਚਕਾਂਕ     < AV_INTEGER_ਮਾਪ) v |= a.v[ਸੂਚਕਾਂਕ];
        ਬਾਹਰਲਾ.v[i]= v >> (s&15);
    }
    ਵਾਪਸ ਬਾਹਰਲਾ;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    ਪੂਰਨ i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_ਆਰਜ਼ੀ;
    ਜੇ(!quot) quot = &quot_ਆਰਜ਼ੀ;

    ਜੇ ((int16_t)a.v[AV_INTEGER_ਮਾਪ-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        ਵਾਪਸ av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_ਮਾਪ-1] >= 0 && (int16_t)b.v[AV_INTEGER_ਮਾਪ-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    ਜੇ(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, ਆਕਾਰ(AVInteger));

    ਜਦੋਂ(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        ਜੇ(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    ਵਾਪਸ a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    ਵਾਪਸ quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger ਬਾਹਰਲਾ;
    ਪੂਰਨ i;

    ਲਈ(i=0; i<AV_INTEGER_ਮਾਪ; i++){
        ਬਾਹਰਲਾ.v[i]= a;
        a>>=16;
    }
    ਵਾਪਸ ਬਾਹਰਲਾ;
}

int64_t av_i2int(AVInteger a){
    uint64_t ਬਾਹਰਲਾ = a.v[3];

    ਲਈ (ਪੂਰਨ i = 2; i >= 0; i--)
        ਬਾਹਰਲਾ = (ਬਾਹਰਲਾ << 16) | a.v[i];
    ਵਾਪਸ ਬਾਹਰਲਾ;
}
