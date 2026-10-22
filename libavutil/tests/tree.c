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

#شامل "libavutil/tree.c"

#شامل <stdint.h>

#شامل "libavutil/common.h"
#شامل "libavutil/lfg.h"
#شامل "libavutil/log.h"
#شامل "libavutil/mem.h"

ایستا صحیح check(AVTree_گره *t)
{
    اگر (t) {
        صحیح چپ  = check(t->child[0]);
        صحیح راست = check(t->child[1]);

        اگر (چپ > 999 || راست > 999)
            بازگشت 1000;
        اگر (راست - چپ != t->state)
            بازگشت 1000;
        اگر (t->state > 1 || t->state < -1)
            بازگشت 1000;
        بازگشت FFMAX(چپ, راست) + 1;
    }
    بازگشت 0;
}

ایستا تهی print(AVTree_گره *t, صحیح depth)
{
    صحیح i;
    برای (i = 0; i < depth * 4; i++)
        av_log(پوچ, AV_LOG_ERROR, " ");
    اگر (t) {
        av_log(پوچ, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } وگرنه
        av_log(پوچ, AV_LOG_ERROR, "NULL\n");
}

ایستا صحیح cmp(ثابت تهی *a, ثابت تهی *b)
{
    بازگشت (ثابت uint8_t *) a - (ثابت uint8_t *) b;
}

صحیح اصلی(صحیح argc, نویسه **argv)
{
    صحیح i;
    تهی *k;
    AVTree_گره *ریشه = پوچ, *گره = پوچ;
    AVLFG prng;
    صحیح log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    برای (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        اگر (check(ریشه) > 999) {
            av_log(پوچ, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(ریشه, 0);
            بازگشت 1;
        }
        av_log(پوچ, AV_LOG_DEBUG, "inserting %4d\n", (صحیح)j);

        اگر (!گره)
            گره = av_درخت_گره_alloc();
        اگر (!گره) {
            av_log(پوچ, AV_LOG_ERROR, "Memory allocation failure.\n");
            بازگشت 1;
        }
        av_درخت_درج(&ریشه, (تهی *)(j + 1), cmp, &گره);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_گره *node2 = پوچ;
            av_log(پوچ, AV_LOG_DEBUG, "removing %4d\n", (صحیح)j);
            av_درخت_درج(&ریشه, (تهی *)(j + 1), cmp, &node2);
            k = av_درخت_find(ریشه, (تهی *)(j + 1), cmp, پوچ);
            اگر (k)
                av_log(پوچ, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(گره);

    av_درخت_destroy(ریشه);

    بازگشت 0;
}
