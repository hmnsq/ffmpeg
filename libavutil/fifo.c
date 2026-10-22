/*
 * a very simple circular buffer FIFO implementation
 * Copyright (c) 2000, 2001, 2002 Fabrice Bellard
 * Copyright (c) 2006 Roman Shaposhnik
 *
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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "fifo.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

// by default the FIFO can be auto-grown to 1MB
#ವ್ಯಾಖ್ಯಾನಿಸು AUTO_GROW_DEFAULT_ಬೈಟುಗಳು (1024 * 1024)

ರಚನೆ AVFifo {
    uint8_t *ಬಫರ್;

    size_t elem_ಗಾತ್ರ, nb_elems;
    size_t ಸ್ಥಾನಾಂತರ_r, ಸ್ಥಾನಾಂತರ_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    ಪೂರ್ಣಾಂಕ    is_ಖಾಲಿಗಳು;

    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flags;
    size_t       auto_grow_ಎಲ್ಲೆ;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_ಗಾತ್ರ,
                       ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flags)
{
    AVFifo *f;
    ಶೂನ್ಯ *ಬಫರ್ = ಖಾಲಿ;

    ಆದರೆ (!elem_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (nb_elems) {
        ಬಫರ್ = av_realloc_array(ಖಾಲಿ, nb_elems, elem_ಗಾತ್ರ);
        ಆದರೆ (!ಬಫರ್)
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    f = av_mallocz(ಗಾತ್ರ(*f));
    ಆದರೆ (!f) {
        av_free(ಬಫರ್);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    f->ಬಫರ್    = ಬಫರ್;
    f->nb_elems  = nb_elems;
    f->elem_ಗಾತ್ರ = elem_ಗಾತ್ರ;
    f->is_ಖಾಲಿಗಳು  = 1;

    f->flags           = flags;
    f->auto_grow_ಎಲ್ಲೆ = FFMAX(AUTO_GROW_DEFAULT_ಬೈಟುಗಳು / elem_ಗಾತ್ರ, 1);

    ಹಿಂತಿರುಗಿ f;
}

ಶೂನ್ಯ av_fifo_auto_grow_ಎಲ್ಲೆ(AVFifo *f, size_t max_elems)
{
    f->auto_grow_ಎಲ್ಲೆ = max_elems;
}

size_t av_fifo_elem_ಗಾತ್ರ(ಸ್ಥಿರಾಂಕ AVFifo *f)
{
    ಹಿಂತಿರುಗಿ f->elem_ಗಾತ್ರ;
}

size_t av_fifo_can_read(ಸ್ಥಿರಾಂಕ AVFifo *f)
{
    ಆದರೆ (f->ಸ್ಥಾನಾಂತರ_w <= f->ಸ್ಥಾನಾಂತರ_r && !f->is_ಖಾಲಿಗಳು)
        ಹಿಂತಿರುಗಿ f->nb_elems - f->ಸ್ಥಾನಾಂತರ_r + f->ಸ್ಥಾನಾಂತರ_w;
    ಹಿಂತಿರುಗಿ f->ಸ್ಥಾನಾಂತರ_w - f->ಸ್ಥಾನಾಂತರ_r;
}

size_t av_fifo_can_write(ಸ್ಥಿರಾಂಕ AVFifo *f)
{
    ಹಿಂತಿರುಗಿ f->nb_elems - av_fifo_can_read(f);
}

ಪೂರ್ಣಾಂಕ av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    ಆದರೆ (inc > SIZE_MAX - f->nb_elems)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    tmp = av_realloc_array(f->ಬಫರ್, f->nb_elems + inc, f->elem_ಗಾತ್ರ);
    ಆದರೆ (!tmp)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    f->ಬಫರ್ = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    ಆದರೆ (f->ಸ್ಥಾನಾಂತರ_w <= f->ಸ್ಥಾನಾಂತರ_r && !f->is_ಖಾಲಿಗಳು) {
        ಸ್ಥಿರಾಂಕ size_t copy = FFMIN(inc, f->ಸ್ಥಾನಾಂತರ_w);
        ಸ್ಮರಣೆ_ನಕಲು(tmp + f->nb_elems * f->elem_ಗಾತ್ರ, tmp, copy * f->elem_ಗಾತ್ರ);
        ಆದರೆ (copy < f->ಸ್ಥಾನಾಂತರ_w) {
            memmove(tmp, tmp + copy * f->elem_ಗಾತ್ರ,
                    (f->ಸ್ಥಾನಾಂತರ_w - copy) * f->elem_ಗಾತ್ರ);
            f->ಸ್ಥಾನಾಂತರ_w -= copy;
        } ಇಲ್ಲದಿದ್ದರೆ
            f->ಸ್ಥಾನಾಂತರ_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ fifo_check_space(AVFifo *f, size_t ಗಮ್ಯ_write)
{
    ಸ್ಥಿರಾಂಕ size_t can_write = av_fifo_can_write(f);
    ಸ್ಥಿರಾಂಕ size_t need_grow = ಗಮ್ಯ_write > can_write ? ಗಮ್ಯ_write - can_write : 0;
    size_t can_grow;

    ಆದರೆ (!need_grow)
        ಹಿಂತಿರುಗಿ 0;

    can_grow = f->auto_grow_ಎಲ್ಲೆ > f->nb_elems ?
               f->auto_grow_ಎಲ್ಲೆ - f->nb_elems : 0;
    ಆದರೆ ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ಸ್ಥಿರಾಂಕ size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        ಹಿಂತಿರುಗಿ av_fifo_grow2(f, inc);
    }

    ಹಿಂತಿರುಗಿ AVERROR(ENOSPC);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ fifo_write_common(AVFifo *f, ಸ್ಥಿರಾಂಕ uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, ಶೂನ್ಯ *opaque)
{
    size_t ಗಮ್ಯ_write = *nb_elems;
    size_t ಸ್ಥಾನಾಂತರ_w;
    ಪೂರ್ಣಾಂಕ         ret = 0;

    ret = fifo_check_space(f, ಗಮ್ಯ_write);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಸ್ಥಾನಾಂತರ_w = f->ಸ್ಥಾನಾಂತರ_w;

    ಆಗ (ಗಮ್ಯ_write > 0) {
        size_t    len = FFMIN(f->nb_elems - ಸ್ಥಾನಾಂತರ_w, ಗಮ್ಯ_write);
        uint8_t *wptr = f->ಬಫರ್ + ಸ್ಥಾನಾಂತರ_w * f->elem_ಗಾತ್ರ;

        ಆದರೆ (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            ಆದರೆ (ret < 0 || len == 0)
                ನಿಲ್ಲಿಸು;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಸ್ಮರಣೆ_ನಕಲು(wptr, buf, len * f->elem_ಗಾತ್ರ);
            buf += len * f->elem_ಗಾತ್ರ;
        }
        ಸ್ಥಾನಾಂತರ_w += len;
        ಆದರೆ (ಸ್ಥಾನಾಂತರ_w >= f->nb_elems)
            ಸ್ಥಾನಾಂತರ_w = 0;
        ಗಮ್ಯ_write -= len;
    }
    f->ಸ್ಥಾನಾಂತರ_w = ಸ್ಥಾನಾಂತರ_w;

    ಆದರೆ (*nb_elems != ಗಮ್ಯ_write)
        f->is_ಖಾಲಿಗಳು = 0;
    *nb_elems -= ಗಮ್ಯ_write;

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_fifo_write(AVFifo *f, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *buf, size_t nb_elems)
{
    ಹಿಂತಿರುಗಿ fifo_write_common(f, buf, &nb_elems, ಖಾಲಿ, ಖಾಲಿ);
}

ಪೂರ್ಣಾಂಕ av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          ಶೂನ್ಯ *opaque, size_t *nb_elems)
{
    ಹಿಂತಿರುಗಿ fifo_write_common(f, ಖಾಲಿ, nb_elems, read_cb, opaque);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ fifo_peek_common(ಸ್ಥಿರಾಂಕ AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t ಸ್ಥಾನಾಂತರ, AVFifoCB write_cb, ಶೂನ್ಯ *opaque)
{
    size_t  ಗಮ್ಯ_read = *nb_elems;
    size_t ಸ್ಥಾನಾಂತರ_r = f->ಸ್ಥಾನಾಂತರ_r;
    size_t can_read = av_fifo_can_read(f);
    ಪೂರ್ಣಾಂಕ         ret = 0;

    ಆದರೆ (ಸ್ಥಾನಾಂತರ > can_read || ಗಮ್ಯ_read > can_read - ಸ್ಥಾನಾಂತರ) {
        *nb_elems = 0;
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ (ಸ್ಥಾನಾಂತರ_r >= f->nb_elems - ಸ್ಥಾನಾಂತರ)
        ಸ್ಥಾನಾಂತರ_r -= f->nb_elems - ಸ್ಥಾನಾಂತರ;
    ಇಲ್ಲದಿದ್ದರೆ
        ಸ್ಥಾನಾಂತರ_r += ಸ್ಥಾನಾಂತರ;

    ಆಗ (ಗಮ್ಯ_read > 0) {
        size_t    len = FFMIN(f->nb_elems - ಸ್ಥಾನಾಂತರ_r, ಗಮ್ಯ_read);
        uint8_t *rptr = f->ಬಫರ್ + ಸ್ಥಾನಾಂತರ_r * f->elem_ಗಾತ್ರ;

        ಆದರೆ (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            ಆದರೆ (ret < 0 || len == 0)
                ನಿಲ್ಲಿಸು;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಸ್ಮರಣೆ_ನಕಲು(buf, rptr, len * f->elem_ಗಾತ್ರ);
            buf += len * f->elem_ಗಾತ್ರ;
        }
        ಸ್ಥಾನಾಂತರ_r += len;
        ಆದರೆ (ಸ್ಥಾನಾಂತರ_r >= f->nb_elems)
            ಸ್ಥಾನಾಂತರ_r = 0;
        ಗಮ್ಯ_read -= len;
    }

    *nb_elems -= ಗಮ್ಯ_read;

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_fifo_read(AVFifo *f, ಶೂನ್ಯ *buf, size_t nb_elems)
{
    ಪೂರ್ಣಾಂಕ ret = fifo_peek_common(f, buf, &nb_elems, 0, ಖಾಲಿ, ಖಾಲಿ);
    av_fifo_drain2(f, nb_elems);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_fifo_read_ಗಮ್ಯ_cb(AVFifo *f, AVFifoCB write_cb,
                       ಶೂನ್ಯ *opaque, size_t *nb_elems)
{
    ಪೂರ್ಣಾಂಕ ret = fifo_peek_common(f, ಖಾಲಿ, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_fifo_peek(ಸ್ಥಿರಾಂಕ AVFifo *f, ಶೂನ್ಯ *buf, size_t nb_elems, size_t ಸ್ಥಾನಾಂತರ)
{
    ಹಿಂತಿರುಗಿ fifo_peek_common(f, buf, &nb_elems, ಸ್ಥಾನಾಂತರ, ಖಾಲಿ, ಖಾಲಿ);
}

ಪೂರ್ಣಾಂಕ av_fifo_peek_ಗಮ್ಯ_cb(ಸ್ಥಿರಾಂಕ AVFifo *f, AVFifoCB write_cb, ಶೂನ್ಯ *opaque,
                       size_t *nb_elems, size_t ಸ್ಥಾನಾಂತರ)
{
    ಹಿಂತಿರುಗಿ fifo_peek_common(f, ಖಾಲಿ, nb_elems, ಸ್ಥಾನಾಂತರ, write_cb, opaque);
}

ಶೂನ್ಯ av_fifo_drain2(AVFifo *f, size_t ಗಾತ್ರ_2)
{
    ಸ್ಥಿರಾಂಕ size_t cur_ಗಾತ್ರ = av_fifo_can_read(f);

    av_assert0(cur_ಗಾತ್ರ >= ಗಾತ್ರ_2);
    ಆದರೆ (cur_ಗಾತ್ರ == ಗಾತ್ರ_2)
        f->is_ಖಾಲಿಗಳು = 1;

    ಆದರೆ (f->ಸ್ಥಾನಾಂತರ_r >= f->nb_elems - ಗಾತ್ರ_2)
        f->ಸ್ಥಾನಾಂತರ_r -= f->nb_elems - ಗಾತ್ರ_2;
    ಇಲ್ಲದಿದ್ದರೆ
        f->ಸ್ಥಾನಾಂತರ_r += ಗಾತ್ರ_2;
}

ಶೂನ್ಯ av_fifo_reset2(AVFifo *f)
{
    f->ಸ್ಥಾನಾಂತರ_r = f->ಸ್ಥಾನಾಂತರ_w = 0;
    f->is_ಖಾಲಿಗಳು = 1;
}

ಶೂನ್ಯ av_fifo_freep2(AVFifo **f)
{
    ಆದರೆ (*f) {
        av_freep(&(*f)->ಬಫರ್);
        av_freep(f);
    }
}
