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

ساكن صحيح check(AVTree_عقدة *t)
{
    إذا (t) {
        صحيح يسار  = check(t->child[0]);
        صحيح يمين = check(t->child[1]);

        إذا (يسار > 999 || يمين > 999)
            إرجاع 1000;
        إذا (يمين - يسار != t->state)
            إرجاع 1000;
        إذا (t->state > 1 || t->state < -1)
            إرجاع 1000;
        إرجاع FFMAX(يسار, يمين) + 1;
    }
    إرجاع 0;
}

ساكن فراغ print(AVTree_عقدة *t, صحيح depth)
{
    صحيح i;
    لكل (i = 0; i < depth * 4; i++)
        av_log(عدم, AV_LOG_ERROR, " ");
    إذا (t) {
        av_log(عدم, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } وإلا
        av_log(عدم, AV_LOG_ERROR, "NULL\n");
}

ساكن صحيح cmp(ثابت فراغ *a, ثابت فراغ *b)
{
    إرجاع (ثابت uint8_t *) a - (ثابت uint8_t *) b;
}

صحيح الرئيسية(صحيح argc, حرف **argv)
{
    صحيح i;
    فراغ *k;
    AVTree_عقدة *جذر = عدم, *عقدة = عدم;
    AVLFG prng;
    صحيح log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    لكل (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        إذا (check(جذر) > 999) {
            av_log(عدم, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(جذر, 0);
            إرجاع 1;
        }
        av_log(عدم, AV_LOG_DEBUG, "inserting %4d\n", (صحيح)j);

        إذا (!عقدة)
            عقدة = av_شجرة_عقدة_alloc();
        إذا (!عقدة) {
            av_log(عدم, AV_LOG_ERROR, "Memory allocation failure.\n");
            إرجاع 1;
        }
        av_شجرة_أدرج(&جذر, (فراغ *)(j + 1), cmp, &عقدة);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_عقدة *node2 = عدم;
            av_log(عدم, AV_LOG_DEBUG, "removing %4d\n", (صحيح)j);
            av_شجرة_أدرج(&جذر, (فراغ *)(j + 1), cmp, &node2);
            k = av_شجرة_find(جذر, (فراغ *)(j + 1), cmp, عدم);
            إذا (k)
                av_log(عدم, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(عقدة);

    av_شجرة_destroy(جذر);

    إرجاع 0;
}
