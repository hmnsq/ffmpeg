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
    ຈຳນວນເຕັມ state;
} AVTreeNode;

const ຈຳນວນເຕັມ av_tree_node_size = parimaa_na(AVTreeNode);

sa_nracanaa AVTreeNode *av_tree_node_alloc(void)
{
    ສົ່ງຄືນ av_mallocz(parimaa_na(sa_nracanaa AVTreeNode));
}

void *av_tree_find(const AVTreeNode *t, void *key,
                   ຈຳນວນເຕັມ (*cmp)(const void *key, const void *b), void *next[2])
{
    ຖ້າ (t) {
        unsigned ຈຳນວນເຕັມ v = cmp(key, t->elem);
        ຖ້າ (v) {
            ຖ້າ (next)
                next[v >> 31] = t->elem;
            ສົ່ງຄືນ av_tree_find(t->child[(v >> 31) ^ 1], key, cmp, next);
        } ບໍ່ດັ່ງນັ້ນ {
            ຖ້າ (next) {
                av_tree_find(t->child[0], key, cmp, next);
                av_tree_find(t->child[1], key, cmp, next);
            }
            ສົ່ງຄືນ t->elem;
        }
    }
    ສົ່ງຄືນ NULL;
}

void *av_tree_insert(AVTreeNode **tp, void *key,
                     ຈຳນວນເຕັມ (*cmp)(const void *key, const void *b), AVTreeNode **next)
{
    AVTreeNode *t = *tp;
    ຖ້າ (t) {
        unsigned ຈຳນວນເຕັມ v = cmp(t->elem, key);
        void *ret;
        ຖ້າ (!v) {
            ຖ້າ (*next)
                ສົ່ງຄືນ t->elem;
            ບໍ່ດັ່ງນັ້ນ ຖ້າ (t->child[0] || t->child[1]) {
                ຈຳນວນເຕັມ i = !t->child[0];
                void *next_elem[2];
                av_tree_find(t->child[i], key, cmp, next_elem);
                key = t->elem = next_elem[i];
                v   = -i;
            } ບໍ່ດັ່ງນັ້ນ {
                *next = t;
                *tp   = NULL;
                ສົ່ງຄືນ NULL;
            }
        }
        ret = av_tree_insert(&t->child[v >> 31], key, cmp, next);
        ຖ້າ (!ret) {
            ຈຳນວນເຕັມ i              = (v >> 31) ^ !!*next;
            AVTreeNode **child = &t->child[i];
            t->state += 2 * i - 1;

            ຖ້າ (!(t->state & 1)) {
                ຖ້າ (t->state) {
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
                    ຖ້າ ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } ບໍ່ດັ່ງນັ້ນ {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        ຖ້າ ((*tp)->state)
                            t->state = 0;
                        ບໍ່ດັ່ງນັ້ນ
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            ຖ້າ (!(*tp)->state ^ !!*next)
                ສົ່ງຄືນ key;
        }
        ສົ່ງຄືນ ret;
    } ບໍ່ດັ່ງນັ້ນ {
        *tp   = *next;
        *next = NULL;
        ຖ້າ (*tp) {
            (*tp)->elem = key;
            ສົ່ງຄືນ NULL;
        } ບໍ່ດັ່ງນັ້ນ
            ສົ່ງຄືນ key;
    }
}

void av_tree_destroy(AVTreeNode *t)
{
    ຖ້າ (t) {
        av_tree_destroy(t->child[0]);
        av_tree_destroy(t->child[1]);
        av_free(t);
    }
}

void av_tree_enumerate(AVTreeNode *t, void *opaque,
                       ຈຳນວນເຕັມ (*cmp)(void *opaque, void *elem),
                       ຈຳນວນເຕັມ (*enu)(void *opaque, void *elem))
{
    ຖ້າ (t) {
        ຈຳນວນເຕັມ v = cmp ? cmp(opaque, t->elem) : 0;
        ຖ້າ (v >= 0)
            av_tree_enumerate(t->child[0], opaque, cmp, enu);
        ຖ້າ (v == 0)
            enu(opaque, t->elem);
        ຖ້າ (v <= 0)
            av_tree_enumerate(t->child[1], opaque, cmp, enu);
    }
}
