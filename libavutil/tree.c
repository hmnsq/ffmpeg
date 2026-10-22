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

تعريفنوع بنية AVTree_غوټه {
    بنية AVTree_غوټه *ماشوم[2];
    فراغ *elem;
    صحيح state;
} AVTree_غوټه;

ثابت صحيح av_ونه_غوټه_اندازه = حجم(AVTree_غوټه);

بنية AVTree_غوټه *av_ونه_غوټه_alloc(فراغ)
{
    أرجع av_mallocz(حجم(بنية AVTree_غوټه));
}

فراغ *av_ونه_پیدا_کړه(ثابت AVTree_غوټه *t, فراغ *کلی,
                   صحيح (*cmp)(ثابت فراغ *کلی, ثابت فراغ *b), فراغ *بل[2])
{
    إذا (t) {
        بینښه صحيح v = cmp(کلی, t->elem);
        إذا (v) {
            إذا (بل)
                بل[v >> 31] = t->elem;
            أرجع av_ونه_پیدا_کړه(t->ماشوم[(v >> 31) ^ 1], کلی, cmp, بل);
        } وإلا {
            إذا (بل) {
                av_ونه_پیدا_کړه(t->ماشوم[0], کلی, cmp, بل);
                av_ونه_پیدا_کړه(t->ماشوم[1], کلی, cmp, بل);
            }
            أرجع t->elem;
        }
    }
    أرجع عدم;
}

فراغ *av_ونه_ورننباسه(AVTree_غوټه **tp, فراغ *کلی,
                     صحيح (*cmp)(ثابت فراغ *کلی, ثابت فراغ *b), AVTree_غوټه **بل)
{
    AVTree_غوټه *t = *tp;
    إذا (t) {
        بینښه صحيح v = cmp(t->elem, کلی);
        فراغ *ret;
        إذا (!v) {
            إذا (*بل)
                أرجع t->elem;
            وإلا إذا (t->ماشوم[0] || t->ماشوم[1]) {
                صحيح i = !t->ماشوم[0];
                فراغ *بل_elem[2];
                av_ونه_پیدا_کړه(t->ماشوم[i], کلی, cmp, بل_elem);
                کلی = t->elem = بل_elem[i];
                v   = -i;
            } وإلا {
                *بل = t;
                *tp   = عدم;
                أرجع عدم;
            }
        }
        ret = av_ونه_ورننباسه(&t->ماشوم[v >> 31], کلی, cmp, بل);
        إذا (!ret) {
            صحيح i              = (v >> 31) ^ !!*بل;
            AVTree_غوټه **ماشوم = &t->ماشوم[i];
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
                    إذا ((*ماشوم)->state * 2 == -t->state) {
                        *tp                    = (*ماشوم)->ماشوم[i ^ 1];
                        (*ماشوم)->ماشوم[i ^ 1] = (*tp)->ماشوم[i];
                        (*tp)->ماشوم[i]        = *ماشوم;
                        *ماشوم                 = (*tp)->ماشوم[i ^ 1];
                        (*tp)->ماشوم[i ^ 1]    = t;

                        (*tp)->ماشوم[0]->state = -((*tp)->state > 0);
                        (*tp)->ماشوم[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } وإلا {
                        *tp                 = *ماشوم;
                        *ماشوم              = (*ماشوم)->ماشوم[i ^ 1];
                        (*tp)->ماشوم[i ^ 1] = t;
                        إذا ((*tp)->state)
                            t->state = 0;
                        وإلا
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            إذا (!(*tp)->state ^ !!*بل)
                أرجع کلی;
        }
        أرجع ret;
    } وإلا {
        *tp   = *بل;
        *بل = عدم;
        إذا (*tp) {
            (*tp)->elem = کلی;
            أرجع عدم;
        } وإلا
            أرجع کلی;
    }
}

فراغ av_ونه_destroy(AVTree_غوټه *t)
{
    إذا (t) {
        av_ونه_destroy(t->ماشوم[0]);
        av_ونه_destroy(t->ماشوم[1]);
        av_free(t);
    }
}

فراغ av_ونه_enumerate(AVTree_غوټه *t, فراغ *opaque,
                       صحيح (*cmp)(فراغ *opaque, فراغ *elem),
                       صحيح (*enu)(فراغ *opaque, فراغ *elem))
{
    إذا (t) {
        صحيح v = cmp ? cmp(opaque, t->elem) : 0;
        إذا (v >= 0)
            av_ونه_enumerate(t->ماشوم[0], opaque, cmp, enu);
        إذا (v == 0)
            enu(opaque, t->elem);
        إذا (v <= 0)
            av_ونه_enumerate(t->ماشوم[1], opaque, cmp, enu);
    }
}
