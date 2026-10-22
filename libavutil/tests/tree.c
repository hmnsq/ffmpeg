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

#समावेश "libavutil/tree.c"

#समावेश <stdint.h>

#समावेश "libavutil/common.h"
#समावेश "libavutil/lfg.h"
#समावेश "libavutil/log.h"
#समावेश "libavutil/mem.h"

अटल पूर्णांक check(AVTree_गाँठ *t)
{
    अगर (t) {
        पूर्णांक बायाँ  = check(t->child[0]);
        पूर्णांक दायाँ = check(t->child[1]);

        अगर (बायाँ > 999 || दायाँ > 999)
            वापस 1000;
        अगर (दायाँ - बायाँ != t->state)
            वापस 1000;
        अगर (t->state > 1 || t->state < -1)
            वापस 1000;
        वापस FFMAX(बायाँ, दायाँ) + 1;
    }
    वापस 0;
}

अटल व्योम print(AVTree_गाँठ *t, पूर्णांक depth)
{
    पूर्णांक i;
    क्रम (i = 0; i < depth * 4; i++)
        av_log(शून्य, AV_LOG_ERROR, " ");
    अगर (t) {
        av_log(शून्य, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } अन्यथा
        av_log(शून्य, AV_LOG_ERROR, "NULL\n");
}

अटल पूर्णांक cmp(स्थिर व्योम *a, स्थिर व्योम *b)
{
    वापस (स्थिर uint8_t *) a - (स्थिर uint8_t *) b;
}

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
{
    पूर्णांक i;
    व्योम *k;
    AVTree_गाँठ *मूल = शून्य, *गाँठ = शून्य;
    AVLFG prng;
    पूर्णांक log_level = argc <= 1 ? AV_LOG_INFO : म_से_प(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    क्रम (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        अगर (check(मूल) > 999) {
            av_log(शून्य, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(मूल, 0);
            वापस 1;
        }
        av_log(शून्य, AV_LOG_DEBUG, "inserting %4d\n", (पूर्णांक)j);

        अगर (!गाँठ)
            गाँठ = av_वृक्ष_गाँठ_alloc();
        अगर (!गाँठ) {
            av_log(शून्य, AV_LOG_ERROR, "Memory allocation failure.\n");
            वापस 1;
        }
        av_वृक्ष_जोड़ो(&मूल, (व्योम *)(j + 1), cmp, &गाँठ);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_गाँठ *node2 = शून्य;
            av_log(शून्य, AV_LOG_DEBUG, "removing %4d\n", (पूर्णांक)j);
            av_वृक्ष_जोड़ो(&मूल, (व्योम *)(j + 1), cmp, &node2);
            k = av_वृक्ष_find(मूल, (व्योम *)(j + 1), cmp, शून्य);
            अगर (k)
                av_log(शून्य, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(गाँठ);

    av_वृक्ष_destroy(मूल);

    वापस 0;
}
