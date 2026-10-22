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

#ضمن "libavutil/pca.c"
#ضمن "libavutil/lfg.h"

#ضمن <stdio.h>
#ضمن <stdlib.h>

صحيح اصلی(فراغ){
    PCA *pca;
    صحيح i, j, k;
#تعریف_کن LEN 8
    مزدوج eigenvector[LEN*LEN];
    مزدوج eigenvalue[LEN];
    AVLFG prng;

    av_lfg_init(&prng, 1);

    pca= ff_pca_init(LEN);

    لكل(i=0; i<9000000; i++){
        مزدوج v[2*LEN+100];
//        double sum=0;
        صحيح pos = av_lfg_get(&prng) % LEN;
        صحيح v2  = (صحيح)(av_lfg_get(&prng) % 101) - 50;
        v[0]    = (صحيح)(av_lfg_get(&prng) % 101) - 50;
        لكل(j=1; j<8; j++){
            إذا(j<=pos) v[j]= v[0];
            وإلا       v[j]= v2;
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
        ff_pca_جمع_کن(pca, v);
    }


    ff_pca(pca, eigenvector, eigenvalue);
    لكل(i=0; i<LEN; i++){
        pca->شمار= 1;
        pca->میانگین[i]= 0;

//        (0.5^|x|)^2 = 0.5^2|x| = 0.25^|x|


//        pca.covariance[i + i*LEN]= pow(0.5, fabs
        لكل(j=i; j<LEN; j++){
            چاپ_کن("%f ", pca->covariance[i + j*LEN]);
        }
        چاپ_کن("\n");
    }

    لكل(i=0; i<LEN; i++){
        مزدوج v[LEN];
        مزدوج error=0;
        memset(v, 0, حجم(v));
        لكل(j=0; j<LEN; j++){
            لكل(k=0; k<LEN; k++){
                v[j] += pca->covariance[FFMIN(k,j) + FFMAX(k,j)*LEN] * eigenvector[i + k*LEN];
            }
            v[j] /= eigenvalue[i];
            error += fabs(v[j] - eigenvector[i + j*LEN]);
        }
        چاپ_کن("%f ", error);
    }
    چاپ_کن("\n");

    لكل(i=0; i<LEN; i++){
        لكل(j=0; j<LEN; j++){
            چاپ_کن("%9.6f ", eigenvector[i + j*LEN]);
        }
        چاپ_کن("  %9.1f %f\n", eigenvalue[i], eigenvalue[i]/eigenvalue[0]);
    }

    ff_pca_free(pca);
    أرجع 0;
}
