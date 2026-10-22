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

#समावेश "libavutil/pca.c"
#समावेश "libavutil/lfg.h"

#समावेश <stdio.h>
#समावेश <stdlib.h>

पूर्णांक मुख्य(व्योम){
    PCA *pca;
    पूर्णांक i, j, k;
#घोषणा LEN 8
    द्विगुन eigenvector[LEN*LEN];
    द्विगुन eigenvalue[LEN];
    AVLFG prng;

    av_lfg_init(&prng, 1);

    pca= ff_pca_init(LEN);

    क्रम(i=0; i<9000000; i++){
        द्विगुन v[2*LEN+100];
//        double sum=0;
        पूर्णांक pos = av_lfg_get(&prng) % LEN;
        पूर्णांक v2  = (पूर्णांक)(av_lfg_get(&prng) % 101) - 50;
        v[0]    = (पूर्णांक)(av_lfg_get(&prng) % 101) - 50;
        क्रम(j=1; j<8; j++){
            अगर(j<=pos) v[j]= v[0];
            अन्यथा       v[j]= v2;
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
    क्रम(i=0; i<LEN; i++){
        pca->गिनती= 1;
        pca->mean[i]= 0;

//        (0.5^|x|)^2 = 0.5^2|x| = 0.25^|x|


//        pca.covariance[i + i*LEN]= pow(0.5, fabs
        क्रम(j=i; j<LEN; j++){
            म_लिखो("%f ", pca->covariance[i + j*LEN]);
        }
        म_लिखो("\n");
    }

    क्रम(i=0; i<LEN; i++){
        द्विगुन v[LEN];
        द्विगुन error=0;
        स_रखो(v, 0, माप(v));
        क्रम(j=0; j<LEN; j++){
            क्रम(k=0; k<LEN; k++){
                v[j] += pca->covariance[FFMIN(k,j) + FFMAX(k,j)*LEN] * eigenvector[i + k*LEN];
            }
            v[j] /= eigenvalue[i];
            error += भ_असल(v[j] - eigenvector[i + j*LEN]);
        }
        म_लिखो("%f ", error);
    }
    म_लिखो("\n");

    क्रम(i=0; i<LEN; i++){
        क्रम(j=0; j<LEN; j++){
            म_लिखो("%9.6f ", eigenvector[i + j*LEN]);
        }
        म_लिखो("  %9.1f %f\n", eigenvalue[i], eigenvalue[i]/eigenvalue[0]);
    }

    ff_pca_free(pca);
    वापस 0;
}
