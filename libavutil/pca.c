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

#அந்தர்பாவ "common.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pca.h"

வகைவரை கட்டமைப்பு PCA{
    முழு மொத்தம்;
    முழு n;
    இரட்டை *covariance;
    இரட்டை *mean;
    இரட்டை *z;
}PCA;

PCA *ff_pca_init(முழு n){
    PCA *pca;
    எனில்(n<=0)
        திரும்பு வெற்று;

    pca= av_mallocz(அளவு(*pca));
    எனில் (!pca)
        திரும்பு வெற்று;

    pca->n= n;
    pca->z = av_malloc_array(n, அளவு(*pca->z));
    pca->மொத்தம்=0;
    pca->covariance= av_calloc(n*n, அளவு(இரட்டை));
    pca->mean= av_calloc(n, அளவு(இரட்டை));

    எனில் (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        திரும்பு வெற்று;
    }

    திரும்பு pca;
}

வெறுமை ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

வெறுமை ff_pca_add(PCA *pca, மாறிலி இரட்டை *v){
    முழு i, j;
    மாறிலி முழு n= pca->n;

    க்கு(i=0; i<n; i++){
        pca->mean[i] += v[i];
        க்கு(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->மொத்தம்++;
}

முழு ff_pca(PCA *pca, இரட்டை *eigenvector, இரட்டை *eigenvalue){
    முழு i, j, pass;
    முழு k=0;
    மாறிலி முழு n= pca->n;
    இரட்டை *z = pca->z;

    memset(eigenvector, 0, அளவு(இரட்டை)*n*n);

    க்கு(j=0; j<n; j++){
        pca->mean[j] /= pca->மொத்தம்;
        eigenvector[j + j*n] = 1.0;
        க்கு(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->மொத்தம்;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    க்கு(pass=0; pass < 50; pass++){
        இரட்டை sum=0;

        க்கு(i=0; i<n; i++)
            க்கு(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        எனில்(sum == 0){
            க்கு(i=0; i<n; i++){
                இரட்டை maxvalue= -1;
                க்கு(j=i; j<n; j++){
                    எனில்(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                க்கு(j=0; j<n; j++){
                    இரட்டை tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            திரும்பு pass;
        }

        க்கு(i=0; i<n; i++){
            க்கு(j=i+1; j<n; j++){
                இரட்டை covar= pca->covariance[j + i*n];
                இரட்டை t,c,s,tau,theta, h;

                எனில்(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    தொடர்;
                எனில்(fabs(covar) == 0.0) //FIXME should not be needed
                    தொடர்;
                எனில்(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    தொடர்;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                எனில்(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    இரட்டை g=a[j + i*n];\
    இரட்டை h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                க்கு(k=0; k<n; k++) {
                    எனில்(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        க்கு (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    திரும்பு -1;
}
