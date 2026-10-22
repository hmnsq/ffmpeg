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

ساکن ثابت AVInteger zero_i;

AVInteger av_جوڑو_i(AVInteger a, AVInteger b){
    صحیح i, حاصل=0;

    برائے(i=0; i<AV_INTEGER_سائز; i++){
        حاصل= (حاصل>>16) + a.v[i] + b.v[i];
        a.v[i]= حاصل;
    }
    واپس a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    صحیح i, حاصل=0;

    برائے(i=0; i<AV_INTEGER_سائز; i++){
        حاصل= (حاصل>>16) + a.v[i] - b.v[i];
        a.v[i]= حاصل;
    }
    واپس a;
}

صحیح av_log2_i(AVInteger a){
    صحیح i;

    برائے(i=AV_INTEGER_سائز-1; i>=0; i--){
        اگر(a.v[i])
            واپس av_log2_16bit(a.v[i]) + 16*i;
    }
    واپس -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger برآمد;
    صحیح i, j;
    صحیح na= (av_log2_i(a)+16) >> 4;
    صحیح nb= (av_log2_i(b)+16) >> 4;

    memset(&برآمد, 0, حجم(برآمد));

    برائے(i=0; i<na; i++){
        غیرعلامتی صحیح حاصل=0;

        اگر(a.v[i])
            برائے(j=i; j<AV_INTEGER_سائز && j-i<=nb; j++){
                حاصل= (حاصل>>16) + برآمد.v[j] + a.v[i]*(غیرعلامتی)b.v[j-i];
                برآمد.v[j]= حاصل;
            }
    }

    واپس برآمد;
}

صحیح av_cmp_i(AVInteger a, AVInteger b){
    صحیح i;
    صحیح v= (int16_t)a.v[AV_INTEGER_سائز-1] - (int16_t)b.v[AV_INTEGER_سائز-1];
    اگر(v) واپس (v>>16)|1;

    برائے(i=AV_INTEGER_سائز-2; i>=0; i--){
        صحیح v= a.v[i] - b.v[i];
        اگر(v) واپس (v>>16)|1;
    }
    واپس 0;
}

AVInteger av_shr_i(AVInteger a, صحیح s){
    AVInteger برآمد;
    صحیح i;

    برائے(i=0; i<AV_INTEGER_سائز; i++){
        غیرعلامتی صحیح اشاریہ= i + (s>>4);
        غیرعلامتی صحیح v=0;
        اگر (اشاریہ + 1 < AV_INTEGER_سائز) v  = a.v[اشاریہ + 1] * (1U << 16);
        اگر (اشاریہ     < AV_INTEGER_سائز) v |= a.v[اشاریہ];
        برآمد.v[i]= v >> (s&15);
    }
    واپس برآمد;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    صحیح i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_عارضی;
    اگر(!quot) quot = &quot_عارضی;

    اگر ((int16_t)a.v[AV_INTEGER_سائز-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        واپس av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_سائز-1] >= 0 && (int16_t)b.v[AV_INTEGER_سائز-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    اگر(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, حجم(AVInteger));

    جب(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        اگر(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    واپس a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    واپس quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger برآمد;
    صحیح i;

    برائے(i=0; i<AV_INTEGER_سائز; i++){
        برآمد.v[i]= a;
        a>>=16;
    }
    واپس برآمد;
}

int64_t av_i2int(AVInteger a){
    uint64_t برآمد = a.v[3];

    برائے (صحیح i = 2; i >= 0; i--)
        برآمد = (برآمد << 16) | a.v[i];
    واپس برآمد;
}
