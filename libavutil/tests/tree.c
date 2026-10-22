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

static ကိန်းပြည့် check(AVTreeNode *t)
{
    အကယ်၍ (t) {
        ကိန်းပြည့် left  = check(t->child[0]);
        ကိန်းပြည့် right = check(t->child[1]);

        အကယ်၍ (left > 999 || right > 999)
            ပြန်ပေး 1000;
        အကယ်၍ (right - left != t->state)
            ပြန်ပေး 1000;
        အကယ်၍ (t->state > 1 || t->state < -1)
            ပြန်ပေး 1000;
        ပြန်ပေး FFMAX(left, right) + 1;
    }
    ပြန်ပေး 0;
}

static void print(AVTreeNode *t, ကိန်းပြည့် depth)
{
    ကိန်းပြည့် i;
    အတွက် (i = 0; i < depth * 4; i++)
        av_log(NULL, AV_LOG_ERROR, " ");
    အကယ်၍ (t) {
        av_log(NULL, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } မဟုတ်ပါက
        av_log(NULL, AV_LOG_ERROR, "NULL\n");
}

static ကိန်းပြည့် cmp(const void *a, const void *b)
{
    ပြန်ပေး (const uint8_t *) a - (const uint8_t *) b;
}

ကိန်းပြည့် main(ကိန်းပြည့် argc, var_na **argv)
{
    ကိန်းပြည့် i;
    void *k;
    AVTreeNode *root = NULL, *node = NULL;
    AVLFG prng;
    ကိန်းပြည့် log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    အတွက် (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        အကယ်၍ (check(root) > 999) {
            av_log(NULL, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(root, 0);
            ပြန်ပေး 1;
        }
        av_log(NULL, AV_LOG_DEBUG, "inserting %4d\n", (ကိန်းပြည့်)j);

        အကယ်၍ (!node)
            node = av_tree_node_alloc();
        အကယ်၍ (!node) {
            av_log(NULL, AV_LOG_ERROR, "Memory allocation failure.\n");
            ပြန်ပေး 1;
        }
        av_tree_insert(&root, (void *)(j + 1), cmp, &node);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTreeNode *node2 = NULL;
            av_log(NULL, AV_LOG_DEBUG, "removing %4d\n", (ကိန်းပြည့်)j);
            av_tree_insert(&root, (void *)(j + 1), cmp, &node2);
            k = av_tree_find(root, (void *)(j + 1), cmp, NULL);
            အကယ်၍ (k)
                av_log(NULL, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(node);

    av_tree_destroy(root);

    ပြန်ပေး 0;
}
