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

#அந்தர்பாவ "error.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "tree.h"

வகைவரை கட்டமைப்பு AVTree_முனை {
    கட்டமைப்பு AVTree_முனை *child[2];
    வெறுமை *elem;
    முழு state;
} AVTree_முனை;

மாறிலி முழு av_மரம்_முனை_size = அளவு(AVTree_முனை);

கட்டமைப்பு AVTree_முனை *av_மரம்_முனை_alloc(வெறுமை)
{
    திரும்பு av_mallocz(அளவு(கட்டமைப்பு AVTree_முனை));
}

வெறுமை *av_மரம்_find(மாறிலி AVTree_முனை *t, வெறுமை *சாவி,
                   முழு (*cmp)(மாறிலி வெறுமை *சாவி, மாறிலி வெறுமை *b), வெறுமை *next[2])
{
    எனில் (t) {
        unsigned முழு v = cmp(சாவி, t->elem);
        எனில் (v) {
            எனில் (next)
                next[v >> 31] = t->elem;
            திரும்பு av_மரம்_find(t->child[(v >> 31) ^ 1], சாவி, cmp, next);
        } இல்லையெனில் {
            எனில் (next) {
                av_மரம்_find(t->child[0], சாவி, cmp, next);
                av_மரம்_find(t->child[1], சாவி, cmp, next);
            }
            திரும்பு t->elem;
        }
    }
    திரும்பு வெற்று;
}

வெறுமை *av_மரம்_செருகு(AVTree_முனை **tp, வெறுமை *சாவி,
                     முழு (*cmp)(மாறிலி வெறுமை *சாவி, மாறிலி வெறுமை *b), AVTree_முனை **next)
{
    AVTree_முனை *t = *tp;
    எனில் (t) {
        unsigned முழு v = cmp(t->elem, சாவி);
        வெறுமை *ret;
        எனில் (!v) {
            எனில் (*next)
                திரும்பு t->elem;
            இல்லையெனில் எனில் (t->child[0] || t->child[1]) {
                முழு i = !t->child[0];
                வெறுமை *next_elem[2];
                av_மரம்_find(t->child[i], சாவி, cmp, next_elem);
                சாவி = t->elem = next_elem[i];
                v   = -i;
            } இல்லையெனில் {
                *next = t;
                *tp   = வெற்று;
                திரும்பு வெற்று;
            }
        }
        ret = av_மரம்_செருகு(&t->child[v >> 31], சாவி, cmp, next);
        எனில் (!ret) {
            முழு i              = (v >> 31) ^ !!*next;
            AVTree_முனை **child = &t->child[i];
            t->state += 2 * i - 1;

            எனில் (!(t->state & 1)) {
                எனில் (t->state) {
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
                    எனில் ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } இல்லையெனில் {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        எனில் ((*tp)->state)
                            t->state = 0;
                        இல்லையெனில்
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            எனில் (!(*tp)->state ^ !!*next)
                திரும்பு சாவி;
        }
        திரும்பு ret;
    } இல்லையெனில் {
        *tp   = *next;
        *next = வெற்று;
        எனில் (*tp) {
            (*tp)->elem = சாவி;
            திரும்பு வெற்று;
        } இல்லையெனில்
            திரும்பு சாவி;
    }
}

வெறுமை av_மரம்_destroy(AVTree_முனை *t)
{
    எனில் (t) {
        av_மரம்_destroy(t->child[0]);
        av_மரம்_destroy(t->child[1]);
        av_free(t);
    }
}

வெறுமை av_மரம்_enumerate(AVTree_முனை *t, வெறுமை *opaque,
                       முழு (*cmp)(வெறுமை *opaque, வெறுமை *elem),
                       முழு (*enu)(வெறுமை *opaque, வெறுமை *elem))
{
    எனில் (t) {
        முழு v = cmp ? cmp(opaque, t->elem) : 0;
        எனில் (v >= 0)
            av_மரம்_enumerate(t->child[0], opaque, cmp, enu);
        எனில் (v == 0)
            enu(opaque, t->elem);
        எனில் (v <= 0)
            av_மரம்_enumerate(t->child[1], opaque, cmp, enu);
    }
}
