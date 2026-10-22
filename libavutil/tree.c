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

#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "tree.h"

પ્રકારવ્યાખ્યા સંરચના AVTree_ગાંઠ {
    સંરચના AVTree_ગાંઠ *child[2];
    શૂન્ય *elem;
    પૂર્ણાંક state;
} AVTree_ગાંઠ;

અચલ પૂર્ણાંક av_વૃક્ષ_ગાંઠ_size = કદ(AVTree_ગાંઠ);

સંરચના AVTree_ગાંઠ *av_વૃક્ષ_ગાંઠ_alloc(શૂન્ય)
{
    પાછા av_mallocz(કદ(સંરચના AVTree_ગાંઠ));
}

શૂન્ય *av_વૃક્ષ_find(અચલ AVTree_ગાંઠ *t, શૂન્ય *ચાવી,
                   પૂર્ણાંક (*cmp)(અચલ શૂન્ય *ચાવી, અચલ શૂન્ય *b), શૂન્ય *next[2])
{
    જો (t) {
        unsigned પૂર્ણાંક v = cmp(ચાવી, t->elem);
        જો (v) {
            જો (next)
                next[v >> 31] = t->elem;
            પાછા av_વૃક્ષ_find(t->child[(v >> 31) ^ 1], ચાવી, cmp, next);
        } નહીંતર {
            જો (next) {
                av_વૃક્ષ_find(t->child[0], ચાવી, cmp, next);
                av_વૃક્ષ_find(t->child[1], ચાવી, cmp, next);
            }
            પાછા t->elem;
        }
    }
    પાછા ખાલી;
}

શૂન્ય *av_વૃક્ષ_ઉમેરો(AVTree_ગાંઠ **tp, શૂન્ય *ચાવી,
                     પૂર્ણાંક (*cmp)(અચલ શૂન્ય *ચાવી, અચલ શૂન્ય *b), AVTree_ગાંઠ **next)
{
    AVTree_ગાંઠ *t = *tp;
    જો (t) {
        unsigned પૂર્ણાંક v = cmp(t->elem, ચાવી);
        શૂન્ય *ret;
        જો (!v) {
            જો (*next)
                પાછા t->elem;
            નહીંતર જો (t->child[0] || t->child[1]) {
                પૂર્ણાંક i = !t->child[0];
                શૂન્ય *next_elem[2];
                av_વૃક્ષ_find(t->child[i], ચાવી, cmp, next_elem);
                ચાવી = t->elem = next_elem[i];
                v   = -i;
            } નહીંતર {
                *next = t;
                *tp   = ખાલી;
                પાછા ખાલી;
            }
        }
        ret = av_વૃક્ષ_ઉમેરો(&t->child[v >> 31], ચાવી, cmp, next);
        જો (!ret) {
            પૂર્ણાંક i              = (v >> 31) ^ !!*next;
            AVTree_ગાંઠ **child = &t->child[i];
            t->state += 2 * i - 1;

            જો (!(t->state & 1)) {
                જો (t->state) {
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
                    જો ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } નહીંતર {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        જો ((*tp)->state)
                            t->state = 0;
                        નહીંતર
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            જો (!(*tp)->state ^ !!*next)
                પાછા ચાવી;
        }
        પાછા ret;
    } નહીંતર {
        *tp   = *next;
        *next = ખાલી;
        જો (*tp) {
            (*tp)->elem = ચાવી;
            પાછા ખાલી;
        } નહીંતર
            પાછા ચાવી;
    }
}

શૂન્ય av_વૃક્ષ_destroy(AVTree_ગાંઠ *t)
{
    જો (t) {
        av_વૃક્ષ_destroy(t->child[0]);
        av_વૃક્ષ_destroy(t->child[1]);
        av_free(t);
    }
}

શૂન્ય av_વૃક્ષ_enumerate(AVTree_ગાંઠ *t, શૂન્ય *opaque,
                       પૂર્ણાંક (*cmp)(શૂન્ય *opaque, શૂન્ય *elem),
                       પૂર્ણાંક (*enu)(શૂન્ય *opaque, શૂન્ય *elem))
{
    જો (t) {
        પૂર્ણાંક v = cmp ? cmp(opaque, t->elem) : 0;
        જો (v >= 0)
            av_વૃક્ષ_enumerate(t->child[0], opaque, cmp, enu);
        જો (v == 0)
            enu(opaque, t->elem);
        જો (v <= 0)
            av_વૃક્ષ_enumerate(t->child[1], opaque, cmp, enu);
    }
}
