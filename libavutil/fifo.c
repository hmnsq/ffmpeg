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

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "fifo.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"

// by default the FIFO can be auto-grown to 1MB
#define AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

ഘടന AVFifo {
    uint8_t *buffer;

    size_t elem_size, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    പൂർണ്ണസംഖ്യ    is_empty;

    unsigned പൂർണ്ണസംഖ്യ flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_size,
                       unsigned പൂർണ്ണസംഖ്യ flags)
{
    AVFifo *f;
    ശൂന്യം *buffer = ശൂന്യ;

    എങ്കിൽ (!elem_size)
        തിരികെ ശൂന്യ;

    എങ്കിൽ (nb_elems) {
        buffer = av_realloc_array(ശൂന്യ, nb_elems, elem_size);
        എങ്കിൽ (!buffer)
            തിരികെ ശൂന്യ;
    }
    f = av_mallocz(വലുപ്പം(*f));
    എങ്കിൽ (!f) {
        av_free(buffer);
        തിരികെ ശൂന്യ;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    തിരികെ f;
}

ശൂന്യം av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(സ്ഥിരം AVFifo *f)
{
    തിരികെ f->elem_size;
}

size_t av_fifo_can_read(സ്ഥിരം AVFifo *f)
{
    എങ്കിൽ (f->offset_w <= f->offset_r && !f->is_empty)
        തിരികെ f->nb_elems - f->offset_r + f->offset_w;
    തിരികെ f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(സ്ഥിരം AVFifo *f)
{
    തിരികെ f->nb_elems - av_fifo_can_read(f);
}

പൂർണ്ണസംഖ്യ av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    എങ്കിൽ (inc > SIZE_MAX - f->nb_elems)
        തിരികെ AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    എങ്കിൽ (!tmp)
        തിരികെ AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    എങ്കിൽ (f->offset_w <= f->offset_r && !f->is_empty) {
        സ്ഥിരം size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        എങ്കിൽ (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } അല്ലെങ്കിൽ
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ fifo_check_space(AVFifo *f, size_t to_write)
{
    സ്ഥിരം size_t can_write = av_fifo_can_write(f);
    സ്ഥിരം size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    എങ്കിൽ (!need_grow)
        തിരികെ 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    എങ്കിൽ ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        സ്ഥിരം size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        തിരികെ av_fifo_grow2(f, inc);
    }

    തിരികെ AVERROR(ENOSPC);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ fifo_write_common(AVFifo *f, സ്ഥിരം uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, ശൂന്യം *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    പൂർണ്ണസംഖ്യ         ret = 0;

    ret = fifo_check_space(f, to_write);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    offset_w = f->offset_w;

    ആകുമ്പോൾ (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        എങ്കിൽ (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            എങ്കിൽ (ret < 0 || len == 0)
                നിർത്തുക;
        } അല്ലെങ്കിൽ {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        എങ്കിൽ (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    എങ്കിൽ (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_fifo_write(AVFifo *f, സ്ഥിരം ശൂന്യം *buf, size_t nb_elems)
{
    തിരികെ fifo_write_common(f, buf, &nb_elems, ശൂന്യ, ശൂന്യ);
}

പൂർണ്ണസംഖ്യ av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          ശൂന്യം *opaque, size_t *nb_elems)
{
    തിരികെ fifo_write_common(f, ശൂന്യ, nb_elems, read_cb, opaque);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ fifo_peek_common(സ്ഥിരം AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, ശൂന്യം *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    പൂർണ്ണസംഖ്യ         ret = 0;

    എങ്കിൽ (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        തിരികെ AVERROR(EINVAL);
    }

    എങ്കിൽ (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    അല്ലെങ്കിൽ
        offset_r += offset;

    ആകുമ്പോൾ (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        എങ്കിൽ (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            എങ്കിൽ (ret < 0 || len == 0)
                നിർത്തുക;
        } അല്ലെങ്കിൽ {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        എങ്കിൽ (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_fifo_read(AVFifo *f, ശൂന്യം *buf, size_t nb_elems)
{
    പൂർണ്ണസംഖ്യ ret = fifo_peek_common(f, buf, &nb_elems, 0, ശൂന്യ, ശൂന്യ);
    av_fifo_drain2(f, nb_elems);
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       ശൂന്യം *opaque, size_t *nb_elems)
{
    പൂർണ്ണസംഖ്യ ret = fifo_peek_common(f, ശൂന്യ, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_fifo_peek(സ്ഥിരം AVFifo *f, ശൂന്യം *buf, size_t nb_elems, size_t offset)
{
    തിരികെ fifo_peek_common(f, buf, &nb_elems, offset, ശൂന്യ, ശൂന്യ);
}

പൂർണ്ണസംഖ്യ av_fifo_peek_to_cb(സ്ഥിരം AVFifo *f, AVFifoCB write_cb, ശൂന്യം *opaque,
                       size_t *nb_elems, size_t offset)
{
    തിരികെ fifo_peek_common(f, ശൂന്യ, nb_elems, offset, write_cb, opaque);
}

ശൂന്യം av_fifo_drain2(AVFifo *f, size_t size)
{
    സ്ഥിരം size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    എങ്കിൽ (cur_size == size)
        f->is_empty = 1;

    എങ്കിൽ (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    അല്ലെങ്കിൽ
        f->offset_r += size;
}

ശൂന്യം av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

ശൂന്യം av_fifo_freep2(AVFifo **f)
{
    എങ്കിൽ (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
