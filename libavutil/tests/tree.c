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

static цео check(AVTreeNode *t)
{
    ако (t) {
        цео left  = check(t->child[0]);
        цео right = check(t->child[1]);

        ако (left > 999 || right > 999)
            врати 1000;
        ако (right - left != t->state)
            врати 1000;
        ако (t->state > 1 || t->state < -1)
            врати 1000;
        врати FFMAX(left, right) + 1;
    }
    врати 0;
}

static void print(AVTreeNode *t, цео depth)
{
    цео i;
    за (i = 0; i < depth * 4; i++)
        av_log(NULL, AV_LOG_ERROR, " ");
    ако (t) {
        av_log(NULL, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } инако
        av_log(NULL, AV_LOG_ERROR, "NULL\n");
}

static цео cmp(const void *a, const void *b)
{
    врати (const uint8_t *) a - (const uint8_t *) b;
}

цео main(цео argc, char **argv)
{
    цео i;
    void *k;
    AVTreeNode *root = NULL, *node = NULL;
    AVLFG prng;
    цео log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    за (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        ако (check(root) > 999) {
            av_log(NULL, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(root, 0);
            врати 1;
        }
        av_log(NULL, AV_LOG_DEBUG, "inserting %4d\n", (цео)j);

        ако (!node)
            node = av_tree_node_alloc();
        ако (!node) {
            av_log(NULL, AV_LOG_ERROR, "Memory allocation failure.\n");
            врати 1;
        }
        av_tree_insert(&root, (void *)(j + 1), cmp, &node);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTreeNode *node2 = NULL;
            av_log(NULL, AV_LOG_DEBUG, "removing %4d\n", (цео)j);
            av_tree_insert(&root, (void *)(j + 1), cmp, &node2);
            k = av_tree_find(root, (void *)(j + 1), cmp, NULL);
            ако (k)
                av_log(NULL, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(node);

    av_tree_destroy(root);

    врати 0;
}
