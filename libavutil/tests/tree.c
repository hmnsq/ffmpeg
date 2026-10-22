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

ساكن صحيح check(AVTree_غوټه *t)
{
    إذا (t) {
        صحيح کیڼ  = check(t->ماشوم[0]);
        صحيح ښی = check(t->ماشوم[1]);

        إذا (کیڼ > 999 || ښی > 999)
            أرجع 1000;
        إذا (ښی - کیڼ != t->state)
            أرجع 1000;
        إذا (t->state > 1 || t->state < -1)
            أرجع 1000;
        أرجع FFMAX(کیڼ, ښی) + 1;
    }
    أرجع 0;
}

ساكن فراغ print(AVTree_غوټه *t, صحيح ژوروالی)
{
    صحيح i;
    لكل (i = 0; i < ژوروالی * 4; i++)
        av_log(عدم, AV_LOG_ERROR, " ");
    إذا (t) {
        av_log(عدم, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->ماشوم[0], ژوروالی + 1);
        print(t->ماشوم[1], ژوروالی + 1);
    } وإلا
        av_log(عدم, AV_LOG_ERROR, "NULL\n");
}

ساكن صحيح cmp(ثابت فراغ *a, ثابت فراغ *b)
{
    أرجع (ثابت uint8_t *) a - (ثابت uint8_t *) b;
}

صحيح اصلي(صحيح argc, حرف **argv)
{
    صحيح i;
    فراغ *k;
    AVTree_غوټه *ریښه = عدم, *غوټه = عدم;
    AVLFG prng;
    صحيح log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_سېټ_level(log_level);

    av_lfg_init(&prng, 1);

    لكل (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        إذا (check(ریښه) > 999) {
            av_log(عدم, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(ریښه, 0);
            أرجع 1;
        }
        av_log(عدم, AV_LOG_DEBUG, "inserting %4d\n", (صحيح)j);

        إذا (!غوټه)
            غوټه = av_ونه_غوټه_alloc();
        إذا (!غوټه) {
            av_log(عدم, AV_LOG_ERROR, "Memory allocation failure.\n");
            أرجع 1;
        }
        av_ونه_ورننباسه(&ریښه, (فراغ *)(j + 1), cmp, &غوټه);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_غوټه *node2 = عدم;
            av_log(عدم, AV_LOG_DEBUG, "removing %4d\n", (صحيح)j);
            av_ونه_ورننباسه(&ریښه, (فراغ *)(j + 1), cmp, &node2);
            k = av_ونه_پیدا_کړه(ریښه, (فراغ *)(j + 1), cmp, عدم);
            إذا (k)
                av_log(عدم, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(غوټه);

    av_ونه_destroy(ریښه);

    أرجع 0;
}
