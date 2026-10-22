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

#অন্তর্ভাব "error.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "tree.h"

প্রকারনির্দেশ সংরচনা AVTree_গ্রন্থি {
    সংরচনা AVTree_গ্রন্থি *child[2];
    শূন্য *elem;
    পূর্ণাঙ্ক state;
} AVTree_গ্রন্থি;

ধ্রুব পূর্ণাঙ্ক av_বৃক্ষ_গ্রন্থি_size = পরিমাণ(AVTree_গ্রন্থি);

সংরচনা AVTree_গ্রন্থি *av_বৃক্ষ_গ্রন্থি_alloc(শূন্য)
{
    প্রত্যাগম av_mallocz(পরিমাণ(সংরচনা AVTree_গ্রন্থি));
}

শূন্য *av_বৃক্ষ_find(ধ্রুব AVTree_গ্রন্থি *t, শূন্য *চাবি,
                   পূর্ণাঙ্ক (*cmp)(ধ্রুব শূন্য *চাবি, ধ্রুব শূন্য *b), শূন্য *next[2])
{
    যদি (t) {
        unsigned পূর্ণাঙ্ক v = cmp(চাবি, t->elem);
        যদি (v) {
            যদি (next)
                next[v >> 31] = t->elem;
            প্রত্যাগম av_বৃক্ষ_find(t->child[(v >> 31) ^ 1], চাবি, cmp, next);
        } অন্যথা {
            যদি (next) {
                av_বৃক্ষ_find(t->child[0], চাবি, cmp, next);
                av_বৃক্ষ_find(t->child[1], চাবি, cmp, next);
            }
            প্রত্যাগম t->elem;
        }
    }
    প্রত্যাগম রিক্ত;
}

শূন্য *av_বৃক্ষ_ঢোকাও(AVTree_গ্রন্থি **tp, শূন্য *চাবি,
                     পূর্ণাঙ্ক (*cmp)(ধ্রুব শূন্য *চাবি, ধ্রুব শূন্য *b), AVTree_গ্রন্থি **next)
{
    AVTree_গ্রন্থি *t = *tp;
    যদি (t) {
        unsigned পূর্ণাঙ্ক v = cmp(t->elem, চাবি);
        শূন্য *ret;
        যদি (!v) {
            যদি (*next)
                প্রত্যাগম t->elem;
            অন্যথা যদি (t->child[0] || t->child[1]) {
                পূর্ণাঙ্ক i = !t->child[0];
                শূন্য *next_elem[2];
                av_বৃক্ষ_find(t->child[i], চাবি, cmp, next_elem);
                চাবি = t->elem = next_elem[i];
                v   = -i;
            } অন্যথা {
                *next = t;
                *tp   = রিক্ত;
                প্রত্যাগম রিক্ত;
            }
        }
        ret = av_বৃক্ষ_ঢোকাও(&t->child[v >> 31], চাবি, cmp, next);
        যদি (!ret) {
            পূর্ণাঙ্ক i              = (v >> 31) ^ !!*next;
            AVTree_গ্রন্থি **child = &t->child[i];
            t->state += 2 * i - 1;

            যদি (!(t->state & 1)) {
                যদি (t->state) {
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
                    যদি ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } অন্যথা {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        যদি ((*tp)->state)
                            t->state = 0;
                        অন্যথা
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            যদি (!(*tp)->state ^ !!*next)
                প্রত্যাগম চাবি;
        }
        প্রত্যাগম ret;
    } অন্যথা {
        *tp   = *next;
        *next = রিক্ত;
        যদি (*tp) {
            (*tp)->elem = চাবি;
            প্রত্যাগম রিক্ত;
        } অন্যথা
            প্রত্যাগম চাবি;
    }
}

শূন্য av_বৃক্ষ_destroy(AVTree_গ্রন্থি *t)
{
    যদি (t) {
        av_বৃক্ষ_destroy(t->child[0]);
        av_বৃক্ষ_destroy(t->child[1]);
        av_free(t);
    }
}

শূন্য av_বৃক্ষ_enumerate(AVTree_গ্রন্থি *t, শূন্য *opaque,
                       পূর্ণাঙ্ক (*cmp)(শূন্য *opaque, শূন্য *elem),
                       পূর্ণাঙ্ক (*enu)(শূন্য *opaque, শূন্য *elem))
{
    যদি (t) {
        পূর্ণাঙ্ক v = cmp ? cmp(opaque, t->elem) : 0;
        যদি (v >= 0)
            av_বৃক্ষ_enumerate(t->child[0], opaque, cmp, enu);
        যদি (v == 0)
            enu(opaque, t->elem);
        যদি (v <= 0)
            av_বৃক্ষ_enumerate(t->child[1], opaque, cmp, enu);
    }
}
