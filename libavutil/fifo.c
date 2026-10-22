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

#ضمن <stdint.h>
#ضمن <string.h>

#ضمن "avassert.h"
#ضمن "error.h"
#ضمن "fifo.h"
#ضمن "macros.h"
#ضمن "mem.h"

// by default the FIFO can be auto-grown to 1MB
#define AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

بنية AVFifo {
    uint8_t *buffer;

    size_t elem_size, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    صحيح    is_empty;

    unsigned صحيح flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_size,
                       unsigned صحيح flags)
{
    AVFifo *f;
    فراغ *buffer = عدم;

    إذا (!elem_size)
        إرجاع عدم;

    إذا (nb_elems) {
        buffer = av_realloc_array(عدم, nb_elems, elem_size);
        إذا (!buffer)
            إرجاع عدم;
    }
    f = av_mallocz(حجم(*f));
    إذا (!f) {
        av_free(buffer);
        إرجاع عدم;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    إرجاع f;
}

فراغ av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(ثابت AVFifo *f)
{
    إرجاع f->elem_size;
}

size_t av_fifo_can_read(ثابت AVFifo *f)
{
    إذا (f->offset_w <= f->offset_r && !f->is_empty)
        إرجاع f->nb_elems - f->offset_r + f->offset_w;
    إرجاع f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(ثابت AVFifo *f)
{
    إرجاع f->nb_elems - av_fifo_can_read(f);
}

صحيح av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    إذا (inc > SIZE_MAX - f->nb_elems)
        إرجاع AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    إذا (!tmp)
        إرجاع AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    إذا (f->offset_w <= f->offset_r && !f->is_empty) {
        ثابت size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        إذا (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } وإلا
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    إرجاع 0;
}

ساكن صحيح fifo_check_space(AVFifo *f, size_t to_write)
{
    ثابت size_t can_write = av_fifo_can_write(f);
    ثابت size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    إذا (!need_grow)
        إرجاع 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    إذا ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ثابت size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        إرجاع av_fifo_grow2(f, inc);
    }

    إرجاع AVERROR(ENOSPC);
}

ساكن صحيح fifo_write_common(AVFifo *f, ثابت uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, فراغ *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    صحيح         ret = 0;

    ret = fifo_check_space(f, to_write);
    إذا (ret < 0)
        إرجاع ret;

    offset_w = f->offset_w;

    بينما (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        إذا (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            إذا (ret < 0 || len == 0)
                اكسر;
        } وإلا {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        إذا (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    إذا (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    إرجاع ret;
}

صحيح av_fifo_write(AVFifo *f, ثابت فراغ *buf, size_t nb_elems)
{
    إرجاع fifo_write_common(f, buf, &nb_elems, عدم, عدم);
}

صحيح av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          فراغ *opaque, size_t *nb_elems)
{
    إرجاع fifo_write_common(f, عدم, nb_elems, read_cb, opaque);
}

ساكن صحيح fifo_peek_common(ثابت AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, فراغ *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    صحيح         ret = 0;

    إذا (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        إرجاع AVERROR(EINVAL);
    }

    إذا (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    وإلا
        offset_r += offset;

    بينما (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        إذا (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            إذا (ret < 0 || len == 0)
                اكسر;
        } وإلا {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        إذا (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    إرجاع ret;
}

صحيح av_fifo_read(AVFifo *f, فراغ *buf, size_t nb_elems)
{
    صحيح ret = fifo_peek_common(f, buf, &nb_elems, 0, عدم, عدم);
    av_fifo_drain2(f, nb_elems);
    إرجاع ret;
}

صحيح av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       فراغ *opaque, size_t *nb_elems)
{
    صحيح ret = fifo_peek_common(f, عدم, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    إرجاع ret;
}

صحيح av_fifo_peek(ثابت AVFifo *f, فراغ *buf, size_t nb_elems, size_t offset)
{
    إرجاع fifo_peek_common(f, buf, &nb_elems, offset, عدم, عدم);
}

صحيح av_fifo_peek_to_cb(ثابت AVFifo *f, AVFifoCB write_cb, فراغ *opaque,
                       size_t *nb_elems, size_t offset)
{
    إرجاع fifo_peek_common(f, عدم, nb_elems, offset, write_cb, opaque);
}

فراغ av_fifo_drain2(AVFifo *f, size_t size)
{
    ثابت size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    إذا (cur_size == size)
        f->is_empty = 1;

    إذا (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    وإلا
        f->offset_r += size;
}

فراغ av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

فراغ av_fifo_freep2(AVFifo **f)
{
    إذا (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
