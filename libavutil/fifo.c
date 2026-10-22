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

#include <stdint.h>
#include <string.h>

#include "avassert.h"
#include "error.h"
#include "fifo.h"
#include "macros.h"
#include "mem.h"

// by default the FIFO can be auto-grown to 1MB
#define AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

struct AVFifo {
    uint8_t *buffer;

    size_t elem_size, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    цео    is_empty;

    unsigned цео flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_size,
                       unsigned цео flags)
{
    AVFifo *f;
    void *buffer = NULL;

    ако (!elem_size)
        врати NULL;

    ако (nb_elems) {
        buffer = av_realloc_array(NULL, nb_elems, elem_size);
        ако (!buffer)
            врати NULL;
    }
    f = av_mallocz(sizeof(*f));
    ако (!f) {
        av_free(buffer);
        врати NULL;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    врати f;
}

void av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(const AVFifo *f)
{
    врати f->elem_size;
}

size_t av_fifo_can_read(const AVFifo *f)
{
    ако (f->offset_w <= f->offset_r && !f->is_empty)
        врати f->nb_elems - f->offset_r + f->offset_w;
    врати f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(const AVFifo *f)
{
    врати f->nb_elems - av_fifo_can_read(f);
}

цео av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    ако (inc > SIZE_MAX - f->nb_elems)
        врати AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    ако (!tmp)
        врати AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    ако (f->offset_w <= f->offset_r && !f->is_empty) {
        const size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        ако (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } инако
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    врати 0;
}

static цео fifo_check_space(AVFifo *f, size_t to_write)
{
    const size_t can_write = av_fifo_can_write(f);
    const size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    ако (!need_grow)
        врати 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    ако ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        const size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        врати av_fifo_grow2(f, inc);
    }

    врати AVERROR(ENOSPC);
}

static цео fifo_write_common(AVFifo *f, const uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, void *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    цео         ret = 0;

    ret = fifo_check_space(f, to_write);
    ако (ret < 0)
        врати ret;

    offset_w = f->offset_w;

    док (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        ако (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            ако (ret < 0 || len == 0)
                break;
        } инако {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        ако (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    ако (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    врати ret;
}

цео av_fifo_write(AVFifo *f, const void *buf, size_t nb_elems)
{
    врати fifo_write_common(f, buf, &nb_elems, NULL, NULL);
}

цео av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          void *opaque, size_t *nb_elems)
{
    врати fifo_write_common(f, NULL, nb_elems, read_cb, opaque);
}

static цео fifo_peek_common(const AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, void *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    цео         ret = 0;

    ако (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        врати AVERROR(EINVAL);
    }

    ако (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    инако
        offset_r += offset;

    док (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        ако (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            ако (ret < 0 || len == 0)
                break;
        } инако {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        ако (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    врати ret;
}

цео av_fifo_read(AVFifo *f, void *buf, size_t nb_elems)
{
    цео ret = fifo_peek_common(f, buf, &nb_elems, 0, NULL, NULL);
    av_fifo_drain2(f, nb_elems);
    врати ret;
}

цео av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       void *opaque, size_t *nb_elems)
{
    цео ret = fifo_peek_common(f, NULL, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    врати ret;
}

цео av_fifo_peek(const AVFifo *f, void *buf, size_t nb_elems, size_t offset)
{
    врати fifo_peek_common(f, buf, &nb_elems, offset, NULL, NULL);
}

цео av_fifo_peek_to_cb(const AVFifo *f, AVFifoCB write_cb, void *opaque,
                       size_t *nb_elems, size_t offset)
{
    врати fifo_peek_common(f, NULL, nb_elems, offset, write_cb, opaque);
}

void av_fifo_drain2(AVFifo *f, size_t size)
{
    const size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    ако (cur_size == size)
        f->is_empty = 1;

    ако (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    инако
        f->offset_r += size;
}

void av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

void av_fifo_freep2(AVFifo **f)
{
    ако (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
