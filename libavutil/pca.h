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

সংরচনা PCA *ff_pca_init(পূর্ণাঙ্ক n);
শূন্য ff_pca_free(সংরচনা PCA *pca);
শূন্য ff_pca_add(সংরচনা PCA *pca, ধ্রুব দ্বিগুণ *v);
পূর্ণাঙ্ক ff_pca(সংরচনা PCA *pca, দ্বিগুণ *eigenvector, দ্বিগুণ *eigenvalue);

#endif /* AVUTIL_PCA_H */
