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

#অন্তর্ভাব "common.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pca.h"

প্রকারলেখ কাঠামো PCA{
    পূর্ণসংখ্যা গুনতি;
    পূর্ণসংখ্যা n;
    দ্বিগুণ *covariance;
    দ্বিগুণ *mean;
    দ্বিগুণ *z;
}PCA;

PCA *ff_pca_init(পূর্ণসংখ্যা n){
    PCA *pca;
    যদি(n<=0)
        ফেরত ফাঁকা;

    pca= av_mallocz(আকার(*pca));
    যদি (!pca)
        ফেরত ফাঁকা;

    pca->n= n;
    pca->z = av_malloc_array(n, আকার(*pca->z));
    pca->গুনতি=0;
    pca->covariance= av_calloc(n*n, আকার(দ্বিগুণ));
    pca->mean= av_calloc(n, আকার(দ্বিগুণ));

    যদি (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        ফেরত ফাঁকা;
    }

    ফেরত pca;
}

শূন্য ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

শূন্য ff_pca_add(PCA *pca, ধ্রুবক দ্বিগুণ *v){
    পূর্ণসংখ্যা i, j;
    ধ্রুবক পূর্ণসংখ্যা n= pca->n;

    জন্য(i=0; i<n; i++){
        pca->mean[i] += v[i];
        জন্য(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->গুনতি++;
}

পূর্ণসংখ্যা ff_pca(PCA *pca, দ্বিগুণ *eigenvector, দ্বিগুণ *eigenvalue){
    পূর্ণসংখ্যা i, j, pass;
    পূর্ণসংখ্যা k=0;
    ধ্রুবক পূর্ণসংখ্যা n= pca->n;
    দ্বিগুণ *z = pca->z;

    memset(eigenvector, 0, আকার(দ্বিগুণ)*n*n);

    জন্য(j=0; j<n; j++){
        pca->mean[j] /= pca->গুনতি;
        eigenvector[j + j*n] = 1.0;
        জন্য(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->গুনতি;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    জন্য(pass=0; pass < 50; pass++){
        দ্বিগুণ যোগ=0;

        জন্য(i=0; i<n; i++)
            জন্য(j=i+1; j<n; j++)
                যোগ += fabs(pca->covariance[j + i*n]);

        যদি(যোগ == 0){
            জন্য(i=0; i<n; i++){
                দ্বিগুণ maxvalue= -1;
                জন্য(j=i; j<n; j++){
                    যদি(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                জন্য(j=0; j<n; j++){
                    দ্বিগুণ tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            ফেরত pass;
        }

        জন্য(i=0; i<n; i++){
            জন্য(j=i+1; j<n; j++){
                দ্বিগুণ covar= pca->covariance[j + i*n];
                দ্বিগুণ t,c,s,tau,theta, h;

                যদি(pass < 3 && fabs(covar) < যোগ / (5*n*n)) //FIXME why pass < 3
                    চালু;
                যদি(fabs(covar) == 0.0) //FIXME should not be needed
                    চালু;
                যদি(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    চালু;
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
    দ্বিগুণ g=a[j + i*n];\
    দ্বিগুণ h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                জন্য(k=0; k<n; k++) {
                    যদি(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        জন্য (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    ফেরত -1;
}
