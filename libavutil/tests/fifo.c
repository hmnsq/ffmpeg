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

#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ "libavutil/common.h"
#അന്തര്ഭാവ "libavutil/fifo.h"
#അന്തര്ഭാവ "libavutil/lfg.h"
#അന്തര്ഭാവ "libavutil/random_seed.h"

തരനിർവചനം ഘടന CBState {
    unsigned പൂർണ്ണസംഖ്യ read_idx;
    unsigned പൂർണ്ണസംഖ്യ write_idx;
    unsigned പൂർണ്ണസംഖ്യ to_process;
    unsigned പൂർണ്ണസംഖ്യ offset;
} CBState;

സ്ഥിതം പൂർണ്ണസംഖ്യ read_cb(ശൂന്യം *opaque, ശൂന്യം *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    unsigned *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->to_process);

    വേണ്ടി (unsigned i = 0; i < *nb_elems; i++)
        എങ്കിൽ (b[i] != s->read_idx + s->offset + i) {
            printf("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->offset, i);
            തിരികെ AVERROR_BUG;
        }

    s->offset     += *nb_elems;
    s->to_process -= *nb_elems;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ write_cb(ശൂന്യം *opaque, ശൂന്യം *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    unsigned *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->to_process);

    വേണ്ടി (unsigned i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->to_process -= *nb_elems;

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    /* create a FIFO buffer */
    AVFifo *fifo = av_fifo_alloc2(13, വലുപ്പം(പൂർണ്ണസംഖ്യ), 0);
    പൂർണ്ണസംഖ്യ i, j, n, *p;

    /* fill data */
    വേണ്ടി (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    വേണ്ടി (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        printf("%d: %d\n", i, j);
    }
    printf("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = malloc(n * av_fifo_elem_size(fifo));
    എങ്കിൽ (p == ശൂന്യ) {
        fprintf(stderr, "failed to allocate memory.\n");
        exit(1);
    }

    (ശൂന്യം) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    വേണ്ടി(i = 0; i < n; ++i)
        printf("%d: %d\n", i, p[i]);

    putchar('\n');

    /* read data */
    വേണ്ടി (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        printf(i == 0 ? "%d" : " %d", j);
    }
    printf("\n");

    /* fill data */
    വേണ്ടി (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    വേണ്ടി (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        printf("%d: %d\n", i, j);
    }
    putchar('\n');

    /* test fifo_grow */
    (ശൂന്യം) av_fifo_grow2(fifo, 15);

    /* fill data */
    n = av_fifo_can_read(fifo);
    വേണ്ടി (i = n; av_fifo_can_write(fifo); ++i)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    വേണ്ടി (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        printf("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    seed = av_get_random_seed();

        AVLFG lfg;
        പൂർണ്ണസംഖ്യ ret;

        av_lfg_init(&lfg, seed);

        fifo = av_fifo_alloc2(1, വലുപ്പം(unsigned), AV_FIFO_FLAG_AUTO_GROW);

        വേണ്ടി (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            unsigned   to_process = av_lfg_get(&lfg) % nb_elems;

            s.to_process = to_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            എങ്കിൽ (ret < 0 || s.to_process || nb_elems != to_process) {
                printf("FIFO write fail; seed %"PRIu32"\n", seed);
                തിരികെ 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            എങ്കിൽ (nb_elems > 1) {
                s.offset     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.offset;

                s.to_process = av_lfg_get(&lfg) % nb_elems;
                to_process   = s.to_process;

                ret = av_fifo_peek_to_cb(fifo, read_cb, &s, &nb_elems, s.offset);
                എങ്കിൽ (ret < 0 || s.to_process || nb_elems != to_process) {
                    printf("FIFO peek fail; seed %"PRIu32"\n", seed);
                    തിരികെ 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            to_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.to_process = to_process;
            s.offset     = 0;

            ret = av_fifo_read_to_cb(fifo, read_cb, &s, &nb_elems);
            എങ്കിൽ (ret < 0 || s.to_process || to_process != nb_elems) {
                printf("FIFO read fail; seed %"PRIu32"\n", seed);
                തിരികെ 1;
            }
            s.read_idx += s.offset;
        }
    }

    av_fifo_freep2(&fifo);
    സ്വതന്ത്രം(p);

    തിരികെ 0;
}
