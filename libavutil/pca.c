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

प्रकारव्याख्या संरचना PCA{
    पूर्णांक मोजणी;
    पूर्णांक n;
    द्विगुण *covariance;
    द्विगुण *mean;
    द्विगुण *z;
}PCA;

PCA *ff_pca_init(पूर्णांक n){
    PCA *pca;
    जर(n<=0)
        परत रिक्त;

    pca= av_mallocz(आकार(*pca));
    जर (!pca)
        परत रिक्त;

    pca->n= n;
    pca->z = av_malloc_array(n, आकार(*pca->z));
    pca->मोजणी=0;
    pca->covariance= av_calloc(n*n, आकार(द्विगुण));
    pca->mean= av_calloc(n, आकार(द्विगुण));

    जर (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        परत रिक्त;
    }

    परत pca;
}

शून्य ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

शून्य ff_pca_add(PCA *pca, स्थिरांक द्विगुण *v){
    पूर्णांक i, j;
    स्थिरांक पूर्णांक n= pca->n;

    साठी(i=0; i<n; i++){
        pca->mean[i] += v[i];
        साठी(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->मोजणी++;
}

पूर्णांक ff_pca(PCA *pca, द्विगुण *eigenvector, द्विगुण *eigenvalue){
    पूर्णांक i, j, pass;
    पूर्णांक k=0;
    स्थिरांक पूर्णांक n= pca->n;
    द्विगुण *z = pca->z;

    स_रखो(eigenvector, 0, आकार(द्विगुण)*n*n);

    साठी(j=0; j<n; j++){
        pca->mean[j] /= pca->मोजणी;
        eigenvector[j + j*n] = 1.0;
        साठी(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->मोजणी;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    साठी(pass=0; pass < 50; pass++){
        द्विगुण sum=0;

        साठी(i=0; i<n; i++)
            साठी(j=i+1; j<n; j++)
                sum += भ_असल(pca->covariance[j + i*n]);

        जर(sum == 0){
            साठी(i=0; i<n; i++){
                द्विगुण maxvalue= -1;
                साठी(j=i; j<n; j++){
                    जर(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                साठी(j=0; j<n; j++){
                    द्विगुण tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            परत pass;
        }

        साठी(i=0; i<n; i++){
            साठी(j=i+1; j<n; j++){
                द्विगुण covar= pca->covariance[j + i*n];
                द्विगुण t,c,s,tau,theta, h;

                जर(pass < 3 && भ_असल(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    सुरूठेवा;
                जर(भ_असल(covar) == 0.0) //FIXME should not be needed
                    सुरूठेवा;
                जर(pass >=3 && भ_असल((eigenvalue[j]+z[j])/covar) > (1LL<<32) && भ_असल((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    सुरूठेवा;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(भ_असल(theta)+वर्ग_मूल(1.0+theta*theta));
                जर(theta < 0.0) t = -t;

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
                साठी(k=0; k<n; k++) {
                    जर(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        साठी (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    परत -1;
}
