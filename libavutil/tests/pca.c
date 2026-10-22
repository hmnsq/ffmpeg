/*
 * principal component analysis (PCA)
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

#அந்தர்பாவ "libavutil/pca.c"
#அந்தர்பாவ "libavutil/lfg.h"

#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>

முழு முதன்மை(வெறுமை){
    PCA *pca;
    முழு i, j, k;
#define LEN 8
    இரட்டை eigenvector[LEN*LEN];
    இரட்டை eigenvalue[LEN];
    AVLFG prng;

    av_lfg_init(&prng, 1);

    pca= ff_pca_init(LEN);

    க்கு(i=0; i<9000000; i++){
        இரட்டை v[2*LEN+100];
//        double sum=0;
        முழு pos = av_lfg_get(&prng) % LEN;
        முழு v2  = (முழு)(av_lfg_get(&prng) % 101) - 50;
        v[0]    = (முழு)(av_lfg_get(&prng) % 101) - 50;
        க்கு(j=1; j<8; j++){
            எனில்(j<=pos) v[j]= v[0];
            இல்லையெனில்       v[j]= v2;
//            sum += v[j];
        }
/*        for(j=0; j<LEN; j++){
            v[j] -= v[pos];
        }*/
//        sum += av_lfg_get(&prng) % 10;
/*        for(j=0; j<LEN; j++){
            v[j] -= sum/LEN;
        }*/
//        lbt1(v+100,v+100,LEN);
        ff_pca_add(pca, v);
    }


    ff_pca(pca, eigenvector, eigenvalue);
    க்கு(i=0; i<LEN; i++){
        pca->மொத்தம்= 1;
        pca->mean[i]= 0;

//        (0.5^|x|)^2 = 0.5^2|x| = 0.25^|x|


//        pca.covariance[i + i*LEN]= pow(0.5, fabs
        க்கு(j=i; j<LEN; j++){
            printf("%f ", pca->covariance[i + j*LEN]);
        }
        printf("\n");
    }

    க்கு(i=0; i<LEN; i++){
        இரட்டை v[LEN];
        இரட்டை error=0;
        memset(v, 0, அளவு(v));
        க்கு(j=0; j<LEN; j++){
            க்கு(k=0; k<LEN; k++){
                v[j] += pca->covariance[FFMIN(k,j) + FFMAX(k,j)*LEN] * eigenvector[i + k*LEN];
            }
            v[j] /= eigenvalue[i];
            error += fabs(v[j] - eigenvector[i + j*LEN]);
        }
        printf("%f ", error);
    }
    printf("\n");

    க்கு(i=0; i<LEN; i++){
        க்கு(j=0; j<LEN; j++){
            printf("%9.6f ", eigenvector[i + j*LEN]);
        }
        printf("  %9.1f %f\n", eigenvalue[i], eigenvalue[i]/eigenvalue[0]);
    }

    ff_pca_free(pca);
    திரும்பு 0;
}
