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

    ܐܢ (!elem_size)
        ܦܢܐ عدم;

    ܐܢ (nb_elems) {
        buffer = av_realloc_array(عدم, nb_elems, elem_size);
        ܐܢ (!buffer)
            ܦܢܐ عدم;
    }
    f = av_mallocz(حجم(*f));
    ܐܢ (!f) {
        av_free(buffer);
        ܦܢܐ عدم;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    ܦܢܐ f;
}

فراغ av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(ثابت AVFifo *f)
{
    ܦܢܐ f->elem_size;
}

size_t av_fifo_can_read(ثابت AVFifo *f)
{
    ܐܢ (f->offset_w <= f->offset_r && !f->is_empty)
        ܦܢܐ f->nb_elems - f->offset_r + f->offset_w;
    ܦܢܐ f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(ثابت AVFifo *f)
{
    ܦܢܐ f->nb_elems - av_fifo_can_read(f);
}

صحيح av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    ܐܢ (inc > SIZE_MAX - f->nb_elems)
        ܦܢܐ AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    ܐܢ (!tmp)
        ܦܢܐ AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    ܐܢ (f->offset_w <= f->offset_r && !f->is_empty) {
        ثابت size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        ܐܢ (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } ܐܚܪܢܐ
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    ܦܢܐ 0;
}

ساكن صحيح fifo_check_space(AVFifo *f, size_t to_write)
{
    ثابت size_t can_write = av_fifo_can_write(f);
    ثابت size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    ܐܢ (!need_grow)
        ܦܢܐ 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    ܐܢ ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ثابت size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        ܦܢܐ av_fifo_grow2(f, inc);
    }

    ܦܢܐ AVERROR(ENOSPC);
}

ساكن صحيح fifo_write_common(AVFifo *f, ثابت uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, فراغ *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    صحيح         ret = 0;

    ret = fifo_check_space(f, to_write);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    offset_w = f->offset_w;

    ܟܡܐ (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        ܐܢ (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            ܐܢ (ret < 0 || len == 0)
                اكسر;
        } ܐܚܪܢܐ {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        ܐܢ (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    ܐܢ (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    ܦܢܐ ret;
}

صحيح av_fifo_write(AVFifo *f, ثابت فراغ *buf, size_t nb_elems)
{
    ܦܢܐ fifo_write_common(f, buf, &nb_elems, عدم, عدم);
}

صحيح av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          فراغ *opaque, size_t *nb_elems)
{
    ܦܢܐ fifo_write_common(f, عدم, nb_elems, read_cb, opaque);
}

ساكن صحيح fifo_peek_common(ثابت AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, فراغ *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    صحيح         ret = 0;

    ܐܢ (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        ܦܢܐ AVERROR(EINVAL);
    }

    ܐܢ (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    ܐܚܪܢܐ
        offset_r += offset;

    ܟܡܐ (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        ܐܢ (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            ܐܢ (ret < 0 || len == 0)
                اكسر;
        } ܐܚܪܢܐ {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        ܐܢ (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    ܦܢܐ ret;
}

صحيح av_fifo_read(AVFifo *f, فراغ *buf, size_t nb_elems)
{
    صحيح ret = fifo_peek_common(f, buf, &nb_elems, 0, عدم, عدم);
    av_fifo_drain2(f, nb_elems);
    ܦܢܐ ret;
}

صحيح av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       فراغ *opaque, size_t *nb_elems)
{
    صحيح ret = fifo_peek_common(f, عدم, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    ܦܢܐ ret;
}

صحيح av_fifo_peek(ثابت AVFifo *f, فراغ *buf, size_t nb_elems, size_t offset)
{
    ܦܢܐ fifo_peek_common(f, buf, &nb_elems, offset, عدم, عدم);
}

صحيح av_fifo_peek_to_cb(ثابت AVFifo *f, AVFifoCB write_cb, فراغ *opaque,
                       size_t *nb_elems, size_t offset)
{
    ܦܢܐ fifo_peek_common(f, عدم, nb_elems, offset, write_cb, opaque);
}

فراغ av_fifo_drain2(AVFifo *f, size_t size)
{
    ثابت size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    ܐܢ (cur_size == size)
        f->is_empty = 1;

    ܐܢ (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    ܐܚܪܢܐ
        f->offset_r += size;
}

فراغ av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

فراغ av_fifo_freep2(AVFifo **f)
{
    ܐܢ (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
