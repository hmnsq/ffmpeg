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

ساكن صحيح check(AVTree_گره *t)
{
    إذا (t) {
        صحيح چپ  = check(t->فرزند[0]);
        صحيح راست = check(t->فرزند[1]);

        إذا (چپ > 999 || راست > 999)
            أرجع 1000;
        إذا (راست - چپ != t->state)
            أرجع 1000;
        إذا (t->state > 1 || t->state < -1)
            أرجع 1000;
        أرجع FFMAX(چپ, راست) + 1;
    }
    أرجع 0;
}

ساكن فراغ print(AVTree_گره *t, صحيح عمق)
{
    صحيح i;
    لكل (i = 0; i < عمق * 4; i++)
        av_log(عدم, AV_LOG_ERROR, " ");
    إذا (t) {
        av_log(عدم, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->فرزند[0], عمق + 1);
        print(t->فرزند[1], عمق + 1);
    } وإلا
        av_log(عدم, AV_LOG_ERROR, "NULL\n");
}

ساكن صحيح cmp(ثابت فراغ *a, ثابت فراغ *b)
{
    أرجع (ثابت uint8_t *) a - (ثابت uint8_t *) b;
}

صحيح اصلی(صحيح argc, حرف **argv)
{
    صحيح i;
    فراغ *k;
    AVTree_گره *ریشه = عدم, *گره = عدم;
    AVLFG prng;
    صحيح log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_مجموعه_level(log_level);

    av_lfg_init(&prng, 1);

    لكل (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        إذا (check(ریشه) > 999) {
            av_log(عدم, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(ریشه, 0);
            أرجع 1;
        }
        av_log(عدم, AV_LOG_DEBUG, "inserting %4d\n", (صحيح)j);

        إذا (!گره)
            گره = av_درخت_گره_alloc();
        إذا (!گره) {
            av_log(عدم, AV_LOG_ERROR, "Memory allocation failure.\n");
            أرجع 1;
        }
        av_درخت_درج(&ریشه, (فراغ *)(j + 1), cmp, &گره);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_گره *node2 = عدم;
            av_log(عدم, AV_LOG_DEBUG, "removing %4d\n", (صحيح)j);
            av_درخت_درج(&ریشه, (فراغ *)(j + 1), cmp, &node2);
            k = av_درخت_پیدا_کن(ریشه, (فراغ *)(j + 1), cmp, عدم);
            إذا (k)
                av_log(عدم, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(گره);

    av_درخت_destroy(ریشه);

    أرجع 0;
}
