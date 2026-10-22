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

ساکن صحیح check(AVTree_گرہ *t)
{
    اگر (t) {
        صحیح بایاں  = check(t->بچہ[0]);
        صحیح دایاں = check(t->بچہ[1]);

        اگر (بایاں > 999 || دایاں > 999)
            واپس 1000;
        اگر (دایاں - بایاں != t->state)
            واپس 1000;
        اگر (t->state > 1 || t->state < -1)
            واپس 1000;
        واپس FFMAX(بایاں, دایاں) + 1;
    }
    واپس 0;
}

ساکن خالی print(AVTree_گرہ *t, صحیح گہرائی)
{
    صحیح i;
    برائے (i = 0; i < گہرائی * 4; i++)
        av_log(تہی, AV_LOG_ERROR, " ");
    اگر (t) {
        av_log(تہی, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->بچہ[0], گہرائی + 1);
        print(t->بچہ[1], گہرائی + 1);
    } ورنہ
        av_log(تہی, AV_LOG_ERROR, "NULL\n");
}

ساکن صحیح cmp(ثابت خالی *a, ثابت خالی *b)
{
    واپس (ثابت uint8_t *) a - (ثابت uint8_t *) b;
}

صحیح مین(صحیح argc, حرف **argv)
{
    صحیح i;
    خالی *k;
    AVTree_گرہ *جڑ = تہی, *گرہ = تہی;
    AVLFG prng;
    صحیح log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_سیٹ_level(log_level);

    av_lfg_init(&prng, 1);

    برائے (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        اگر (check(جڑ) > 999) {
            av_log(تہی, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(جڑ, 0);
            واپس 1;
        }
        av_log(تہی, AV_LOG_DEBUG, "inserting %4d\n", (صحیح)j);

        اگر (!گرہ)
            گرہ = av_درخت_گرہ_alloc();
        اگر (!گرہ) {
            av_log(تہی, AV_LOG_ERROR, "Memory allocation failure.\n");
            واپس 1;
        }
        av_درخت_داخل_کرو(&جڑ, (خالی *)(j + 1), cmp, &گرہ);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_گرہ *node2 = تہی;
            av_log(تہی, AV_LOG_DEBUG, "removing %4d\n", (صحیح)j);
            av_درخت_داخل_کرو(&جڑ, (خالی *)(j + 1), cmp, &node2);
            k = av_درخت_ڈھونڈو(جڑ, (خالی *)(j + 1), cmp, تہی);
            اگر (k)
                av_log(تہی, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(گرہ);

    av_درخت_destroy(جڑ);

    واپس 0;
}
