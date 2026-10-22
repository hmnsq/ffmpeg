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
    ཧྲིལ state;
} AVTreeNode;

const ཧྲིལ av_tree_node_size = parimaa_na(AVTreeNode);

sa_nracanaa AVTreeNode *av_tree_node_alloc(void)
{
    ལོག av_mallocz(parimaa_na(sa_nracanaa AVTreeNode));
}

void *av_tree_find(const AVTreeNode *t, void *key,
                   ཧྲིལ (*cmp)(const void *key, const void *b), void *next[2])
{
    གལ་སྲིད (t) {
        unsigned ཧྲིལ v = cmp(key, t->elem);
        གལ་སྲིད (v) {
            གལ་སྲིད (next)
                next[v >> 31] = t->elem;
            ལོག av_tree_find(t->child[(v >> 31) ^ 1], key, cmp, next);
        } དེ་མིན {
            གལ་སྲིད (next) {
                av_tree_find(t->child[0], key, cmp, next);
                av_tree_find(t->child[1], key, cmp, next);
            }
            ལོག t->elem;
        }
    }
    ལོག NULL;
}

void *av_tree_insert(AVTreeNode **tp, void *key,
                     ཧྲིལ (*cmp)(const void *key, const void *b), AVTreeNode **next)
{
    AVTreeNode *t = *tp;
    གལ་སྲིད (t) {
        unsigned ཧྲིལ v = cmp(t->elem, key);
        void *ret;
        གལ་སྲིད (!v) {
            གལ་སྲིད (*next)
                ལོག t->elem;
            དེ་མིན གལ་སྲིད (t->child[0] || t->child[1]) {
                ཧྲིལ i = !t->child[0];
                void *next_elem[2];
                av_tree_find(t->child[i], key, cmp, next_elem);
                key = t->elem = next_elem[i];
                v   = -i;
            } དེ་མིན {
                *next = t;
                *tp   = NULL;
                ལོག NULL;
            }
        }
        ret = av_tree_insert(&t->child[v >> 31], key, cmp, next);
        གལ་སྲིད (!ret) {
            ཧྲིལ i              = (v >> 31) ^ !!*next;
            AVTreeNode **child = &t->child[i];
            t->state += 2 * i - 1;

            གལ་སྲིད (!(t->state & 1)) {
                གལ་སྲིད (t->state) {
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
                    གལ་སྲིད ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } དེ་མིན {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        གལ་སྲིད ((*tp)->state)
                            t->state = 0;
                        དེ་མིན
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            གལ་སྲིད (!(*tp)->state ^ !!*next)
                ལོག key;
        }
        ལོག ret;
    } དེ་མིན {
        *tp   = *next;
        *next = NULL;
        གལ་སྲིད (*tp) {
            (*tp)->elem = key;
            ལོག NULL;
        } དེ་མིན
            ལོག key;
    }
}

void av_tree_destroy(AVTreeNode *t)
{
    གལ་སྲིད (t) {
        av_tree_destroy(t->child[0]);
        av_tree_destroy(t->child[1]);
        av_free(t);
    }
}

void av_tree_enumerate(AVTreeNode *t, void *opaque,
                       ཧྲིལ (*cmp)(void *opaque, void *elem),
                       ཧྲིལ (*enu)(void *opaque, void *elem))
{
    གལ་སྲིད (t) {
        ཧྲིལ v = cmp ? cmp(opaque, t->elem) : 0;
        གལ་སྲིད (v >= 0)
            av_tree_enumerate(t->child[0], opaque, cmp, enu);
        གལ་སྲིད (v == 0)
            enu(opaque, t->elem);
        གལ་སྲིད (v <= 0)
            av_tree_enumerate(t->child[1], opaque, cmp, enu);
    }
}
