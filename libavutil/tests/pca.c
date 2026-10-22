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

#অন্তর্ভাব "libavutil/pca.c"
#অন্তর্ভাব "libavutil/lfg.h"

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>

পূর্ণাঙ্ক main(শূন্য){
    PCA *pca;
    পূর্ণাঙ্ক i, j, k;
#define LEN 8
    দ্বিগুণ eigenvector[LEN*LEN];
    দ্বিগুণ eigenvalue[LEN];
    AVLFG prng;

    av_lfg_init(&prng, 1);

    pca= ff_pca_init(LEN);

    প্রতি(i=0; i<9000000; i++){
        দ্বিগুণ v[2*LEN+100];
//        double sum=0;
        পূর্ণাঙ্ক pos = av_lfg_get(&prng) % LEN;
        পূর্ণাঙ্ক v2  = (পূর্ণাঙ্ক)(av_lfg_get(&prng) % 101) - 50;
        v[0]    = (পূর্ণাঙ্ক)(av_lfg_get(&prng) % 101) - 50;
        প্রতি(j=1; j<8; j++){
            যদি(j<=pos) v[j]= v[0];
            অন্যথা       v[j]= v2;
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
    প্রতি(i=0; i<LEN; i++){
        pca->গুনতি= 1;
        pca->mean[i]= 0;

//        (0.5^|x|)^2 = 0.5^2|x| = 0.25^|x|


//        pca.covariance[i + i*LEN]= pow(0.5, fabs
        প্রতি(j=i; j<LEN; j++){
            printf("%f ", pca->covariance[i + j*LEN]);
        }
        printf("\n");
    }

    প্রতি(i=0; i<LEN; i++){
        দ্বিগুণ v[LEN];
        দ্বিগুণ error=0;
        memset(v, 0, পরিমাণ(v));
        প্রতি(j=0; j<LEN; j++){
            প্রতি(k=0; k<LEN; k++){
                v[j] += pca->covariance[FFMIN(k,j) + FFMAX(k,j)*LEN] * eigenvector[i + k*LEN];
            }
            v[j] /= eigenvalue[i];
            error += fabs(v[j] - eigenvector[i + j*LEN]);
        }
        printf("%f ", error);
    }
    printf("\n");

    প্রতি(i=0; i<LEN; i++){
        প্রতি(j=0; j<LEN; j++){
            printf("%9.6f ", eigenvector[i + j*LEN]);
        }
        printf("  %9.1f %f\n", eigenvalue[i], eigenvalue[i]/eigenvalue[0]);
    }

    ff_pca_free(pca);
    প্রত্যাগম 0;
}
