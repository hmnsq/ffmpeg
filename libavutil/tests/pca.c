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

#અન્તર્ભાવ "libavutil/pca.c"
#અન્તર્ભાવ "libavutil/lfg.h"

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>

પૂર્ણાંક મુખ્ય(શૂન્ય){
    PCA *pca;
    પૂર્ણાંક i, j, k;
#define LEN 8
    દ્વિગુણ eigenvector[LEN*LEN];
    દ્વિગુણ eigenvalue[LEN];
    AVLFG prng;

    av_lfg_init(&prng, 1);

    pca= ff_pca_init(LEN);

    માટે(i=0; i<9000000; i++){
        દ્વિગુણ v[2*LEN+100];
//        double sum=0;
        પૂર્ણાંક pos = av_lfg_get(&prng) % LEN;
        પૂર્ણાંક v2  = (પૂર્ણાંક)(av_lfg_get(&prng) % 101) - 50;
        v[0]    = (પૂર્ણાંક)(av_lfg_get(&prng) % 101) - 50;
        માટે(j=1; j<8; j++){
            જો(j<=pos) v[j]= v[0];
            નહીંતર       v[j]= v2;
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
    માટે(i=0; i<LEN; i++){
        pca->ગણતરી= 1;
        pca->mean[i]= 0;

//        (0.5^|x|)^2 = 0.5^2|x| = 0.25^|x|


//        pca.covariance[i + i*LEN]= pow(0.5, fabs
        માટે(j=i; j<LEN; j++){
            printf("%f ", pca->covariance[i + j*LEN]);
        }
        printf("\n");
    }

    માટે(i=0; i<LEN; i++){
        દ્વિગુણ v[LEN];
        દ્વિગુણ error=0;
        memset(v, 0, કદ(v));
        માટે(j=0; j<LEN; j++){
            માટે(k=0; k<LEN; k++){
                v[j] += pca->covariance[FFMIN(k,j) + FFMAX(k,j)*LEN] * eigenvector[i + k*LEN];
            }
            v[j] /= eigenvalue[i];
            error += fabs(v[j] - eigenvector[i + j*LEN]);
        }
        printf("%f ", error);
    }
    printf("\n");

    માટે(i=0; i<LEN; i++){
        માટે(j=0; j<LEN; j++){
            printf("%9.6f ", eigenvector[i + j*LEN]);
        }
        printf("  %9.1f %f\n", eigenvalue[i], eigenvalue[i]/eigenvalue[0]);
    }

    ff_pca_free(pca);
    પાછા 0;
}
