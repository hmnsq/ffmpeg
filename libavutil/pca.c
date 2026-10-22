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

#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pca.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା PCA{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା n;
    ଦ୍ୱିଗୁଣ *covariance;
    ଦ୍ୱିଗୁଣ *mean;
    ଦ୍ୱିଗୁଣ *z;
}PCA;

PCA *ff_pca_init(ପୂର୍ଣ୍ଣସଂଖ୍ୟା n){
    PCA *pca;
    ଯଦି(n<=0)
        ଫେରନ୍ତୁ ଖାଲି;

    pca= av_mallocz(ଆକାର(*pca));
    ଯଦି (!pca)
        ଫେରନ୍ତୁ ଖାଲି;

    pca->n= n;
    pca->z = av_malloc_array(n, ଆକାର(*pca->z));
    pca->ଗଣନା_2=0;
    pca->covariance= av_calloc(n*n, ଆକାର(ଦ୍ୱିଗୁଣ));
    pca->mean= av_calloc(n, ଆକାର(ଦ୍ୱିଗୁଣ));

    ଯଦି (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ pca;
}

ଶୂନ୍ୟ ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

ଶୂନ୍ୟ ff_pca_add(PCA *pca, ଅଚଳ ଦ୍ୱିଗୁଣ *v){
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା n= pca->n;

    ପାଇଁ(i=0; i<n; i++){
        pca->mean[i] += v[i];
        ପାଇଁ(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->ଗଣନା_2++;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pca(PCA *pca, ଦ୍ୱିଗୁଣ *eigenvector, ଦ୍ୱିଗୁଣ *eigenvalue){
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j, pass;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା k=0;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା n= pca->n;
    ଦ୍ୱିଗୁଣ *z = pca->z;

    memset(eigenvector, 0, ଆକାର(ଦ୍ୱିଗୁଣ)*n*n);

    ପାଇଁ(j=0; j<n; j++){
        pca->mean[j] /= pca->ଗଣନା_2;
        eigenvector[j + j*n] = 1.0;
        ପାଇଁ(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->ଗଣନା_2;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    ପାଇଁ(pass=0; pass < 50; pass++){
        ଦ୍ୱିଗୁଣ sum=0;

        ପାଇଁ(i=0; i<n; i++)
            ପାଇଁ(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        ଯଦି(sum == 0){
            ପାଇଁ(i=0; i<n; i++){
                ଦ୍ୱିଗୁଣ maxvalue= -1;
                ପାଇଁ(j=i; j<n; j++){
                    ଯଦି(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                ପାଇଁ(j=0; j<n; j++){
                    ଦ୍ୱିଗୁଣ tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            ଫେରନ୍ତୁ pass;
        }

        ପାଇଁ(i=0; i<n; i++){
            ପାଇଁ(j=i+1; j<n; j++){
                ଦ୍ୱିଗୁଣ covar= pca->covariance[j + i*n];
                ଦ୍ୱିଗୁଣ t,c,s,tau,theta, h;

                ଯଦି(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    ଜାରି;
                ଯଦି(fabs(covar) == 0.0) //FIXME should not be needed
                    ଜାରି;
                ଯଦି(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    ଜାରି;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                ଯଦି(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    ଦ୍ୱିଗୁଣ g=a[j + i*n];\
    ଦ୍ୱିଗୁଣ h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                ପାଇଁ(k=0; k<n; k++) {
                    ଯଦି(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        ପାଇଁ (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    ଫେରନ୍ତୁ -1;
}
