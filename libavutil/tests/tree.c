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

#അന്തര്ഭാവ "libavutil/tree.c"

#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "libavutil/common.h"
#അന്തര്ഭാവ "libavutil/lfg.h"
#അന്തര്ഭാവ "libavutil/log.h"
#അന്തര്ഭാവ "libavutil/mem.h"

സ്ഥിതം പൂർണ്ണസംഖ്യ check(AVTree_കണ്ണി *t)
{
    എങ്കിൽ (t) {
        പൂർണ്ണസംഖ്യ ഇടത്  = check(t->child[0]);
        പൂർണ്ണസംഖ്യ വലത് = check(t->child[1]);

        എങ്കിൽ (ഇടത് > 999 || വലത് > 999)
            തിരികെ 1000;
        എങ്കിൽ (വലത് - ഇടത് != t->state)
            തിരികെ 1000;
        എങ്കിൽ (t->state > 1 || t->state < -1)
            തിരികെ 1000;
        തിരികെ FFMAX(ഇടത്, വലത്) + 1;
    }
    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം print(AVTree_കണ്ണി *t, പൂർണ്ണസംഖ്യ depth)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < depth * 4; i++)
        av_log(ശൂന്യ, AV_LOG_ERROR, " ");
    എങ്കിൽ (t) {
        av_log(ശൂന്യ, AV_LOG_ERROR, "Node %p %2d %p\n", t, t->state, t->elem);
        print(t->child[0], depth + 1);
        print(t->child[1], depth + 1);
    } അല്ലെങ്കിൽ
        av_log(ശൂന്യ, AV_LOG_ERROR, "NULL\n");
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cmp(സ്ഥിരം ശൂന്യം *a, സ്ഥിരം ശൂന്യം *b)
{
    തിരികെ (സ്ഥിരം uint8_t *) a - (സ്ഥിരം uint8_t *) b;
}

പൂർണ്ണസംഖ്യ പ്രധാന(പൂർണ്ണസംഖ്യ argc, അക്ഷരം **argv)
{
    പൂർണ്ണസംഖ്യ i;
    ശൂന്യം *k;
    AVTree_കണ്ണി *വേര് = ശൂന്യ, *കണ്ണി = ശൂന്യ;
    AVLFG prng;
    പൂർണ്ണസംഖ്യ log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    വേണ്ടി (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        എങ്കിൽ (check(വേര്) > 999) {
            av_log(ശൂന്യ, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(വേര്, 0);
            തിരികെ 1;
        }
        av_log(ശൂന്യ, AV_LOG_DEBUG, "inserting %4d\n", (പൂർണ്ണസംഖ്യ)j);

        എങ്കിൽ (!കണ്ണി)
            കണ്ണി = av_വൃക്ഷം_കണ്ണി_alloc();
        എങ്കിൽ (!കണ്ണി) {
            av_log(ശൂന്യ, AV_LOG_ERROR, "Memory allocation failure.\n");
            തിരികെ 1;
        }
        av_വൃക്ഷം_തിരുകുക(&വേര്, (ശൂന്യം *)(j + 1), cmp, &കണ്ണി);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTree_കണ്ണി *node2 = ശൂന്യ;
            av_log(ശൂന്യ, AV_LOG_DEBUG, "removing %4d\n", (പൂർണ്ണസംഖ്യ)j);
            av_വൃക്ഷം_തിരുകുക(&വേര്, (ശൂന്യം *)(j + 1), cmp, &node2);
            k = av_വൃക്ഷം_find(വേര്, (ശൂന്യം *)(j + 1), cmp, ശൂന്യ);
            എങ്കിൽ (k)
                av_log(ശൂന്യ, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(കണ്ണി);

    av_വൃക്ഷം_destroy(വേര്);

    തിരികെ 0;
}
