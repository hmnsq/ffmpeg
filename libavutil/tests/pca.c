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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pca.c"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/lfg.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ){
    PCA *pca;
    ਪੂਰਨ i, j, k;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LEN 8
    ਦੁੱਗਣਾ eigenvector[LEN*LEN];
    ਦੁੱਗਣਾ eigenvalue[LEN];
    AVLFG prng;

    av_lfg_init(&prng, 1);

    pca= ff_pca_init(LEN);

    ਲਈ(i=0; i<9000000; i++){
        ਦੁੱਗਣਾ v[2*LEN+100];
//        double sum=0;
        ਪੂਰਨ pos = av_lfg_get(&prng) % LEN;
        ਪੂਰਨ v2  = (ਪੂਰਨ)(av_lfg_get(&prng) % 101) - 50;
        v[0]    = (ਪੂਰਨ)(av_lfg_get(&prng) % 101) - 50;
        ਲਈ(j=1; j<8; j++){
            ਜੇ(j<=pos) v[j]= v[0];
            ਨਹੀਂਤਾਂ       v[j]= v2;
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
        ff_pca_ਜੋੜੋ(pca, v);
    }


    ff_pca(pca, eigenvector, eigenvalue);
    ਲਈ(i=0; i<LEN; i++){
        pca->ਗਿਣਤੀ_2= 1;
        pca->ਔਸਤ[i]= 0;

//        (0.5^|x|)^2 = 0.5^2|x| = 0.25^|x|


//        pca.covariance[i + i*LEN]= pow(0.5, fabs
        ਲਈ(j=i; j<LEN; j++){
            ਲਿਖੋ("%f ", pca->covariance[i + j*LEN]);
        }
        ਲਿਖੋ("\n");
    }

    ਲਈ(i=0; i<LEN; i++){
        ਦੁੱਗਣਾ v[LEN];
        ਦੁੱਗਣਾ error=0;
        memset(v, 0, ਆਕਾਰ(v));
        ਲਈ(j=0; j<LEN; j++){
            ਲਈ(k=0; k<LEN; k++){
                v[j] += pca->covariance[FFMIN(k,j) + FFMAX(k,j)*LEN] * eigenvector[i + k*LEN];
            }
            v[j] /= eigenvalue[i];
            error += fabs(v[j] - eigenvector[i + j*LEN]);
        }
        ਲਿਖੋ("%f ", error);
    }
    ਲਿਖੋ("\n");

    ਲਈ(i=0; i<LEN; i++){
        ਲਈ(j=0; j<LEN; j++){
            ਲਿਖੋ("%9.6f ", eigenvector[i + j*LEN]);
        }
        ਲਿਖੋ("  %9.1f %f\n", eigenvalue[i], eigenvalue[i]/eigenvalue[0]);
    }

    ff_pca_free(pca);
    ਵਾਪਸ 0;
}
