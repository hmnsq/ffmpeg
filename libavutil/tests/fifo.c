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

#شامل <stdio.h>
#شامل <stdlib.h>
#شامل "libavutil/common.h"
#شامل "libavutil/fifo.h"
#شامل "libavutil/lfg.h"
#شامل "libavutil/random_seed.h"

قسمتعریف ساخت CBState {
    غیرعلامتی صحیح read_idx;
    غیرعلامتی صحیح write_idx;
    غیرعلامتی صحیح مقصد_process;
    غیرعلامتی صحیح انحراف;
} CBState;

ساکن صحیح read_cb(خالی *opaque, خالی *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    غیرعلامتی *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->مقصد_process);

    برائے (غیرعلامتی i = 0; i < *nb_elems; i++)
        اگر (b[i] != s->read_idx + s->انحراف + i) {
            لکھو("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->انحراف, i);
            واپس AVERROR_BUG;
        }

    s->انحراف     += *nb_elems;
    s->مقصد_process -= *nb_elems;

    واپس 0;
}

ساکن صحیح write_cb(خالی *opaque, خالی *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    غیرعلامتی *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->مقصد_process);

    برائے (غیرعلامتی i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->مقصد_process -= *nb_elems;

    واپس 0;
}

صحیح مین(خالی)
{
    /* create a FIFO buffer */
    AVFifo *fifo = av_fifo_alloc2(13, حجم(صحیح), 0);
    صحیح i, j, n, *p;

    /* fill data */
    برائے (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    برائے (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        لکھو("%d: %d\n", i, j);
    }
    لکھو("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = حافظہ_دو(n * av_fifo_elem_سائز(fifo));
    اگر (p == تہی) {
        fprintf(stderr, "failed to allocate memory.\n");
        باہر_نکلو(1);
    }

    (خالی) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    برائے(i = 0; i < n; ++i)
        لکھو("%d: %d\n", i, p[i]);

    حرف_لکھو('\n');

    /* read data */
    برائے (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        لکھو(i == 0 ? "%d" : " %d", j);
    }
    لکھو("\n");

    /* fill data */
    برائے (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    برائے (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        لکھو("%d: %d\n", i, j);
    }
    حرف_لکھو('\n');

    /* test fifo_grow */
    (خالی) av_fifo_grow2(fifo, 15);

    /* fill data */
    n = av_fifo_can_read(fifo);
    برائے (i = n; av_fifo_can_write(fifo); ++i)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    برائے (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        لکھو("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    بیج = av_get_random_بیج();

        AVLFG lfg;
        صحیح ret;

        av_lfg_init(&lfg, بیج);

        fifo = av_fifo_alloc2(1, حجم(غیرعلامتی), AV_FIFO_FLAG_AUTO_GROW);

        برائے (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            غیرعلامتی   مقصد_process = av_lfg_get(&lfg) % nb_elems;

            s.مقصد_process = مقصد_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            اگر (ret < 0 || s.مقصد_process || nb_elems != مقصد_process) {
                لکھو("FIFO write fail; seed %"PRIu32"\n", بیج);
                واپس 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            اگر (nb_elems > 1) {
                s.انحراف     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.انحراف;

                s.مقصد_process = av_lfg_get(&lfg) % nb_elems;
                مقصد_process   = s.مقصد_process;

                ret = av_fifo_peek_مقصد_cb(fifo, read_cb, &s, &nb_elems, s.انحراف);
                اگر (ret < 0 || s.مقصد_process || nb_elems != مقصد_process) {
                    لکھو("FIFO peek fail; seed %"PRIu32"\n", بیج);
                    واپس 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            مقصد_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.مقصد_process = مقصد_process;
            s.انحراف     = 0;

            ret = av_fifo_read_مقصد_cb(fifo, read_cb, &s, &nb_elems);
            اگر (ret < 0 || s.مقصد_process || مقصد_process != nb_elems) {
                لکھو("FIFO read fail; seed %"PRIu32"\n", بیج);
                واپس 1;
            }
            s.read_idx += s.انحراف;
        }
    }

    av_fifo_freep2(&fifo);
    آزاد(p);

    واپس 0;
}
