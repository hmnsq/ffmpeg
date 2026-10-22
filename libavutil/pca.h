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

#నిర్వచితం_కాకపోతే AVUTIL_PCA_H
#నిర్వచించు AVUTIL_PCA_H

నిర్మాణం PCA *ff_pca_init(పూర్ణాంకం n);
శూన్య ff_pca_free(నిర్మాణం PCA *pca);
శూన్య ff_pca_కూడు(నిర్మాణం PCA *pca, స్థిరరాశి ద్విగుణ *v);
పూర్ణాంకం ff_pca(నిర్మాణం PCA *pca, ద్విగుణ *eigenvector, ద్విగుణ *eigenvalue);

#అయితే_ముగింపు /* AVUTIL_PCA_H */
