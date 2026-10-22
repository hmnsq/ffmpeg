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

#অন্তর্ভাৱ "common.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "pca.h"

প্রকারনির্দেশ সংরচনা PCA{
    পূর্ণাঙ্ক গুনতি;
    পূর্ণাঙ্ক n;
    দ্ৱিগুণ *covariance;
    দ্ৱিগুণ *mean;
    দ্ৱিগুণ *z;
}PCA;

PCA *ff_pca_init(পূর্ণাঙ্ক n){
    PCA *pca;
    যদি(n<=0)
        ঘূৰাই রিক্ত;

    pca= av_mallocz(পরিমাণ(*pca));
    যদি (!pca)
        ঘূৰাই রিক্ত;

    pca->n= n;
    pca->z = av_malloc_array(n, পরিমাণ(*pca->z));
    pca->গুনতি=0;
    pca->covariance= av_calloc(n*n, পরিমাণ(দ্ৱিগুণ));
    pca->mean= av_calloc(n, পরিমাণ(দ্ৱিগুণ));

    যদি (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        ঘূৰাই রিক্ত;
    }

    ঘূৰাই pca;
}

শূন্য ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

শূন্য ff_pca_add(PCA *pca, ধ্রুৱ দ্ৱিগুণ *v){
    পূর্ণাঙ্ক i, j;
    ধ্রুৱ পূর্ণাঙ্ক n= pca->n;

    বাবে(i=0; i<n; i++){
        pca->mean[i] += v[i];
        বাবে(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->গুনতি++;
}

পূর্ণাঙ্ক ff_pca(PCA *pca, দ্ৱিগুণ *eigenvector, দ্ৱিগুণ *eigenvalue){
    পূর্ণাঙ্ক i, j, pass;
    পূর্ণাঙ্ক k=0;
    ধ্রুৱ পূর্ণাঙ্ক n= pca->n;
    দ্ৱিগুণ *z = pca->z;

    memset(eigenvector, 0, পরিমাণ(দ্ৱিগুণ)*n*n);

    বাবে(j=0; j<n; j++){
        pca->mean[j] /= pca->গুনতি;
        eigenvector[j + j*n] = 1.0;
        বাবে(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->গুনতি;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    বাবে(pass=0; pass < 50; pass++){
        দ্ৱিগুণ sum=0;

        বাবে(i=0; i<n; i++)
            বাবে(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        যদি(sum == 0){
            বাবে(i=0; i<n; i++){
                দ্ৱিগুণ maxvalue= -1;
                বাবে(j=i; j<n; j++){
                    যদি(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                বাবে(j=0; j<n; j++){
                    দ্ৱিগুণ tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            ঘূৰাই pass;
        }

        বাবে(i=0; i<n; i++){
            বাবে(j=i+1; j<n; j++){
                দ্ৱিগুণ covar= pca->covariance[j + i*n];
                দ্ৱিগুণ t,c,s,tau,theta, h;

                যদি(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    অনুৱর্ত;
                যদি(fabs(covar) == 0.0) //FIXME should not be needed
                    অনুৱর্ত;
                যদি(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    অনুৱর্ত;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                যদি(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    দ্ৱিগুণ g=a[j + i*n];\
    দ্ৱিগুণ h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                বাবে(k=0; k<n; k++) {
                    যদি(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        বাবে (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    ঘূৰাই -1;
}
