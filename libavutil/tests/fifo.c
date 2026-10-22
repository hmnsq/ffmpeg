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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/fifo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/lfg.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/random_seed.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ CBState {
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ read_idx;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_idx;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਮੰਜ਼ਿਲ_process;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਵਿੱਥ;
} CBState;

ਸਥਿਰ ਪੂਰਨ read_cb(ਖਾਲੀ *opaque, ਖਾਲੀ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    ਬਿਨਾਨਿਸ਼ਾਨੀ *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->ਮੰਜ਼ਿਲ_process);

    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < *nb_elems; i++)
        ਜੇ (b[i] != s->read_idx + s->ਵਿੱਥ + i) {
            ਲਿਖੋ("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->ਵਿੱਥ, i);
            ਵਾਪਸ AVERROR_BUG;
        }

    s->ਵਿੱਥ     += *nb_elems;
    s->ਮੰਜ਼ਿਲ_process -= *nb_elems;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ write_cb(ਖਾਲੀ *opaque, ਖਾਲੀ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    ਬਿਨਾਨਿਸ਼ਾਨੀ *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->ਮੰਜ਼ਿਲ_process);

    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->ਮੰਜ਼ਿਲ_process -= *nb_elems;

    ਵਾਪਸ 0;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    /* create a FIFO buffer */
    AVFifo *fifo = av_fifo_alloc2(13, ਆਕਾਰ(ਪੂਰਨ), 0);
    ਪੂਰਨ i, j, n, *p;

    /* fill data */
    ਲਈ (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    ਲਈ (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        ਲਿਖੋ("%d: %d\n", i, j);
    }
    ਲਿਖੋ("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = ਸਮ੍ਰਿਤੀ_ਦਿਓ(n * av_fifo_elem_ਮਾਪ(fifo));
    ਜੇ (p == ਨਿਰਾ) {
        fprintf(stderr, "failed to allocate memory.\n");
        ਬਾਹਰ_ਨਿਕਲੋ(1);
    }

    (ਖਾਲੀ) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    ਲਈ(i = 0; i < n; ++i)
        ਲਿਖੋ("%d: %d\n", i, p[i]);

    ਅੱਖਰ_ਲਿਖੋ('\n');

    /* read data */
    ਲਈ (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        ਲਿਖੋ(i == 0 ? "%d" : " %d", j);
    }
    ਲਿਖੋ("\n");

    /* fill data */
    ਲਈ (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    ਲਈ (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        ਲਿਖੋ("%d: %d\n", i, j);
    }
    ਅੱਖਰ_ਲਿਖੋ('\n');

    /* test fifo_grow */
    (ਖਾਲੀ) av_fifo_grow2(fifo, 15);

    /* fill data */
    n = av_fifo_can_read(fifo);
    ਲਈ (i = n; av_fifo_can_write(fifo); ++i)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    ਲਈ (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        ਲਿਖੋ("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    ਬੀਜ = av_get_random_ਬੀਜ();

        AVLFG lfg;
        ਪੂਰਨ ret;

        av_lfg_init(&lfg, ਬੀਜ);

        fifo = av_fifo_alloc2(1, ਆਕਾਰ(ਬਿਨਾਨਿਸ਼ਾਨੀ), AV_FIFO_FLAG_AUTO_GROW);

        ਲਈ (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            ਬਿਨਾਨਿਸ਼ਾਨੀ   ਮੰਜ਼ਿਲ_process = av_lfg_get(&lfg) % nb_elems;

            s.ਮੰਜ਼ਿਲ_process = ਮੰਜ਼ਿਲ_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            ਜੇ (ret < 0 || s.ਮੰਜ਼ਿਲ_process || nb_elems != ਮੰਜ਼ਿਲ_process) {
                ਲਿਖੋ("FIFO write fail; seed %"PRIu32"\n", ਬੀਜ);
                ਵਾਪਸ 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            ਜੇ (nb_elems > 1) {
                s.ਵਿੱਥ     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.ਵਿੱਥ;

                s.ਮੰਜ਼ਿਲ_process = av_lfg_get(&lfg) % nb_elems;
                ਮੰਜ਼ਿਲ_process   = s.ਮੰਜ਼ਿਲ_process;

                ret = av_fifo_peek_ਮੰਜ਼ਿਲ_cb(fifo, read_cb, &s, &nb_elems, s.ਵਿੱਥ);
                ਜੇ (ret < 0 || s.ਮੰਜ਼ਿਲ_process || nb_elems != ਮੰਜ਼ਿਲ_process) {
                    ਲਿਖੋ("FIFO peek fail; seed %"PRIu32"\n", ਬੀਜ);
                    ਵਾਪਸ 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            ਮੰਜ਼ਿਲ_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.ਮੰਜ਼ਿਲ_process = ਮੰਜ਼ਿਲ_process;
            s.ਵਿੱਥ     = 0;

            ret = av_fifo_read_ਮੰਜ਼ਿਲ_cb(fifo, read_cb, &s, &nb_elems);
            ਜੇ (ret < 0 || s.ਮੰਜ਼ਿਲ_process || ਮੰਜ਼ਿਲ_process != nb_elems) {
                ਲਿਖੋ("FIFO read fail; seed %"PRIu32"\n", ਬੀਜ);
                ਵਾਪਸ 1;
            }
            s.read_idx += s.ਵਿੱਥ;
        }
    }

    av_fifo_freep2(&fifo);
    ਮੁਕਤ(p);

    ਵਾਪਸ 0;
}
