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

स्थिर ध्रुव AVInteger zero_i;

AVInteger av_add_i(AVInteger a, AVInteger b){
    पूर्णाङ्क i, carry=0;

    प्रति(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] + b.v[i];
        a.v[i]= carry;
    }
    प्रत्यागम a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    पूर्णाङ्क i, carry=0;

    प्रति(i=0; i<AV_INTEGER_SIZE; i++){
        carry= (carry>>16) + a.v[i] - b.v[i];
        a.v[i]= carry;
    }
    प्रत्यागम a;
}

पूर्णाङ्क av_log2_i(AVInteger a){
    पूर्णाङ्क i;

    प्रति(i=AV_INTEGER_SIZE-1; i>=0; i--){
        यदि(a.v[i])
            प्रत्यागम av_log2_16bit(a.v[i]) + 16*i;
    }
    प्रत्यागम -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger out;
    पूर्णाङ्क i, j;
    पूर्णाङ्क na= (av_log2_i(a)+16) >> 4;
    पूर्णाङ्क nb= (av_log2_i(b)+16) >> 4;

    स_रखो(&out, 0, परिमाण(out));

    प्रति(i=0; i<na; i++){
        अचिन्हित पूर्णाङ्क carry=0;

        यदि(a.v[i])
            प्रति(j=i; j<AV_INTEGER_SIZE && j-i<=nb; j++){
                carry= (carry>>16) + out.v[j] + a.v[i]*(अचिन्हित)b.v[j-i];
                out.v[j]= carry;
            }
    }

    प्रत्यागम out;
}

पूर्णाङ्क av_cmp_i(AVInteger a, AVInteger b){
    पूर्णाङ्क i;
    पूर्णाङ्क v= (int16_t)a.v[AV_INTEGER_SIZE-1] - (int16_t)b.v[AV_INTEGER_SIZE-1];
    यदि(v) प्रत्यागम (v>>16)|1;

    प्रति(i=AV_INTEGER_SIZE-2; i>=0; i--){
        पूर्णाङ्क v= a.v[i] - b.v[i];
        यदि(v) प्रत्यागम (v>>16)|1;
    }
    प्रत्यागम 0;
}

AVInteger av_shr_i(AVInteger a, पूर्णाङ्क s){
    AVInteger out;
    पूर्णाङ्क i;

    प्रति(i=0; i<AV_INTEGER_SIZE; i++){
        अचिन्हित पूर्णाङ्क index= i + (s>>4);
        अचिन्हित पूर्णाङ्क v=0;
        यदि (index + 1 < AV_INTEGER_SIZE) v  = a.v[index + 1] * (1U << 16);
        यदि (index     < AV_INTEGER_SIZE) v |= a.v[index];
        out.v[i]= v >> (s&15);
    }
    प्रत्यागम out;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    पूर्णाङ्क i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_temp;
    यदि(!quot) quot = &quot_temp;

    यदि ((int16_t)a.v[AV_INTEGER_SIZE-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        प्रत्यागम av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_SIZE-1] >= 0 && (int16_t)b.v[AV_INTEGER_SIZE-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    यदि(i > 0)
        b= av_shr_i(b, -i);

    स_रखो(quot, 0, परिमाण(AVInteger));

    यावत्(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        यदि(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    प्रत्यागम a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    प्रत्यागम quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger out;
    पूर्णाङ्क i;

    प्रति(i=0; i<AV_INTEGER_SIZE; i++){
        out.v[i]= a;
        a>>=16;
    }
    प्रत्यागम out;
}

int64_t av_i2int(AVInteger a){
    uint64_t out = a.v[3];

    प्रति (पूर्णाङ्क i = 2; i >= 0; i--)
        out = (out << 16) | a.v[i];
    प्रत्यागम out;
}
