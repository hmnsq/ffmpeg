/*
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

#include "libavutil/tree.c"

#include <stdint.h>

#include "libavutil/common.h"
#include "libavutil/lfg.h"
#include "libavutil/log.h"
#include "libavutil/mem.h"

static ціле check(AVTreeNode *t)
{
    якщо (t) {
        ціле left  = check(t->child[0]);
        ціле right = check(t->child[1]);

        якщо (left > 999 || right > 999)
            повернути 1000;
        якщо (right - left != t->state)
            повернути 1000;
        якщо (t->state > 1 || t->state < -1)
            повернути 1000;
        повернути FFMAX(left, right) + 1;
    }
    повернути 0;
}

static void print(AVTreeNode *t, ціле depth)
{
    ціле i;
    для (i = 0; i < depth * 4; i++)
        av_log(NULL, AV_LOG_ERROR, " ");
    якщо (t) {
        av_log(NULL, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } інакше
        av_log(NULL, AV_LOG_ERROR, "NULL\n");
}

static ціле cmp(const void *a, const void *b)
{
    повернути (const uint8_t *) a - (const uint8_t *) b;
}

ціле main(ціле argc, char **argv)
{
    ціле i;
    void *k;
    AVTreeNode *root = NULL, *node = NULL;
    AVLFG prng;
    ціле log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    для (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        якщо (check(root) > 999) {
            av_log(NULL, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(root, 0);
            повернути 1;
        }
        av_log(NULL, AV_LOG_DEBUG, "inserting %4d\n", (ціле)j);

        якщо (!node)
            node = av_tree_node_alloc();
        якщо (!node) {
            av_log(NULL, AV_LOG_ERROR, "Memory allocation failure.\n");
            повернути 1;
        }
        av_tree_insert(&root, (void *)(j + 1), cmp, &node);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTreeNode *node2 = NULL;
            av_log(NULL, AV_LOG_DEBUG, "removing %4d\n", (ціле)j);
            av_tree_insert(&root, (void *)(j + 1), cmp, &node2);
            k = av_tree_find(root, (void *)(j + 1), cmp, NULL);
            якщо (k)
                av_log(NULL, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(node);

    av_tree_destroy(root);

    повернути 0;
}
