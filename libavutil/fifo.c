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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "fifo.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

// by default the FIFO can be auto-grown to 1MB
#define AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

ସଂରଚନା AVFifo {
    uint8_t *buffer;

    size_t elem_size, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା    is_empty;

    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_size,
                       unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVFifo *f;
    ଶୂନ୍ୟ *buffer = ଖାଲି;

    ଯଦି (!elem_size)
        ଫେରନ୍ତୁ ଖାଲି;

    ଯଦି (nb_elems) {
        buffer = av_realloc_array(ଖାଲି, nb_elems, elem_size);
        ଯଦି (!buffer)
            ଫେରନ୍ତୁ ଖାଲି;
    }
    f = av_mallocz(ଆକାର(*f));
    ଯଦି (!f) {
        av_free(buffer);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    ଫେରନ୍ତୁ f;
}

ଶୂନ୍ୟ av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(ଅଚଳ AVFifo *f)
{
    ଫେରନ୍ତୁ f->elem_size;
}

size_t av_fifo_can_read(ଅଚଳ AVFifo *f)
{
    ଯଦି (f->offset_w <= f->offset_r && !f->is_empty)
        ଫେରନ୍ତୁ f->nb_elems - f->offset_r + f->offset_w;
    ଫେରନ୍ତୁ f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(ଅଚଳ AVFifo *f)
{
    ଫେରନ୍ତୁ f->nb_elems - av_fifo_can_read(f);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    ଯଦି (inc > SIZE_MAX - f->nb_elems)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    ଯଦି (!tmp)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    ଯଦି (f->offset_w <= f->offset_r && !f->is_empty) {
        ଅଚଳ size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        ଯଦି (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } ଅନ୍ୟଥା
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା fifo_check_space(AVFifo *f, size_t to_write)
{
    ଅଚଳ size_t can_write = av_fifo_can_write(f);
    ଅଚଳ size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    ଯଦି (!need_grow)
        ଫେରନ୍ତୁ 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    ଯଦି ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ଅଚଳ size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        ଫେରନ୍ତୁ av_fifo_grow2(f, inc);
    }

    ଫେରନ୍ତୁ AVERROR(ENOSPC);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା fifo_write_common(AVFifo *f, ଅଚଳ uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, ଶୂନ୍ୟ *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା         ret = 0;

    ret = fifo_check_space(f, to_write);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    offset_w = f->offset_w;

    ଯେତେବେଳେ (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        ଯଦି (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            ଯଦି (ret < 0 || len == 0)
                ଭାଙ୍ଗ;
        } ଅନ୍ୟଥା {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        ଯଦି (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    ଯଦି (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_fifo_write(AVFifo *f, ଅଚଳ ଶୂନ୍ୟ *buf, size_t nb_elems)
{
    ଫେରନ୍ତୁ fifo_write_common(f, buf, &nb_elems, ଖାଲି, ଖାଲି);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          ଶୂନ୍ୟ *opaque, size_t *nb_elems)
{
    ଫେରନ୍ତୁ fifo_write_common(f, ଖାଲି, nb_elems, read_cb, opaque);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା fifo_peek_common(ଅଚଳ AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, ଶୂନ୍ୟ *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା         ret = 0;

    ଯଦି (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    ଅନ୍ୟଥା
        offset_r += offset;

    ଯେତେବେଳେ (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        ଯଦି (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            ଯଦି (ret < 0 || len == 0)
                ଭାଙ୍ଗ;
        } ଅନ୍ୟଥା {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        ଯଦି (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_fifo_read(AVFifo *f, ଶୂନ୍ୟ *buf, size_t nb_elems)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = fifo_peek_common(f, buf, &nb_elems, 0, ଖାଲି, ଖାଲି);
    av_fifo_drain2(f, nb_elems);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       ଶୂନ୍ୟ *opaque, size_t *nb_elems)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = fifo_peek_common(f, ଖାଲି, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_fifo_peek(ଅଚଳ AVFifo *f, ଶୂନ୍ୟ *buf, size_t nb_elems, size_t offset)
{
    ଫେରନ୍ତୁ fifo_peek_common(f, buf, &nb_elems, offset, ଖାଲି, ଖାଲି);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_fifo_peek_to_cb(ଅଚଳ AVFifo *f, AVFifoCB write_cb, ଶୂନ୍ୟ *opaque,
                       size_t *nb_elems, size_t offset)
{
    ଫେରନ୍ତୁ fifo_peek_common(f, ଖାଲି, nb_elems, offset, write_cb, opaque);
}

ଶୂନ୍ୟ av_fifo_drain2(AVFifo *f, size_t size)
{
    ଅଚଳ size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    ଯଦି (cur_size == size)
        f->is_empty = 1;

    ଯଦି (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    ଅନ୍ୟଥା
        f->offset_r += size;
}

ଶୂନ୍ୟ av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

ଶୂନ୍ୟ av_fifo_freep2(AVFifo **f)
{
    ଯଦି (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
