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
    цяло count;
    цяло n;
    double *covariance;
    double *mean;
    double *z;
}PCA;

PCA *ff_pca_init(цяло n){
    PCA *pca;
    ако(n<=0)
        върни NULL;

    pca= av_mallocz(sizeof(*pca));
    ако (!pca)
        върни NULL;

    pca->n= n;
    pca->z = av_malloc_array(n, sizeof(*pca->z));
    pca->count=0;
    pca->covariance= av_calloc(n*n, sizeof(double));
    pca->mean= av_calloc(n, sizeof(double));

    ако (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        върни NULL;
    }

    върни pca;
}

void ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

void ff_pca_add(PCA *pca, const double *v){
    цяло i, j;
    const цяло n= pca->n;

    за(i=0; i<n; i++){
        pca->mean[i] += v[i];
        за(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->count++;
}

цяло ff_pca(PCA *pca, double *eigenvector, double *eigenvalue){
    цяло i, j, pass;
    цяло k=0;
    const цяло n= pca->n;
    double *z = pca->z;

    memset(eigenvector, 0, sizeof(double)*n*n);

    за(j=0; j<n; j++){
        pca->mean[j] /= pca->count;
        eigenvector[j + j*n] = 1.0;
        за(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->count;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    за(pass=0; pass < 50; pass++){
        double sum=0;

        за(i=0; i<n; i++)
            за(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        ако(sum == 0){
            за(i=0; i<n; i++){
                double maxvalue= -1;
                за(j=i; j<n; j++){
                    ако(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                за(j=0; j<n; j++){
                    double tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            върни pass;
        }

        за(i=0; i<n; i++){
            за(j=i+1; j<n; j++){
                double covar= pca->covariance[j + i*n];
                double t,c,s,tau,theta, h;

                ако(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    continue;
                ако(fabs(covar) == 0.0) //FIXME should not be needed
                    continue;
                ако(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    continue;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                ако(theta < 0.0) t = -t;

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
                за(k=0; k<n; k++) {
                    ако(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        за (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    върни -1;
}
