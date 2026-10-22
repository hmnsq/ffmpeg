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

#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "pca.h"

തരനിർവചനം ഘടന PCA{
    പൂർണ്ണസംഖ്യ എണ്ണം;
    പൂർണ്ണസംഖ്യ n;
    ഇരട്ട *covariance;
    ഇരട്ട *mean;
    ഇരട്ട *z;
}PCA;

PCA *ff_pca_init(പൂർണ്ണസംഖ്യ n){
    PCA *pca;
    എങ്കിൽ(n<=0)
        തിരികെ ശൂന്യ;

    pca= av_mallocz(വലുപ്പം(*pca));
    എങ്കിൽ (!pca)
        തിരികെ ശൂന്യ;

    pca->n= n;
    pca->z = av_malloc_array(n, വലുപ്പം(*pca->z));
    pca->എണ്ണം=0;
    pca->covariance= av_calloc(n*n, വലുപ്പം(ഇരട്ട));
    pca->mean= av_calloc(n, വലുപ്പം(ഇരട്ട));

    എങ്കിൽ (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        തിരികെ ശൂന്യ;
    }

    തിരികെ pca;
}

ശൂന്യം ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

ശൂന്യം ff_pca_add(PCA *pca, സ്ഥിരം ഇരട്ട *v){
    പൂർണ്ണസംഖ്യ i, j;
    സ്ഥിരം പൂർണ്ണസംഖ്യ n= pca->n;

    വേണ്ടി(i=0; i<n; i++){
        pca->mean[i] += v[i];
        വേണ്ടി(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->എണ്ണം++;
}

പൂർണ്ണസംഖ്യ ff_pca(PCA *pca, ഇരട്ട *eigenvector, ഇരട്ട *eigenvalue){
    പൂർണ്ണസംഖ്യ i, j, pass;
    പൂർണ്ണസംഖ്യ k=0;
    സ്ഥിരം പൂർണ്ണസംഖ്യ n= pca->n;
    ഇരട്ട *z = pca->z;

    memset(eigenvector, 0, വലുപ്പം(ഇരട്ട)*n*n);

    വേണ്ടി(j=0; j<n; j++){
        pca->mean[j] /= pca->എണ്ണം;
        eigenvector[j + j*n] = 1.0;
        വേണ്ടി(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->എണ്ണം;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    വേണ്ടി(pass=0; pass < 50; pass++){
        ഇരട്ട sum=0;

        വേണ്ടി(i=0; i<n; i++)
            വേണ്ടി(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        എങ്കിൽ(sum == 0){
            വേണ്ടി(i=0; i<n; i++){
                ഇരട്ട maxvalue= -1;
                വേണ്ടി(j=i; j<n; j++){
                    എങ്കിൽ(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                വേണ്ടി(j=0; j<n; j++){
                    ഇരട്ട tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            തിരികെ pass;
        }

        വേണ്ടി(i=0; i<n; i++){
            വേണ്ടി(j=i+1; j<n; j++){
                ഇരട്ട covar= pca->covariance[j + i*n];
                ഇരട്ട t,c,s,tau,theta, h;

                എങ്കിൽ(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    തുടരുക;
                എങ്കിൽ(fabs(covar) == 0.0) //FIXME should not be needed
                    തുടരുക;
                എങ്കിൽ(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    തുടരുക;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                എങ്കിൽ(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    ഇരട്ട g=a[j + i*n];\
    ഇരട്ട h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                വേണ്ടി(k=0; k<n; k++) {
                    എങ്കിൽ(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        വേണ്ടി (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    തിരികെ -1;
}
