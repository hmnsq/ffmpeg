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
#define AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

ಸಂರಚನಾ AVFifo {
    uint8_t *buffer;

    size_t elem_size, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    ಪೂರ್ಣಾಙ್ಕ    is_empty;

    unsigned ಪೂರ್ಣಾಙ್ಕ flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_size,
                       unsigned ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVFifo *f;
    ಶೂನ್ಯ *buffer = ರಿಕ್ತ;

    ಯದಿ (!elem_size)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಯದಿ (nb_elems) {
        buffer = av_realloc_array(ರಿಕ್ತ, nb_elems, elem_size);
        ಯದಿ (!buffer)
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    f = av_mallocz(ಪರಿಮಾಣ(*f));
    ಯದಿ (!f) {
        av_free(buffer);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    ಪ್ರತ್ಯಾಗಮ f;
}

ಶೂನ್ಯ av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(ಧ್ರುವ AVFifo *f)
{
    ಪ್ರತ್ಯಾಗಮ f->elem_size;
}

size_t av_fifo_can_read(ಧ್ರುವ AVFifo *f)
{
    ಯದಿ (f->offset_w <= f->offset_r && !f->is_empty)
        ಪ್ರತ್ಯಾಗಮ f->nb_elems - f->offset_r + f->offset_w;
    ಪ್ರತ್ಯಾಗಮ f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(ಧ್ರುವ AVFifo *f)
{
    ಪ್ರತ್ಯಾಗಮ f->nb_elems - av_fifo_can_read(f);
}

ಪೂರ್ಣಾಙ್ಕ av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    ಯದಿ (inc > SIZE_MAX - f->nb_elems)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    ಯದಿ (!tmp)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    ಯದಿ (f->offset_w <= f->offset_r && !f->is_empty) {
        ಧ್ರುವ size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        ಯದಿ (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } ಅನ್ಯಥಾ
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ fifo_check_space(AVFifo *f, size_t to_write)
{
    ಧ್ರುವ size_t can_write = av_fifo_can_write(f);
    ಧ್ರುವ size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    ಯದಿ (!need_grow)
        ಪ್ರತ್ಯಾಗಮ 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    ಯದಿ ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ಧ್ರುವ size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        ಪ್ರತ್ಯಾಗಮ av_fifo_grow2(f, inc);
    }

    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSPC);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ fifo_write_common(AVFifo *f, ಧ್ರುವ uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, ಶೂನ್ಯ *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    ಪೂರ್ಣಾಙ್ಕ         ret = 0;

    ret = fifo_check_space(f, to_write);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    offset_w = f->offset_w;

    ಯಾವತ್ (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        ಯದಿ (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            ಯದಿ (ret < 0 || len == 0)
                ಭಙ್ಗ;
        } ಅನ್ಯಥಾ {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        ಯದಿ (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    ಯದಿ (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_fifo_write(AVFifo *f, ಧ್ರುವ ಶೂನ್ಯ *buf, size_t nb_elems)
{
    ಪ್ರತ್ಯಾಗಮ fifo_write_common(f, buf, &nb_elems, ರಿಕ್ತ, ರಿಕ್ತ);
}

ಪೂರ್ಣಾಙ್ಕ av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          ಶೂನ್ಯ *opaque, size_t *nb_elems)
{
    ಪ್ರತ್ಯಾಗಮ fifo_write_common(f, ರಿಕ್ತ, nb_elems, read_cb, opaque);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ fifo_peek_common(ಧ್ರುವ AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, ಶೂನ್ಯ *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    ಪೂರ್ಣಾಙ್ಕ         ret = 0;

    ಯದಿ (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಯದಿ (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    ಅನ್ಯಥಾ
        offset_r += offset;

    ಯಾವತ್ (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        ಯದಿ (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            ಯದಿ (ret < 0 || len == 0)
                ಭಙ್ಗ;
        } ಅನ್ಯಥಾ {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        ಯದಿ (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_fifo_read(AVFifo *f, ಶೂನ್ಯ *buf, size_t nb_elems)
{
    ಪೂರ್ಣಾಙ್ಕ ret = fifo_peek_common(f, buf, &nb_elems, 0, ರಿಕ್ತ, ರಿಕ್ತ);
    av_fifo_drain2(f, nb_elems);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       ಶೂನ್ಯ *opaque, size_t *nb_elems)
{
    ಪೂರ್ಣಾಙ್ಕ ret = fifo_peek_common(f, ರಿಕ್ತ, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_fifo_peek(ಧ್ರುವ AVFifo *f, ಶೂನ್ಯ *buf, size_t nb_elems, size_t offset)
{
    ಪ್ರತ್ಯಾಗಮ fifo_peek_common(f, buf, &nb_elems, offset, ರಿಕ್ತ, ರಿಕ್ತ);
}

ಪೂರ್ಣಾಙ್ಕ av_fifo_peek_to_cb(ಧ್ರುವ AVFifo *f, AVFifoCB write_cb, ಶೂನ್ಯ *opaque,
                       size_t *nb_elems, size_t offset)
{
    ಪ್ರತ್ಯಾಗಮ fifo_peek_common(f, ರಿಕ್ತ, nb_elems, offset, write_cb, opaque);
}

ಶೂನ್ಯ av_fifo_drain2(AVFifo *f, size_t size)
{
    ಧ್ರುವ size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    ಯದಿ (cur_size == size)
        f->is_empty = 1;

    ಯದಿ (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    ಅನ್ಯಥಾ
        f->offset_r += size;
}

ಶೂನ್ಯ av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

ಶೂನ್ಯ av_fifo_freep2(AVFifo **f)
{
    ಯದಿ (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
