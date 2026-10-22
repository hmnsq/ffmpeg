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

#شامل "error.h"
#شامل "log.h"
#شامل "mem.h"
#شامل "tree.h"

تعریفنوع ساختار AVTree_گره {
    ساختار AVTree_گره *child[2];
    تهی *elem;
    صحیح state;
} AVTree_گره;

ثابت صحیح av_درخت_گره_size = اندازه(AVTree_گره);

ساختار AVTree_گره *av_درخت_گره_alloc(تهی)
{
    بازگشت av_mallocz(اندازه(ساختار AVTree_گره));
}

تهی *av_درخت_find(ثابت AVTree_گره *t, تهی *کلید,
                   صحیح (*cmp)(ثابت تهی *کلید, ثابت تهی *b), تهی *next[2])
{
    اگر (t) {
        unsigned صحیح v = cmp(کلید, t->elem);
        اگر (v) {
            اگر (next)
                next[v >> 31] = t->elem;
            بازگشت av_درخت_find(t->child[(v >> 31) ^ 1], کلید, cmp, next);
        } وگرنه {
            اگر (next) {
                av_درخت_find(t->child[0], کلید, cmp, next);
                av_درخت_find(t->child[1], کلید, cmp, next);
            }
            بازگشت t->elem;
        }
    }
    بازگشت پوچ;
}

تهی *av_درخت_درج(AVTree_گره **tp, تهی *کلید,
                     صحیح (*cmp)(ثابت تهی *کلید, ثابت تهی *b), AVTree_گره **next)
{
    AVTree_گره *t = *tp;
    اگر (t) {
        unsigned صحیح v = cmp(t->elem, کلید);
        تهی *ret;
        اگر (!v) {
            اگر (*next)
                بازگشت t->elem;
            وگرنه اگر (t->child[0] || t->child[1]) {
                صحیح i = !t->child[0];
                تهی *next_elem[2];
                av_درخت_find(t->child[i], کلید, cmp, next_elem);
                کلید = t->elem = next_elem[i];
                v   = -i;
            } وگرنه {
                *next = t;
                *tp   = پوچ;
                بازگشت پوچ;
            }
        }
        ret = av_درخت_درج(&t->child[v >> 31], کلید, cmp, next);
        اگر (!ret) {
            صحیح i              = (v >> 31) ^ !!*next;
            AVTree_گره **child = &t->child[i];
            t->state += 2 * i - 1;

            اگر (!(t->state & 1)) {
                اگر (t->state) {
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
                    اگر ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } وگرنه {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        اگر ((*tp)->state)
                            t->state = 0;
                        وگرنه
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            اگر (!(*tp)->state ^ !!*next)
                بازگشت کلید;
        }
        بازگشت ret;
    } وگرنه {
        *tp   = *next;
        *next = پوچ;
        اگر (*tp) {
            (*tp)->elem = کلید;
            بازگشت پوچ;
        } وگرنه
            بازگشت کلید;
    }
}

تهی av_درخت_destroy(AVTree_گره *t)
{
    اگر (t) {
        av_درخت_destroy(t->child[0]);
        av_درخت_destroy(t->child[1]);
        av_free(t);
    }
}

تهی av_درخت_enumerate(AVTree_گره *t, تهی *opaque,
                       صحیح (*cmp)(تهی *opaque, تهی *elem),
                       صحیح (*enu)(تهی *opaque, تهی *elem))
{
    اگر (t) {
        صحیح v = cmp ? cmp(opaque, t->elem) : 0;
        اگر (v >= 0)
            av_درخت_enumerate(t->child[0], opaque, cmp, enu);
        اگر (v == 0)
            enu(opaque, t->elem);
        اگر (v <= 0)
            av_درخت_enumerate(t->child[1], opaque, cmp, enu);
    }
}
