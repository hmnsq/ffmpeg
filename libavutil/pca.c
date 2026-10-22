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

#ضمن "common.h"
#ضمن "mem.h"
#ضمن "pca.h"

تعريفنوع بنية PCA{
    صحيح گنتی;
    صحيح n;
    مزدوج *covariance;
    مزدوج *اوسط;
    مزدوج *z;
}PCA;

PCA *ff_pca_init(صحيح n){
    PCA *pca;
    إذا(n<=0)
        أرجع عدم;

    pca= av_mallocz(حجم(*pca));
    إذا (!pca)
        أرجع عدم;

    pca->n= n;
    pca->z = av_malloc_array(n, حجم(*pca->z));
    pca->گنتی=0;
    pca->covariance= av_calloc(n*n, حجم(مزدوج));
    pca->اوسط= av_calloc(n, حجم(مزدوج));

    إذا (!pca->z || !pca->covariance || !pca->اوسط) {
        ff_pca_free(pca);
        أرجع عدم;
    }

    أرجع pca;
}

فراغ ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->اوسط);
    av_freep(&pca->z);
    av_free(pca);
}

فراغ ff_pca_جوڑو(PCA *pca, ثابت مزدوج *v){
    صحيح i, j;
    ثابت صحيح n= pca->n;

    لكل(i=0; i<n; i++){
        pca->اوسط[i] += v[i];
        لكل(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->گنتی++;
}

صحيح ff_pca(PCA *pca, مزدوج *eigenvector, مزدوج *eigenvalue){
    صحيح i, j, pass;
    صحيح k=0;
    ثابت صحيح n= pca->n;
    مزدوج *z = pca->z;

    memset(eigenvector, 0, حجم(مزدوج)*n*n);

    لكل(j=0; j<n; j++){
        pca->اوسط[j] /= pca->گنتی;
        eigenvector[j + j*n] = 1.0;
        لكل(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->گنتی;
            pca->covariance[j + i*n] -= pca->اوسط[i] * pca->اوسط[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    لكل(pass=0; pass < 50; pass++){
        مزدوج جوڑ=0;

        لكل(i=0; i<n; i++)
            لكل(j=i+1; j<n; j++)
                جوڑ += fabs(pca->covariance[j + i*n]);

        إذا(جوڑ == 0){
            لكل(i=0; i<n; i++){
                مزدوج maxvalue= -1;
                لكل(j=i; j<n; j++){
                    إذا(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                لكل(j=0; j<n; j++){
                    مزدوج tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            أرجع pass;
        }

        لكل(i=0; i<n; i++){
            لكل(j=i+1; j<n; j++){
                مزدوج covar= pca->covariance[j + i*n];
                مزدوج t,c,s,tau,theta, h;

                إذا(pass < 3 && fabs(covar) < جوڑ / (5*n*n)) //FIXME why pass < 3
                    استمر;
                إذا(fabs(covar) == 0.0) //FIXME should not be needed
                    استمر;
                إذا(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    استمر;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+جذر(1.0+theta*theta));
                إذا(theta < 0.0) t = -t;

                c=1.0/جذر(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#تعریف_کرو ROTATE(a,i,j,k,l) {\
    مزدوج g=a[j + i*n];\
    مزدوج h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                لكل(k=0; k<n; k++) {
                    إذا(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        لكل (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    أرجع -1;
}
