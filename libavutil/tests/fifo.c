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

#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن "libavutil/common.h"
#ضمن "libavutil/fifo.h"
#ضمن "libavutil/lfg.h"
#ضمن "libavutil/random_seed.h"

تعريفنوع بنية CBState {
    بنانشانی صحيح read_idx;
    بنانشانی صحيح write_idx;
    بنانشانی صحيح منزل_process;
    بنانشانی صحيح وتھ;
} CBState;

ساكن صحيح read_cb(فراغ *opaque, فراغ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    بنانشانی *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->منزل_process);

    لكل (بنانشانی i = 0; i < *nb_elems; i++)
        إذا (b[i] != s->read_idx + s->وتھ + i) {
            لکھو("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->وتھ, i);
            أرجع AVERROR_BUG;
        }

    s->وتھ     += *nb_elems;
    s->منزل_process -= *nb_elems;

    أرجع 0;
}

ساكن صحيح write_cb(فراغ *opaque, فراغ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    بنانشانی *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->منزل_process);

    لكل (بنانشانی i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->منزل_process -= *nb_elems;

    أرجع 0;
}

صحيح مکھ(فراغ)
{
    /* create a FIFO buffer */
    AVFifo *fifo = av_fifo_alloc2(13, حجم(صحيح), 0);
    صحيح i, j, n, *p;

    /* fill data */
    لكل (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    لكل (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        لکھو("%d: %d\n", i, j);
    }
    لکھو("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = حافظہ_دیو(n * av_fifo_elem_ناپ(fifo));
    إذا (p == عدم) {
        fprintf(stderr, "failed to allocate memory.\n");
        باہر_نکلو(1);
    }

    (فراغ) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    لكل(i = 0; i < n; ++i)
        لکھو("%d: %d\n", i, p[i]);

    حرف_لکھو('\n');

    /* read data */
    لكل (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        لکھو(i == 0 ? "%d" : " %d", j);
    }
    لکھو("\n");

    /* fill data */
    لكل (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    لكل (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        لکھو("%d: %d\n", i, j);
    }
    حرف_لکھو('\n');

    /* test fifo_grow */
    (فراغ) av_fifo_grow2(fifo, 15);

    /* fill data */
    n = av_fifo_can_read(fifo);
    لكل (i = n; av_fifo_can_write(fifo); ++i)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    لكل (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        لکھو("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    بیج = av_get_random_بیج();

        AVLFG lfg;
        صحيح ret;

        av_lfg_init(&lfg, بیج);

        fifo = av_fifo_alloc2(1, حجم(بنانشانی), AV_FIFO_FLAG_AUTO_GROW);

        لكل (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            بنانشانی   منزل_process = av_lfg_get(&lfg) % nb_elems;

            s.منزل_process = منزل_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            إذا (ret < 0 || s.منزل_process || nb_elems != منزل_process) {
                لکھو("FIFO write fail; seed %"PRIu32"\n", بیج);
                أرجع 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            إذا (nb_elems > 1) {
                s.وتھ     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.وتھ;

                s.منزل_process = av_lfg_get(&lfg) % nb_elems;
                منزل_process   = s.منزل_process;

                ret = av_fifo_peek_منزل_cb(fifo, read_cb, &s, &nb_elems, s.وتھ);
                إذا (ret < 0 || s.منزل_process || nb_elems != منزل_process) {
                    لکھو("FIFO peek fail; seed %"PRIu32"\n", بیج);
                    أرجع 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            منزل_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.منزل_process = منزل_process;
            s.وتھ     = 0;

            ret = av_fifo_read_منزل_cb(fifo, read_cb, &s, &nb_elems);
            إذا (ret < 0 || s.منزل_process || منزل_process != nb_elems) {
                لکھو("FIFO read fail; seed %"PRIu32"\n", بیج);
                أرجع 1;
            }
            s.read_idx += s.وتھ;
        }
    }

    av_fifo_freep2(&fifo);
    حرر(p);

    أرجع 0;
}
