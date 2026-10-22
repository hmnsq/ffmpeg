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
    החזר av_mallocz(حجم(بنية AVTreeNode));
}

فراغ *av_tree_find(ثابت AVTreeNode *t, فراغ *key,
                   صحيح (*cmp)(ثابت فراغ *key, ثابت فراغ *b), فراغ *next[2])
{
    אם (t) {
        unsigned صحيح v = cmp(key, t->elem);
        אם (v) {
            אם (next)
                next[v >> 31] = t->elem;
            החזר av_tree_find(t->child[(v >> 31) ^ 1], key, cmp, next);
        } אחרת {
            אם (next) {
                av_tree_find(t->child[0], key, cmp, next);
                av_tree_find(t->child[1], key, cmp, next);
            }
            החזר t->elem;
        }
    }
    החזר عدم;
}

فراغ *av_tree_insert(AVTreeNode **tp, فراغ *key,
                     صحيح (*cmp)(ثابت فراغ *key, ثابت فراغ *b), AVTreeNode **next)
{
    AVTreeNode *t = *tp;
    אם (t) {
        unsigned صحيح v = cmp(t->elem, key);
        فراغ *ret;
        אם (!v) {
            אם (*next)
                החזר t->elem;
            אחרת אם (t->child[0] || t->child[1]) {
                صحيح i = !t->child[0];
                فراغ *next_elem[2];
                av_tree_find(t->child[i], key, cmp, next_elem);
                key = t->elem = next_elem[i];
                v   = -i;
            } אחרת {
                *next = t;
                *tp   = عدم;
                החזר عدم;
            }
        }
        ret = av_tree_insert(&t->child[v >> 31], key, cmp, next);
        אם (!ret) {
            صحيح i              = (v >> 31) ^ !!*next;
            AVTreeNode **child = &t->child[i];
            t->state += 2 * i - 1;

            אם (!(t->state & 1)) {
                אם (t->state) {
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
                    אם ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } אחרת {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        אם ((*tp)->state)
                            t->state = 0;
                        אחרת
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            אם (!(*tp)->state ^ !!*next)
                החזר key;
        }
        החזר ret;
    } אחרת {
        *tp   = *next;
        *next = عدم;
        אם (*tp) {
            (*tp)->elem = key;
            החזר عدم;
        } אחרת
            החזר key;
    }
}

فراغ av_tree_destroy(AVTreeNode *t)
{
    אם (t) {
        av_tree_destroy(t->child[0]);
        av_tree_destroy(t->child[1]);
        av_free(t);
    }
}

فراغ av_tree_enumerate(AVTreeNode *t, فراغ *opaque,
                       صحيح (*cmp)(فراغ *opaque, فراغ *elem),
                       صحيح (*enu)(فراغ *opaque, فراغ *elem))
{
    אם (t) {
        صحيح v = cmp ? cmp(opaque, t->elem) : 0;
        אם (v >= 0)
            av_tree_enumerate(t->child[0], opaque, cmp, enu);
        אם (v == 0)
            enu(opaque, t->elem);
        אם (v <= 0)
            av_tree_enumerate(t->child[1], opaque, cmp, enu);
    }
}
