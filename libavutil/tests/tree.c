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

#அந்தர்பாவ "libavutil/tree.c"

#அந்தர்பாவ <stdint.h>

#அந்தர்பாவ "libavutil/common.h"
#அந்தர்பாவ "libavutil/lfg.h"
#அந்தர்பாவ "libavutil/log.h"
#அந்தர்பாவ "libavutil/mem.h"

நிலையான முழு check(AVTree_முனை *t)
{
    எனில் (t) {
        முழு இடது  = check(t->child[0]);
        முழு வலது = check(t->child[1]);

        எனில் (இடது > 999 || வலது > 999)
            திரும்பு 1000;
        எனில் (வலது - இடது != t->state)
            திரும்பு 1000;
        எனில் (t->state > 1 || t->state < -1)
            திரும்பு 1000;
        திரும்பு FFMAX(இடது, வலது) + 1;
    }
    திரும்பு 0;
}

நிலையான வெறுமை print(AVTree_முனை *t, முழு depth)
{
    முழு i;
    க்கு (i = 0; i < depth * 4; i++)
        av_log(வெற்று, AV_LOG_ERROR, " ");
    எனில் (t) {
        av_log(வெற்று, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } இல்லையெனில்
        av_log(வெற்று, AV_LOG_ERROR, "NULL\n");
}

நிலையான முழு cmp(மாறிலி வெறுமை *a, மாறிலி வெறுமை *b)
{
    திரும்பு (மாறிலி uint8_t *) a - (மாறிலி uint8_t *) b;
}

முழு முதன்மை(முழு argc, எழுத்து **argv)
{
    முழு i;
    வெறுமை *k;
    AVTree_முனை *வேர் = வெற்று, *முனை = வெற்று;
    AVLFG prng;
    முழு log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    க்கு (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        எனில் (check(வேர்) > 999) {
            av_log(வெற்று, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(வேர், 0);
            திரும்பு 1;
        }
        av_log(வெற்று, AV_LOG_DEBUG, "inserting %4d\n", (முழு)j);

        எனில் (!முனை)
            முனை = av_மரம்_முனை_alloc();
        எனில் (!முனை) {
            av_log(வெற்று, AV_LOG_ERROR, "Memory allocation failure.\n");
            திரும்பு 1;
        }
        av_மரம்_செருகு(&வேர், (வெறுமை *)(j + 1), cmp, &முனை);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_முனை *node2 = வெற்று;
            av_log(வெற்று, AV_LOG_DEBUG, "removing %4d\n", (முழு)j);
            av_மரம்_செருகு(&வேர், (வெறுமை *)(j + 1), cmp, &node2);
            k = av_மரம்_find(வேர், (வெறுமை *)(j + 1), cmp, வெற்று);
            எனில் (k)
                av_log(வெற்று, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(முனை);

    av_மரம்_destroy(வேர்);

    திரும்பு 0;
}
