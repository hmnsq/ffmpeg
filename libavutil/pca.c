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

#شامل "common.h"
#شامل "mem.h"
#شامل "pca.h"

قسمتعریف ساخت PCA{
    صحیح گنتی;
    صحیح n;
    دوہرا *covariance;
    دوہرا *اوسط;
    دوہرا *z;
}PCA;

PCA *ff_pca_init(صحیح n){
    PCA *pca;
    اگر(n<=0)
        واپس تہی;

    pca= av_mallocz(حجم(*pca));
    اگر (!pca)
        واپس تہی;

    pca->n= n;
    pca->z = av_malloc_array(n, حجم(*pca->z));
    pca->گنتی=0;
    pca->covariance= av_calloc(n*n, حجم(دوہرا));
    pca->اوسط= av_calloc(n, حجم(دوہرا));

    اگر (!pca->z || !pca->covariance || !pca->اوسط) {
        ff_pca_free(pca);
        واپس تہی;
    }

    واپس pca;
}

خالی ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->اوسط);
    av_freep(&pca->z);
    av_free(pca);
}

خالی ff_pca_جوڑو(PCA *pca, ثابت دوہرا *v){
    صحیح i, j;
    ثابت صحیح n= pca->n;

    برائے(i=0; i<n; i++){
        pca->اوسط[i] += v[i];
        برائے(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->گنتی++;
}

صحیح ff_pca(PCA *pca, دوہرا *eigenvector, دوہرا *eigenvalue){
    صحیح i, j, pass;
    صحیح k=0;
    ثابت صحیح n= pca->n;
    دوہرا *z = pca->z;

    memset(eigenvector, 0, حجم(دوہرا)*n*n);

    برائے(j=0; j<n; j++){
        pca->اوسط[j] /= pca->گنتی;
        eigenvector[j + j*n] = 1.0;
        برائے(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->گنتی;
            pca->covariance[j + i*n] -= pca->اوسط[i] * pca->اوسط[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    برائے(pass=0; pass < 50; pass++){
        دوہرا مجموع=0;

        برائے(i=0; i<n; i++)
            برائے(j=i+1; j<n; j++)
                مجموع += fabs(pca->covariance[j + i*n]);

        اگر(مجموع == 0){
            برائے(i=0; i<n; i++){
                دوہرا maxvalue= -1;
                برائے(j=i; j<n; j++){
                    اگر(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                برائے(j=0; j<n; j++){
                    دوہرا tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            واپس pass;
        }

        برائے(i=0; i<n; i++){
            برائے(j=i+1; j<n; j++){
                دوہرا covar= pca->covariance[j + i*n];
                دوہرا t,c,s,tau,theta, h;

                اگر(pass < 3 && fabs(covar) < مجموع / (5*n*n)) //FIXME why pass < 3
                    جاری;
                اگر(fabs(covar) == 0.0) //FIXME should not be needed
                    جاری;
                اگر(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    جاری;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+جذر(1.0+theta*theta));
                اگر(theta < 0.0) t = -t;

                c=1.0/جذر(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#تعریف_کرو ROTATE(a,i,j,k,l) {\
    دوہرا g=a[j + i*n];\
    دوہرا h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                برائے(k=0; k<n; k++) {
                    اگر(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        برائے (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    واپس -1;
}
