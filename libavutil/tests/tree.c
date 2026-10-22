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

#ಅನ್ತರ್ಭಾವ "libavutil/tree.c"

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "libavutil/common.h"
#ಅನ್ತರ್ಭಾವ "libavutil/lfg.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ check(AVTree_ಗಂಟು *t)
{
    ಯದಿ (t) {
        ಪೂರ್ಣಾಙ್ಕ ಎಡ  = check(t->child[0]);
        ಪೂರ್ಣಾಙ್ಕ ಬಲ = check(t->child[1]);

        ಯದಿ (ಎಡ > 999 || ಬಲ > 999)
            ಪ್ರತ್ಯಾಗಮ 1000;
        ಯದಿ (ಬಲ - ಎಡ != t->state)
            ಪ್ರತ್ಯಾಗಮ 1000;
        ಯದಿ (t->state > 1 || t->state < -1)
            ಪ್ರತ್ಯಾಗಮ 1000;
        ಪ್ರತ್ಯಾಗಮ FFMAX(ಎಡ, ಬಲ) + 1;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ print(AVTree_ಗಂಟು *t, ಪೂರ್ಣಾಙ್ಕ depth)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < depth * 4; i++)
        av_log(ರಿಕ್ತ, AV_LOG_ERROR, " ");
    ಯದಿ (t) {
        av_log(ರಿಕ್ತ, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } ಅನ್ಯಥಾ
        av_log(ರಿಕ್ತ, AV_LOG_ERROR, "NULL\n");
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cmp(ಧ್ರುವ ಶೂನ್ಯ *a, ಧ್ರುವ ಶೂನ್ಯ *b)
{
    ಪ್ರತ್ಯಾಗಮ (ಧ್ರುವ uint8_t *) a - (ಧ್ರುವ uint8_t *) b;
}

ಪೂರ್ಣಾಙ್ಕ main(ಪೂರ್ಣಾಙ್ಕ argc, ವರ್ಣ **argv)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಶೂನ್ಯ *k;
    AVTree_ಗಂಟು *ಬೇರು = ರಿಕ್ತ, *ಗಂಟು = ರಿಕ್ತ;
    AVLFG prng;
    ಪೂರ್ಣಾಙ್ಕ log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    ಪ್ರತಿ (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        ಯದಿ (check(ಬೇರು) > 999) {
            av_log(ರಿಕ್ತ, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(ಬೇರು, 0);
            ಪ್ರತ್ಯಾಗಮ 1;
        }
        av_log(ರಿಕ್ತ, AV_LOG_DEBUG, "inserting %4d\n", (ಪೂರ್ಣಾಙ್ಕ)j);

        ಯದಿ (!ಗಂಟು)
            ಗಂಟು = av_ವೃಕ್ಷ_ಗಂಟು_alloc();
        ಯದಿ (!ಗಂಟು) {
            av_log(ರಿಕ್ತ, AV_LOG_ERROR, "Memory allocation failure.\n");
            ಪ್ರತ್ಯಾಗಮ 1;
        }
        av_ವೃಕ್ಷ_ಸೇರಿಸು(&ಬೇರು, (ಶೂನ್ಯ *)(j + 1), cmp, &ಗಂಟು);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_ಗಂಟು *node2 = ರಿಕ್ತ;
            av_log(ರಿಕ್ತ, AV_LOG_DEBUG, "removing %4d\n", (ಪೂರ್ಣಾಙ್ಕ)j);
            av_ವೃಕ್ಷ_ಸೇರಿಸು(&ಬೇರು, (ಶೂನ್ಯ *)(j + 1), cmp, &node2);
            k = av_ವೃಕ್ಷ_find(ಬೇರು, (ಶೂನ್ಯ *)(j + 1), cmp, ರಿಕ್ತ);
            ಯದಿ (k)
                av_log(ರಿಕ್ತ, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(ಗಂಟು);

    av_ವೃಕ್ಷ_destroy(ಬೇರು);

    ಪ್ರತ್ಯಾಗಮ 0;
}
