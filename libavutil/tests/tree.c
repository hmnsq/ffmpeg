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

#include "libavutil/tree.c"

#include <stdint.h>

#include "libavutil/common.h"
#include "libavutil/lfg.h"
#include "libavutil/log.h"
#include "libavutil/mem.h"

static int check(AVTree_बुहोल *t)
{
    if (t) {
        int कालिवा  = check(t->child[0]);
        int कानान = check(t->child[1]);

        if (कालिवा > 999 || कानान > 999)
            return 1000;
        if (कानान - कालिवा != t->state)
            return 1000;
        if (t->state > 1 || t->state < -1)
            return 1000;
        return FFMAX(कालिवा, कानान) + 1;
    }
    return 0;
}

static void इलिम्बाग(AVTree_बुहोल *t, int depth)
{
    int i;
    for (i = 0; i < depth * 4; i++)
        av_log(NULL, AV_LOG_ERROR, " ");
    if (t) {
        av_log(NULL, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        इलिम्बाग(t->child[0], depth + 1);
        इलिम्बाग(t->child[1], depth + 1);
    } else
        av_log(NULL, AV_LOG_ERROR, "NULL\n");
}

static int cmp(const void *a, const void *b)
{
    return (const uint8_t *) a - (const uint8_t *) b;
}

int main(int argc, char **argv)
{
    int i;
    void *k;
    AVTree_बुहोल *उगात = NULL, *बुहोल = NULL;
    AVLFG prng;
    int log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    for (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        if (check(उगात) > 999) {
            av_log(NULL, AV_LOG_ERROR, "FATAL error %d\n", i);
            इलिम्बाग(उगात, 0);
            return 1;
        }
        av_log(NULL, AV_LOG_DEBUG, "inserting %4d\n", (int)j);

        if (!बुहोल)
            बुहोल = av_पुनो_बुहोल_alloc();
        if (!बुहोल) {
            av_log(NULL, AV_LOG_ERROR, "Memory allocation failure.\n");
            return 1;
        }
        av_पुनो_इसिंगित(&उगात, (void *)(j + 1), cmp, &बुहोल);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_बुहोल *node2 = NULL;
            av_log(NULL, AV_LOG_DEBUG, "removing %4d\n", (int)j);
            av_पुनो_इसिंगित(&उगात, (void *)(j + 1), cmp, &node2);
            k = av_पुनो_find(उगात, (void *)(j + 1), cmp, NULL);
            if (k)
                av_log(NULL, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(बुहोल);

    av_पुनो_destroy(उगात);

    return 0;
}
