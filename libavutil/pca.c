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
    पूर्णाङ्क गन्ती;
    पूर्णाङ्क n;
    द्विगुण *covariance;
    द्विगुण *mean;
    द्विगुण *z;
}PCA;

PCA *ff_pca_init(पूर्णाङ्क n){
    PCA *pca;
    यदि(n<=0)
        फर्काऊ रिक्त;

    pca= av_mallocz(परिमाण(*pca));
    यदि (!pca)
        फर्काऊ रिक्त;

    pca->n= n;
    pca->z = av_malloc_array(n, परिमाण(*pca->z));
    pca->गन्ती=0;
    pca->covariance= av_calloc(n*n, परिमाण(द्विगुण));
    pca->mean= av_calloc(n, परिमाण(द्विगुण));

    यदि (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        फर्काऊ रिक्त;
    }

    फर्काऊ pca;
}

शून्य ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

शून्य ff_pca_add(PCA *pca, अचर द्विगुण *v){
    पूर्णाङ्क i, j;
    अचर पूर्णाङ्क n= pca->n;

    लागि(i=0; i<n; i++){
        pca->mean[i] += v[i];
        लागि(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->गन्ती++;
}

पूर्णाङ्क ff_pca(PCA *pca, द्विगुण *eigenvector, द्विगुण *eigenvalue){
    पूर्णाङ्क i, j, pass;
    पूर्णाङ्क k=0;
    अचर पूर्णाङ्क n= pca->n;
    द्विगुण *z = pca->z;

    स_रखो(eigenvector, 0, परिमाण(द्विगुण)*n*n);

    लागि(j=0; j<n; j++){
        pca->mean[j] /= pca->गन्ती;
        eigenvector[j + j*n] = 1.0;
        लागि(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->गन्ती;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    लागि(pass=0; pass < 50; pass++){
        द्विगुण sum=0;

        लागि(i=0; i<n; i++)
            लागि(j=i+1; j<n; j++)
                sum += भ_असल(pca->covariance[j + i*n]);

        यदि(sum == 0){
            लागि(i=0; i<n; i++){
                द्विगुण maxvalue= -1;
                लागि(j=i; j<n; j++){
                    यदि(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                लागि(j=0; j<n; j++){
                    द्विगुण tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            फर्काऊ pass;
        }

        लागि(i=0; i<n; i++){
            लागि(j=i+1; j<n; j++){
                द्विगुण covar= pca->covariance[j + i*n];
                द्विगुण t,c,s,tau,theta, h;

                यदि(pass < 3 && भ_असल(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    जारी;
                यदि(भ_असल(covar) == 0.0) //FIXME should not be needed
                    जारी;
                यदि(pass >=3 && भ_असल((eigenvalue[j]+z[j])/covar) > (1LL<<32) && भ_असल((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    जारी;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(भ_असल(theta)+वर्ग_मूल(1.0+theta*theta));
                यदि(theta < 0.0) t = -t;

                c=1.0/वर्ग_मूल(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    द्विगुण g=a[j + i*n];\
    द्विगुण h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                लागि(k=0; k<n; k++) {
                    यदि(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        लागि (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    फर्काऊ -1;
}
