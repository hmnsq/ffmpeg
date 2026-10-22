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

typedef sa_nracanaa PCA{
    จำนวนเต็ม count;
    จำนวนเต็ม n;
    dviguu_na *covariance;
    dviguu_na *mean;
    dviguu_na *z;
}PCA;

PCA *ff_pca_init(จำนวนเต็ม n){
    PCA *pca;
    ถ้า(n<=0)
        คืน NULL;

    pca= av_mallocz(parimaa_na(*pca));
    ถ้า (!pca)
        คืน NULL;

    pca->n= n;
    pca->z = av_malloc_array(n, parimaa_na(*pca->z));
    pca->count=0;
    pca->covariance= av_calloc(n*n, parimaa_na(dviguu_na));
    pca->mean= av_calloc(n, parimaa_na(dviguu_na));

    ถ้า (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        คืน NULL;
    }

    คืน pca;
}

void ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

void ff_pca_add(PCA *pca, const dviguu_na *v){
    จำนวนเต็ม i, j;
    const จำนวนเต็ม n= pca->n;

    สำหรับ(i=0; i<n; i++){
        pca->mean[i] += v[i];
        สำหรับ(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->count++;
}

จำนวนเต็ม ff_pca(PCA *pca, dviguu_na *eigenvector, dviguu_na *eigenvalue){
    จำนวนเต็ม i, j, pass;
    จำนวนเต็ม k=0;
    const จำนวนเต็ม n= pca->n;
    dviguu_na *z = pca->z;

    memset(eigenvector, 0, parimaa_na(dviguu_na)*n*n);

    สำหรับ(j=0; j<n; j++){
        pca->mean[j] /= pca->count;
        eigenvector[j + j*n] = 1.0;
        สำหรับ(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->count;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    สำหรับ(pass=0; pass < 50; pass++){
        dviguu_na sum=0;

        สำหรับ(i=0; i<n; i++)
            สำหรับ(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        ถ้า(sum == 0){
            สำหรับ(i=0; i<n; i++){
                dviguu_na maxvalue= -1;
                สำหรับ(j=i; j<n; j++){
                    ถ้า(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                สำหรับ(j=0; j<n; j++){
                    dviguu_na tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            คืน pass;
        }

        สำหรับ(i=0; i<n; i++){
            สำหรับ(j=i+1; j<n; j++){
                dviguu_na covar= pca->covariance[j + i*n];
                dviguu_na t,c,s,tau,theta, h;

                ถ้า(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    continue;
                ถ้า(fabs(covar) == 0.0) //FIXME should not be needed
                    continue;
                ถ้า(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    continue;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                ถ้า(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    dviguu_na g=a[j + i*n];\
    dviguu_na h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                สำหรับ(k=0; k<n; k++) {
                    ถ้า(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        สำหรับ (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    คืน -1;
}
