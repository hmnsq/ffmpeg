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

static ចំនួនគត់ check(AVTreeNode *t)
{
    ប្រសិនបើ (t) {
        ចំនួនគត់ left  = check(t->child[0]);
        ចំនួនគត់ right = check(t->child[1]);

        ប្រសិនបើ (left > 999 || right > 999)
            ត្រឡប់ 1000;
        ប្រសិនបើ (right - left != t->state)
            ត្រឡប់ 1000;
        ប្រសិនបើ (t->state > 1 || t->state < -1)
            ត្រឡប់ 1000;
        ត្រឡប់ FFMAX(left, right) + 1;
    }
    ត្រឡប់ 0;
}

static void print(AVTreeNode *t, ចំនួនគត់ depth)
{
    ចំនួនគត់ i;
    សម្រាប់ (i = 0; i < depth * 4; i++)
        av_log(NULL, AV_LOG_ERROR, " ");
    ប្រសិនបើ (t) {
        av_log(NULL, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } បើមិនដូច្នេះ
        av_log(NULL, AV_LOG_ERROR, "NULL\n");
}

static ចំនួនគត់ cmp(const void *a, const void *b)
{
    ត្រឡប់ (const uint8_t *) a - (const uint8_t *) b;
}

ចំនួនគត់ main(ចំនួនគត់ argc, var_na **argv)
{
    ចំនួនគត់ i;
    void *k;
    AVTreeNode *root = NULL, *node = NULL;
    AVLFG prng;
    ចំនួនគត់ log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    សម្រាប់ (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        ប្រសិនបើ (check(root) > 999) {
            av_log(NULL, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(root, 0);
            ត្រឡប់ 1;
        }
        av_log(NULL, AV_LOG_DEBUG, "inserting %4d\n", (ចំនួនគត់)j);

        ប្រសិនបើ (!node)
            node = av_tree_node_alloc();
        ប្រសិនបើ (!node) {
            av_log(NULL, AV_LOG_ERROR, "Memory allocation failure.\n");
            ត្រឡប់ 1;
        }
        av_tree_insert(&root, (void *)(j + 1), cmp, &node);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTreeNode *node2 = NULL;
            av_log(NULL, AV_LOG_DEBUG, "removing %4d\n", (ចំនួនគត់)j);
            av_tree_insert(&root, (void *)(j + 1), cmp, &node2);
            k = av_tree_find(root, (void *)(j + 1), cmp, NULL);
            ប្រសិនបើ (k)
                av_log(NULL, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(node);

    av_tree_destroy(root);

    ត្រឡប់ 0;
}
