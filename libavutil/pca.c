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

تعریفنوع ساختار PCA{
    صحیح شمار;
    صحیح n;
    دوگانه *covariance;
    دوگانه *mean;
    دوگانه *z;
}PCA;

PCA *ff_pca_init(صحیح n){
    PCA *pca;
    اگر(n<=0)
        بازگشت پوچ;

    pca= av_mallocz(اندازه(*pca));
    اگر (!pca)
        بازگشت پوچ;

    pca->n= n;
    pca->z = av_malloc_array(n, اندازه(*pca->z));
    pca->شمار=0;
    pca->covariance= av_calloc(n*n, اندازه(دوگانه));
    pca->mean= av_calloc(n, اندازه(دوگانه));

    اگر (!pca->z || !pca->covariance || !pca->mean) {
        ff_pca_free(pca);
        بازگشت پوچ;
    }

    بازگشت pca;
}

تهی ff_pca_free(PCA *pca){
    av_freep(&pca->covariance);
    av_freep(&pca->mean);
    av_freep(&pca->z);
    av_free(pca);
}

تهی ff_pca_add(PCA *pca, ثابت دوگانه *v){
    صحیح i, j;
    ثابت صحیح n= pca->n;

    برای(i=0; i<n; i++){
        pca->mean[i] += v[i];
        برای(j=i; j<n; j++)
            pca->covariance[j + i*n] += v[i]*v[j];
    }
    pca->شمار++;
}

صحیح ff_pca(PCA *pca, دوگانه *eigenvector, دوگانه *eigenvalue){
    صحیح i, j, pass;
    صحیح k=0;
    ثابت صحیح n= pca->n;
    دوگانه *z = pca->z;

    memset(eigenvector, 0, اندازه(دوگانه)*n*n);

    برای(j=0; j<n; j++){
        pca->mean[j] /= pca->شمار;
        eigenvector[j + j*n] = 1.0;
        برای(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->شمار;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    برای(pass=0; pass < 50; pass++){
        دوگانه sum=0;

        برای(i=0; i<n; i++)
            برای(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        اگر(sum == 0){
            برای(i=0; i<n; i++){
                دوگانه maxvalue= -1;
                برای(j=i; j<n; j++){
                    اگر(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                برای(j=0; j<n; j++){
                    دوگانه tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            بازگشت pass;
        }

        برای(i=0; i<n; i++){
            برای(j=i+1; j<n; j++){
                دوگانه covar= pca->covariance[j + i*n];
                دوگانه t,c,s,tau,theta, h;

                اگر(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    ادامه;
                اگر(fabs(covar) == 0.0) //FIXME should not be needed
                    ادامه;
                اگر(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    ادامه;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                اگر(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    دوگانه g=a[j + i*n];\
    دوگانه h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                برای(k=0; k<n; k++) {
                    اگر(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        برای (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    بازگشت -1;
}
