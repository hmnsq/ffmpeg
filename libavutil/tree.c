/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
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

#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "tree.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVTree_ಗಂಟು {
    ರಚನೆ AVTree_ಗಂಟು *ಮಗು[2];
    ಶೂನ್ಯ *elem;
    ಪೂರ್ಣಾಂಕ state;
} AVTree_ಗಂಟು;

ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ av_ವೃಕ್ಷ_ಗಂಟು_ಗಾತ್ರ = ಗಾತ್ರ(AVTree_ಗಂಟು);

ರಚನೆ AVTree_ಗಂಟು *av_ವೃಕ್ಷ_ಗಂಟು_alloc(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ av_mallocz(ಗಾತ್ರ(ರಚನೆ AVTree_ಗಂಟು));
}

ಶೂನ್ಯ *av_ವೃಕ್ಷ_ಕಂಡುಹಿಡಿ(ಸ್ಥಿರಾಂಕ AVTree_ಗಂಟು *t, ಶೂನ್ಯ *ಕೀಲಿ,
                   ಪೂರ್ಣಾಂಕ (*cmp)(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಕೀಲಿ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *b), ಶೂನ್ಯ *ಮುಂದಿನ[2])
{
    ಆದರೆ (t) {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ v = cmp(ಕೀಲಿ, t->elem);
        ಆದರೆ (v) {
            ಆದರೆ (ಮುಂದಿನ)
                ಮುಂದಿನ[v >> 31] = t->elem;
            ಹಿಂತಿರುಗಿ av_ವೃಕ್ಷ_ಕಂಡುಹಿಡಿ(t->ಮಗು[(v >> 31) ^ 1], ಕೀಲಿ, cmp, ಮುಂದಿನ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (ಮುಂದಿನ) {
                av_ವೃಕ್ಷ_ಕಂಡುಹಿಡಿ(t->ಮಗು[0], ಕೀಲಿ, cmp, ಮುಂದಿನ);
                av_ವೃಕ್ಷ_ಕಂಡುಹಿಡಿ(t->ಮಗು[1], ಕೀಲಿ, cmp, ಮುಂದಿನ);
            }
            ಹಿಂತಿರುಗಿ t->elem;
        }
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಶೂನ್ಯ *av_ವೃಕ್ಷ_ಸೇರಿಸು(AVTree_ಗಂಟು **tp, ಶೂನ್ಯ *ಕೀಲಿ,
                     ಪೂರ್ಣಾಂಕ (*cmp)(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಕೀಲಿ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *b), AVTree_ಗಂಟು **ಮುಂದಿನ)
{
    AVTree_ಗಂಟು *t = *tp;
    ಆದರೆ (t) {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ v = cmp(t->elem, ಕೀಲಿ);
        ಶೂನ್ಯ *ret;
        ಆದರೆ (!v) {
            ಆದರೆ (*ಮುಂದಿನ)
                ಹಿಂತಿರುಗಿ t->elem;
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (t->ಮಗು[0] || t->ಮಗು[1]) {
                ಪೂರ್ಣಾಂಕ i = !t->ಮಗು[0];
                ಶೂನ್ಯ *ಮುಂದಿನ_elem[2];
                av_ವೃಕ್ಷ_ಕಂಡುಹಿಡಿ(t->ಮಗು[i], ಕೀಲಿ, cmp, ಮುಂದಿನ_elem);
                ಕೀಲಿ = t->elem = ಮುಂದಿನ_elem[i];
                v   = -i;
            } ಇಲ್ಲದಿದ್ದರೆ {
                *ಮುಂದಿನ = t;
                *tp   = ಖಾಲಿ;
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            }
        }
        ret = av_ವೃಕ್ಷ_ಸೇರಿಸು(&t->ಮಗು[v >> 31], ಕೀಲಿ, cmp, ಮುಂದಿನ);
        ಆದರೆ (!ret) {
            ಪೂರ್ಣಾಂಕ i              = (v >> 31) ^ !!*ಮುಂದಿನ;
            AVTree_ಗಂಟು **ಮಗು = &t->ಮಗು[i];
            t->state += 2 * i - 1;

            ಆದರೆ (!(t->state & 1)) {
                ಆದರೆ (t->state) {
                    /* The following code is equivalent to
                     * if ((*child)->state * 2 == -t->state)
                     *     rotate(child, i ^ 1);
                     * rotate(tp, i);
                     *
                     * with rotate():
                     * static void rotate(AVTreeNode **tp, int i)
                     * {
                     *     AVTreeNode *t= *tp;
                     *
                     *     *tp = t->child[i];
                     *     t->child[i] = t->child[i]->child[i ^ 1];
                     *     (*tp)->child[i ^ 1] = t;
                     *     i = 4 * t->state + 2 * (*tp)->state + 12;
                     *     t->state     = ((0x614586 >> i) & 3) - 1;
                     *     (*tp)->state = ((0x400EEA >> i) & 3) - 1 +
                     *                    ((*tp)->state >> 1);
                     * }
                     * but such a rotate function is both bigger and slower
                     */
                    ಆದರೆ ((*ಮಗು)->state * 2 == -t->state) {
                        *tp                    = (*ಮಗು)->ಮಗು[i ^ 1];
                        (*ಮಗು)->ಮಗು[i ^ 1] = (*tp)->ಮಗು[i];
                        (*tp)->ಮಗು[i]        = *ಮಗು;
                        *ಮಗು                 = (*tp)->ಮಗು[i ^ 1];
                        (*tp)->ಮಗು[i ^ 1]    = t;

                        (*tp)->ಮಗು[0]->state = -((*tp)->state > 0);
                        (*tp)->ಮಗು[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        *tp                 = *ಮಗು;
                        *ಮಗು              = (*ಮಗು)->ಮಗು[i ^ 1];
                        (*tp)->ಮಗು[i ^ 1] = t;
                        ಆದರೆ ((*tp)->state)
                            t->state = 0;
                        ಇಲ್ಲದಿದ್ದರೆ
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            ಆದರೆ (!(*tp)->state ^ !!*ಮುಂದಿನ)
                ಹಿಂತಿರುಗಿ ಕೀಲಿ;
        }
        ಹಿಂತಿರುಗಿ ret;
    } ಇಲ್ಲದಿದ್ದರೆ {
        *tp   = *ಮುಂದಿನ;
        *ಮುಂದಿನ = ಖಾಲಿ;
        ಆದರೆ (*tp) {
            (*tp)->elem = ಕೀಲಿ;
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        } ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ ಕೀಲಿ;
    }
}

ಶೂನ್ಯ av_ವೃಕ್ಷ_destroy(AVTree_ಗಂಟು *t)
{
    ಆದರೆ (t) {
        av_ವೃಕ್ಷ_destroy(t->ಮಗು[0]);
        av_ವೃಕ್ಷ_destroy(t->ಮಗು[1]);
        av_free(t);
    }
}

ಶೂನ್ಯ av_ವೃಕ್ಷ_enumerate(AVTree_ಗಂಟು *t, ಶೂನ್ಯ *opaque,
                       ಪೂರ್ಣಾಂಕ (*cmp)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *elem),
                       ಪೂರ್ಣಾಂಕ (*enu)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *elem))
{
    ಆದರೆ (t) {
        ಪೂರ್ಣಾಂಕ v = cmp ? cmp(opaque, t->elem) : 0;
        ಆದರೆ (v >= 0)
            av_ವೃಕ್ಷ_enumerate(t->ಮಗು[0], opaque, cmp, enu);
        ಆದರೆ (v == 0)
            enu(opaque, t->elem);
        ಆದರೆ (v <= 0)
            av_ವೃಕ್ಷ_enumerate(t->ಮಗು[1], opaque, cmp, enu);
    }
}
