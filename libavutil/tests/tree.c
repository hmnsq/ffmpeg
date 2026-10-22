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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ check(AVTree_ಗಂಟು *t)
{
    ಆದರೆ (t) {
        ಪೂರ್ಣಾಂಕ ಎಡ  = check(t->ಮಗು[0]);
        ಪೂರ್ಣಾಂಕ ಬಲ = check(t->ಮಗು[1]);

        ಆದರೆ (ಎಡ > 999 || ಬಲ > 999)
            ಹಿಂತಿರುಗಿ 1000;
        ಆದರೆ (ಬಲ - ಎಡ != t->state)
            ಹಿಂತಿರುಗಿ 1000;
        ಆದರೆ (t->state > 1 || t->state < -1)
            ಹಿಂತಿರುಗಿ 1000;
        ಹಿಂತಿರುಗಿ FFMAX(ಎಡ, ಬಲ) + 1;
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ print(AVTree_ಗಂಟು *t, ಪೂರ್ಣಾಂಕ ಆಳ)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < ಆಳ * 4; i++)
        av_log(ಖಾಲಿ, AV_LOG_ERROR, " ");
    ಆದರೆ (t) {
        av_log(ಖಾಲಿ, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->ಮಗು[0], ಆಳ + 1);
        print(t->ಮಗು[1], ಆಳ + 1);
    } ಇಲ್ಲದಿದ್ದರೆ
        av_log(ಖಾಲಿ, AV_LOG_ERROR, "NULL\n");
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cmp(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *a, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *b)
{
    ಹಿಂತಿರುಗಿ (ಸ್ಥಿರಾಂಕ uint8_t *) a - (ಸ್ಥಿರಾಂಕ uint8_t *) b;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ **argv)
{
    ಪೂರ್ಣಾಂಕ i;
    ಶೂನ್ಯ *k;
    AVTree_ಗಂಟು *ಬೇರು = ಖಾಲಿ, *ಗಂಟು = ಖಾಲಿ;
    AVLFG prng;
    ಪೂರ್ಣಾಂಕ log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_ಗಣ_level(log_level);

    av_lfg_init(&prng, 1);

    ಗಾಗಿ (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        ಆದರೆ (check(ಬೇರು) > 999) {
            av_log(ಖಾಲಿ, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(ಬೇರು, 0);
            ಹಿಂತಿರುಗಿ 1;
        }
        av_log(ಖಾಲಿ, AV_LOG_DEBUG, "inserting %4d\n", (ಪೂರ್ಣಾಂಕ)j);

        ಆದರೆ (!ಗಂಟು)
            ಗಂಟು = av_ವೃಕ್ಷ_ಗಂಟು_alloc();
        ಆದರೆ (!ಗಂಟು) {
            av_log(ಖಾಲಿ, AV_LOG_ERROR, "Memory allocation failure.\n");
            ಹಿಂತಿರುಗಿ 1;
        }
        av_ವೃಕ್ಷ_ಸೇರಿಸು(&ಬೇರು, (ಶೂನ್ಯ *)(j + 1), cmp, &ಗಂಟು);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_ಗಂಟು *node2 = ಖಾಲಿ;
            av_log(ಖಾಲಿ, AV_LOG_DEBUG, "removing %4d\n", (ಪೂರ್ಣಾಂಕ)j);
            av_ವೃಕ್ಷ_ಸೇರಿಸು(&ಬೇರು, (ಶೂನ್ಯ *)(j + 1), cmp, &node2);
            k = av_ವೃಕ್ಷ_ಕಂಡುಹಿಡಿ(ಬೇರು, (ಶೂನ್ಯ *)(j + 1), cmp, ಖಾಲಿ);
            ಆದರೆ (k)
                av_log(ಖಾಲಿ, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(ಗಂಟು);

    av_ವೃಕ್ಷ_destroy(ಬೇರು);

    ಹಿಂತಿರುಗಿ 0;
}
