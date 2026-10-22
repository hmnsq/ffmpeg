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

تعريفنوع بنية AVTree_ڳنڍ {
    بنية AVTree_ڳنڍ *ٻار[2];
    فراغ *elem;
    صحيح state;
} AVTree_ڳنڍ;

ثابت صحيح av_وڻ_ڳنڍ_سائيز = حجم(AVTree_ڳنڍ);

بنية AVTree_ڳنڍ *av_وڻ_ڳنڍ_alloc(فراغ)
{
    أرجع av_mallocz(حجم(بنية AVTree_ڳنڍ));
}

فراغ *av_وڻ_ڳوليو(ثابت AVTree_ڳنڍ *t, فراغ *ڪنجي,
                   صحيح (*cmp)(ثابت فراغ *ڪنجي, ثابت فراغ *b), فراغ *ايندڙ[2])
{
    إذا (t) {
        بنانشان صحيح v = cmp(ڪنجي, t->elem);
        إذا (v) {
            إذا (ايندڙ)
                ايندڙ[v >> 31] = t->elem;
            أرجع av_وڻ_ڳوليو(t->ٻار[(v >> 31) ^ 1], ڪنجي, cmp, ايندڙ);
        } وإلا {
            إذا (ايندڙ) {
                av_وڻ_ڳوليو(t->ٻار[0], ڪنجي, cmp, ايندڙ);
                av_وڻ_ڳوليو(t->ٻار[1], ڪنجي, cmp, ايندڙ);
            }
            أرجع t->elem;
        }
    }
    أرجع عدم;
}

فراغ *av_وڻ_وجهو(AVTree_ڳنڍ **tp, فراغ *ڪنجي,
                     صحيح (*cmp)(ثابت فراغ *ڪنجي, ثابت فراغ *b), AVTree_ڳنڍ **ايندڙ)
{
    AVTree_ڳنڍ *t = *tp;
    إذا (t) {
        بنانشان صحيح v = cmp(t->elem, ڪنجي);
        فراغ *ret;
        إذا (!v) {
            إذا (*ايندڙ)
                أرجع t->elem;
            وإلا إذا (t->ٻار[0] || t->ٻار[1]) {
                صحيح i = !t->ٻار[0];
                فراغ *ايندڙ_elem[2];
                av_وڻ_ڳوليو(t->ٻار[i], ڪنجي, cmp, ايندڙ_elem);
                ڪنجي = t->elem = ايندڙ_elem[i];
                v   = -i;
            } وإلا {
                *ايندڙ = t;
                *tp   = عدم;
                أرجع عدم;
            }
        }
        ret = av_وڻ_وجهو(&t->ٻار[v >> 31], ڪنجي, cmp, ايندڙ);
        إذا (!ret) {
            صحيح i              = (v >> 31) ^ !!*ايندڙ;
            AVTree_ڳنڍ **ٻار = &t->ٻار[i];
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
                    إذا ((*ٻار)->state * 2 == -t->state) {
                        *tp                    = (*ٻار)->ٻار[i ^ 1];
                        (*ٻار)->ٻار[i ^ 1] = (*tp)->ٻار[i];
                        (*tp)->ٻار[i]        = *ٻار;
                        *ٻار                 = (*tp)->ٻار[i ^ 1];
                        (*tp)->ٻار[i ^ 1]    = t;

                        (*tp)->ٻار[0]->state = -((*tp)->state > 0);
                        (*tp)->ٻار[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } وإلا {
                        *tp                 = *ٻار;
                        *ٻار              = (*ٻار)->ٻار[i ^ 1];
                        (*tp)->ٻار[i ^ 1] = t;
                        إذا ((*tp)->state)
                            t->state = 0;
                        وإلا
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            إذا (!(*tp)->state ^ !!*ايندڙ)
                أرجع ڪنجي;
        }
        أرجع ret;
    } وإلا {
        *tp   = *ايندڙ;
        *ايندڙ = عدم;
        إذا (*tp) {
            (*tp)->elem = ڪنجي;
            أرجع عدم;
        } وإلا
            أرجع ڪنجي;
    }
}

فراغ av_وڻ_destroy(AVTree_ڳنڍ *t)
{
    إذا (t) {
        av_وڻ_destroy(t->ٻار[0]);
        av_وڻ_destroy(t->ٻار[1]);
        av_free(t);
    }
}

فراغ av_وڻ_enumerate(AVTree_ڳنڍ *t, فراغ *opaque,
                       صحيح (*cmp)(فراغ *opaque, فراغ *elem),
                       صحيح (*enu)(فراغ *opaque, فراغ *elem))
{
    إذا (t) {
        صحيح v = cmp ? cmp(opaque, t->elem) : 0;
        إذا (v >= 0)
            av_وڻ_enumerate(t->ٻار[0], opaque, cmp, enu);
        إذا (v == 0)
            enu(opaque, t->elem);
        إذا (v <= 0)
            av_وڻ_enumerate(t->ٻار[1], opaque, cmp, enu);
    }
}
