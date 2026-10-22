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

/**
 * @file
 * principal component analysis (PCA)
 */

#समावेश "common.h"
#समावेश "mem.h"
#समावेश "pca.h"

प्रकार काष्ठा PCA{
    पूर्णांक गिनती;
    पूर्णांक n;
    द्विगुन *covariance;
    द्विगुन *mean;
    द्विगुन *z;
}PCA;

PCA *ff_pca_init(पूर्णांक n){
    PCA *pca;
    अगर(n<=0)
        वापस शून्य;

    pca= av_mallocz(माप(*pca));
    अगर (!pca)
        वापस शून्य;

    pca->n= n;
    pca->z = av_malloc_array(n, माप(*pca->z));
    pca->गिनती=0;
    pca->covariance= av_calloc(n*n, माप(द्विगुन));
    pca->mean= av_calloc(n, माप(द्विगुन));

    अगर (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        वापस शून्य;
    }

    वापस pca;
}

व्योम ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

व्योम ff_pca_add(PCA *pca, स्थिर द्विगुन *v){
    पूर्णांक i, j;
    स्थिर पूर्णांक n= pca->n;

    क्रम(i=0; i<n; i++){
        pca->mean[i] += v[i];
        क्रम(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->गिनती++;
}

पूर्णांक ff_pca(PCA *pca, द्विगुन *eigenvector, द्विगुन *eigenvalue){
    पूर्णांक i, j, pass;
    पूर्णांक k=0;
    स्थिर पूर्णांक n= pca->n;
    द्विगुन *z = pca->z;

    स_रखो(eigenvector, 0, माप(द्विगुन)*n*n);

    क्रम(j=0; j<n; j++){
        pca->mean[j] /= pca->गिनती;
        eigenvector[j + j*n] = 1.0;
        क्रम(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->गिनती;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    क्रम(pass=0; pass < 50; pass++){
        द्विगुन योग=0;

        क्रम(i=0; i<n; i++)
            क्रम(j=i+1; j<n; j++)
                योग += भ_असल(pca->covariance[j + i*n]);

        अगर(योग == 0){
            क्रम(i=0; i<n; i++){
                द्विगुन maxvalue= -1;
                क्रम(j=i; j<n; j++){
                    अगर(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                क्रम(j=0; j<n; j++){
                    द्विगुन tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            वापस pass;
        }

        क्रम(i=0; i<n; i++){
            क्रम(j=i+1; j<n; j++){
                द्विगुन covar= pca->covariance[j + i*n];
                द्विगुन t,c,s,tau,theta, h;

                अगर(pass < 3 && भ_असल(covar) < योग / (5*n*n)) //FIXME why pass < 3
                    जारी;
                अगर(भ_असल(covar) == 0.0) //FIXME should not be needed
                    जारी;
                अगर(pass >=3 && भ_असल((eigenvalue[j]+z[j])/covar) > (1LL<<32) && भ_असल((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    जारी;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(भ_असल(theta)+वर्ग_मूल(1.0+theta*theta));
                अगर(theta < 0.0) t = -t;

                c=1.0/वर्ग_मूल(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#घोषणा ROTATE(a,i,j,k,l) {\
    द्विगुन g=a[j + i*n];\
    द्विगुन h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                क्रम(k=0; k<n; k++) {
                    अगर(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        क्रम (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    वापस -1;
}
