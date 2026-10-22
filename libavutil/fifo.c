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

sa_nracanaa AVFifo {
    uint8_t *buffer;

    size_t elem_size, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    จำนวนเต็ม    is_empty;

    unsigned จำนวนเต็ม flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_size,
                       unsigned จำนวนเต็ม flags)
{
    AVFifo *f;
    void *buffer = NULL;

    ถ้า (!elem_size)
        คืน NULL;

    ถ้า (nb_elems) {
        buffer = av_realloc_array(NULL, nb_elems, elem_size);
        ถ้า (!buffer)
            คืน NULL;
    }
    f = av_mallocz(parimaa_na(*f));
    ถ้า (!f) {
        av_free(buffer);
        คืน NULL;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    คืน f;
}

void av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(const AVFifo *f)
{
    คืน f->elem_size;
}

size_t av_fifo_can_read(const AVFifo *f)
{
    ถ้า (f->offset_w <= f->offset_r && !f->is_empty)
        คืน f->nb_elems - f->offset_r + f->offset_w;
    คืน f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(const AVFifo *f)
{
    คืน f->nb_elems - av_fifo_can_read(f);
}

จำนวนเต็ม av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    ถ้า (inc > SIZE_MAX - f->nb_elems)
        คืน AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    ถ้า (!tmp)
        คืน AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    ถ้า (f->offset_w <= f->offset_r && !f->is_empty) {
        const size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        ถ้า (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } มิฉะนั้น
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    คืน 0;
}

static จำนวนเต็ม fifo_check_space(AVFifo *f, size_t to_write)
{
    const size_t can_write = av_fifo_can_write(f);
    const size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    ถ้า (!need_grow)
        คืน 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    ถ้า ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        const size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        คืน av_fifo_grow2(f, inc);
    }

    คืน AVERROR(ENOSPC);
}

static จำนวนเต็ม fifo_write_common(AVFifo *f, const uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, void *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    จำนวนเต็ม         ret = 0;

    ret = fifo_check_space(f, to_write);
    ถ้า (ret < 0)
        คืน ret;

    offset_w = f->offset_w;

    ขณะ (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        ถ้า (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            ถ้า (ret < 0 || len == 0)
                bha_nga;
        } มิฉะนั้น {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        ถ้า (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    ถ้า (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    คืน ret;
}

จำนวนเต็ม av_fifo_write(AVFifo *f, const void *buf, size_t nb_elems)
{
    คืน fifo_write_common(f, buf, &nb_elems, NULL, NULL);
}

จำนวนเต็ม av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          void *opaque, size_t *nb_elems)
{
    คืน fifo_write_common(f, NULL, nb_elems, read_cb, opaque);
}

static จำนวนเต็ม fifo_peek_common(const AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, void *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    จำนวนเต็ม         ret = 0;

    ถ้า (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        คืน AVERROR(EINVAL);
    }

    ถ้า (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    มิฉะนั้น
        offset_r += offset;

    ขณะ (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        ถ้า (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            ถ้า (ret < 0 || len == 0)
                bha_nga;
        } มิฉะนั้น {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        ถ้า (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    คืน ret;
}

จำนวนเต็ม av_fifo_read(AVFifo *f, void *buf, size_t nb_elems)
{
    จำนวนเต็ม ret = fifo_peek_common(f, buf, &nb_elems, 0, NULL, NULL);
    av_fifo_drain2(f, nb_elems);
    คืน ret;
}

จำนวนเต็ม av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       void *opaque, size_t *nb_elems)
{
    จำนวนเต็ม ret = fifo_peek_common(f, NULL, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    คืน ret;
}

จำนวนเต็ม av_fifo_peek(const AVFifo *f, void *buf, size_t nb_elems, size_t offset)
{
    คืน fifo_peek_common(f, buf, &nb_elems, offset, NULL, NULL);
}

จำนวนเต็ม av_fifo_peek_to_cb(const AVFifo *f, AVFifoCB write_cb, void *opaque,
                       size_t *nb_elems, size_t offset)
{
    คืน fifo_peek_common(f, NULL, nb_elems, offset, write_cb, opaque);
}

void av_fifo_drain2(AVFifo *f, size_t size)
{
    const size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    ถ้า (cur_size == size)
        f->is_empty = 1;

    ถ้า (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    มิฉะนั้น
        f->offset_r += size;
}

void av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

void av_fifo_freep2(AVFifo **f)
{
    ถ้า (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
