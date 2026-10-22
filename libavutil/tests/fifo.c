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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ "libavutil/common.h"
#ಅನ್ತರ್ಭಾವ "libavutil/fifo.h"
#ಅನ್ತರ್ಭಾವ "libavutil/lfg.h"
#ಅನ್ತರ್ಭಾವ "libavutil/random_seed.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ CBState {
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ read_idx;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_idx;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಗಮ್ಯ_process;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ;
} CBState;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ read_cb(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    ಚಿಹ್ನೆರಹಿತ *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->ಗಮ್ಯ_process);

    ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < *nb_elems; i++)
        ಆದರೆ (b[i] != s->read_idx + s->ಸ್ಥಾನಾಂತರ + i) {
            ಬರೆ("Mismatch at idx %u offset %u i %u\n",
                   s->read_idx, s->ಸ್ಥಾನಾಂತರ, i);
            ಹಿಂತಿರುಗಿ AVERROR_BUG;
        }

    s->ಸ್ಥಾನಾಂತರ     += *nb_elems;
    s->ಗಮ್ಯ_process -= *nb_elems;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ write_cb(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *buf, size_t *nb_elems)
{
    CBState  *s = opaque;
    ಚಿಹ್ನೆರಹಿತ *b = buf;

    *nb_elems = FFMIN(*nb_elems, s->ಗಮ್ಯ_process);

    ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < *nb_elems; i++)
        b[i] = s->write_idx + i;

    s->write_idx  += *nb_elems;
    s->ಗಮ್ಯ_process -= *nb_elems;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    /* create a FIFO buffer */
    AVFifo *fifo = av_fifo_alloc2(13, ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ), 0);
    ಪೂರ್ಣಾಂಕ i, j, n, *p;

    /* fill data */
    ಗಾಗಿ (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    ಗಾಗಿ (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        ಬರೆ("%d: %d\n", i, j);
    }
    ಬರೆ("\n");

    /* generic peek at FIFO */

    n = av_fifo_can_read(fifo);
    p = ಸ್ಮರಣೆ_ಕೊಡು(n * av_fifo_elem_ಗಾತ್ರ(fifo));
    ಆದರೆ (p == ಖಾಲಿ) {
        fprintf(stderr, "failed to allocate memory.\n");
        ನಿರ್ಗಮಿಸು(1);
    }

    (ಶೂನ್ಯ) av_fifo_peek(fifo, p, n, 0);

    /* read data at p */
    ಗಾಗಿ(i = 0; i < n; ++i)
        ಬರೆ("%d: %d\n", i, p[i]);

    ಅಕ್ಷರ_ಬರೆ('\n');

    /* read data */
    ಗಾಗಿ (i = 0; av_fifo_can_read(fifo); i++) {
        av_fifo_read(fifo, &j, 1);
        ಬರೆ(i == 0 ? "%d" : " %d", j);
    }
    ಬರೆ("\n");

    /* fill data */
    ಗಾಗಿ (i = 0; av_fifo_can_write(fifo); i++)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    ಗಾಗಿ (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        ಬರೆ("%d: %d\n", i, j);
    }
    ಅಕ್ಷರ_ಬರೆ('\n');

    /* test fifo_grow */
    (ಶೂನ್ಯ) av_fifo_grow2(fifo, 15);

    /* fill data */
    n = av_fifo_can_read(fifo);
    ಗಾಗಿ (i = n; av_fifo_can_write(fifo); ++i)
        av_fifo_write(fifo, &i, 1);

    /* peek_at at FIFO */
    n = av_fifo_can_read(fifo);
    ಗಾಗಿ (i = 0; i < n; i++) {
        av_fifo_peek(fifo, &j, 1, i);
        ಬರೆ("%d: %d\n", i, j);
    }

    av_fifo_freep2(&fifo);

    /* test randomly-sized write/read/peek with a callback */
    {
        CBState        s = { 0 };
        uint32_t    ಬೀಜ = av_get_random_ಬೀಜ();

        AVLFG lfg;
        ಪೂರ್ಣಾಂಕ ret;

        av_lfg_init(&lfg, ಬೀಜ);

        fifo = av_fifo_alloc2(1, ಗಾತ್ರ(ಚಿಹ್ನೆರಹಿತ), AV_FIFO_FLAG_AUTO_GROW);

        ಗಾಗಿ (i = 0; i < 32; i++) {
            size_t       nb_elems = 16;
            ಚಿಹ್ನೆರಹಿತ   ಗಮ್ಯ_process = av_lfg_get(&lfg) % nb_elems;

            s.ಗಮ್ಯ_process = ಗಮ್ಯ_process;

            ret = av_fifo_write_from_cb(fifo, write_cb, &s, &nb_elems);
            ಆದರೆ (ret < 0 || s.ಗಮ್ಯ_process || nb_elems != ಗಮ್ಯ_process) {
                ಬರೆ("FIFO write fail; seed %"PRIu32"\n", ಬೀಜ);
                ಹಿಂತಿರುಗಿ 1;
            }

            nb_elems = av_fifo_can_read(fifo);
            ಆದರೆ (nb_elems > 1) {
                s.ಸ್ಥಾನಾಂತರ     = av_lfg_get(&lfg) % (nb_elems - 1);
                nb_elems    -= s.ಸ್ಥಾನಾಂತರ;

                s.ಗಮ್ಯ_process = av_lfg_get(&lfg) % nb_elems;
                ಗಮ್ಯ_process   = s.ಗಮ್ಯ_process;

                ret = av_fifo_peek_ಗಮ್ಯ_cb(fifo, read_cb, &s, &nb_elems, s.ಸ್ಥಾನಾಂತರ);
                ಆದರೆ (ret < 0 || s.ಗಮ್ಯ_process || nb_elems != ಗಮ್ಯ_process) {
                    ಬರೆ("FIFO peek fail; seed %"PRIu32"\n", ಬೀಜ);
                    ಹಿಂತಿರುಗಿ 1;
                }
            }

            nb_elems     = av_fifo_can_read(fifo);
            ಗಮ್ಯ_process   = nb_elems ? av_lfg_get(&lfg) % nb_elems : 0;
            s.ಗಮ್ಯ_process = ಗಮ್ಯ_process;
            s.ಸ್ಥಾನಾಂತರ     = 0;

            ret = av_fifo_read_ಗಮ್ಯ_cb(fifo, read_cb, &s, &nb_elems);
            ಆದರೆ (ret < 0 || s.ಗಮ್ಯ_process || ಗಮ್ಯ_process != nb_elems) {
                ಬರೆ("FIFO read fail; seed %"PRIu32"\n", ಬೀಜ);
                ಹಿಂತಿರುಗಿ 1;
            }
            s.read_idx += s.ಸ್ಥಾನಾಂತರ;
        }
    }

    av_fifo_freep2(&fifo);
    ಬಿಡುಗಡೆ(p);

    ಹಿಂತಿರುಗಿ 0;
}
