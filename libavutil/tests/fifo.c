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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव "libavutil/common.h"
#अन्तर्भाव "libavutil/fifo.h"
#अन्तर्भाव "libavutil/lfg.h"
#अन्तर्भाव "libavutil/random_seed.h"

प्रकारनिर्देश संरचना CBState {
    अचिह्नित पूर्णाङ्क read_idx;
    अचिह्नित पूर्णाङ्क write_idx;
    अचिह्नित पूर्णाङ्क गन्तव्यम्_process;
    अचिह्नित पूर्णाङ्क विस्थापनम्;
} CBState;

स्थिर पूर्णाङ्क read_cb(शून्य *opaque, शून्य *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    अचिह्नित *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->गन्तव्यम्_process);

    प्रति (अचिह्नित i = 0; i < *nb_elems; i++)
        यदि (b[i] != s->read_idx + s->विस्थापनम् + i) {
            प्रारूप_लिख("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->विस्थापनम्, i);
            प्रत्यागम AVERROR_BUG;
        }

    s->विस्थापनम्     += *nb_elems;
    s->गन्तव्यम्_process -= *nb_elems;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क write_cb(शून्य *opaque, शून्य *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    अचिह्नित *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->गन्तव्यम्_process);

    प्रति (अचिह्नित i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->गन्तव्यम्_process -= *nb_elems;

    प्रत्यागम 0;
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    /* create a FIFO buffer */
    AVFifo *fifo = av_fifo_alloc2(13, परिमाण(पूर्णाङ्क), 0);
    पूर्णाङ्क i, j, n, *p;

    /* fill data */
    प्रति (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    प्रति (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        प्रारूप_लिख("%d: %d\n", i, j);
    }
    प्रारूप_लिख("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = स्मृतिं_देहि(n * av_fifo_elem_आकार(fifo));
    यदि (p == रिक्त) {
        fprintf(stderr, "failed to allocate memory.\n");
        निर्गच्छ(1);
    }

    (शून्य) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    प्रति(i = 0; i < n; ++i)
        प्रारूप_लिख("%d: %d\n", i, p[i]);

    अक्षरं_लिख('\n');

    /* read data */
    प्रति (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        प्रारूप_लिख(i == 0 ? "%d" : " %d", j);
    }
    प्रारूप_लिख("\n");

    /* fill data */
    प्रति (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    प्रति (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        प्रारूप_लिख("%d: %d\n", i, j);
    }
    अक्षरं_लिख('\n');

    /* test fifo_grow */
    (शून्य) av_fifo_grow2(fifo, 15);

    /* fill data */
    n = av_fifo_can_read(fifo);
    प्रति (i = n; av_fifo_can_write(fifo); ++i)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    प्रति (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        प्रारूप_लिख("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    बीजम् = av_get_random_बीजम्();

        AVLFG lfg;
        पूर्णाङ्क ret;

        av_lfg_init(&lfg, बीजम्);

        fifo = av_fifo_alloc2(1, परिमाण(अचिह्नित), AV_FIFO_FLAG_AUTO_GROW);

        प्रति (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            अचिह्नित   गन्तव्यम्_process = av_lfg_get(&lfg) % nb_elems;

            s.गन्तव्यम्_process = गन्तव्यम्_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            यदि (ret < 0 || s.गन्तव्यम्_process || nb_elems != गन्तव्यम्_process) {
                प्रारूप_लिख("FIFO write fail; seed %"PRIu32"\n", बीजम्);
                प्रत्यागम 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            यदि (nb_elems > 1) {
                s.विस्थापनम्     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.विस्थापनम्;

                s.गन्तव्यम्_process = av_lfg_get(&lfg) % nb_elems;
                गन्तव्यम्_process   = s.गन्तव्यम्_process;

                ret = av_fifo_peek_गन्तव्यम्_cb(fifo, read_cb, &s, &nb_elems, s.विस्थापनम्);
                यदि (ret < 0 || s.गन्तव्यम्_process || nb_elems != गन्तव्यम्_process) {
                    प्रारूप_लिख("FIFO peek fail; seed %"PRIu32"\n", बीजम्);
                    प्रत्यागम 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            गन्तव्यम्_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.गन्तव्यम्_process = गन्तव्यम्_process;
            s.विस्थापनम्     = 0;

            ret = av_fifo_read_गन्तव्यम्_cb(fifo, read_cb, &s, &nb_elems);
            यदि (ret < 0 || s.गन्तव्यम्_process || गन्तव्यम्_process != nb_elems) {
                प्रारूप_लिख("FIFO read fail; seed %"PRIu32"\n", बीजम्);
                प्रत्यागम 1;
            }
            s.read_idx += s.विस्थापनम्;
        }
    }

    av_fifo_freep2(&fifo);
    मुक्त(p);

    प्रत्यागम 0;
}
