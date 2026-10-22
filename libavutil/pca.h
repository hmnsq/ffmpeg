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

#अगर_अघोषित AVUTIL_PCA_H
#घोषणा AVUTIL_PCA_H

काष्ठा PCA *ff_pca_init(पूर्णांक n);
व्योम ff_pca_free(काष्ठा PCA *pca);
व्योम ff_pca_add(काष्ठा PCA *pca, स्थिर द्विगुन *v);
पूर्णांक ff_pca(काष्ठा PCA *pca, द्विगुन *eigenvector, द्विगुन *eigenvalue);

#पूर्ण_अगर /* AVUTIL_PCA_H */
