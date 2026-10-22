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

AVInteger av_جوڙيو_i(AVInteger a, AVInteger b){
    صحيح i, حاصل=0;

    لكل(i=0; i<AV_INTEGER_سائيز; i++){
        حاصل= (حاصل>>16) + a.v[i] + b.v[i];
        a.v[i]= حاصل;
    }
    أرجع a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    صحيح i, حاصل=0;

    لكل(i=0; i<AV_INTEGER_سائيز; i++){
        حاصل= (حاصل>>16) + a.v[i] - b.v[i];
        a.v[i]= حاصل;
    }
    أرجع a;
}

صحيح av_log2_i(AVInteger a){
    صحيح i;

    لكل(i=AV_INTEGER_سائيز-1; i>=0; i--){
        إذا(a.v[i])
            أرجع av_log2_16bit(a.v[i]) + 16*i;
    }
    أرجع -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger ٻاهريون;
    صحيح i, j;
    صحيح na= (av_log2_i(a)+16) >> 4;
    صحيح nb= (av_log2_i(b)+16) >> 4;

    memset(&ٻاهريون, 0, حجم(ٻاهريون));

    لكل(i=0; i<na; i++){
        بنانشان صحيح حاصل=0;

        إذا(a.v[i])
            لكل(j=i; j<AV_INTEGER_سائيز && j-i<=nb; j++){
                حاصل= (حاصل>>16) + ٻاهريون.v[j] + a.v[i]*(بنانشان)b.v[j-i];
                ٻاهريون.v[j]= حاصل;
            }
    }

    أرجع ٻاهريون;
}

صحيح av_cmp_i(AVInteger a, AVInteger b){
    صحيح i;
    صحيح v= (int16_t)a.v[AV_INTEGER_سائيز-1] - (int16_t)b.v[AV_INTEGER_سائيز-1];
    إذا(v) أرجع (v>>16)|1;

    لكل(i=AV_INTEGER_سائيز-2; i>=0; i--){
        صحيح v= a.v[i] - b.v[i];
        إذا(v) أرجع (v>>16)|1;
    }
    أرجع 0;
}

AVInteger av_shr_i(AVInteger a, صحيح s){
    AVInteger ٻاهريون;
    صحيح i;

    لكل(i=0; i<AV_INTEGER_سائيز; i++){
        بنانشان صحيح اشاريو= i + (s>>4);
        بنانشان صحيح v=0;
        إذا (اشاريو + 1 < AV_INTEGER_سائيز) v  = a.v[اشاريو + 1] * (1U << 16);
        إذا (اشاريو     < AV_INTEGER_سائيز) v |= a.v[اشاريو];
        ٻاهريون.v[i]= v >> (s&15);
    }
    أرجع ٻاهريون;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    صحيح i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_عارضي;
    إذا(!quot) quot = &quot_عارضي;

    إذا ((int16_t)a.v[AV_INTEGER_سائيز-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        أرجع av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_سائيز-1] >= 0 && (int16_t)b.v[AV_INTEGER_سائيز-1] >= 0);
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
    AVInteger ٻاهريون;
    صحيح i;

    لكل(i=0; i<AV_INTEGER_سائيز; i++){
        ٻاهريون.v[i]= a;
        a>>=16;
    }
    أرجع ٻاهريون;
}

int64_t av_i2int(AVInteger a){
    uint64_t ٻاهريون = a.v[3];

    لكل (صحيح i = 2; i >= 0; i--)
        ٻاهريون = (ٻاهريون << 16) | a.v[i];
    أرجع ٻاهريون;
}
