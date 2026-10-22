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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/tree.c"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/lfg.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਸਥਿਰ ਪੂਰਨ check(AVTree_ਗੰਢ *t)
{
    ਜੇ (t) {
        ਪੂਰਨ ਖੱਬਾ  = check(t->ਬੱਚਾ[0]);
        ਪੂਰਨ ਸੱਜਾ = check(t->ਬੱਚਾ[1]);

        ਜੇ (ਖੱਬਾ > 999 || ਸੱਜਾ > 999)
            ਵਾਪਸ 1000;
        ਜੇ (ਸੱਜਾ - ਖੱਬਾ != t->state)
            ਵਾਪਸ 1000;
        ਜੇ (t->state > 1 || t->state < -1)
            ਵਾਪਸ 1000;
        ਵਾਪਸ FFMAX(ਖੱਬਾ, ਸੱਜਾ) + 1;
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ print(AVTree_ਗੰਢ *t, ਪੂਰਨ ਡੂੰਘਾਈ)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < ਡੂੰਘਾਈ * 4; i++)
        av_log(ਨਿਰਾ, AV_LOG_ERROR, " ");
    ਜੇ (t) {
        av_log(ਨਿਰਾ, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->ਬੱਚਾ[0], ਡੂੰਘਾਈ + 1);
        print(t->ਬੱਚਾ[1], ਡੂੰਘਾਈ + 1);
    } ਨਹੀਂਤਾਂ
        av_log(ਨਿਰਾ, AV_LOG_ERROR, "NULL\n");
}

ਸਥਿਰ ਪੂਰਨ cmp(ਅਚਲ ਖਾਲੀ *a, ਅਚਲ ਖਾਲੀ *b)
{
    ਵਾਪਸ (ਅਚਲ uint8_t *) a - (ਅਚਲ uint8_t *) b;
}

ਪੂਰਨ ਮੁੱਖ(ਪੂਰਨ argc, ਅੱਖਰ **argv)
{
    ਪੂਰਨ i;
    ਖਾਲੀ *k;
    AVTree_ਗੰਢ *ਜੜ੍ਹ = ਨਿਰਾ, *ਗੰਢ = ਨਿਰਾ;
    AVLFG prng;
    ਪੂਰਨ log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_ਸੈੱਟ_level(log_level);

    av_lfg_init(&prng, 1);

    ਲਈ (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        ਜੇ (check(ਜੜ੍ਹ) > 999) {
            av_log(ਨਿਰਾ, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(ਜੜ੍ਹ, 0);
            ਵਾਪਸ 1;
        }
        av_log(ਨਿਰਾ, AV_LOG_DEBUG, "inserting %4d\n", (ਪੂਰਨ)j);

        ਜੇ (!ਗੰਢ)
            ਗੰਢ = av_ਰੁੱਖ_ਗੰਢ_alloc();
        ਜੇ (!ਗੰਢ) {
            av_log(ਨਿਰਾ, AV_LOG_ERROR, "Memory allocation failure.\n");
            ਵਾਪਸ 1;
        }
        av_ਰੁੱਖ_ਪਾਓ(&ਜੜ੍ਹ, (ਖਾਲੀ *)(j + 1), cmp, &ਗੰਢ);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_ਗੰਢ *node2 = ਨਿਰਾ;
            av_log(ਨਿਰਾ, AV_LOG_DEBUG, "removing %4d\n", (ਪੂਰਨ)j);
            av_ਰੁੱਖ_ਪਾਓ(&ਜੜ੍ਹ, (ਖਾਲੀ *)(j + 1), cmp, &node2);
            k = av_ਰੁੱਖ_ਲੱਭੋ(ਜੜ੍ਹ, (ਖਾਲੀ *)(j + 1), cmp, ਨਿਰਾ);
            ਜੇ (k)
                av_log(ਨਿਰਾ, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(ਗੰਢ);

    av_ਰੁੱਖ_destroy(ਜੜ੍ਹ);

    ਵਾਪਸ 0;
}
