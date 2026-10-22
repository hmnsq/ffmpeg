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

#ضمن "error.h"
#ضمن "log.h"
#ضمن "mem.h"
#ضمن "tree.h"

تعريفنوع بنية AVTree_كلي {
    بنية AVTree_كلي *child[2];
    فراغ *elem;
    صحيح state;
} AVTree_كلي;

ثابت صحيح av_بشيا_كلي_size = حجم(AVTree_كلي);

بنية AVTree_كلي *av_بشيا_كلي_alloc(فراغ)
{
    أرجع av_mallocz(حجم(بنية AVTree_كلي));
}

فراغ *av_بشيا_find(ثابت AVTree_كلي *t, فراغ *مبودي,
                   صحيح (*cmp)(ثابت فراغ *مبودي, ثابت فراغ *b), فراغ *next[2])
{
    إذا (t) {
        unsigned صحيح v = cmp(مبودي, t->elem);
        إذا (v) {
            إذا (next)
                next[v >> 31] = t->elem;
            أرجع av_بشيا_find(t->child[(v >> 31) ^ 1], مبودي, cmp, next);
        } وإلا {
            إذا (next) {
                av_بشيا_find(t->child[0], مبودي, cmp, next);
                av_بشيا_find(t->child[1], مبودي, cmp, next);
            }
            أرجع t->elem;
        }
    }
    أرجع عدم;
}

فراغ *av_بشيا_سك(AVTree_كلي **tp, فراغ *مبودي,
                     صحيح (*cmp)(ثابت فراغ *مبودي, ثابت فراغ *b), AVTree_كلي **next)
{
    AVTree_كلي *t = *tp;
    إذا (t) {
        unsigned صحيح v = cmp(t->elem, مبودي);
        فراغ *ret;
        إذا (!v) {
            إذا (*next)
                أرجع t->elem;
            وإلا إذا (t->child[0] || t->child[1]) {
                صحيح i = !t->child[0];
                فراغ *next_elem[2];
                av_بشيا_find(t->child[i], مبودي, cmp, next_elem);
                مبودي = t->elem = next_elem[i];
                v   = -i;
            } وإلا {
                *next = t;
                *tp   = عدم;
                أرجع عدم;
            }
        }
        ret = av_بشيا_سك(&t->child[v >> 31], مبودي, cmp, next);
        إذا (!ret) {
            صحيح i              = (v >> 31) ^ !!*next;
            AVTree_كلي **child = &t->child[i];
            t->state += 2 * i - 1;

            إذا (!(t->state & 1)) {
                إذا (t->state) {
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
                    إذا ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } وإلا {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        إذا ((*tp)->state)
                            t->state = 0;
                        وإلا
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            إذا (!(*tp)->state ^ !!*next)
                أرجع مبودي;
        }
        أرجع ret;
    } وإلا {
        *tp   = *next;
        *next = عدم;
        إذا (*tp) {
            (*tp)->elem = مبودي;
            أرجع عدم;
        } وإلا
            أرجع مبودي;
    }
}

فراغ av_بشيا_destroy(AVTree_كلي *t)
{
    إذا (t) {
        av_بشيا_destroy(t->child[0]);
        av_بشيا_destroy(t->child[1]);
        av_free(t);
    }
}

فراغ av_بشيا_enumerate(AVTree_كلي *t, فراغ *opaque,
                       صحيح (*cmp)(فراغ *opaque, فراغ *elem),
                       صحيح (*enu)(فراغ *opaque, فراغ *elem))
{
    إذا (t) {
        صحيح v = cmp ? cmp(opaque, t->elem) : 0;
        إذا (v >= 0)
            av_بشيا_enumerate(t->child[0], opaque, cmp, enu);
        إذا (v == 0)
            enu(opaque, t->elem);
        إذا (v <= 0)
            av_بشيا_enumerate(t->child[1], opaque, cmp, enu);
    }
}
