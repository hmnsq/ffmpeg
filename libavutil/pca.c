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

#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pca.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ PCA{
    ਪੂਰਨ ਗਿਣਤੀ_2;
    ਪੂਰਨ n;
    ਦੁੱਗਣਾ *covariance;
    ਦੁੱਗਣਾ *ਔਸਤ;
    ਦੁੱਗਣਾ *z;
}PCA;

PCA *ff_pca_init(ਪੂਰਨ n){
    PCA *pca;
    ਜੇ(n<=0)
        ਵਾਪਸ ਨਿਰਾ;

    pca= av_mallocz(ਆਕਾਰ(*pca));
    ਜੇ (!pca)
        ਵਾਪਸ ਨਿਰਾ;

    pca->n= n;
    pca->z = av_malloc_array(n, ਆਕਾਰ(*pca->z));
    pca->ਗਿਣਤੀ_2=0;
    pca->covariance= av_calloc(n*n, ਆਕਾਰ(ਦੁੱਗਣਾ));
    pca->ਔਸਤ= av_calloc(n, ਆਕਾਰ(ਦੁੱਗਣਾ));

    ਜੇ (!pca->z || !pca->covariance || !pca->ਔਸਤ) {
        ff_pca_free(pca);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ pca;
}

ਖਾਲੀ ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->ਔਸਤ);
    av_freep(&pca->z);
    av_free(pca);
}

ਖਾਲੀ ff_pca_ਜੋੜੋ(PCA *pca, ਅਚਲ ਦੁੱਗਣਾ *v){
    ਪੂਰਨ i, j;
    ਅਚਲ ਪੂਰਨ n= pca->n;

    ਲਈ(i=0; i<n; i++){
        pca->ਔਸਤ[i] += v[i];
        ਲਈ(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->ਗਿਣਤੀ_2++;
}

ਪੂਰਨ ff_pca(PCA *pca, ਦੁੱਗਣਾ *eigenvector, ਦੁੱਗਣਾ *eigenvalue){
    ਪੂਰਨ i, j, pass;
    ਪੂਰਨ k=0;
    ਅਚਲ ਪੂਰਨ n= pca->n;
    ਦੁੱਗਣਾ *z = pca->z;

    memset(eigenvector, 0, ਆਕਾਰ(ਦੁੱਗਣਾ)*n*n);

    ਲਈ(j=0; j<n; j++){
        pca->ਔਸਤ[j] /= pca->ਗਿਣਤੀ_2;
        eigenvector[j + j*n] = 1.0;
        ਲਈ(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->ਗਿਣਤੀ_2;
            pca->covariance[j + i*n] -= pca->ਔਸਤ[i] * pca->ਔਸਤ[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    ਲਈ(pass=0; pass < 50; pass++){
        ਦੁੱਗਣਾ ਜੋੜ=0;

        ਲਈ(i=0; i<n; i++)
            ਲਈ(j=i+1; j<n; j++)
                ਜੋੜ += fabs(pca->covariance[j + i*n]);

        ਜੇ(ਜੋੜ == 0){
            ਲਈ(i=0; i<n; i++){
                ਦੁੱਗਣਾ maxvalue= -1;
                ਲਈ(j=i; j<n; j++){
                    ਜੇ(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                ਲਈ(j=0; j<n; j++){
                    ਦੁੱਗਣਾ tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            ਵਾਪਸ pass;
        }

        ਲਈ(i=0; i<n; i++){
            ਲਈ(j=i+1; j<n; j++){
                ਦੁੱਗਣਾ covar= pca->covariance[j + i*n];
                ਦੁੱਗਣਾ t,c,s,tau,theta, h;

                ਜੇ(pass < 3 && fabs(covar) < ਜੋੜ / (5*n*n)) //FIXME why pass < 3
                    ਜਾਰੀ;
                ਜੇ(fabs(covar) == 0.0) //FIXME should not be needed
                    ਜਾਰੀ;
                ਜੇ(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    ਜਾਰੀ;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+ਵਰਗਮੂਲ(1.0+theta*theta));
                ਜੇ(theta < 0.0) t = -t;

                c=1.0/ਵਰਗਮੂਲ(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROTATE(a,i,j,k,l) {\
    ਦੁੱਗਣਾ g=a[j + i*n];\
    ਦੁੱਗਣਾ h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                ਲਈ(k=0; k<n; k++) {
                    ਜੇ(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        ਲਈ (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    ਵਾਪਸ -1;
}
