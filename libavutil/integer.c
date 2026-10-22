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

#అన్తర్భావ <string.h>

#అన్తర్భావ "integer.h"
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "intmath.h"

స్థిర స్థిరరాశి AVInteger zero_i;

AVInteger av_కూడు_i(AVInteger a, AVInteger b){
    పూర్ణాంకం i, వాహకం=0;

    కొరకు(i=0; i<AV_INTEGER_కొలత; i++){
        వాహకం= (వాహకం>>16) + a.v[i] + b.v[i];
        a.v[i]= వాహకం;
    }
    తిరిగి a;
}

AVInteger av_sub_i(AVInteger a, AVInteger b){
    పూర్ణాంకం i, వాహకం=0;

    కొరకు(i=0; i<AV_INTEGER_కొలత; i++){
        వాహకం= (వాహకం>>16) + a.v[i] - b.v[i];
        a.v[i]= వాహకం;
    }
    తిరిగి a;
}

పూర్ణాంకం av_log2_i(AVInteger a){
    పూర్ణాంకం i;

    కొరకు(i=AV_INTEGER_కొలత-1; i>=0; i--){
        ఒకవేళ(a.v[i])
            తిరిగి av_log2_16bit(a.v[i]) + 16*i;
    }
    తిరిగి -1;
}

AVInteger av_mul_i(AVInteger a, AVInteger b){
    AVInteger బహిర్గతం;
    పూర్ణాంకం i, j;
    పూర్ణాంకం na= (av_log2_i(a)+16) >> 4;
    పూర్ణాంకం nb= (av_log2_i(b)+16) >> 4;

    memset(&బహిర్గతం, 0, పరిమాణం(బహిర్గతం));

    కొరకు(i=0; i<na; i++){
        గుర్తులేని పూర్ణాంకం వాహకం=0;

        ఒకవేళ(a.v[i])
            కొరకు(j=i; j<AV_INTEGER_కొలత && j-i<=nb; j++){
                వాహకం= (వాహకం>>16) + బహిర్గతం.v[j] + a.v[i]*(గుర్తులేని)b.v[j-i];
                బహిర్గతం.v[j]= వాహకం;
            }
    }

    తిరిగి బహిర్గతం;
}

పూర్ణాంకం av_cmp_i(AVInteger a, AVInteger b){
    పూర్ణాంకం i;
    పూర్ణాంకం v= (int16_t)a.v[AV_INTEGER_కొలత-1] - (int16_t)b.v[AV_INTEGER_కొలత-1];
    ఒకవేళ(v) తిరిగి (v>>16)|1;

    కొరకు(i=AV_INTEGER_కొలత-2; i>=0; i--){
        పూర్ణాంకం v= a.v[i] - b.v[i];
        ఒకవేళ(v) తిరిగి (v>>16)|1;
    }
    తిరిగి 0;
}

AVInteger av_shr_i(AVInteger a, పూర్ణాంకం s){
    AVInteger బహిర్గతం;
    పూర్ణాంకం i;

    కొరకు(i=0; i<AV_INTEGER_కొలత; i++){
        గుర్తులేని పూర్ణాంకం సూచీ= i + (s>>4);
        గుర్తులేని పూర్ణాంకం v=0;
        ఒకవేళ (సూచీ + 1 < AV_INTEGER_కొలత) v  = a.v[సూచీ + 1] * (1U << 16);
        ఒకవేళ (సూచీ     < AV_INTEGER_కొలత) v |= a.v[సూచీ];
        బహిర్గతం.v[i]= v >> (s&15);
    }
    తిరిగి బహిర్గతం;
}

AVInteger av_mod_i(AVInteger *quot, AVInteger a, AVInteger b){
    పూర్ణాంకం i= av_log2_i(a) - av_log2_i(b);
    AVInteger quot_తాత్కాలిక;
    ఒకవేళ(!quot) quot = &quot_తాత్కాలిక;

    ఒకవేళ ((int16_t)a.v[AV_INTEGER_కొలత-1] < 0) {
        a = av_mod_i(quot, av_sub_i(zero_i, a), b);
        *quot = av_sub_i(zero_i, *quot);
        తిరిగి av_sub_i(zero_i, a);
    }

    av_assert2((int16_t)a.v[AV_INTEGER_కొలత-1] >= 0 && (int16_t)b.v[AV_INTEGER_కొలత-1] >= 0);
    av_assert2(av_log2_i(b)>=0);

    ఒకవేళ(i > 0)
        b= av_shr_i(b, -i);

    memset(quot, 0, పరిమాణం(AVInteger));

    అయితే(i-- >= 0){
        *quot= av_shr_i(*quot, -1);
        ఒకవేళ(av_cmp_i(a, b) >= 0){
            a= av_sub_i(a, b);
            quot->v[0] += 1;
        }
        b= av_shr_i(b, 1);
    }
    తిరిగి a;
}

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    తిరిగి quot;
}

AVInteger av_int2i(int64_t a){
    AVInteger బహిర్గతం;
    పూర్ణాంకం i;

    కొరకు(i=0; i<AV_INTEGER_కొలత; i++){
        బహిర్గతం.v[i]= a;
        a>>=16;
    }
    తిరిగి బహిర్గతం;
}

int64_t av_i2int(AVInteger a){
    uint64_t బహిర్గతం = a.v[3];

    కొరకు (పూర్ణాంకం i = 2; i >= 0; i--)
        బహిర్గతం = (బహిర్గతం << 16) | a.v[i];
    తిరిగి బహిర్గతం;
}
