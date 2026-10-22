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

static ຈຳນວນເຕັມ check(AVTreeNode *t)
{
    ຖ້າ (t) {
        ຈຳນວນເຕັມ left  = check(t->child[0]);
        ຈຳນວນເຕັມ right = check(t->child[1]);

        ຖ້າ (left > 999 || right > 999)
            ສົ່ງຄືນ 1000;
        ຖ້າ (right - left != t->state)
            ສົ່ງຄືນ 1000;
        ຖ້າ (t->state > 1 || t->state < -1)
            ສົ່ງຄືນ 1000;
        ສົ່ງຄືນ FFMAX(left, right) + 1;
    }
    ສົ່ງຄືນ 0;
}

static void print(AVTreeNode *t, ຈຳນວນເຕັມ depth)
{
    ຈຳນວນເຕັມ i;
    ສຳລັບ (i = 0; i < depth * 4; i++)
        av_log(NULL, AV_LOG_ERROR, " ");
    ຖ້າ (t) {
        av_log(NULL, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } ບໍ່ດັ່ງນັ້ນ
        av_log(NULL, AV_LOG_ERROR, "NULL\n");
}

static ຈຳນວນເຕັມ cmp(const void *a, const void *b)
{
    ສົ່ງຄືນ (const uint8_t *) a - (const uint8_t *) b;
}

ຈຳນວນເຕັມ main(ຈຳນວນເຕັມ argc, var_na **argv)
{
    ຈຳນວນເຕັມ i;
    void *k;
    AVTreeNode *root = NULL, *node = NULL;
    AVLFG prng;
    ຈຳນວນເຕັມ log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    ສຳລັບ (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        ຖ້າ (check(root) > 999) {
            av_log(NULL, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(root, 0);
            ສົ່ງຄືນ 1;
        }
        av_log(NULL, AV_LOG_DEBUG, "inserting %4d\n", (ຈຳນວນເຕັມ)j);

        ຖ້າ (!node)
            node = av_tree_node_alloc();
        ຖ້າ (!node) {
            av_log(NULL, AV_LOG_ERROR, "Memory allocation failure.\n");
            ສົ່ງຄືນ 1;
        }
        av_tree_insert(&root, (void *)(j + 1), cmp, &node);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTreeNode *node2 = NULL;
            av_log(NULL, AV_LOG_DEBUG, "removing %4d\n", (ຈຳນວນເຕັມ)j);
            av_tree_insert(&root, (void *)(j + 1), cmp, &node2);
            k = av_tree_find(root, (void *)(j + 1), cmp, NULL);
            ຖ້າ (k)
                av_log(NULL, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(node);

    av_tree_destroy(root);

    ສົ່ງຄືນ 0;
}
