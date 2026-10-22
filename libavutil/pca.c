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

#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "pca.h"

પ્રકારવ્યાખ્યા સંરચના PCA{
    પૂર્ણાંક ગણતરી;
    પૂર્ણાંક n;
    દ્વિગુણ *covariance;
    દ્વિગુણ *mean;
    દ્વિગુણ *z;
}PCA;

PCA *ff_pca_init(પૂર્ણાંક n){
    PCA *pca;
    જો(n<=0)
        પાછા ખાલી;

    pca= av_mallocz(કદ(*pca));
    જો (!pca)
        પાછા ખાલી;

    pca->n= n;
    pca->z = av_malloc_array(n, કદ(*pca->z));
    pca->ગણતરી=0;
    pca->covariance= av_calloc(n*n, કદ(દ્વિગુણ));
    pca->mean= av_calloc(n, કદ(દ્વિગુણ));

    જો (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        પાછા ખાલી;
    }

    પાછા pca;
}

શૂન્ય ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

શૂન્ય ff_pca_add(PCA *pca, અચલ દ્વિગુણ *v){
    પૂર્ણાંક i, j;
    અચલ પૂર્ણાંક n= pca->n;

    માટે(i=0; i<n; i++){
        pca->mean[i] += v[i];
        માટે(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->ગણતરી++;
}

પૂર્ણાંક ff_pca(PCA *pca, દ્વિગુણ *eigenvector, દ્વિગુણ *eigenvalue){
    પૂર્ણાંક i, j, pass;
    પૂર્ણાંક k=0;
    અચલ પૂર્ણાંક n= pca->n;
    દ્વિગુણ *z = pca->z;

    memset(eigenvector, 0, કદ(દ્વિગુણ)*n*n);

    માટે(j=0; j<n; j++){
        pca->mean[j] /= pca->ગણતરી;
        eigenvector[j + j*n] = 1.0;
        માટે(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->ગણતરી;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    માટે(pass=0; pass < 50; pass++){
        દ્વિગુણ sum=0;

        માટે(i=0; i<n; i++)
            માટે(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        જો(sum == 0){
            માટે(i=0; i<n; i++){
                દ્વિગુણ maxvalue= -1;
                માટે(j=i; j<n; j++){
                    જો(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                માટે(j=0; j<n; j++){
                    દ્વિગુણ tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            પાછા pass;
        }

        માટે(i=0; i<n; i++){
            માટે(j=i+1; j<n; j++){
                દ્વિગુણ covar= pca->covariance[j + i*n];
                દ્વિગુણ t,c,s,tau,theta, h;

                જો(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    ચાલુ;
                જો(fabs(covar) == 0.0) //FIXME should not be needed
                    ચાલુ;
                જો(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    ચાલુ;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                જો(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    દ્વિગુણ g=a[j + i*n];\
    દ્વિગુણ h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                માટે(k=0; k<n; k++) {
                    જો(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        માટે (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    પાછા -1;
}
