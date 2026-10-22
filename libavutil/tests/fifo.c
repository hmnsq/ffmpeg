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

#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ "libavutil/common.h"
#அந்தர்பாவ "libavutil/fifo.h"
#அந்தர்பாவ "libavutil/lfg.h"
#அந்தர்பாவ "libavutil/random_seed.h"

வகைவரை கட்டமைப்பு CBState {
    unsigned முழு read_idx;
    unsigned முழு write_idx;
    unsigned முழு to_process;
    unsigned முழு offset;
} CBState;

நிலையான முழு read_cb(வெறுமை *opaque, வெறுமை *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    unsigned *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->to_process);

    க்கு (unsigned i = 0; i < *nb_elems; i++)
        எனில் (b[i] != s->read_idx + s->offset + i) {
            printf("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->offset, i);
            திரும்பு AVERROR_BUG;
        }

    s->offset     += *nb_elems;
    s->to_process -= *nb_elems;

    திரும்பு 0;
}

நிலையான முழு write_cb(வெறுமை *opaque, வெறுமை *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    unsigned *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->to_process);

    க்கு (unsigned i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->to_process -= *nb_elems;

    திரும்பு 0;
}

முழு முதன்மை(வெறுமை)
{
    /* create a FIFO buffer */
    AVFifo *fifo = av_fifo_alloc2(13, அளவு(முழு), 0);
    முழு i, j, n, *p;

    /* fill data */
    க்கு (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    க்கு (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        printf("%d: %d\n", i, j);
    }
    printf("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = malloc(n * av_fifo_elem_size(fifo));
    எனில் (p == வெற்று) {
        fprintf(stderr, "failed to allocate memory.\n");
        exit(1);
    }

    (வெறுமை) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    க்கு(i = 0; i < n; ++i)
        printf("%d: %d\n", i, p[i]);

    putchar('\n');

    /* read data */
    க்கு (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        printf(i == 0 ? "%d" : " %d", j);
    }
    printf("\n");

    /* fill data */
    க்கு (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    க்கு (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        printf("%d: %d\n", i, j);
    }
    putchar('\n');

    /* test fifo_grow */
    (வெறுமை) av_fifo_grow2(fifo, 15);

    /* fill data */
    n = av_fifo_can_read(fifo);
    க்கு (i = n; av_fifo_can_write(fifo); ++i)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    க்கு (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        printf("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    seed = av_get_random_seed();

        AVLFG lfg;
        முழு ret;

        av_lfg_init(&lfg, seed);

        fifo = av_fifo_alloc2(1, அளவு(unsigned), AV_FIFO_FLAG_AUTO_GROW);

        க்கு (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            unsigned   to_process = av_lfg_get(&lfg) % nb_elems;

            s.to_process = to_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            எனில் (ret < 0 || s.to_process || nb_elems != to_process) {
                printf("FIFO write fail; seed %"PRIu32"\n", seed);
                திரும்பு 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            எனில் (nb_elems > 1) {
                s.offset     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.offset;

                s.to_process = av_lfg_get(&lfg) % nb_elems;
                to_process   = s.to_process;

                ret = av_fifo_peek_to_cb(fifo, read_cb, &s, &nb_elems, s.offset);
                எனில் (ret < 0 || s.to_process || nb_elems != to_process) {
                    printf("FIFO peek fail; seed %"PRIu32"\n", seed);
                    திரும்பு 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            to_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.to_process = to_process;
            s.offset     = 0;

            ret = av_fifo_read_to_cb(fifo, read_cb, &s, &nb_elems);
            எனில் (ret < 0 || s.to_process || to_process != nb_elems) {
                printf("FIFO read fail; seed %"PRIu32"\n", seed);
                திரும்பு 1;
            }
            s.read_idx += s.offset;
        }
    }

    av_fifo_freep2(&fifo);
    விடுவி(p);

    திரும்பு 0;
}
