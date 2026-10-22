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

स्थिर पूर्णाङ्क check(AVTree_गाँठो *t)
{
    यदि (t) {
        पूर्णाङ्क बायाँ  = check(t->child[0]);
        पूर्णाङ्क दायाँ = check(t->child[1]);

        यदि (बायाँ > 999 || दायाँ > 999)
            फर्काऊ 1000;
        यदि (दायाँ - बायाँ != t->state)
            फर्काऊ 1000;
        यदि (t->state > 1 || t->state < -1)
            फर्काऊ 1000;
        फर्काऊ FFMAX(बायाँ, दायाँ) + 1;
    }
    फर्काऊ 0;
}

स्थिर शून्य print(AVTree_गाँठो *t, पूर्णाङ्क depth)
{
    पूर्णाङ्क i;
    लागि (i = 0; i < depth * 4; i++)
        av_log(रिक्त, AV_LOG_ERROR, " ");
    यदि (t) {
        av_log(रिक्त, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } अन्यथा
        av_log(रिक्त, AV_LOG_ERROR, "NULL\n");
}

स्थिर पूर्णाङ्क cmp(अचर शून्य *a, अचर शून्य *b)
{
    फर्काऊ (अचर uint8_t *) a - (अचर uint8_t *) b;
}

पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण **argv)
{
    पूर्णाङ्क i;
    शून्य *k;
    AVTree_गाँठो *जरा = रिक्त, *गाँठो = रिक्त;
    AVLFG prng;
    पूर्णाङ्क log_level = argc <= 1 ? AV_LOG_INFO : म_से_प(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    लागि (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        यदि (check(जरा) > 999) {
            av_log(रिक्त, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(जरा, 0);
            फर्काऊ 1;
        }
        av_log(रिक्त, AV_LOG_DEBUG, "inserting %4d\n", (पूर्णाङ्क)j);

        यदि (!गाँठो)
            गाँठो = av_रूख_गाँठो_alloc();
        यदि (!गाँठो) {
            av_log(रिक्त, AV_LOG_ERROR, "Memory allocation failure.\n");
            फर्काऊ 1;
        }
        av_रूख_घुसाउ(&जरा, (शून्य *)(j + 1), cmp, &गाँठो);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_गाँठो *node2 = रिक्त;
            av_log(रिक्त, AV_LOG_DEBUG, "removing %4d\n", (पूर्णाङ्क)j);
            av_रूख_घुसाउ(&जरा, (शून्य *)(j + 1), cmp, &node2);
            k = av_रूख_find(जरा, (शून्य *)(j + 1), cmp, रिक्त);
            यदि (k)
                av_log(रिक्त, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(गाँठो);

    av_रूख_destroy(जरा);

    फर्काऊ 0;
}
