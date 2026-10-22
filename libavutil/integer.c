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

#अन्तर्भाव <string.h>

#अन्तर्भाव "integer.h"
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "intmath.h"

स्थिर स्थिरांक AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    पूर्णांक i, carry=0;

    साठी(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    परत a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    पूर्णांक i, carry=0;

    साठी(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    परत a;
}

पूर्णांक av_log2_i(AVInteger a){
    पूर्णांक i;

    साठी(i=AV_INTEGER_SIZE-1; i>=0; i--){
        जर(a.v[i])
            परत av_log2_16bit(a.v[i]) + 16*i;
    }
    परत -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    पूर्णांक i, j;
    पूर्णांक na= (av_log2_i(a)+16) >> 4;
    पूर्णांक nb= (av_log2_i(b)+16) >> 4;

    स_रखो(&out, 0, आकार(out));

    साठी(i=0; i<na; i++){
        अचिन्हित पूर्णांक carry=0;

        जर(a.v[i])
            साठी(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(अचिन्हित)b.v[j-i];
                out.v[j]= carry;
            }
    }

    परत out;
}

पूर्णांक av_cmp_i(AVInteger a, AVInteger b){
    पूर्णांक i;
    पूर्णांक v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    जर(v) परत (v>>16)|1;

    साठी(i=AV_INTEGER_SIZE-2; i>=0; i--){
        पूर्णांक v= a.v[i] - b.v[i];
        जर(v) परत (v>>16)|1;
    }
    परत 0;
}

AVInteger av_shr_i(AVInteger a, पूर्णांक s){
    AVInteger out;
    पूर्णांक i;

    साठी(i=0; i<AV_INTEGER_SIZE; i++){
        अचिन्हित पूर्णांक index= i + (s>>4);
        अचिन्हित पूर्णांक v=0;
        जर (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        जर (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    परत out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    पूर्णांक i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    जर(!quot) quot = &quot_temp;

    जर ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        परत av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    जर(i > 0)
        b= av_shr_i(b, -i);

    स_रखो(quot, 0, आकार(AVInteger));

    पर्यंत(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        जर(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    परत a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    परत quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    पूर्णांक i;

    साठी(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    परत out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    साठी (पूर्णांक i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    परत out;
}
