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

static ཧྲིལ check(AVTreeNode *t)
{
    གལ་ཏེ (t) {
        ཧྲིལ left  = check(t->child[0]);
        ཧྲིལ right = check(t->child[1]);

        གལ་ཏེ (left > 999 || right > 999)
            ཕྱིར 1000;
        གལ་ཏེ (right - left != t->state)
            ཕྱིར 1000;
        གལ་ཏེ (t->state > 1 || t->state < -1)
            ཕྱིར 1000;
        ཕྱིར FFMAX(left, right) + 1;
    }
    ཕྱིར 0;
}

static void print(AVTreeNode *t, ཧྲིལ depth)
{
    ཧྲིལ i;
    ཆེད་དུ (i = 0; i < depth * 4; i++)
        av_log(NULL, AV_LOG_ERROR, " ");
    གལ་ཏེ (t) {
        av_log(NULL, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } དེ་མིན
        av_log(NULL, AV_LOG_ERROR, "NULL\n");
}

static ཧྲིལ cmp(const void *a, const void *b)
{
    ཕྱིར (const uint8_t *) a - (const uint8_t *) b;
}

ཧྲིལ གཙོ(ཧྲིལ argc, var_na **argv)
{
    ཧྲིལ i;
    void *k;
    AVTreeNode *root = NULL, *node = NULL;
    AVLFG prng;
    ཧྲིལ log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    ཆེད་དུ (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        གལ་ཏེ (check(root) > 999) {
            av_log(NULL, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(root, 0);
            ཕྱིར 1;
        }
        av_log(NULL, AV_LOG_DEBUG, "inserting %4d\n", (ཧྲིལ)j);

        གལ་ཏེ (!node)
            node = av_tree_node_alloc();
        གལ་ཏེ (!node) {
            av_log(NULL, AV_LOG_ERROR, "Memory allocation failure.\n");
            ཕྱིར 1;
        }
        av_tree_insert(&root, (void *)(j + 1), cmp, &node);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTreeNode *node2 = NULL;
            av_log(NULL, AV_LOG_DEBUG, "removing %4d\n", (ཧྲིལ)j);
            av_tree_insert(&root, (void *)(j + 1), cmp, &node2);
            k = av_tree_find(root, (void *)(j + 1), cmp, NULL);
            གལ་ཏེ (k)
                av_log(NULL, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(node);

    av_tree_destroy(root);

    ཕྱིར 0;
}
