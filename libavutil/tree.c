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

قسمتعریف ساخت AVTree_گرہ {
    ساخت AVTree_گرہ *بچہ[2];
    خالی *elem;
    صحیح state;
} AVTree_گرہ;

ثابت صحیح av_درخت_گرہ_سائز = حجم(AVTree_گرہ);

ساخت AVTree_گرہ *av_درخت_گرہ_alloc(خالی)
{
    واپس av_mallocz(حجم(ساخت AVTree_گرہ));
}

خالی *av_درخت_ڈھونڈو(ثابت AVTree_گرہ *t, خالی *کلید,
                   صحیح (*cmp)(ثابت خالی *کلید, ثابت خالی *b), خالی *اگلا[2])
{
    اگر (t) {
        غیرعلامتی صحیح v = cmp(کلید, t->elem);
        اگر (v) {
            اگر (اگلا)
                اگلا[v >> 31] = t->elem;
            واپس av_درخت_ڈھونڈو(t->بچہ[(v >> 31) ^ 1], کلید, cmp, اگلا);
        } ورنہ {
            اگر (اگلا) {
                av_درخت_ڈھونڈو(t->بچہ[0], کلید, cmp, اگلا);
                av_درخت_ڈھونڈو(t->بچہ[1], کلید, cmp, اگلا);
            }
            واپس t->elem;
        }
    }
    واپس تہی;
}

خالی *av_درخت_داخل_کرو(AVTree_گرہ **tp, خالی *کلید,
                     صحیح (*cmp)(ثابت خالی *کلید, ثابت خالی *b), AVTree_گرہ **اگلا)
{
    AVTree_گرہ *t = *tp;
    اگر (t) {
        غیرعلامتی صحیح v = cmp(t->elem, کلید);
        خالی *ret;
        اگر (!v) {
            اگر (*اگلا)
                واپس t->elem;
            ورنہ اگر (t->بچہ[0] || t->بچہ[1]) {
                صحیح i = !t->بچہ[0];
                خالی *اگلا_elem[2];
                av_درخت_ڈھونڈو(t->بچہ[i], کلید, cmp, اگلا_elem);
                کلید = t->elem = اگلا_elem[i];
                v   = -i;
            } ورنہ {
                *اگلا = t;
                *tp   = تہی;
                واپس تہی;
            }
        }
        ret = av_درخت_داخل_کرو(&t->بچہ[v >> 31], کلید, cmp, اگلا);
        اگر (!ret) {
            صحیح i              = (v >> 31) ^ !!*اگلا;
            AVTree_گرہ **بچہ = &t->بچہ[i];
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
                    اگر ((*بچہ)->state * 2 == -t->state) {
                        *tp                    = (*بچہ)->بچہ[i ^ 1];
                        (*بچہ)->بچہ[i ^ 1] = (*tp)->بچہ[i];
                        (*tp)->بچہ[i]        = *بچہ;
                        *بچہ                 = (*tp)->بچہ[i ^ 1];
                        (*tp)->بچہ[i ^ 1]    = t;

                        (*tp)->بچہ[0]->state = -((*tp)->state > 0);
                        (*tp)->بچہ[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } ورنہ {
                        *tp                 = *بچہ;
                        *بچہ              = (*بچہ)->بچہ[i ^ 1];
                        (*tp)->بچہ[i ^ 1] = t;
                        اگر ((*tp)->state)
                            t->state = 0;
                        ورنہ
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            اگر (!(*tp)->state ^ !!*اگلا)
                واپس کلید;
        }
        واپس ret;
    } ورنہ {
        *tp   = *اگلا;
        *اگلا = تہی;
        اگر (*tp) {
            (*tp)->elem = کلید;
            واپس تہی;
        } ورنہ
            واپس کلید;
    }
}

خالی av_درخت_destroy(AVTree_گرہ *t)
{
    اگر (t) {
        av_درخت_destroy(t->بچہ[0]);
        av_درخت_destroy(t->بچہ[1]);
        av_free(t);
    }
}

خالی av_درخت_enumerate(AVTree_گرہ *t, خالی *opaque,
                       صحیح (*cmp)(خالی *opaque, خالی *elem),
                       صحیح (*enu)(خالی *opaque, خالی *elem))
{
    اگر (t) {
        صحیح v = cmp ? cmp(opaque, t->elem) : 0;
        اگر (v >= 0)
            av_درخت_enumerate(t->بچہ[0], opaque, cmp, enu);
        اگر (v == 0)
            enu(opaque, t->elem);
        اگر (v <= 0)
            av_درخت_enumerate(t->بچہ[1], opaque, cmp, enu);
    }
}
