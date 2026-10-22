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

تعريفنوع بنية AVTree_گره {
    بنية AVTree_گره *فرزند[2];
    فراغ *elem;
    صحيح state;
} AVTree_گره;

ثابت صحيح av_درخت_گره_اندازه = حجم(AVTree_گره);

بنية AVTree_گره *av_درخت_گره_alloc(فراغ)
{
    أرجع av_mallocz(حجم(بنية AVTree_گره));
}

فراغ *av_درخت_پیدا_کن(ثابت AVTree_گره *t, فراغ *کلید,
                   صحيح (*cmp)(ثابت فراغ *کلید, ثابت فراغ *b), فراغ *بعدی[2])
{
    إذا (t) {
        بیعلامت صحيح v = cmp(کلید, t->elem);
        إذا (v) {
            إذا (بعدی)
                بعدی[v >> 31] = t->elem;
            أرجع av_درخت_پیدا_کن(t->فرزند[(v >> 31) ^ 1], کلید, cmp, بعدی);
        } وإلا {
            إذا (بعدی) {
                av_درخت_پیدا_کن(t->فرزند[0], کلید, cmp, بعدی);
                av_درخت_پیدا_کن(t->فرزند[1], کلید, cmp, بعدی);
            }
            أرجع t->elem;
        }
    }
    أرجع عدم;
}

فراغ *av_درخت_درج(AVTree_گره **tp, فراغ *کلید,
                     صحيح (*cmp)(ثابت فراغ *کلید, ثابت فراغ *b), AVTree_گره **بعدی)
{
    AVTree_گره *t = *tp;
    إذا (t) {
        بیعلامت صحيح v = cmp(t->elem, کلید);
        فراغ *ret;
        إذا (!v) {
            إذا (*بعدی)
                أرجع t->elem;
            وإلا إذا (t->فرزند[0] || t->فرزند[1]) {
                صحيح i = !t->فرزند[0];
                فراغ *بعدی_elem[2];
                av_درخت_پیدا_کن(t->فرزند[i], کلید, cmp, بعدی_elem);
                کلید = t->elem = بعدی_elem[i];
                v   = -i;
            } وإلا {
                *بعدی = t;
                *tp   = عدم;
                أرجع عدم;
            }
        }
        ret = av_درخت_درج(&t->فرزند[v >> 31], کلید, cmp, بعدی);
        إذا (!ret) {
            صحيح i              = (v >> 31) ^ !!*بعدی;
            AVTree_گره **فرزند = &t->فرزند[i];
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
                    إذا ((*فرزند)->state * 2 == -t->state) {
                        *tp                    = (*فرزند)->فرزند[i ^ 1];
                        (*فرزند)->فرزند[i ^ 1] = (*tp)->فرزند[i];
                        (*tp)->فرزند[i]        = *فرزند;
                        *فرزند                 = (*tp)->فرزند[i ^ 1];
                        (*tp)->فرزند[i ^ 1]    = t;

                        (*tp)->فرزند[0]->state = -((*tp)->state > 0);
                        (*tp)->فرزند[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } وإلا {
                        *tp                 = *فرزند;
                        *فرزند              = (*فرزند)->فرزند[i ^ 1];
                        (*tp)->فرزند[i ^ 1] = t;
                        إذا ((*tp)->state)
                            t->state = 0;
                        وإلا
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            إذا (!(*tp)->state ^ !!*بعدی)
                أرجع کلید;
        }
        أرجع ret;
    } وإلا {
        *tp   = *بعدی;
        *بعدی = عدم;
        إذا (*tp) {
            (*tp)->elem = کلید;
            أرجع عدم;
        } وإلا
            أرجع کلید;
    }
}

فراغ av_درخت_destroy(AVTree_گره *t)
{
    إذا (t) {
        av_درخت_destroy(t->فرزند[0]);
        av_درخت_destroy(t->فرزند[1]);
        av_free(t);
    }
}

فراغ av_درخت_enumerate(AVTree_گره *t, فراغ *opaque,
                       صحيح (*cmp)(فراغ *opaque, فراغ *elem),
                       صحيح (*enu)(فراغ *opaque, فراغ *elem))
{
    إذا (t) {
        صحيح v = cmp ? cmp(opaque, t->elem) : 0;
        إذا (v >= 0)
            av_درخت_enumerate(t->فرزند[0], opaque, cmp, enu);
        إذا (v == 0)
            enu(opaque, t->elem);
        إذا (v <= 0)
            av_درخت_enumerate(t->فرزند[1], opaque, cmp, enu);
    }
}
