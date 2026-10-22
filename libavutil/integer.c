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

#ضمن <string.h>

#ضمن "integer.h"
#ضمن "avassert.h"
#ضمن "intmath.h"

ساكن ثابت AVInteger zero_i;

AVInteger av_جمع_کن_i(AVInteger a, AVInteger b){
    صحيح i, انتقال=0;

    لكل(i=0; i<AV_INTEGER_اندازه; i++){
        انتقال= (انتقال>>16) + a.v[i] + b.v[i];
        a.v[i]= انتقال;
    }
    أرجع a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    صحيح i, انتقال=0;

    لكل(i=0; i<AV_INTEGER_اندازه; i++){
        انتقال= (انتقال>>16) + a.v[i] - b.v[i];
        a.v[i]= انتقال;
    }
    أرجع a;
}

صحيح av_log2_i(AVInteger a){
    صحيح i;

    لكل(i=AV_INTEGER_اندازه-1; i>=0; i--){
        إذا(a.v[i])
            أرجع av_log2_16bit(a.v[i]) + 16*i;
    }
    أرجع -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger بیرون;
    صحيح i, j;
    صحيح na= (av_log2_i(a)+16) >> 4;
    صحيح nb= (av_log2_i(b)+16) >> 4;

    memset(&بیرون, 0, حجم(بیرون));

    لكل(i=0; i<na; i++){
        بیعلامت صحيح انتقال=0;

        إذا(a.v[i])
            لكل(j=i; j<AV_INTEGER_اندازه && j-i<=nb; j++){
                انتقال= (انتقال>>16) + بیرون.v[j] + a.v[i]*(بیعلامت)b.v[j-i];
                بیرون.v[j]= انتقال;
            }
    }

    أرجع بیرون;
}

صحيح av_cmp_i(AVInteger a, AVInteger b){
    صحيح i;
    صحيح v= (int16_t)a.v[AV_INTEGER_اندازه-1] - (int16_t)b.v[AV_INTEGER_اندازه-1];
    إذا(v) أرجع (v>>16)|1;

    لكل(i=AV_INTEGER_اندازه-2; i>=0; i--){
        صحيح v= a.v[i] - b.v[i];
        إذا(v) أرجع (v>>16)|1;
    }
    أرجع 0;
}

AVInteger av_shr_i(AVInteger a, صحيح s){
    AVInteger بیرون;
    صحيح i;

    لكل(i=0; i<AV_INTEGER_اندازه; i++){
        بیعلامت صحيح شاخص= i + (s>>4);
        بیعلامت صحيح v=0;
        إذا (شاخص + 1 < AV_INTEGER_اندازه) v  = a.v[شاخص + 1] * (1U << 16);
        إذا (شاخص     < AV_INTEGER_اندازه) v |= a.v[شاخص];
        بیرون.v[i]= v >> (s&15);
    }
    أرجع بیرون;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    صحيح i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_موقت;
    إذا(!quot) quot = &quot_موقت;

    إذا ((int16_t)a.v[AV_INTEGER_اندازه-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        أرجع av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_اندازه-1] >= 0 && (int16_t)b.v[AV_INTEGER_اندازه-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    إذا(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, حجم(AVInteger));

    طالما(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        إذا(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    أرجع a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    أرجع quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger بیرون;
    صحيح i;

    لكل(i=0; i<AV_INTEGER_اندازه; i++){
        بیرون.v[i]= a;
        a>>=16;
    }
    أرجع بیرون;
}

int64_t av_i2int(AVInteger a){
    uint64_t بیرون = a.v[3];

    لكل (صحيح i = 2; i >= 0; i--)
        بیرون = (بیرون << 16) | a.v[i];
    أرجع بیرون;
}
