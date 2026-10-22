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

प्रकारव्याख्या संरचना CBState {
    अचिन्हित पूर्णांक read_idx;
    अचिन्हित पूर्णांक write_idx;
    अचिन्हित पूर्णांक to_process;
    अचिन्हित पूर्णांक offset;
} CBState;

स्थिर पूर्णांक read_cb(शून्य *opaque, शून्य *buf, माप_प्रकार *nb_elems)
{
    CBState  *s = opaque;
    अचिन्हित *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->to_process);

    साठी (अचिन्हित i = 0; i < *nb_elems; i++)
        जर (b[i] != s->read_idx + s->offset + i) {
            म_लिखो("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->offset, i);
            परत AVERROR_BUG;
        }

    s->offset     += *nb_elems;
    s->to_process -= *nb_elems;

    परत 0;
}

स्थिर पूर्णांक write_cb(शून्य *opaque, शून्य *buf, माप_प्रकार *nb_elems)
{
    CBState  *s = opaque;
    अचिन्हित *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->to_process);

    साठी (अचिन्हित i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->to_process -= *nb_elems;

    परत 0;
}

पूर्णांक main(शून्य)
{
    /* create a FIFO buffer */
    AVFifo *fifo = av_fifo_alloc2(13, आकार(पूर्णांक), 0);
    पूर्णांक i, j, n, *p;

    /* fill data */
    साठी (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    साठी (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        म_लिखो("%d: %d\n", i, j);
    }
    म_लिखो("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = दो_स्मृति(n * av_fifo_elem_size(fifo));
    जर (p == रिक्त) {
        ख_लिखो(मानक_त्रुटि, "failed to allocate memory.\n");
        निकास(1);
    }

    (शून्य) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    साठी(i = 0; i < n; ++i)
        म_लिखो("%d: %d\n", i, p[i]);

    अक्षर_दो('\n');

    /* read data */
    साठी (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        म_लिखो(i == 0 ? "%d" : " %d", j);
    }
    म_लिखो("\n");

    /* fill data */
    साठी (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    साठी (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        म_लिखो("%d: %d\n", i, j);
    }
    अक्षर_दो('\n');

    /* test fifo_grow */
    (शून्य) av_fifo_grow2(fifo, 15);

    /* fill data */
    n = av_fifo_can_read(fifo);
    साठी (i = n; av_fifo_can_write(fifo); ++i)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    साठी (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        म_लिखो("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    seed = av_get_random_seed();

        AVLFG lfg;
        पूर्णांक ret;

        av_lfg_init(&lfg, seed);

        fifo = av_fifo_alloc2(1, आकार(अचिन्हित), AV_FIFO_FLAG_AUTO_GROW);

        साठी (i = 0; i < 32; i++) {
            माप_प्रकार       nb_elems = 16;
            अचिन्हित   to_process = av_lfg_get(&lfg) % nb_elems;

            s.to_process = to_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            जर (ret < 0 || s.to_process || nb_elems != to_process) {
                म_लिखो("FIFO write fail; seed %"PRIu32"\n", seed);
                परत 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            जर (nb_elems > 1) {
                s.offset     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.offset;

                s.to_process = av_lfg_get(&lfg) % nb_elems;
                to_process   = s.to_process;

                ret = av_fifo_peek_to_cb(fifo, read_cb, &s, &nb_elems, s.offset);
                जर (ret < 0 || s.to_process || nb_elems != to_process) {
                    म_लिखो("FIFO peek fail; seed %"PRIu32"\n", seed);
                    परत 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            to_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.to_process = to_process;
            s.offset     = 0;

            ret = av_fifo_read_to_cb(fifo, read_cb, &s, &nb_elems);
            जर (ret < 0 || s.to_process || to_process != nb_elems) {
                म_लिखो("FIFO read fail; seed %"PRIu32"\n", seed);
                परत 1;
            }
            s.read_idx += s.offset;
        }
    }

    av_fifo_freep2(&fifo);
    मुक्त(p);

    परत 0;
}
