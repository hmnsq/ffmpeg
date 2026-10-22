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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "fifo.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"

// by default the FIFO can be auto-grown to 1MB
#define AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

সংরচনা AVFifo {
    uint8_t *buffer;

    size_t elem_size, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    পূর্ণাঙ্ক    is_empty;

    unsigned পূর্ণাঙ্ক flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_size,
                       unsigned পূর্ণাঙ্ক flags)
{
    AVFifo *f;
    শূন্য *buffer = রিক্ত;

    যদি (!elem_size)
        প্রত্যাগম রিক্ত;

    যদি (nb_elems) {
        buffer = av_realloc_array(রিক্ত, nb_elems, elem_size);
        যদি (!buffer)
            প্রত্যাগম রিক্ত;
    }
    f = av_mallocz(পরিমাণ(*f));
    যদি (!f) {
        av_free(buffer);
        প্রত্যাগম রিক্ত;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    প্রত্যাগম f;
}

শূন্য av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(ধ্রুব AVFifo *f)
{
    প্রত্যাগম f->elem_size;
}

size_t av_fifo_can_read(ধ্রুব AVFifo *f)
{
    যদি (f->offset_w <= f->offset_r && !f->is_empty)
        প্রত্যাগম f->nb_elems - f->offset_r + f->offset_w;
    প্রত্যাগম f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(ধ্রুব AVFifo *f)
{
    প্রত্যাগম f->nb_elems - av_fifo_can_read(f);
}

পূর্ণাঙ্ক av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    যদি (inc > SIZE_MAX - f->nb_elems)
        প্রত্যাগম AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    যদি (!tmp)
        প্রত্যাগম AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    যদি (f->offset_w <= f->offset_r && !f->is_empty) {
        ধ্রুব size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        যদি (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } অন্যথা
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক fifo_check_space(AVFifo *f, size_t to_write)
{
    ধ্রুব size_t can_write = av_fifo_can_write(f);
    ধ্রুব size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    যদি (!need_grow)
        প্রত্যাগম 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    যদি ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ধ্রুব size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        প্রত্যাগম av_fifo_grow2(f, inc);
    }

    প্রত্যাগম AVERROR(ENOSPC);
}

স্থির পূর্ণাঙ্ক fifo_write_common(AVFifo *f, ধ্রুব uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, শূন্য *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    পূর্ণাঙ্ক         ret = 0;

    ret = fifo_check_space(f, to_write);
    যদি (ret < 0)
        প্রত্যাগম ret;

    offset_w = f->offset_w;

    যাবত্ (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        যদি (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            যদি (ret < 0 || len == 0)
                ভঙ্গ;
        } অন্যথা {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        যদি (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    যদি (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_fifo_write(AVFifo *f, ধ্রুব শূন্য *buf, size_t nb_elems)
{
    প্রত্যাগম fifo_write_common(f, buf, &nb_elems, রিক্ত, রিক্ত);
}

পূর্ণাঙ্ক av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          শূন্য *opaque, size_t *nb_elems)
{
    প্রত্যাগম fifo_write_common(f, রিক্ত, nb_elems, read_cb, opaque);
}

স্থির পূর্ণাঙ্ক fifo_peek_common(ধ্রুব AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, শূন্য *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    পূর্ণাঙ্ক         ret = 0;

    যদি (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        প্রত্যাগম AVERROR(EINVAL);
    }

    যদি (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    অন্যথা
        offset_r += offset;

    যাবত্ (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        যদি (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            যদি (ret < 0 || len == 0)
                ভঙ্গ;
        } অন্যথা {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        যদি (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_fifo_read(AVFifo *f, শূন্য *buf, size_t nb_elems)
{
    পূর্ণাঙ্ক ret = fifo_peek_common(f, buf, &nb_elems, 0, রিক্ত, রিক্ত);
    av_fifo_drain2(f, nb_elems);
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       শূন্য *opaque, size_t *nb_elems)
{
    পূর্ণাঙ্ক ret = fifo_peek_common(f, রিক্ত, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_fifo_peek(ধ্রুব AVFifo *f, শূন্য *buf, size_t nb_elems, size_t offset)
{
    প্রত্যাগম fifo_peek_common(f, buf, &nb_elems, offset, রিক্ত, রিক্ত);
}

পূর্ণাঙ্ক av_fifo_peek_to_cb(ধ্রুব AVFifo *f, AVFifoCB write_cb, শূন্য *opaque,
                       size_t *nb_elems, size_t offset)
{
    প্রত্যাগম fifo_peek_common(f, রিক্ত, nb_elems, offset, write_cb, opaque);
}

শূন্য av_fifo_drain2(AVFifo *f, size_t size)
{
    ধ্রুব size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    যদি (cur_size == size)
        f->is_empty = 1;

    যদি (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    অন্যথা
        f->offset_r += size;
}

শূন্য av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

শূন্য av_fifo_freep2(AVFifo **f)
{
    যদি (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
