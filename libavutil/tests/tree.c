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

#ଅନ୍ତର୍ଭାଵ "libavutil/tree.c"

#ଅନ୍ତର୍ଭାଵ <stdint.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/common.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/lfg.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/log.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/mem.h"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା check(AVTree_ଗଣ୍ଠି *t)
{
    ଯଦି (t) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ  = check(t->child[0]);
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ = check(t->child[1]);

        ଯଦି (ବାମ > 999 || ଡାହାଣ > 999)
            ଫେରନ୍ତୁ 1000;
        ଯଦି (ଡାହାଣ - ବାମ != t->state)
            ଫେରନ୍ତୁ 1000;
        ଯଦି (t->state > 1 || t->state < -1)
            ଫେରନ୍ତୁ 1000;
        ଫେରନ୍ତୁ FFMAX(ବାମ, ଡାହାଣ) + 1;
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ print(AVTree_ଗଣ୍ଠି *t, ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < depth * 4; i++)
        av_log(ଖାଲି, AV_LOG_ERROR, " ");
    ଯଦି (t) {
        av_log(ଖାଲି, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } ଅନ୍ୟଥା
        av_log(ଖାଲି, AV_LOG_ERROR, "NULL\n");
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cmp(ଅଚଳ ଶୂନ୍ୟ *a, ଅଚଳ ଶୂନ୍ୟ *b)
{
    ଫେରନ୍ତୁ (ଅଚଳ uint8_t *) a - (ଅଚଳ uint8_t *) b;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର **argv)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ଶୂନ୍ୟ *k;
    AVTree_ଗଣ୍ଠି *ମୂଳ = ଖାଲି, *ଗଣ୍ଠି = ଖାଲି;
    AVLFG prng;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    ପାଇଁ (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        ଯଦି (check(ମୂଳ) > 999) {
            av_log(ଖାଲି, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(ମୂଳ, 0);
            ଫେରନ୍ତୁ 1;
        }
        av_log(ଖାଲି, AV_LOG_DEBUG, "inserting %4d\n", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)j);

        ଯଦି (!ଗଣ୍ଠି)
            ଗଣ୍ଠି = av_ବୃକ୍ଷ_ଗଣ୍ଠି_alloc();
        ଯଦି (!ଗଣ୍ଠି) {
            av_log(ଖାଲି, AV_LOG_ERROR, "Memory allocation failure.\n");
            ଫେରନ୍ତୁ 1;
        }
        av_ବୃକ୍ଷ_ଭର୍ତ୍ତି(&ମୂଳ, (ଶୂନ୍ୟ *)(j + 1), cmp, &ଗଣ୍ଠି);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_ଗଣ୍ଠି *node2 = ଖାଲି;
            av_log(ଖାଲି, AV_LOG_DEBUG, "removing %4d\n", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)j);
            av_ବୃକ୍ଷ_ଭର୍ତ୍ତି(&ମୂଳ, (ଶୂନ୍ୟ *)(j + 1), cmp, &node2);
            k = av_ବୃକ୍ଷ_find(ମୂଳ, (ଶୂନ୍ୟ *)(j + 1), cmp, ଖାଲି);
            ଯଦି (k)
                av_log(ଖାଲି, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(ଗଣ୍ଠି);

    av_ବୃକ୍ଷ_destroy(ମୂଳ);

    ଫେରନ୍ତୁ 0;
}
