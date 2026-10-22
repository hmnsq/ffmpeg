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

تعريفنوع بنية AVTree_گرہ {
    بنية AVTree_گرہ *بچہ[2];
    فراغ *elem;
    صحيح state;
} AVTree_گرہ;

ثابت صحيح av_درخت_گرہ_ناپ = حجم(AVTree_گرہ);

بنية AVTree_گرہ *av_درخت_گرہ_alloc(فراغ)
{
    أرجع av_mallocz(حجم(بنية AVTree_گرہ));
}

فراغ *av_درخت_لبھو(ثابت AVTree_گرہ *t, فراغ *کلید,
                   صحيح (*cmp)(ثابت فراغ *کلید, ثابت فراغ *b), فراغ *اگلا[2])
{
    إذا (t) {
        بنانشانی صحيح v = cmp(کلید, t->elem);
        إذا (v) {
            إذا (اگلا)
                اگلا[v >> 31] = t->elem;
            أرجع av_درخت_لبھو(t->بچہ[(v >> 31) ^ 1], کلید, cmp, اگلا);
        } وإلا {
            إذا (اگلا) {
                av_درخت_لبھو(t->بچہ[0], کلید, cmp, اگلا);
                av_درخت_لبھو(t->بچہ[1], کلید, cmp, اگلا);
            }
            أرجع t->elem;
        }
    }
    أرجع عدم;
}

فراغ *av_درخت_داخل_کرو(AVTree_گرہ **tp, فراغ *کلید,
                     صحيح (*cmp)(ثابت فراغ *کلید, ثابت فراغ *b), AVTree_گرہ **اگلا)
{
    AVTree_گرہ *t = *tp;
    إذا (t) {
        بنانشانی صحيح v = cmp(t->elem, کلید);
        فراغ *ret;
        إذا (!v) {
            إذا (*اگلا)
                أرجع t->elem;
            وإلا إذا (t->بچہ[0] || t->بچہ[1]) {
                صحيح i = !t->بچہ[0];
                فراغ *اگلا_elem[2];
                av_درخت_لبھو(t->بچہ[i], کلید, cmp, اگلا_elem);
                کلید = t->elem = اگلا_elem[i];
                v   = -i;
            } وإلا {
                *اگلا = t;
                *tp   = عدم;
                أرجع عدم;
            }
        }
        ret = av_درخت_داخل_کرو(&t->بچہ[v >> 31], کلید, cmp, اگلا);
        إذا (!ret) {
            صحيح i              = (v >> 31) ^ !!*اگلا;
            AVTree_گرہ **بچہ = &t->بچہ[i];
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
                    إذا ((*بچہ)->state * 2 == -t->state) {
                        *tp                    = (*بچہ)->بچہ[i ^ 1];
                        (*بچہ)->بچہ[i ^ 1] = (*tp)->بچہ[i];
                        (*tp)->بچہ[i]        = *بچہ;
                        *بچہ                 = (*tp)->بچہ[i ^ 1];
                        (*tp)->بچہ[i ^ 1]    = t;

                        (*tp)->بچہ[0]->state = -((*tp)->state > 0);
                        (*tp)->بچہ[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } وإلا {
                        *tp                 = *بچہ;
                        *بچہ              = (*بچہ)->بچہ[i ^ 1];
                        (*tp)->بچہ[i ^ 1] = t;
                        إذا ((*tp)->state)
                            t->state = 0;
                        وإلا
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            إذا (!(*tp)->state ^ !!*اگلا)
                أرجع کلید;
        }
        أرجع ret;
    } وإلا {
        *tp   = *اگلا;
        *اگلا = عدم;
        إذا (*tp) {
            (*tp)->elem = کلید;
            أرجع عدم;
        } وإلا
            أرجع کلید;
    }
}

فراغ av_درخت_destroy(AVTree_گرہ *t)
{
    إذا (t) {
        av_درخت_destroy(t->بچہ[0]);
        av_درخت_destroy(t->بچہ[1]);
        av_free(t);
    }
}

فراغ av_درخت_enumerate(AVTree_گرہ *t, فراغ *opaque,
                       صحيح (*cmp)(فراغ *opaque, فراغ *elem),
                       صحيح (*enu)(فراغ *opaque, فراغ *elem))
{
    إذا (t) {
        صحيح v = cmp ? cmp(opaque, t->elem) : 0;
        إذا (v >= 0)
            av_درخت_enumerate(t->بچہ[0], opaque, cmp, enu);
        إذا (v == 0)
            enu(opaque, t->elem);
        إذا (v <= 0)
            av_درخت_enumerate(t->بچہ[1], opaque, cmp, enu);
    }
}
