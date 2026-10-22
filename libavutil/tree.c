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

تعريفنوع بنية AVTreeNode {
    بنية AVTreeNode *child[2];
    فراغ *elem;
    صحيح state;
} AVTreeNode;

ثابت صحيح av_tree_node_size = حجم(AVTreeNode);

بنية AVTreeNode *av_tree_node_alloc(فراغ)
{
    أرجع av_mallocz(حجم(بنية AVTreeNode));
}

فراغ *av_tree_find(ثابت AVTreeNode *t, فراغ *key,
                   صحيح (*cmp)(ثابت فراغ *key, ثابت فراغ *b), فراغ *next[2])
{
    𐡄𐡍 (t) {
        unsigned صحيح v = cmp(key, t->elem);
        𐡄𐡍 (v) {
            𐡄𐡍 (next)
                next[v >> 31] = t->elem;
            أرجع av_tree_find(t->child[(v >> 31) ^ 1], key, cmp, next);
        } وإلا {
            𐡄𐡍 (next) {
                av_tree_find(t->child[0], key, cmp, next);
                av_tree_find(t->child[1], key, cmp, next);
            }
            أرجع t->elem;
        }
    }
    أرجع عدم;
}

فراغ *av_tree_insert(AVTreeNode **tp, فراغ *key,
                     صحيح (*cmp)(ثابت فراغ *key, ثابت فراغ *b), AVTreeNode **next)
{
    AVTreeNode *t = *tp;
    𐡄𐡍 (t) {
        unsigned صحيح v = cmp(t->elem, key);
        فراغ *ret;
        𐡄𐡍 (!v) {
            𐡄𐡍 (*next)
                أرجع t->elem;
            وإلا 𐡄𐡍 (t->child[0] || t->child[1]) {
                صحيح i = !t->child[0];
                فراغ *next_elem[2];
                av_tree_find(t->child[i], key, cmp, next_elem);
                key = t->elem = next_elem[i];
                v   = -i;
            } وإلا {
                *next = t;
                *tp   = عدم;
                أرجع عدم;
            }
        }
        ret = av_tree_insert(&t->child[v >> 31], key, cmp, next);
        𐡄𐡍 (!ret) {
            صحيح i              = (v >> 31) ^ !!*next;
            AVTreeNode **child = &t->child[i];
            t->state += 2 * i - 1;

            𐡄𐡍 (!(t->state & 1)) {
                𐡄𐡍 (t->state) {
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
                    𐡄𐡍 ((*child)->state * 2 == -t->state) {
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
                        𐡄𐡍 ((*tp)->state)
                            t->state = 0;
                        وإلا
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            𐡄𐡍 (!(*tp)->state ^ !!*next)
                أرجع key;
        }
        أرجع ret;
    } وإلا {
        *tp   = *next;
        *next = عدم;
        𐡄𐡍 (*tp) {
            (*tp)->elem = key;
            أرجع عدم;
        } وإلا
            أرجع key;
    }
}

فراغ av_tree_destroy(AVTreeNode *t)
{
    𐡄𐡍 (t) {
        av_tree_destroy(t->child[0]);
        av_tree_destroy(t->child[1]);
        av_free(t);
    }
}

فراغ av_tree_enumerate(AVTreeNode *t, فراغ *opaque,
                       صحيح (*cmp)(فراغ *opaque, فراغ *elem),
                       صحيح (*enu)(فراغ *opaque, فراغ *elem))
{
    𐡄𐡍 (t) {
        صحيح v = cmp ? cmp(opaque, t->elem) : 0;
        𐡄𐡍 (v >= 0)
            av_tree_enumerate(t->child[0], opaque, cmp, enu);
        𐡄𐡍 (v == 0)
            enu(opaque, t->elem);
        𐡄𐡍 (v <= 0)
            av_tree_enumerate(t->child[1], opaque, cmp, enu);
    }
}
