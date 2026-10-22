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

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVTree_ಗಂಟು {
    ಸಂರಚನಾ AVTree_ಗಂಟು *child[2];
    ಶೂನ್ಯ *elem;
    ಪೂರ್ಣಾಙ್ಕ state;
} AVTree_ಗಂಟು;

ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ av_ವೃಕ್ಷ_ಗಂಟು_size = ಪರಿಮಾಣ(AVTree_ಗಂಟು);

ಸಂರಚನಾ AVTree_ಗಂಟು *av_ವೃಕ್ಷ_ಗಂಟು_alloc(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ av_mallocz(ಪರಿಮಾಣ(ಸಂರಚನಾ AVTree_ಗಂಟು));
}

ಶೂನ್ಯ *av_ವೃಕ್ಷ_find(ಧ್ರುವ AVTree_ಗಂಟು *t, ಶೂನ್ಯ *ಕೀಲಿ,
                   ಪೂರ್ಣಾಙ್ಕ (*cmp)(ಧ್ರುವ ಶೂನ್ಯ *ಕೀಲಿ, ಧ್ರುವ ಶೂನ್ಯ *b), ಶೂನ್ಯ *next[2])
{
    ಯದಿ (t) {
        unsigned ಪೂರ್ಣಾಙ್ಕ v = cmp(ಕೀಲಿ, t->elem);
        ಯದಿ (v) {
            ಯದಿ (next)
                next[v >> 31] = t->elem;
            ಪ್ರತ್ಯಾಗಮ av_ವೃಕ್ಷ_find(t->child[(v >> 31) ^ 1], ಕೀಲಿ, cmp, next);
        } ಅನ್ಯಥಾ {
            ಯದಿ (next) {
                av_ವೃಕ್ಷ_find(t->child[0], ಕೀಲಿ, cmp, next);
                av_ವೃಕ್ಷ_find(t->child[1], ಕೀಲಿ, cmp, next);
            }
            ಪ್ರತ್ಯಾಗಮ t->elem;
        }
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಶೂನ್ಯ *av_ವೃಕ್ಷ_ಸೇರಿಸು(AVTree_ಗಂಟು **tp, ಶೂನ್ಯ *ಕೀಲಿ,
                     ಪೂರ್ಣಾಙ್ಕ (*cmp)(ಧ್ರುವ ಶೂನ್ಯ *ಕೀಲಿ, ಧ್ರುವ ಶೂನ್ಯ *b), AVTree_ಗಂಟು **next)
{
    AVTree_ಗಂಟು *t = *tp;
    ಯದಿ (t) {
        unsigned ಪೂರ್ಣಾಙ್ಕ v = cmp(t->elem, ಕೀಲಿ);
        ಶೂನ್ಯ *ret;
        ಯದಿ (!v) {
            ಯದಿ (*next)
                ಪ್ರತ್ಯಾಗಮ t->elem;
            ಅನ್ಯಥಾ ಯದಿ (t->child[0] || t->child[1]) {
                ಪೂರ್ಣಾಙ್ಕ i = !t->child[0];
                ಶೂನ್ಯ *next_elem[2];
                av_ವೃಕ್ಷ_find(t->child[i], ಕೀಲಿ, cmp, next_elem);
                ಕೀಲಿ = t->elem = next_elem[i];
                v   = -i;
            } ಅನ್ಯಥಾ {
                *next = t;
                *tp   = ರಿಕ್ತ;
                ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
            }
        }
        ret = av_ವೃಕ್ಷ_ಸೇರಿಸು(&t->child[v >> 31], ಕೀಲಿ, cmp, next);
        ಯದಿ (!ret) {
            ಪೂರ್ಣಾಙ್ಕ i              = (v >> 31) ^ !!*next;
            AVTree_ಗಂಟು **child = &t->child[i];
            t->state += 2 * i - 1;

            ಯದಿ (!(t->state & 1)) {
                ಯದಿ (t->state) {
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
                    ಯದಿ ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } ಅನ್ಯಥಾ {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        ಯದಿ ((*tp)->state)
                            t->state = 0;
                        ಅನ್ಯಥಾ
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            ಯದಿ (!(*tp)->state ^ !!*next)
                ಪ್ರತ್ಯಾಗಮ ಕೀಲಿ;
        }
        ಪ್ರತ್ಯಾಗಮ ret;
    } ಅನ್ಯಥಾ {
        *tp   = *next;
        *next = ರಿಕ್ತ;
        ಯದಿ (*tp) {
            (*tp)->elem = ಕೀಲಿ;
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        } ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ ಕೀಲಿ;
    }
}

ಶೂನ್ಯ av_ವೃಕ್ಷ_destroy(AVTree_ಗಂಟು *t)
{
    ಯದಿ (t) {
        av_ವೃಕ್ಷ_destroy(t->child[0]);
        av_ವೃಕ್ಷ_destroy(t->child[1]);
        av_free(t);
    }
}

ಶೂನ್ಯ av_ವೃಕ್ಷ_enumerate(AVTree_ಗಂಟು *t, ಶೂನ್ಯ *opaque,
                       ಪೂರ್ಣಾಙ್ಕ (*cmp)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *elem),
                       ಪೂರ್ಣಾಙ್ಕ (*enu)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *elem))
{
    ಯದಿ (t) {
        ಪೂರ್ಣಾಙ್ಕ v = cmp ? cmp(opaque, t->elem) : 0;
        ಯದಿ (v >= 0)
            av_ವೃಕ್ಷ_enumerate(t->child[0], opaque, cmp, enu);
        ಯದಿ (v == 0)
            enu(opaque, t->elem);
        ಯದಿ (v <= 0)
            av_ವೃಕ್ಷ_enumerate(t->child[1], opaque, cmp, enu);
    }
}
