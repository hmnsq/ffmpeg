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

ساكن صحيح check(AVTree_ڳنڍ *t)
{
    إذا (t) {
        صحيح کاٻو  = check(t->ٻار[0]);
        صحيح ساڄو = check(t->ٻار[1]);

        إذا (کاٻو > 999 || ساڄو > 999)
            أرجع 1000;
        إذا (ساڄو - کاٻو != t->state)
            أرجع 1000;
        إذا (t->state > 1 || t->state < -1)
            أرجع 1000;
        أرجع FFMAX(کاٻو, ساڄو) + 1;
    }
    أرجع 0;
}

ساكن فراغ print(AVTree_ڳنڍ *t, صحيح اونهائي)
{
    صحيح i;
    لكل (i = 0; i < اونهائي * 4; i++)
        av_log(عدم, AV_LOG_ERROR, " ");
    إذا (t) {
        av_log(عدم, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->ٻار[0], اونهائي + 1);
        print(t->ٻار[1], اونهائي + 1);
    } وإلا
        av_log(عدم, AV_LOG_ERROR, "NULL\n");
}

ساكن صحيح cmp(ثابت فراغ *a, ثابت فراغ *b)
{
    أرجع (ثابت uint8_t *) a - (ثابت uint8_t *) b;
}

صحيح مکيه(صحيح argc, حرف **argv)
{
    صحيح i;
    فراغ *k;
    AVTree_ڳنڍ *پاڙ = عدم, *ڳنڍ = عدم;
    AVLFG prng;
    صحيح log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_سيٽ_level(log_level);

    av_lfg_init(&prng, 1);

    لكل (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        إذا (check(پاڙ) > 999) {
            av_log(عدم, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(پاڙ, 0);
            أرجع 1;
        }
        av_log(عدم, AV_LOG_DEBUG, "inserting %4d\n", (صحيح)j);

        إذا (!ڳنڍ)
            ڳنڍ = av_وڻ_ڳنڍ_alloc();
        إذا (!ڳنڍ) {
            av_log(عدم, AV_LOG_ERROR, "Memory allocation failure.\n");
            أرجع 1;
        }
        av_وڻ_وجهو(&پاڙ, (فراغ *)(j + 1), cmp, &ڳنڍ);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_ڳنڍ *node2 = عدم;
            av_log(عدم, AV_LOG_DEBUG, "removing %4d\n", (صحيح)j);
            av_وڻ_وجهو(&پاڙ, (فراغ *)(j + 1), cmp, &node2);
            k = av_وڻ_ڳوليو(پاڙ, (فراغ *)(j + 1), cmp, عدم);
            إذا (k)
                av_log(عدم, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(ڳنڍ);

    av_وڻ_destroy(پاڙ);

    أرجع 0;
}
