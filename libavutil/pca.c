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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ PCA{
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2;
    ಪೂರ್ಣಾಂಕ n;
    ದ್ವಿಗುಣ *covariance;
    ದ್ವಿಗುಣ *ಸರಾಸರಿ;
    ದ್ವಿಗುಣ *z;
}PCA;

PCA *ff_pca_init(ಪೂರ್ಣಾಂಕ n){
    PCA *pca;
    ಆದರೆ(n<=0)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    pca= av_mallocz(ಗಾತ್ರ(*pca));
    ಆದರೆ (!pca)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    pca->n= n;
    pca->z = av_malloc_array(n, ಗಾತ್ರ(*pca->z));
    pca->ಎಣಿಕೆ_2=0;
    pca->covariance= av_calloc(n*n, ಗಾತ್ರ(ದ್ವಿಗುಣ));
    pca->ಸರಾಸರಿ= av_calloc(n, ಗಾತ್ರ(ದ್ವಿಗುಣ));

    ಆದರೆ (!pca->z || !pca->covariance || !pca->ಸರಾಸರಿ) {
        ff_pca_free(pca);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ pca;
}

ಶೂನ್ಯ ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->ಸರಾಸರಿ);
    av_freep(&pca->z);
    av_free(pca);
}

ಶೂನ್ಯ ff_pca_ಕೂಡಿಸು(PCA *pca, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v){
    ಪೂರ್ಣಾಂಕ i, j;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ n= pca->n;

    ಗಾಗಿ(i=0; i<n; i++){
        pca->ಸರಾಸರಿ[i] += v[i];
        ಗಾಗಿ(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->ಎಣಿಕೆ_2++;
}

ಪೂರ್ಣಾಂಕ ff_pca(PCA *pca, ದ್ವಿಗುಣ *eigenvector, ದ್ವಿಗುಣ *eigenvalue){
    ಪೂರ್ಣಾಂಕ i, j, pass;
    ಪೂರ್ಣಾಂಕ k=0;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ n= pca->n;
    ದ್ವಿಗುಣ *z = pca->z;

    memset(eigenvector, 0, ಗಾತ್ರ(ದ್ವಿಗುಣ)*n*n);

    ಗಾಗಿ(j=0; j<n; j++){
        pca->ಸರಾಸರಿ[j] /= pca->ಎಣಿಕೆ_2;
        eigenvector[j + j*n] = 1.0;
        ಗಾಗಿ(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->ಎಣಿಕೆ_2;
            pca->covariance[j + i*n] -= pca->ಸರಾಸರಿ[i] * pca->ಸರಾಸರಿ[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    ಗಾಗಿ(pass=0; pass < 50; pass++){
        ದ್ವಿಗುಣ ಮೊತ್ತ=0;

        ಗಾಗಿ(i=0; i<n; i++)
            ಗಾಗಿ(j=i+1; j<n; j++)
                ಮೊತ್ತ += fabs(pca->covariance[j + i*n]);

        ಆದರೆ(ಮೊತ್ತ == 0){
            ಗಾಗಿ(i=0; i<n; i++){
                ದ್ವಿಗುಣ maxvalue= -1;
                ಗಾಗಿ(j=i; j<n; j++){
                    ಆದರೆ(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                ಗಾಗಿ(j=0; j<n; j++){
                    ದ್ವಿಗುಣ tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            ಹಿಂತಿರುಗಿ pass;
        }

        ಗಾಗಿ(i=0; i<n; i++){
            ಗಾಗಿ(j=i+1; j<n; j++){
                ದ್ವಿಗುಣ covar= pca->covariance[j + i*n];
                ದ್ವಿಗುಣ t,c,s,tau,theta, h;

                ಆದರೆ(pass < 3 && fabs(covar) < ಮೊತ್ತ / (5*n*n)) //FIXME why pass < 3
                    ಮುಂದುವರಿ;
                ಆದರೆ(fabs(covar) == 0.0) //FIXME should not be needed
                    ಮುಂದುವರಿ;
                ಆದರೆ(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    ಮುಂದುವರಿ;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+ವರ್ಗಮೂಲ(1.0+theta*theta));
                ಆದರೆ(theta < 0.0) t = -t;

                c=1.0/ವರ್ಗಮೂಲ(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#ವ್ಯಾಖ್ಯಾನಿಸು ROTATE(a,i,j,k,l) {\
    ದ್ವಿಗುಣ g=a[j + i*n];\
    ದ್ವಿಗುಣ h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                ಗಾಗಿ(k=0; k<n; k++) {
                    ಆದರೆ(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        ಗಾಗಿ (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    ಹಿಂತಿರುಗಿ -1;
}
