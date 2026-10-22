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

#অন্তর্ভাব "libavutil/tree.c"

#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "libavutil/common.h"
#অন্তর্ভাব "libavutil/lfg.h"
#অন্তর্ভাব "libavutil/log.h"
#অন্তর্ভাব "libavutil/mem.h"

স্থির পূর্ণাঙ্ক check(AVTree_গ্রন্থি *t)
{
    যদি (t) {
        পূর্ণাঙ্ক বাম  = check(t->child[0]);
        পূর্ণাঙ্ক ডান = check(t->child[1]);

        যদি (বাম > 999 || ডান > 999)
            প্রত্যাগম 1000;
        যদি (ডান - বাম != t->state)
            প্রত্যাগম 1000;
        যদি (t->state > 1 || t->state < -1)
            প্রত্যাগম 1000;
        প্রত্যাগম FFMAX(বাম, ডান) + 1;
    }
    প্রত্যাগম 0;
}

স্থির শূন্য print(AVTree_গ্রন্থি *t, পূর্ণাঙ্ক depth)
{
    পূর্ণাঙ্ক i;
    প্রতি (i = 0; i < depth * 4; i++)
        av_log(রিক্ত, AV_LOG_ERROR, " ");
    যদি (t) {
        av_log(রিক্ত, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } অন্যথা
        av_log(রিক্ত, AV_LOG_ERROR, "NULL\n");
}

স্থির পূর্ণাঙ্ক cmp(ধ্রুব শূন্য *a, ধ্রুব শূন্য *b)
{
    প্রত্যাগম (ধ্রুব uint8_t *) a - (ধ্রুব uint8_t *) b;
}

পূর্ণাঙ্ক main(পূর্ণাঙ্ক argc, বর্ণ **argv)
{
    পূর্ণাঙ্ক i;
    শূন্য *k;
    AVTree_গ্রন্থি *মূল = রিক্ত, *গ্রন্থি = রিক্ত;
    AVLFG prng;
    পূর্ণাঙ্ক log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    প্রতি (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        যদি (check(মূল) > 999) {
            av_log(রিক্ত, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(মূল, 0);
            প্রত্যাগম 1;
        }
        av_log(রিক্ত, AV_LOG_DEBUG, "inserting %4d\n", (পূর্ণাঙ্ক)j);

        যদি (!গ্রন্থি)
            গ্রন্থি = av_বৃক্ষ_গ্রন্থি_alloc();
        যদি (!গ্রন্থি) {
            av_log(রিক্ত, AV_LOG_ERROR, "Memory allocation failure.\n");
            প্রত্যাগম 1;
        }
        av_বৃক্ষ_ঢোকাও(&মূল, (শূন্য *)(j + 1), cmp, &গ্রন্থি);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_গ্রন্থি *node2 = রিক্ত;
            av_log(রিক্ত, AV_LOG_DEBUG, "removing %4d\n", (পূর্ণাঙ্ক)j);
            av_বৃক্ষ_ঢোকাও(&মূল, (শূন্য *)(j + 1), cmp, &node2);
            k = av_বৃক্ষ_find(মূল, (শূন্য *)(j + 1), cmp, রিক্ত);
            যদি (k)
                av_log(রিক্ত, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(গ্রন্থি);

    av_বৃক্ষ_destroy(মূল);

    প্রত্যাগম 0;
}
