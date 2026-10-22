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

#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pca.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ PCA{
    ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ;
    ಪೂರ್ಣಾಙ್ಕ n;
    ದ್ವಿಗುಣ *covariance;
    ದ್ವಿಗುಣ *mean;
    ದ್ವಿಗುಣ *z;
}PCA;

PCA *ff_pca_init(ಪೂರ್ಣಾಙ್ಕ n){
    PCA *pca;
    ಯದಿ(n<=0)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    pca= av_mallocz(ಪರಿಮಾಣ(*pca));
    ಯದಿ (!pca)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    pca->n= n;
    pca->z = av_malloc_array(n, ಪರಿಮಾಣ(*pca->z));
    pca->ಎಣಿಕೆ=0;
    pca->covariance= av_calloc(n*n, ಪರಿಮಾಣ(ದ್ವಿಗುಣ));
    pca->mean= av_calloc(n, ಪರಿಮಾಣ(ದ್ವಿಗುಣ));

    ಯದಿ (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ pca;
}

ಶೂನ್ಯ ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

ಶೂನ್ಯ ff_pca_add(PCA *pca, ಧ್ರುವ ದ್ವಿಗುಣ *v){
    ಪೂರ್ಣಾಙ್ಕ i, j;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ n= pca->n;

    ಪ್ರತಿ(i=0; i<n; i++){
        pca->mean[i] += v[i];
        ಪ್ರತಿ(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->ಎಣಿಕೆ++;
}

ಪೂರ್ಣಾಙ್ಕ ff_pca(PCA *pca, ದ್ವಿಗುಣ *eigenvector, ದ್ವಿಗುಣ *eigenvalue){
    ಪೂರ್ಣಾಙ್ಕ i, j, pass;
    ಪೂರ್ಣಾಙ್ಕ k=0;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ n= pca->n;
    ದ್ವಿಗುಣ *z = pca->z;

    memset(eigenvector, 0, ಪರಿಮಾಣ(ದ್ವಿಗುಣ)*n*n);

    ಪ್ರತಿ(j=0; j<n; j++){
        pca->mean[j] /= pca->ಎಣಿಕೆ;
        eigenvector[j + j*n] = 1.0;
        ಪ್ರತಿ(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->ಎಣಿಕೆ;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    ಪ್ರತಿ(pass=0; pass < 50; pass++){
        ದ್ವಿಗುಣ sum=0;

        ಪ್ರತಿ(i=0; i<n; i++)
            ಪ್ರತಿ(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        ಯದಿ(sum == 0){
            ಪ್ರತಿ(i=0; i<n; i++){
                ದ್ವಿಗುಣ maxvalue= -1;
                ಪ್ರತಿ(j=i; j<n; j++){
                    ಯದಿ(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                ಪ್ರತಿ(j=0; j<n; j++){
                    ದ್ವಿಗುಣ tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            ಪ್ರತ್ಯಾಗಮ pass;
        }

        ಪ್ರತಿ(i=0; i<n; i++){
            ಪ್ರತಿ(j=i+1; j<n; j++){
                ದ್ವಿಗುಣ covar= pca->covariance[j + i*n];
                ದ್ವಿಗುಣ t,c,s,tau,theta, h;

                ಯದಿ(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    ಅನುವರ್ತ;
                ಯದಿ(fabs(covar) == 0.0) //FIXME should not be needed
                    ಅನುವರ್ತ;
                ಯದಿ(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    ಅನುವರ್ತ;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                ಯದಿ(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    ದ್ವಿಗುಣ g=a[j + i*n];\
    ದ್ವಿಗುಣ h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                ಪ್ರತಿ(k=0; k<n; k++) {
                    ಯದಿ(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        ಪ್ರತಿ (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    ಪ್ರತ್ಯಾಗಮ -1;
}
