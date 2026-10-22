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

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "fifo.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"

// by default the FIFO can be auto-grown to 1MB
#define AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

સંરચના AVFifo {
    uint8_t *buffer;

    size_t elem_size, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    પૂર્ણાંક    is_empty;

    unsigned પૂર્ણાંક flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_size,
                       unsigned પૂર્ણાંક flags)
{
    AVFifo *f;
    શૂન્ય *buffer = ખાલી;

    જો (!elem_size)
        પાછા ખાલી;

    જો (nb_elems) {
        buffer = av_realloc_array(ખાલી, nb_elems, elem_size);
        જો (!buffer)
            પાછા ખાલી;
    }
    f = av_mallocz(કદ(*f));
    જો (!f) {
        av_free(buffer);
        પાછા ખાલી;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    પાછા f;
}

શૂન્ય av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(અચલ AVFifo *f)
{
    પાછા f->elem_size;
}

size_t av_fifo_can_read(અચલ AVFifo *f)
{
    જો (f->offset_w <= f->offset_r && !f->is_empty)
        પાછા f->nb_elems - f->offset_r + f->offset_w;
    પાછા f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(અચલ AVFifo *f)
{
    પાછા f->nb_elems - av_fifo_can_read(f);
}

પૂર્ણાંક av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    જો (inc > SIZE_MAX - f->nb_elems)
        પાછા AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    જો (!tmp)
        પાછા AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    જો (f->offset_w <= f->offset_r && !f->is_empty) {
        અચલ size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        જો (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } નહીંતર
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    પાછા 0;
}

સ્થિર પૂર્ણાંક fifo_check_space(AVFifo *f, size_t to_write)
{
    અચલ size_t can_write = av_fifo_can_write(f);
    અચલ size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    જો (!need_grow)
        પાછા 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    જો ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        અચલ size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        પાછા av_fifo_grow2(f, inc);
    }

    પાછા AVERROR(ENOSPC);
}

સ્થિર પૂર્ણાંક fifo_write_common(AVFifo *f, અચલ uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, શૂન્ય *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    પૂર્ણાંક         ret = 0;

    ret = fifo_check_space(f, to_write);
    જો (ret < 0)
        પાછા ret;

    offset_w = f->offset_w;

    જ્યારે (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        જો (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            જો (ret < 0 || len == 0)
                તોડો;
        } નહીંતર {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        જો (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    જો (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    પાછા ret;
}

પૂર્ણાંક av_fifo_write(AVFifo *f, અચલ શૂન્ય *buf, size_t nb_elems)
{
    પાછા fifo_write_common(f, buf, &nb_elems, ખાલી, ખાલી);
}

પૂર્ણાંક av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          શૂન્ય *opaque, size_t *nb_elems)
{
    પાછા fifo_write_common(f, ખાલી, nb_elems, read_cb, opaque);
}

સ્થિર પૂર્ણાંક fifo_peek_common(અચલ AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, શૂન્ય *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    પૂર્ણાંક         ret = 0;

    જો (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        પાછા AVERROR(EINVAL);
    }

    જો (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    નહીંતર
        offset_r += offset;

    જ્યારે (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        જો (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            જો (ret < 0 || len == 0)
                તોડો;
        } નહીંતર {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        જો (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    પાછા ret;
}

પૂર્ણાંક av_fifo_read(AVFifo *f, શૂન્ય *buf, size_t nb_elems)
{
    પૂર્ણાંક ret = fifo_peek_common(f, buf, &nb_elems, 0, ખાલી, ખાલી);
    av_fifo_drain2(f, nb_elems);
    પાછા ret;
}

પૂર્ણાંક av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       શૂન્ય *opaque, size_t *nb_elems)
{
    પૂર્ણાંક ret = fifo_peek_common(f, ખાલી, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    પાછા ret;
}

પૂર્ણાંક av_fifo_peek(અચલ AVFifo *f, શૂન્ય *buf, size_t nb_elems, size_t offset)
{
    પાછા fifo_peek_common(f, buf, &nb_elems, offset, ખાલી, ખાલી);
}

પૂર્ણાંક av_fifo_peek_to_cb(અચલ AVFifo *f, AVFifoCB write_cb, શૂન્ય *opaque,
                       size_t *nb_elems, size_t offset)
{
    પાછા fifo_peek_common(f, ખાલી, nb_elems, offset, write_cb, opaque);
}

શૂન્ય av_fifo_drain2(AVFifo *f, size_t size)
{
    અચલ size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    જો (cur_size == size)
        f->is_empty = 1;

    જો (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    નહીંતર
        f->offset_r += size;
}

શૂન્ય av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

શૂન્ય av_fifo_freep2(AVFifo **f)
{
    જો (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
