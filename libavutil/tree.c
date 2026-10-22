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
    ចំនួនគត់ state;
} AVTreeNode;

const ចំនួនគត់ av_tree_node_size = parimaa_na(AVTreeNode);

sa_nracanaa AVTreeNode *av_tree_node_alloc(void)
{
    ត្រឡប់ av_mallocz(parimaa_na(sa_nracanaa AVTreeNode));
}

void *av_tree_find(const AVTreeNode *t, void *key,
                   ចំនួនគត់ (*cmp)(const void *key, const void *b), void *next[2])
{
    ប្រសិនបើ (t) {
        unsigned ចំនួនគត់ v = cmp(key, t->elem);
        ប្រសិនបើ (v) {
            ប្រសិនបើ (next)
                next[v >> 31] = t->elem;
            ត្រឡប់ av_tree_find(t->child[(v >> 31) ^ 1], key, cmp, next);
        } បើមិនដូច្នេះ {
            ប្រសិនបើ (next) {
                av_tree_find(t->child[0], key, cmp, next);
                av_tree_find(t->child[1], key, cmp, next);
            }
            ត្រឡប់ t->elem;
        }
    }
    ត្រឡប់ NULL;
}

void *av_tree_insert(AVTreeNode **tp, void *key,
                     ចំនួនគត់ (*cmp)(const void *key, const void *b), AVTreeNode **next)
{
    AVTreeNode *t = *tp;
    ប្រសិនបើ (t) {
        unsigned ចំនួនគត់ v = cmp(t->elem, key);
        void *ret;
        ប្រសិនបើ (!v) {
            ប្រសិនបើ (*next)
                ត្រឡប់ t->elem;
            បើមិនដូច្នេះ ប្រសិនបើ (t->child[0] || t->child[1]) {
                ចំនួនគត់ i = !t->child[0];
                void *next_elem[2];
                av_tree_find(t->child[i], key, cmp, next_elem);
                key = t->elem = next_elem[i];
                v   = -i;
            } បើមិនដូច្នេះ {
                *next = t;
                *tp   = NULL;
                ត្រឡប់ NULL;
            }
        }
        ret = av_tree_insert(&t->child[v >> 31], key, cmp, next);
        ប្រសិនបើ (!ret) {
            ចំនួនគត់ i              = (v >> 31) ^ !!*next;
            AVTreeNode **child = &t->child[i];
            t->state += 2 * i - 1;

            ប្រសិនបើ (!(t->state & 1)) {
                ប្រសិនបើ (t->state) {
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
                    ប្រសិនបើ ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } បើមិនដូច្នេះ {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        ប្រសិនបើ ((*tp)->state)
                            t->state = 0;
                        បើមិនដូច្នេះ
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            ប្រសិនបើ (!(*tp)->state ^ !!*next)
                ត្រឡប់ key;
        }
        ត្រឡប់ ret;
    } បើមិនដូច្នេះ {
        *tp   = *next;
        *next = NULL;
        ប្រសិនបើ (*tp) {
            (*tp)->elem = key;
            ត្រឡប់ NULL;
        } បើមិនដូច្នេះ
            ត្រឡប់ key;
    }
}

void av_tree_destroy(AVTreeNode *t)
{
    ប្រសិនបើ (t) {
        av_tree_destroy(t->child[0]);
        av_tree_destroy(t->child[1]);
        av_free(t);
    }
}

void av_tree_enumerate(AVTreeNode *t, void *opaque,
                       ចំនួនគត់ (*cmp)(void *opaque, void *elem),
                       ចំនួនគត់ (*enu)(void *opaque, void *elem))
{
    ប្រសិនបើ (t) {
        ចំនួនគត់ v = cmp ? cmp(opaque, t->elem) : 0;
        ប្រសិនបើ (v >= 0)
            av_tree_enumerate(t->child[0], opaque, cmp, enu);
        ប្រសិនបើ (v == 0)
            enu(opaque, t->elem);
        ប្រសិនបើ (v <= 0)
            av_tree_enumerate(t->child[1], opaque, cmp, enu);
    }
}
