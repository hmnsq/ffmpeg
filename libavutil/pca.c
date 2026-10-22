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

#అన్తర్భావ "common.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pca.h"

రకనిర్వచనం నిర్మాణం PCA{
    పూర్ణాంకం లెక్క;
    పూర్ణాంకం n;
    ద్విగుణ *covariance;
    ద్విగుణ *సగటు;
    ద్విగుణ *z;
}PCA;

PCA *ff_pca_init(పూర్ణాంకం n){
    PCA *pca;
    ఒకవేళ(n<=0)
        తిరిగి ఖాళీ;

    pca= av_mallocz(పరిమాణం(*pca));
    ఒకవేళ (!pca)
        తిరిగి ఖాళీ;

    pca->n= n;
    pca->z = av_malloc_array(n, పరిమాణం(*pca->z));
    pca->లెక్క=0;
    pca->covariance= av_calloc(n*n, పరిమాణం(ద్విగుణ));
    pca->సగటు= av_calloc(n, పరిమాణం(ద్విగుణ));

    ఒకవేళ (!pca->z || !pca->covariance || !pca->సగటు) {
        ff_pca_free(pca);
        తిరిగి ఖాళీ;
    }

    తిరిగి pca;
}

శూన్య ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->సగటు);
    av_freep(&pca->z);
    av_free(pca);
}

శూన్య ff_pca_కూడు(PCA *pca, స్థిరరాశి ద్విగుణ *v){
    పూర్ణాంకం i, j;
    స్థిరరాశి పూర్ణాంకం n= pca->n;

    కొరకు(i=0; i<n; i++){
        pca->సగటు[i] += v[i];
        కొరకు(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->లెక్క++;
}

పూర్ణాంకం ff_pca(PCA *pca, ద్విగుణ *eigenvector, ద్విగుణ *eigenvalue){
    పూర్ణాంకం i, j, pass;
    పూర్ణాంకం k=0;
    స్థిరరాశి పూర్ణాంకం n= pca->n;
    ద్విగుణ *z = pca->z;

    memset(eigenvector, 0, పరిమాణం(ద్విగుణ)*n*n);

    కొరకు(j=0; j<n; j++){
        pca->సగటు[j] /= pca->లెక్క;
        eigenvector[j + j*n] = 1.0;
        కొరకు(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->లెక్క;
            pca->covariance[j + i*n] -= pca->సగటు[i] * pca->సగటు[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    కొరకు(pass=0; pass < 50; pass++){
        ద్విగుణ కూడిక=0;

        కొరకు(i=0; i<n; i++)
            కొరకు(j=i+1; j<n; j++)
                కూడిక += fabs(pca->covariance[j + i*n]);

        ఒకవేళ(కూడిక == 0){
            కొరకు(i=0; i<n; i++){
                ద్విగుణ maxvalue= -1;
                కొరకు(j=i; j<n; j++){
                    ఒకవేళ(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                కొరకు(j=0; j<n; j++){
                    ద్విగుణ tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            తిరిగి pass;
        }

        కొరకు(i=0; i<n; i++){
            కొరకు(j=i+1; j<n; j++){
                ద్విగుణ covar= pca->covariance[j + i*n];
                ద్విగుణ t,c,s,tau,theta, h;

                ఒకవేళ(pass < 3 && fabs(covar) < కూడిక / (5*n*n)) //FIXME why pass < 3
                    కొనసాగు;
                ఒకవేళ(fabs(covar) == 0.0) //FIXME should not be needed
                    కొనసాగు;
                ఒకవేళ(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    కొనసాగు;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+వర్గమూలం(1.0+theta*theta));
                ఒకవేళ(theta < 0.0) t = -t;

                c=1.0/వర్గమూలం(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#నిర్వచించు ROTATE(a,i,j,k,l) {\
    ద్విగుణ g=a[j + i*n];\
    ద్విగుణ h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                కొరకు(k=0; k<n; k++) {
                    ఒకవేళ(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        కొరకు (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    తిరిగి -1;
}
