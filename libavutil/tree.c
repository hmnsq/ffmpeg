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

#include "error.h"
#include "log.h"
#include "mem.h"
#include "tree.h"

typedef struct AVTreeNode {
    struct AVTreeNode *child[2];
    void *elem;
    số_nguyên state;
} AVTreeNode;

const số_nguyên av_tree_node_size = sizeof(AVTreeNode);

struct AVTreeNode *av_tree_node_alloc(void)
{
    trả_về av_mallocz(sizeof(struct AVTreeNode));
}

void *av_tree_find(const AVTreeNode *t, void *key,
                   số_nguyên (*cmp)(const void *key, const void *b), void *next[2])
{
    nếu (t) {
        unsigned số_nguyên v = cmp(key, t->elem);
        nếu (v) {
            nếu (next)
                next[v >> 31] = t->elem;
            trả_về av_tree_find(t->child[(v >> 31) ^ 1], key, cmp, next);
        } không_thì {
            nếu (next) {
                av_tree_find(t->child[0], key, cmp, next);
                av_tree_find(t->child[1], key, cmp, next);
            }
            trả_về t->elem;
        }
    }
    trả_về NULL;
}

void *av_tree_insert(AVTreeNode **tp, void *key,
                     số_nguyên (*cmp)(const void *key, const void *b), AVTreeNode **next)
{
    AVTreeNode *t = *tp;
    nếu (t) {
        unsigned số_nguyên v = cmp(t->elem, key);
        void *ret;
        nếu (!v) {
            nếu (*next)
                trả_về t->elem;
            không_thì nếu (t->child[0] || t->child[1]) {
                số_nguyên i = !t->child[0];
                void *next_elem[2];
                av_tree_find(t->child[i], key, cmp, next_elem);
                key = t->elem = next_elem[i];
                v   = -i;
            } không_thì {
                *next = t;
                *tp   = NULL;
                trả_về NULL;
            }
        }
        ret = av_tree_insert(&t->child[v >> 31], key, cmp, next);
        nếu (!ret) {
            số_nguyên i              = (v >> 31) ^ !!*next;
            AVTreeNode **child = &t->child[i];
            t->state += 2 * i - 1;

            nếu (!(t->state & 1)) {
                nếu (t->state) {
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
                    nếu ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } không_thì {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        nếu ((*tp)->state)
                            t->state = 0;
                        không_thì
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            nếu (!(*tp)->state ^ !!*next)
                trả_về key;
        }
        trả_về ret;
    } không_thì {
        *tp   = *next;
        *next = NULL;
        nếu (*tp) {
            (*tp)->elem = key;
            trả_về NULL;
        } không_thì
            trả_về key;
    }
}

void av_tree_destroy(AVTreeNode *t)
{
    nếu (t) {
        av_tree_destroy(t->child[0]);
        av_tree_destroy(t->child[1]);
        av_free(t);
    }
}

void av_tree_enumerate(AVTreeNode *t, void *opaque,
                       số_nguyên (*cmp)(void *opaque, void *elem),
                       số_nguyên (*enu)(void *opaque, void *elem))
{
    nếu (t) {
        số_nguyên v = cmp ? cmp(opaque, t->elem) : 0;
        nếu (v >= 0)
            av_tree_enumerate(t->child[0], opaque, cmp, enu);
        nếu (v == 0)
            enu(opaque, t->elem);
        nếu (v <= 0)
            av_tree_enumerate(t->child[1], opaque, cmp, enu);
    }
}
