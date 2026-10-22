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

#અન્તર્ભાવ "libavutil/tree.c"

#અન્તર્ભાવ <stdint.h>

#અન્તર્ભાવ "libavutil/common.h"
#અન્તર્ભાવ "libavutil/lfg.h"
#અન્તર્ભાવ "libavutil/log.h"
#અન્તર્ભાવ "libavutil/mem.h"

સ્થિર પૂર્ણાંક check(AVTree_ગાંઠ *t)
{
    જો (t) {
        પૂર્ણાંક ડાબું  = check(t->child[0]);
        પૂર્ણાંક જમણું = check(t->child[1]);

        જો (ડાબું > 999 || જમણું > 999)
            પાછા 1000;
        જો (જમણું - ડાબું != t->state)
            પાછા 1000;
        જો (t->state > 1 || t->state < -1)
            પાછા 1000;
        પાછા FFMAX(ડાબું, જમણું) + 1;
    }
    પાછા 0;
}

સ્થિર શૂન્ય print(AVTree_ગાંઠ *t, પૂર્ણાંક depth)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < depth * 4; i++)
        av_log(ખાલી, AV_LOG_ERROR, " ");
    જો (t) {
        av_log(ખાલી, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } નહીંતર
        av_log(ખાલી, AV_LOG_ERROR, "NULL\n");
}

સ્થિર પૂર્ણાંક cmp(અચલ શૂન્ય *a, અચલ શૂન્ય *b)
{
    પાછા (અચલ uint8_t *) a - (અચલ uint8_t *) b;
}

પૂર્ણાંક મુખ્ય(પૂર્ણાંક argc, અક્ષર **argv)
{
    પૂર્ણાંક i;
    શૂન્ય *k;
    AVTree_ગાંઠ *મૂળ = ખાલી, *ગાંઠ = ખાલી;
    AVLFG prng;
    પૂર્ણાંક log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    માટે (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        જો (check(મૂળ) > 999) {
            av_log(ખાલી, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(મૂળ, 0);
            પાછા 1;
        }
        av_log(ખાલી, AV_LOG_DEBUG, "inserting %4d\n", (પૂર્ણાંક)j);

        જો (!ગાંઠ)
            ગાંઠ = av_વૃક્ષ_ગાંઠ_alloc();
        જો (!ગાંઠ) {
            av_log(ખાલી, AV_LOG_ERROR, "Memory allocation failure.\n");
            પાછા 1;
        }
        av_વૃક્ષ_ઉમેરો(&મૂળ, (શૂન્ય *)(j + 1), cmp, &ગાંઠ);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_ગાંઠ *node2 = ખાલી;
            av_log(ખાલી, AV_LOG_DEBUG, "removing %4d\n", (પૂર્ણાંક)j);
            av_વૃક્ષ_ઉમેરો(&મૂળ, (શૂન્ય *)(j + 1), cmp, &node2);
            k = av_વૃક્ષ_find(મૂળ, (શૂન્ય *)(j + 1), cmp, ખાલી);
            જો (k)
                av_log(ખાલી, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(ગાંઠ);

    av_વૃક્ષ_destroy(મૂળ);

    પાછા 0;
}
