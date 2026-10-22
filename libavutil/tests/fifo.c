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

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ "libavutil/common.h"
#అన్తర్భావ "libavutil/fifo.h"
#అన్తర్భావ "libavutil/lfg.h"
#అన్తర్భావ "libavutil/random_seed.h"

రకనిర్వచనం నిర్మాణం CBState {
    గుర్తులేని పూర్ణాంకం read_idx;
    గుర్తులేని పూర్ణాంకం write_idx;
    గుర్తులేని పూర్ణాంకం గమ్యం_process;
    గుర్తులేని పూర్ణాంకం స్థానభ్రంశం;
} CBState;

స్థిర పూర్ణాంకం read_cb(శూన్య *opaque, శూన్య *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    గుర్తులేని *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->గమ్యం_process);

    కొరకు (గుర్తులేని i = 0; i < *nb_elems; i++)
        ఒకవేళ (b[i] != s->read_idx + s->స్థానభ్రంశం + i) {
            రాయి("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->స్థానభ్రంశం, i);
            తిరిగి AVERROR_BUG;
        }

    s->స్థానభ్రంశం     += *nb_elems;
    s->గమ్యం_process -= *nb_elems;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం write_cb(శూన్య *opaque, శూన్య *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    గుర్తులేని *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->గమ్యం_process);

    కొరకు (గుర్తులేని i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->గమ్యం_process -= *nb_elems;

    తిరిగి 0;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    /* create a FIFO buffer */
    AVFifo *fifo = av_fifo_alloc2(13, పరిమాణం(పూర్ణాంకం), 0);
    పూర్ణాంకం i, j, n, *p;

    /* fill data */
    కొరకు (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    కొరకు (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        రాయి("%d: %d\n", i, j);
    }
    రాయి("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = జ్ఞాపకం_ఇవ్వు(n * av_fifo_elem_కొలత(fifo));
    ఒకవేళ (p == ఖాళీ) {
        fprintf(stderr, "failed to allocate memory.\n");
        నిష్క్రమించు(1);
    }

    (శూన్య) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    కొరకు(i = 0; i < n; ++i)
        రాయి("%d: %d\n", i, p[i]);

    అక్షరం_రాయి('\n');

    /* read data */
    కొరకు (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        రాయి(i == 0 ? "%d" : " %d", j);
    }
    రాయి("\n");

    /* fill data */
    కొరకు (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    కొరకు (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        రాయి("%d: %d\n", i, j);
    }
    అక్షరం_రాయి('\n');

    /* test fifo_grow */
    (శూన్య) av_fifo_grow2(fifo, 15);

    /* fill data */
    n = av_fifo_can_read(fifo);
    కొరకు (i = n; av_fifo_can_write(fifo); ++i)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    కొరకు (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        రాయి("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    విత్తనం = av_get_random_విత్తనం();

        AVLFG lfg;
        పూర్ణాంకం ret;

        av_lfg_init(&lfg, విత్తనం);

        fifo = av_fifo_alloc2(1, పరిమాణం(గుర్తులేని), AV_FIFO_FLAG_AUTO_GROW);

        కొరకు (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            గుర్తులేని   గమ్యం_process = av_lfg_get(&lfg) % nb_elems;

            s.గమ్యం_process = గమ్యం_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            ఒకవేళ (ret < 0 || s.గమ్యం_process || nb_elems != గమ్యం_process) {
                రాయి("FIFO write fail; seed %"PRIu32"\n", విత్తనం);
                తిరిగి 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            ఒకవేళ (nb_elems > 1) {
                s.స్థానభ్రంశం     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.స్థానభ్రంశం;

                s.గమ్యం_process = av_lfg_get(&lfg) % nb_elems;
                గమ్యం_process   = s.గమ్యం_process;

                ret = av_fifo_peek_గమ్యం_cb(fifo, read_cb, &s, &nb_elems, s.స్థానభ్రంశం);
                ఒకవేళ (ret < 0 || s.గమ్యం_process || nb_elems != గమ్యం_process) {
                    రాయి("FIFO peek fail; seed %"PRIu32"\n", విత్తనం);
                    తిరిగి 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            గమ్యం_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.గమ్యం_process = గమ్యం_process;
            s.స్థానభ్రంశం     = 0;

            ret = av_fifo_read_గమ్యం_cb(fifo, read_cb, &s, &nb_elems);
            ఒకవేళ (ret < 0 || s.గమ్యం_process || గమ్యం_process != nb_elems) {
                రాయి("FIFO read fail; seed %"PRIu32"\n", విత్తనం);
                తిరిగి 1;
            }
            s.read_idx += s.స్థానభ్రంశం;
        }
    }

    av_fifo_freep2(&fifo);
    విడుదల(p);

    తిరిగి 0;
}
