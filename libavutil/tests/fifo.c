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
    بیعلامت صحيح read_idx;
    بیعلامت صحيح write_idx;
    بیعلامت صحيح مقصد_process;
    بیعلامت صحيح جابه_جایی;
} CBState;

ساكن صحيح read_cb(فراغ *opaque, فراغ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    بیعلامت *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->مقصد_process);

    لكل (بیعلامت i = 0; i < *nb_elems; i++)
        إذا (b[i] != s->read_idx + s->جابه_جایی + i) {
            چاپ_کن("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->جابه_جایی, i);
            أرجع AVERROR_BUG;
        }

    s->جابه_جایی     += *nb_elems;
    s->مقصد_process -= *nb_elems;

    أرجع 0;
}

ساكن صحيح write_cb(فراغ *opaque, فراغ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    بیعلامت *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->مقصد_process);

    لكل (بیعلامت i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->مقصد_process -= *nb_elems;

    أرجع 0;
}

صحيح اصلی(فراغ)
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
        چاپ_کن("%d: %d\n", i, j);
    }
    چاپ_کن("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = حافظه_بده(n * av_fifo_elem_اندازه(fifo));
    إذا (p == عدم) {
        fprintf(stderr, "failed to allocate memory.\n");
        خروج(1);
    }

    (فراغ) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    لكل(i = 0; i < n; ++i)
        چاپ_کن("%d: %d\n", i, p[i]);

    حرف_چاپ_کن('\n');

    /* read data */
    لكل (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        چاپ_کن(i == 0 ? "%d" : " %d", j);
    }
    چاپ_کن("\n");

    /* fill data */
    لكل (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    لكل (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        چاپ_کن("%d: %d\n", i, j);
    }
    حرف_چاپ_کن('\n');

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
        چاپ_کن("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    دانه = av_get_random_دانه();

        AVLFG lfg;
        صحيح ret;

        av_lfg_init(&lfg, دانه);

        fifo = av_fifo_alloc2(1, حجم(بیعلامت), AV_FIFO_FLAG_AUTO_GROW);

        لكل (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            بیعلامت   مقصد_process = av_lfg_get(&lfg) % nb_elems;

            s.مقصد_process = مقصد_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            إذا (ret < 0 || s.مقصد_process || nb_elems != مقصد_process) {
                چاپ_کن("FIFO write fail; seed %"PRIu32"\n", دانه);
                أرجع 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            إذا (nb_elems > 1) {
                s.جابه_جایی     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.جابه_جایی;

                s.مقصد_process = av_lfg_get(&lfg) % nb_elems;
                مقصد_process   = s.مقصد_process;

                ret = av_fifo_peek_مقصد_cb(fifo, read_cb, &s, &nb_elems, s.جابه_جایی);
                إذا (ret < 0 || s.مقصد_process || nb_elems != مقصد_process) {
                    چاپ_کن("FIFO peek fail; seed %"PRIu32"\n", دانه);
                    أرجع 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            مقصد_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.مقصد_process = مقصد_process;
            s.جابه_جایی     = 0;

            ret = av_fifo_read_مقصد_cb(fifo, read_cb, &s, &nb_elems);
            إذا (ret < 0 || s.مقصد_process || مقصد_process != nb_elems) {
                چاپ_کن("FIFO read fail; seed %"PRIu32"\n", دانه);
                أرجع 1;
            }
            s.read_idx += s.جابه_جایی;
        }
    }

    av_fifo_freep2(&fifo);
    حرر(p);

    أرجع 0;
}
