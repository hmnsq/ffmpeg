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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_PCA_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_PCA_H

ರಚನೆ PCA *ff_pca_init(ಪೂರ್ಣಾಂಕ n);
ಶೂನ್ಯ ff_pca_free(ರಚನೆ PCA *pca);
ಶೂನ್ಯ ff_pca_ಕೂಡಿಸು(ರಚನೆ PCA *pca, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v);
ಪೂರ್ಣಾಂಕ ff_pca(ರಚನೆ PCA *pca, ದ್ವಿಗುಣ *eigenvector, ದ್ವಿಗುಣ *eigenvalue);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_PCA_H */
