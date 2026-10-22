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

#অন্তর্ভাৱ "libavutil/tree.c"

#অন্তর্ভাৱ <stdint.h>

#অন্তর্ভাৱ "libavutil/common.h"
#অন্তর্ভাৱ "libavutil/lfg.h"
#অন্তর্ভাৱ "libavutil/log.h"
#অন্তর্ভাৱ "libavutil/mem.h"

স্থির পূর্ণাঙ্ক check(AVTree_গ্ৰন্থি *t)
{
    যদি (t) {
        পূর্ণাঙ্ক বাম  = check(t->child[0]);
        পূর্ণাঙ্ক ডান = check(t->child[1]);

        যদি (বাম > 999 || ডান > 999)
            ঘূৰাই 1000;
        যদি (ডান - বাম != t->state)
            ঘূৰাই 1000;
        যদি (t->state > 1 || t->state < -1)
            ঘূৰাই 1000;
        ঘূৰাই FFMAX(বাম, ডান) + 1;
    }
    ঘূৰাই 0;
}

স্থির শূন্য print(AVTree_গ্ৰন্থি *t, পূর্ণাঙ্ক depth)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < depth * 4; i++)
        av_log(রিক্ত, AV_LOG_ERROR, " ");
    যদি (t) {
        av_log(রিক্ত, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } অন্যথা
        av_log(রিক্ত, AV_LOG_ERROR, "NULL\n");
}

স্থির পূর্ণাঙ্ক cmp(ধ্রুৱ শূন্য *a, ধ্রুৱ শূন্য *b)
{
    ঘূৰাই (ধ্রুৱ uint8_t *) a - (ধ্রুৱ uint8_t *) b;
}

পূর্ণাঙ্ক main(পূর্ণাঙ্ক argc, ৱর্ণ **argv)
{
    পূর্ণাঙ্ক i;
    শূন্য *k;
    AVTree_গ্ৰন্থি *মূল = রিক্ত, *গ্ৰন্থি = রিক্ত;
    AVLFG prng;
    পূর্ণাঙ্ক log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    বাবে (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        যদি (check(মূল) > 999) {
            av_log(রিক্ত, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(মূল, 0);
            ঘূৰাই 1;
        }
        av_log(রিক্ত, AV_LOG_DEBUG, "inserting %4d\n", (পূর্ণাঙ্ক)j);

        যদি (!গ্ৰন্থি)
            গ্ৰন্থি = av_বৃক্ষ_গ্ৰন্থি_alloc();
        যদি (!গ্ৰন্থি) {
            av_log(রিক্ত, AV_LOG_ERROR, "Memory allocation failure.\n");
            ঘূৰাই 1;
        }
        av_বৃক্ষ_ঢোকাও(&মূল, (শূন্য *)(j + 1), cmp, &গ্ৰন্থি);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_গ্ৰন্থি *node2 = রিক্ত;
            av_log(রিক্ত, AV_LOG_DEBUG, "removing %4d\n", (পূর্ণাঙ্ক)j);
            av_বৃক্ষ_ঢোকাও(&মূল, (শূন্য *)(j + 1), cmp, &node2);
            k = av_বৃক্ষ_find(মূল, (শূন্য *)(j + 1), cmp, রিক্ত);
            যদি (k)
                av_log(রিক্ত, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(গ্ৰন্থি);

    av_বৃক্ষ_destroy(মূল);

    ঘূৰাই 0;
}
