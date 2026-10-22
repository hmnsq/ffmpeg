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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "fifo.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"

// by default the FIFO can be auto-grown to 1MB
#define AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

संरचना AVFifo {
    uint8_t *buffer;

    माप_प्रकार elem_size, nb_elems;
    माप_प्रकार offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    पूर्णाङ्क    is_empty;

    अचिन्हित पूर्णाङ्क flags;
    माप_प्रकार       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(माप_प्रकार nb_elems, माप_प्रकार elem_size,
                       अचिन्हित पूर्णाङ्क flags)
{
    AVFifo *f;
    शून्य *buffer = रिक्त;

    यदि (!elem_size)
        प्रत्यागम रिक्त;

    यदि (nb_elems) {
        buffer = av_realloc_array(रिक्त, nb_elems, elem_size);
        यदि (!buffer)
            प्रत्यागम रिक्त;
    }
    f = av_mallocz(परिमाण(*f));
    यदि (!f) {
        av_free(buffer);
        प्रत्यागम रिक्त;
    }
    f->buffer    = buffer;
    f->nb_elems  = nb_elems;
    f->elem_size = elem_size;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_size, 1);

    प्रत्यागम f;
}

शून्य av_fifo_auto_grow_limit(AVFifo *f, माप_प्रकार max_elems)
{
    f->auto_grow_limit = max_elems;
}

माप_प्रकार av_fifo_elem_size(ध्रुव AVFifo *f)
{
    प्रत्यागम f->elem_size;
}

माप_प्रकार av_fifo_can_read(ध्रुव AVFifo *f)
{
    यदि (f->offset_w <= f->offset_r && !f->is_empty)
        प्रत्यागम f->nb_elems - f->offset_r + f->offset_w;
    प्रत्यागम f->offset_w - f->offset_r;
}

माप_प्रकार av_fifo_can_write(ध्रुव AVFifo *f)
{
    प्रत्यागम f->nb_elems - av_fifo_can_read(f);
}

पूर्णाङ्क av_fifo_grow2(AVFifo *f, माप_प्रकार inc)
{
    uint8_t *tmp;

    यदि (inc > SIZE_MAX - f->nb_elems)
        प्रत्यागम AVERROR(EINVAL);

    tmp = av_realloc_array(f->buffer, f->nb_elems + inc, f->elem_size);
    यदि (!tmp)
        प्रत्यागम AVERROR(ENOMEM);
    f->buffer = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    यदि (f->offset_w <= f->offset_r && !f->is_empty) {
        ध्रुव माप_प्रकार copy = FFMIN(inc, f->offset_w);
        स_नकल(tmp + f->nb_elems * f->elem_size, tmp, copy * f->elem_size);
        यदि (copy < f->offset_w) {
            स_हटाओ(tmp, tmp + copy * f->elem_size,
                    (f->offset_w - copy) * f->elem_size);
            f->offset_w -= copy;
        } अन्यथा
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क fifo_check_space(AVFifo *f, माप_प्रकार to_write)
{
    ध्रुव माप_प्रकार can_write = av_fifo_can_write(f);
    ध्रुव माप_प्रकार need_grow = to_write > can_write ? to_write - can_write : 0;
    माप_प्रकार can_grow;

    यदि (!need_grow)
        प्रत्यागम 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    यदि ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ध्रुव माप_प्रकार inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        प्रत्यागम av_fifo_grow2(f, inc);
    }

    प्रत्यागम AVERROR(ENOSPC);
}

स्थिर पूर्णाङ्क fifo_write_common(AVFifo *f, ध्रुव uint8_t *buf, माप_प्रकार *nb_elems,
                             AVFifoCB read_cb, शून्य *opaque)
{
    माप_प्रकार to_write = *nb_elems;
    माप_प्रकार offset_w;
    पूर्णाङ्क         ret = 0;

    ret = fifo_check_space(f, to_write);
    यदि (ret < 0)
        प्रत्यागम ret;

    offset_w = f->offset_w;

    यावत् (to_write > 0) {
        माप_प्रकार    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->buffer + offset_w * f->elem_size;

        यदि (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            यदि (ret < 0 || len == 0)
                भङ्ग;
        } अन्यथा {
            स_नकल(wptr, buf, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_w += len;
        यदि (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    यदि (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    प्रत्यागम ret;
}

पूर्णाङ्क av_fifo_write(AVFifo *f, ध्रुव शून्य *buf, माप_प्रकार nb_elems)
{
    प्रत्यागम fifo_write_common(f, buf, &nb_elems, रिक्त, रिक्त);
}

पूर्णाङ्क av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          शून्य *opaque, माप_प्रकार *nb_elems)
{
    प्रत्यागम fifo_write_common(f, रिक्त, nb_elems, read_cb, opaque);
}

स्थिर पूर्णाङ्क fifo_peek_common(ध्रुव AVFifo *f, uint8_t *buf, माप_प्रकार *nb_elems,
                            माप_प्रकार offset, AVFifoCB write_cb, शून्य *opaque)
{
    माप_प्रकार  to_read = *nb_elems;
    माप_प्रकार offset_r = f->offset_r;
    माप_प्रकार can_read = av_fifo_can_read(f);
    पूर्णाङ्क         ret = 0;

    यदि (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    अन्यथा
        offset_r += offset;

    यावत् (to_read > 0) {
        माप_प्रकार    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->buffer + offset_r * f->elem_size;

        यदि (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            यदि (ret < 0 || len == 0)
                भङ्ग;
        } अन्यथा {
            स_नकल(buf, rptr, len * f->elem_size);
            buf += len * f->elem_size;
        }
        offset_r += len;
        यदि (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    प्रत्यागम ret;
}

पूर्णाङ्क av_fifo_read(AVFifo *f, शून्य *buf, माप_प्रकार nb_elems)
{
    पूर्णाङ्क ret = fifo_peek_common(f, buf, &nb_elems, 0, रिक्त, रिक्त);
    av_fifo_drain2(f, nb_elems);
    प्रत्यागम ret;
}

पूर्णाङ्क av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       शून्य *opaque, माप_प्रकार *nb_elems)
{
    पूर्णाङ्क ret = fifo_peek_common(f, रिक्त, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    प्रत्यागम ret;
}

पूर्णाङ्क av_fifo_peek(ध्रुव AVFifo *f, शून्य *buf, माप_प्रकार nb_elems, माप_प्रकार offset)
{
    प्रत्यागम fifo_peek_common(f, buf, &nb_elems, offset, रिक्त, रिक्त);
}

पूर्णाङ्क av_fifo_peek_to_cb(ध्रुव AVFifo *f, AVFifoCB write_cb, शून्य *opaque,
                       माप_प्रकार *nb_elems, माप_प्रकार offset)
{
    प्रत्यागम fifo_peek_common(f, रिक्त, nb_elems, offset, write_cb, opaque);
}

शून्य av_fifo_drain2(AVFifo *f, माप_प्रकार size)
{
    ध्रुव माप_प्रकार cur_size = av_fifo_can_read(f);

    av_assert0(cur_size >= size);
    यदि (cur_size == size)
        f->is_empty = 1;

    यदि (f->offset_r >= f->nb_elems - size)
        f->offset_r -= f->nb_elems - size;
    अन्यथा
        f->offset_r += size;
}

शून्य av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

शून्य av_fifo_freep2(AVFifo **f)
{
    यदि (*f) {
        av_freep(&(*f)->buffer);
        av_freep(f);
    }
}
