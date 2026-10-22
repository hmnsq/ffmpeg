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

स्थिर पूर्णाङ्क check(AVTree_ग्रन्थिः *t)
{
    सचे (t) {
        पूर्णाङ्क वामः  = check(t->child[0]);
        पूर्णाङ्क दक्षिणः = check(t->child[1]);

        सचे (वामः > 999 || दक्षिणः > 999)
            पटिनिवत्त 1000;
        सचे (दक्षिणः - वामः != t->state)
            पटिनिवत्त 1000;
        सचे (t->state > 1 || t->state < -1)
            पटिनिवत्त 1000;
        पटिनिवत्त FFMAX(वामः, दक्षिणः) + 1;
    }
    पटिनिवत्त 0;
}

स्थिर शून्य print(AVTree_ग्रन्थिः *t, पूर्णाङ्क depth)
{
    पूर्णाङ्क i;
    अत्थाय (i = 0; i < depth * 4; i++)
        av_log(रिक्त, AV_LOG_ERROR, " ");
    सचे (t) {
        av_log(रिक्त, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } अञ्ञथा
        av_log(रिक्त, AV_LOG_ERROR, "NULL\n");
}

स्थिर पूर्णाङ्क cmp(ध्रुव शून्य *a, ध्रुव शून्य *b)
{
    पटिनिवत्त (ध्रुव uint8_t *) a - (ध्रुव uint8_t *) b;
}

पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण **argv)
{
    पूर्णाङ्क i;
    शून्य *k;
    AVTree_ग्रन्थिः *मूलम् = रिक्त, *ग्रन्थिः = रिक्त;
    AVLFG prng;
    पूर्णाङ्क log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    अत्थाय (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        सचे (check(मूलम्) > 999) {
            av_log(रिक्त, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(मूलम्, 0);
            पटिनिवत्त 1;
        }
        av_log(रिक्त, AV_LOG_DEBUG, "inserting %4d\n", (पूर्णाङ्क)j);

        सचे (!ग्रन्थिः)
            ग्रन्थिः = av_वृक्षः_ग्रन्थिः_alloc();
        सचे (!ग्रन्थिः) {
            av_log(रिक्त, AV_LOG_ERROR, "Memory allocation failure.\n");
            पटिनिवत्त 1;
        }
        av_वृक्षः_निवेशय(&मूलम्, (शून्य *)(j + 1), cmp, &ग्रन्थिः);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_ग्रन्थिः *node2 = रिक्त;
            av_log(रिक्त, AV_LOG_DEBUG, "removing %4d\n", (पूर्णाङ्क)j);
            av_वृक्षः_निवेशय(&मूलम्, (शून्य *)(j + 1), cmp, &node2);
            k = av_वृक्षः_find(मूलम्, (शून्य *)(j + 1), cmp, रिक्त);
            सचे (k)
                av_log(रिक्त, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(ग्रन्थिः);

    av_वृक्षः_destroy(मूलम्);

    पटिनिवत्त 0;
}
