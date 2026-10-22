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

#अन्तर्भाव "common.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pca.h"

प्रकारनिर्देश संरचना PCA{
    पूर्णाङ्क गणनम्;
    पूर्णाङ्क n;
    द्विगुण *covariance;
    द्विगुण *mean;
    द्विगुण *z;
}PCA;

PCA *ff_pca_init(पूर्णाङ्क n){
    PCA *pca;
    जइ(n<=0)
        प्रत्यागम रिक्त;

    pca= av_mallocz(परिमाण(*pca));
    जइ (!pca)
        प्रत्यागम रिक्त;

    pca->n= n;
    pca->z = av_malloc_array(n, परिमाण(*pca->z));
    pca->गणनम्=0;
    pca->covariance= av_calloc(n*n, परिमाण(द्विगुण));
    pca->mean= av_calloc(n, परिमाण(द्विगुण));

    जइ (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम pca;
}

शून्य ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

शून्य ff_pca_add(PCA *pca, ध्रुव द्विगुण *v){
    पूर्णाङ्क i, j;
    ध्रुव पूर्णाङ्क n= pca->n;

    प्रति(i=0; i<n; i++){
        pca->mean[i] += v[i];
        प्रति(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->गणनम्++;
}

पूर्णाङ्क ff_pca(PCA *pca, द्विगुण *eigenvector, द्विगुण *eigenvalue){
    पूर्णाङ्क i, j, pass;
    पूर्णाङ्क k=0;
    ध्रुव पूर्णाङ्क n= pca->n;
    द्विगुण *z = pca->z;

    memset(eigenvector, 0, परिमाण(द्विगुण)*n*n);

    प्रति(j=0; j<n; j++){
        pca->mean[j] /= pca->गणनम्;
        eigenvector[j + j*n] = 1.0;
        प्रति(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->गणनम्;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    प्रति(pass=0; pass < 50; pass++){
        द्विगुण sum=0;

        प्रति(i=0; i<n; i++)
            प्रति(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        जइ(sum == 0){
            प्रति(i=0; i<n; i++){
                द्विगुण maxvalue= -1;
                प्रति(j=i; j<n; j++){
                    जइ(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                प्रति(j=0; j<n; j++){
                    द्विगुण tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            प्रत्यागम pass;
        }

        प्रति(i=0; i<n; i++){
            प्रति(j=i+1; j<n; j++){
                द्विगुण covar= pca->covariance[j + i*n];
                द्विगुण t,c,s,tau,theta, h;

                जइ(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    अनुवर्त;
                जइ(fabs(covar) == 0.0) //FIXME should not be needed
                    अनुवर्त;
                जइ(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    अनुवर्त;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                जइ(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    द्विगुण g=a[j + i*n];\
    द्विगुण h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                प्रति(k=0; k<n; k++) {
                    जइ(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        प्रति (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    प्रत्यागम -1;
}
