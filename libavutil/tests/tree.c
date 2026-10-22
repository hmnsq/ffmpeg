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

#ضمن "libavutil/tree.c"

#ضمن <stdint.h>

#ضمن "libavutil/common.h"
#ضمن "libavutil/lfg.h"
#ضمن "libavutil/log.h"
#ضمن "libavutil/mem.h"

ساكن صحيح check(AVTreeNode *t)
{
    אם (t) {
        صحيح left  = check(t->child[0]);
        صحيح right = check(t->child[1]);

        אם (left > 999 || right > 999)
            החזר 1000;
        אם (right - left != t->state)
            החזר 1000;
        אם (t->state > 1 || t->state < -1)
            החזר 1000;
        החזר FFMAX(left, right) + 1;
    }
    החזר 0;
}

ساكن فراغ print(AVTreeNode *t, صحيح depth)
{
    صحيح i;
    עבור (i = 0; i < depth * 4; i++)
        av_log(عدم, AV_LOG_ERROR, " ");
    אם (t) {
        av_log(عدم, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } אחרת
        av_log(عدم, AV_LOG_ERROR, "NULL\n");
}

ساكن صحيح cmp(ثابت فراغ *a, ثابت فراغ *b)
{
    החזר (ثابت uint8_t *) a - (ثابت uint8_t *) b;
}

صحيح main(صحيح argc, حرف **argv)
{
    صحيح i;
    فراغ *k;
    AVTreeNode *root = عدم, *node = عدم;
    AVLFG prng;
    صحيح log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    עבור (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        אם (check(root) > 999) {
            av_log(عدم, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(root, 0);
            החזר 1;
        }
        av_log(عدم, AV_LOG_DEBUG, "inserting %4d\n", (صحيح)j);

        אם (!node)
            node = av_tree_node_alloc();
        אם (!node) {
            av_log(عدم, AV_LOG_ERROR, "Memory allocation failure.\n");
            החזר 1;
        }
        av_tree_insert(&root, (فراغ *)(j + 1), cmp, &node);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTreeNode *node2 = عدم;
            av_log(عدم, AV_LOG_DEBUG, "removing %4d\n", (صحيح)j);
            av_tree_insert(&root, (فراغ *)(j + 1), cmp, &node2);
            k = av_tree_find(root, (فراغ *)(j + 1), cmp, عدم);
            אם (k)
                av_log(عدم, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(node);

    av_tree_destroy(root);

    החזר 0;
}
