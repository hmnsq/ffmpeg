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

typedef sa_nracanaa AVTreeNode {
    sa_nracanaa AVTreeNode *child[2];
    void *elem;
    จำนวนเต็ม state;
} AVTreeNode;

const จำนวนเต็ม av_tree_node_size = parimaa_na(AVTreeNode);

sa_nracanaa AVTreeNode *av_tree_node_alloc(void)
{
    คืน av_mallocz(parimaa_na(sa_nracanaa AVTreeNode));
}

void *av_tree_find(const AVTreeNode *t, void *key,
                   จำนวนเต็ม (*cmp)(const void *key, const void *b), void *next[2])
{
    ถ้า (t) {
        unsigned จำนวนเต็ม v = cmp(key, t->elem);
        ถ้า (v) {
            ถ้า (next)
                next[v >> 31] = t->elem;
            คืน av_tree_find(t->child[(v >> 31) ^ 1], key, cmp, next);
        } มิฉะนั้น {
            ถ้า (next) {
                av_tree_find(t->child[0], key, cmp, next);
                av_tree_find(t->child[1], key, cmp, next);
            }
            คืน t->elem;
        }
    }
    คืน NULL;
}

void *av_tree_insert(AVTreeNode **tp, void *key,
                     จำนวนเต็ม (*cmp)(const void *key, const void *b), AVTreeNode **next)
{
    AVTreeNode *t = *tp;
    ถ้า (t) {
        unsigned จำนวนเต็ม v = cmp(t->elem, key);
        void *ret;
        ถ้า (!v) {
            ถ้า (*next)
                คืน t->elem;
            มิฉะนั้น ถ้า (t->child[0] || t->child[1]) {
                จำนวนเต็ม i = !t->child[0];
                void *next_elem[2];
                av_tree_find(t->child[i], key, cmp, next_elem);
                key = t->elem = next_elem[i];
                v   = -i;
            } มิฉะนั้น {
                *next = t;
                *tp   = NULL;
                คืน NULL;
            }
        }
        ret = av_tree_insert(&t->child[v >> 31], key, cmp, next);
        ถ้า (!ret) {
            จำนวนเต็ม i              = (v >> 31) ^ !!*next;
            AVTreeNode **child = &t->child[i];
            t->state += 2 * i - 1;

            ถ้า (!(t->state & 1)) {
                ถ้า (t->state) {
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
                    ถ้า ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } มิฉะนั้น {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        ถ้า ((*tp)->state)
                            t->state = 0;
                        มิฉะนั้น
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            ถ้า (!(*tp)->state ^ !!*next)
                คืน key;
        }
        คืน ret;
    } มิฉะนั้น {
        *tp   = *next;
        *next = NULL;
        ถ้า (*tp) {
            (*tp)->elem = key;
            คืน NULL;
        } มิฉะนั้น
            คืน key;
    }
}

void av_tree_destroy(AVTreeNode *t)
{
    ถ้า (t) {
        av_tree_destroy(t->child[0]);
        av_tree_destroy(t->child[1]);
        av_free(t);
    }
}

void av_tree_enumerate(AVTreeNode *t, void *opaque,
                       จำนวนเต็ม (*cmp)(void *opaque, void *elem),
                       จำนวนเต็ม (*enu)(void *opaque, void *elem))
{
    ถ้า (t) {
        จำนวนเต็ม v = cmp ? cmp(opaque, t->elem) : 0;
        ถ้า (v >= 0)
            av_tree_enumerate(t->child[0], opaque, cmp, enu);
        ถ้า (v == 0)
            enu(opaque, t->elem);
        ถ้า (v <= 0)
            av_tree_enumerate(t->child[1], opaque, cmp, enu);
    }
}
