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

ସଂରଚନା PCA *ff_pca_init(ପୂର୍ଣ୍ଣସଂଖ୍ୟା n);
ଶୂନ୍ୟ ff_pca_free(ସଂରଚନା PCA *pca);
ଶୂନ୍ୟ ff_pca_add(ସଂରଚନା PCA *pca, ଅଚଳ ଦ୍ୱିଗୁଣ *v);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pca(ସଂରଚନା PCA *pca, ଦ୍ୱିଗୁଣ *eigenvector, ଦ୍ୱିଗୁଣ *eigenvalue);

#endif /* AVUTIL_PCA_H */
