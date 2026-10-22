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

#ifndef AVUTIL_PCA_H
#define AVUTIL_PCA_H

ಸಂರಚನಾ PCA *ff_pca_init(ಪೂರ್ಣಾಙ್ಕ n);
ಶೂನ್ಯ ff_pca_free(ಸಂರಚನಾ PCA *pca);
ಶೂನ್ಯ ff_pca_add(ಸಂರಚನಾ PCA *pca, ಧ್ರುವ ದ್ವಿಗುಣ *v);
ಪೂರ್ಣಾಙ್ಕ ff_pca(ಸಂರಚನಾ PCA *pca, ದ್ವಿಗುಣ *eigenvector, ದ್ವಿಗುಣ *eigenvalue);

#endif /* AVUTIL_PCA_H */
