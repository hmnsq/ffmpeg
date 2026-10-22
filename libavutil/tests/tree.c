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

#అన్తర్భావ "libavutil/tree.c"

#అన్తర్భావ <stdint.h>

#అన్తర్భావ "libavutil/common.h"
#అన్తర్భావ "libavutil/lfg.h"
#అన్తర్భావ "libavutil/log.h"
#అన్తర్భావ "libavutil/mem.h"

స్థిర పూర్ణాంకం check(AVTree_కణుపు *t)
{
    ఒకవేళ (t) {
        పూర్ణాంకం ఎడమ  = check(t->బిడ్డ[0]);
        పూర్ణాంకం కుడి = check(t->బిడ్డ[1]);

        ఒకవేళ (ఎడమ > 999 || కుడి > 999)
            తిరిగి 1000;
        ఒకవేళ (కుడి - ఎడమ != t->state)
            తిరిగి 1000;
        ఒకవేళ (t->state > 1 || t->state < -1)
            తిరిగి 1000;
        తిరిగి FFMAX(ఎడమ, కుడి) + 1;
    }
    తిరిగి 0;
}

స్థిర శూన్య print(AVTree_కణుపు *t, పూర్ణాంకం లోతు)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < లోతు * 4; i++)
        av_log(ఖాళీ, AV_LOG_ERROR, " ");
    ఒకవేళ (t) {
        av_log(ఖాళీ, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->బిడ్డ[0], లోతు + 1);
        print(t->బిడ్డ[1], లోతు + 1);
    } లేకపోతే
        av_log(ఖాళీ, AV_LOG_ERROR, "NULL\n");
}

స్థిర పూర్ణాంకం cmp(స్థిరరాశి శూన్య *a, స్థిరరాశి శూన్య *b)
{
    తిరిగి (స్థిరరాశి uint8_t *) a - (స్థిరరాశి uint8_t *) b;
}

పూర్ణాంకం ప్రధాన(పూర్ణాంకం argc, అక్షరం **argv)
{
    పూర్ణాంకం i;
    శూన్య *k;
    AVTree_కణుపు *మూలం = ఖాళీ, *కణుపు = ఖాళీ;
    AVLFG prng;
    పూర్ణాంకం log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_సమితి_level(log_level);

    av_lfg_init(&prng, 1);

    కొరకు (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        ఒకవేళ (check(మూలం) > 999) {
            av_log(ఖాళీ, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(మూలం, 0);
            తిరిగి 1;
        }
        av_log(ఖాళీ, AV_LOG_DEBUG, "inserting %4d\n", (పూర్ణాంకం)j);

        ఒకవేళ (!కణుపు)
            కణుపు = av_వృక్షం_కణుపు_alloc();
        ఒకవేళ (!కణుపు) {
            av_log(ఖాళీ, AV_LOG_ERROR, "Memory allocation failure.\n");
            తిరిగి 1;
        }
        av_వృక్షం_చొప్పించు(&మూలం, (శూన్య *)(j + 1), cmp, &కణుపు);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_కణుపు *node2 = ఖాళీ;
            av_log(ఖాళీ, AV_LOG_DEBUG, "removing %4d\n", (పూర్ణాంకం)j);
            av_వృక్షం_చొప్పించు(&మూలం, (శూన్య *)(j + 1), cmp, &node2);
            k = av_వృక్షం_కనుగొను(మూలం, (శూన్య *)(j + 1), cmp, ఖాళీ);
            ఒకవేళ (k)
                av_log(ఖాళీ, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(కణుపు);

    av_వృక్షం_destroy(మూలం);

    తిరిగి 0;
}
