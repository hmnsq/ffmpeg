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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "fifo.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"

// by default the FIFO can be auto-grown to 1MB
#define AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

கட்டமைப்பு AVFifo {
    uint8_t *buffer;

    size_t elem_size, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    முழு    is_empty;

    unsigned முழு flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_size,
                       unsigned முழு flags)
{
    AVFifo *f;
    வெறுமை *buffer = வெற்று;

    எனில் (!elem_size)
        திரும்பு வெற்று;

    எனில் (nb_elems) {
        buffer = av_realloc_array(வெற்று, nb_elems, elem_size);
        எனில் (!buffer)
            திரும்பு வெற்று;
    }
    f = av_mallocz(அளவு(*f));
    எனில் (!f) {
        av_free(buffer);
        திரும்பு வெற்று;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    திரும்பு f;
}

வெறுமை av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_size(மாறிலி AVFifo *f)
{
    திரும்பு f->elem_size;
}

size_t av_fifo_can_read(மாறிலி AVFifo *f)
{
    எனில் (f->offset_w <= f->offset_r && !f->is_empty)
        திரும்பு f->nb_elems - f->offset_r + f->offset_w;
    திரும்பு f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(மாறிலி AVFifo *f)
{
    திரும்பு f->nb_elems - av_fifo_can_read(f);
}

முழு av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    எனில் (inc > SIZE_MAX - f->nb_elems)
        திரும்பு AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    எனில் (!tmp)
        திரும்பு AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    எனில் (f->offset_w <= f->offset_r && !f->is_empty) {
        மாறிலி size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        எனில் (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } இல்லையெனில்
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    திரும்பு 0;
}

நிலையான முழு fifo_check_space(AVFifo *f, size_t to_write)
{
    மாறிலி size_t can_write = av_fifo_can_write(f);
    மாறிலி size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    எனில் (!need_grow)
        திரும்பு 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    எனில் ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        மாறிலி size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        திரும்பு av_fifo_grow2(f, inc);
    }

    திரும்பு AVERROR(ENOSPC);
}

நிலையான முழு fifo_write_common(AVFifo *f, மாறிலி uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, வெறுமை *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    முழு         ret = 0;

    ret = fifo_check_space(f, to_write);
    எனில் (ret < 0)
        திரும்பு ret;

    offset_w = f->offset_w;

    போது (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        எனில் (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            எனில் (ret < 0 || len == 0)
                நிறுத்து;
        } இல்லையெனில் {
            memcpy(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        எனில் (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    எனில் (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    திரும்பு ret;
}

முழு av_fifo_write(AVFifo *f, மாறிலி வெறுமை *buf, size_t nb_elems)
{
    திரும்பு fifo_write_common(f, buf, &nb_elems, வெற்று, வெற்று);
}

முழு av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          வெறுமை *opaque, size_t *nb_elems)
{
    திரும்பு fifo_write_common(f, வெற்று, nb_elems, read_cb, opaque);
}

நிலையான முழு fifo_peek_common(மாறிலி AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, வெறுமை *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    முழு         ret = 0;

    எனில் (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        திரும்பு AVERROR(EINVAL);
    }

    எனில் (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    இல்லையெனில்
        offset_r += offset;

    போது (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        எனில் (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            எனில் (ret < 0 || len == 0)
                நிறுத்து;
        } இல்லையெனில் {
            memcpy(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        எனில் (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    திரும்பு ret;
}

முழு av_fifo_read(AVFifo *f, வெறுமை *buf, size_t nb_elems)
{
    முழு ret = fifo_peek_common(f, buf, &nb_elems, 0, வெற்று, வெற்று);
    av_fifo_drain2(f, nb_elems);
    திரும்பு ret;
}

முழு av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       வெறுமை *opaque, size_t *nb_elems)
{
    முழு ret = fifo_peek_common(f, வெற்று, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    திரும்பு ret;
}

முழு av_fifo_peek(மாறிலி AVFifo *f, வெறுமை *buf, size_t nb_elems, size_t offset)
{
    திரும்பு fifo_peek_common(f, buf, &nb_elems, offset, வெற்று, வெற்று);
}

முழு av_fifo_peek_to_cb(மாறிலி AVFifo *f, AVFifoCB write_cb, வெறுமை *opaque,
                       size_t *nb_elems, size_t offset)
{
    திரும்பு fifo_peek_common(f, வெற்று, nb_elems, offset, write_cb, opaque);
}

வெறுமை av_fifo_drain2(AVFifo *f, size_t size)
{
    மாறிலி size_t cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    எனில் (cur_size == size)
        f->is_empty = 1;

    எனில் (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    இல்லையெனில்
        f->offset_r += size;
}

வெறுமை av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

வெறுமை av_fifo_freep2(AVFifo **f)
{
    எனில் (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
