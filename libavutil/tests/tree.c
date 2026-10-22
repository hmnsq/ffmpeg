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

#अन्तर्भाव "libavutil/tree.c"

#अन्तर्भाव <stdint.h>

#अन्तर्भाव "libavutil/common.h"
#अन्तर्भाव "libavutil/lfg.h"
#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "libavutil/mem.h"

स्थिर पूर्णांक check(AVTree_गाठ *t)
{
    जर (t) {
        पूर्णांक डावा  = check(t->child[0]);
        पूर्णांक उजवा = check(t->child[1]);

        जर (डावा > 999 || उजवा > 999)
            परत 1000;
        जर (उजवा - डावा != t->state)
            परत 1000;
        जर (t->state > 1 || t->state < -1)
            परत 1000;
        परत FFMAX(डावा, उजवा) + 1;
    }
    परत 0;
}

स्थिर शून्य print(AVTree_गाठ *t, पूर्णांक depth)
{
    पूर्णांक i;
    साठी (i = 0; i < depth * 4; i++)
        av_log(रिक्त, AV_LOG_ERROR, " ");
    जर (t) {
        av_log(रिक्त, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } अन्यथा
        av_log(रिक्त, AV_LOG_ERROR, "NULL\n");
}

स्थिर पूर्णांक cmp(स्थिरांक शून्य *a, स्थिरांक शून्य *b)
{
    परत (स्थिरांक uint8_t *) a - (स्थिरांक uint8_t *) b;
}

पूर्णांक main(पूर्णांक argc, अक्षर **argv)
{
    पूर्णांक i;
    शून्य *k;
    AVTree_गाठ *मूळ = रिक्त, *गाठ = रिक्त;
    AVLFG prng;
    पूर्णांक log_level = argc <= 1 ? AV_LOG_INFO : म_से_प(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    साठी (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        जर (check(मूळ) > 999) {
            av_log(रिक्त, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(मूळ, 0);
            परत 1;
        }
        av_log(रिक्त, AV_LOG_DEBUG, "inserting %4d\n", (पूर्णांक)j);

        जर (!गाठ)
            गाठ = av_वृक्ष_गाठ_alloc();
        जर (!गाठ) {
            av_log(रिक्त, AV_LOG_ERROR, "Memory allocation failure.\n");
            परत 1;
        }
        av_वृक्ष_घाला(&मूळ, (शून्य *)(j + 1), cmp, &गाठ);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_गाठ *node2 = रिक्त;
            av_log(रिक्त, AV_LOG_DEBUG, "removing %4d\n", (पूर्णांक)j);
            av_वृक्ष_घाला(&मूळ, (शून्य *)(j + 1), cmp, &node2);
            k = av_वृक्ष_find(मूळ, (शून्य *)(j + 1), cmp, रिक्त);
            जर (k)
                av_log(रिक्त, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(गाठ);

    av_वृक्ष_destroy(मूळ);

    परत 0;
}
