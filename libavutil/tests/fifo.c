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
    بینښه صحيح read_idx;
    بینښه صحيح write_idx;
    بینښه صحيح منزل_process;
    بینښه صحيح دننه_واټن;
} CBState;

ساكن صحيح read_cb(فراغ *opaque, فراغ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    بینښه *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->منزل_process);

    لكل (بینښه i = 0; i < *nb_elems; i++)
        إذا (b[i] != s->read_idx + s->دننه_واټن + i) {
            چاپ_کړه("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->دننه_واټن, i);
            أرجع AVERROR_BUG;
        }

    s->دننه_واټن     += *nb_elems;
    s->منزل_process -= *nb_elems;

    أرجع 0;
}

ساكن صحيح write_cb(فراغ *opaque, فراغ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    بینښه *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->منزل_process);

    لكل (بینښه i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->منزل_process -= *nb_elems;

    أرجع 0;
}

صحيح اصلي(فراغ)
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
        چاپ_کړه("%d: %d\n", i, j);
    }
    چاپ_کړه("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = حافظه_ورکړه(n * av_fifo_elem_اندازه(fifo));
    إذا (p == عدم) {
        fprintf(stderr, "failed to allocate memory.\n");
        وتل(1);
    }

    (فراغ) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    لكل(i = 0; i < n; ++i)
        چاپ_کړه("%d: %d\n", i, p[i]);

    توری_چاپ_کړه('\n');

    /* read data */
    لكل (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        چاپ_کړه(i == 0 ? "%d" : " %d", j);
    }
    چاپ_کړه("\n");

    /* fill data */
    لكل (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    لكل (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        چاپ_کړه("%d: %d\n", i, j);
    }
    توری_چاپ_کړه('\n');

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
        چاپ_کړه("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    تخم = av_get_random_تخم();

        AVLFG lfg;
        صحيح ret;

        av_lfg_init(&lfg, تخم);

        fifo = av_fifo_alloc2(1, حجم(بینښه), AV_FIFO_FLAG_AUTO_GROW);

        لكل (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            بینښه   منزل_process = av_lfg_get(&lfg) % nb_elems;

            s.منزل_process = منزل_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            إذا (ret < 0 || s.منزل_process || nb_elems != منزل_process) {
                چاپ_کړه("FIFO write fail; seed %"PRIu32"\n", تخم);
                أرجع 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            إذا (nb_elems > 1) {
                s.دننه_واټن     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.دننه_واټن;

                s.منزل_process = av_lfg_get(&lfg) % nb_elems;
                منزل_process   = s.منزل_process;

                ret = av_fifo_peek_منزل_cb(fifo, read_cb, &s, &nb_elems, s.دننه_واټن);
                إذا (ret < 0 || s.منزل_process || nb_elems != منزل_process) {
                    چاپ_کړه("FIFO peek fail; seed %"PRIu32"\n", تخم);
                    أرجع 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            منزل_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.منزل_process = منزل_process;
            s.دننه_واټن     = 0;

            ret = av_fifo_read_منزل_cb(fifo, read_cb, &s, &nb_elems);
            إذا (ret < 0 || s.منزل_process || منزل_process != nb_elems) {
                چاپ_کړه("FIFO read fail; seed %"PRIu32"\n", تخم);
                أرجع 1;
            }
            s.read_idx += s.دننه_واټن;
        }
    }

    av_fifo_freep2(&fifo);
    حرر(p);

    أرجع 0;
}
