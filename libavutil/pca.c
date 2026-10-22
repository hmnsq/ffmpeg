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

#include "common.h"
#include "mem.h"
#include "pca.h"

typedef struct PCA{
    ціле count;
    ціле n;
    double *covariance;
    double *mean;
    double *z;
}PCA;

PCA *ff_pca_init(ціле n){
    PCA *pca;
    якщо(n<=0)
        повернути NULL;

    pca= av_mallocz(sizeof(*pca));
    якщо (!pca)
        повернути NULL;

    pca->n= n;
    pca->z = av_malloc_array(n, sizeof(*pca->z));
    pca->count=0;
    pca->covariance= av_calloc(n*n, sizeof(double));
    pca->mean= av_calloc(n, sizeof(double));

    якщо (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        повернути NULL;
    }

    повернути pca;
}

void ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

void ff_pca_add(PCA *pca, const double *v){
    ціле i, j;
    const ціле n= pca->n;

    для(i=0; i<n; i++){
        pca->mean[i] += v[i];
        для(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->count++;
}

ціле ff_pca(PCA *pca, double *eigenvector, double *eigenvalue){
    ціле i, j, pass;
    ціле k=0;
    const ціле n= pca->n;
    double *z = pca->z;

    memset(eigenvector, 0, sizeof(double)*n*n);

    для(j=0; j<n; j++){
        pca->mean[j] /= pca->count;
        eigenvector[j + j*n] = 1.0;
        для(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->count;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    для(pass=0; pass < 50; pass++){
        double sum=0;

        для(i=0; i<n; i++)
            для(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        якщо(sum == 0){
            для(i=0; i<n; i++){
                double maxvalue= -1;
                для(j=i; j<n; j++){
                    якщо(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                для(j=0; j<n; j++){
                    double tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            повернути pass;
        }

        для(i=0; i<n; i++){
            для(j=i+1; j<n; j++){
                double covar= pca->covariance[j + i*n];
                double t,c,s,tau,theta, h;

                якщо(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    continue;
                якщо(fabs(covar) == 0.0) //FIXME should not be needed
                    continue;
                якщо(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    continue;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                якщо(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    double g=a[j + i*n];\
    double h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                для(k=0; k<n; k++) {
                    якщо(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        для (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    повернути -1;
}
