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

কাঠামো AVFifo {
    uint8_t *বাফার;

    size_t elem_আকার, nb_elems;
    size_t offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    পূর্ণসংখ্যা    is_empty;

    unsigned পূর্ণসংখ্যা flags;
    size_t       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_আকার,
                       unsigned পূর্ণসংখ্যা flags)
{
    AVFifo *f;
    শূন্য *বাফার = ফাঁকা;

    যদি (!elem_আকার)
        ফেরত ফাঁকা;

    যদি (nb_elems) {
        বাফার = av_realloc_array(ফাঁকা, nb_elems, elem_আকার);
        যদি (!বাফার)
            ফেরত ফাঁকা;
    }
    f = av_mallocz(আকার(*f));
    যদি (!f) {
        av_free(বাফার);
        ফেরত ফাঁকা;
    }
    f->বাফার    = বাফার;
    f->nb_elems  = nb_elems;
    f->elem_আকার = elem_আকার;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_আকার, 1);

    ফেরত f;
}

শূন্য av_fifo_auto_grow_limit(AVFifo *f, size_t max_elems)
{
    f->auto_grow_limit = max_elems;
}

size_t av_fifo_elem_আকার(ধ্রুবক AVFifo *f)
{
    ফেরত f->elem_আকার;
}

size_t av_fifo_can_read(ধ্রুবক AVFifo *f)
{
    যদি (f->offset_w <= f->offset_r && !f->is_empty)
        ফেরত f->nb_elems - f->offset_r + f->offset_w;
    ফেরত f->offset_w - f->offset_r;
}

size_t av_fifo_can_write(ধ্রুবক AVFifo *f)
{
    ফেরত f->nb_elems - av_fifo_can_read(f);
}

পূর্ণসংখ্যা av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    যদি (inc > SIZE_MAX - f->nb_elems)
        ফেরত AVERROR(EINVAL);

    tmp = av_realloc_array(f->বাফার, f->nb_elems + inc, f->elem_আকার);
    যদি (!tmp)
        ফেরত AVERROR(ENOMEM);
    f->বাফার = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    যদি (f->offset_w <= f->offset_r && !f->is_empty) {
        ধ্রুবক size_t copy = FFMIN(inc, f->offset_w);
        memcpy(tmp + f->nb_elems * f->elem_আকার, tmp, copy * f->elem_আকার);
        যদি (copy < f->offset_w) {
            memmove(tmp, tmp + copy * f->elem_আকার,
                    (f->offset_w - copy) * f->elem_আকার);
            f->offset_w -= copy;
        } অন্যথা
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা fifo_check_space(AVFifo *f, size_t to_write)
{
    ধ্রুবক size_t can_write = av_fifo_can_write(f);
    ধ্রুবক size_t need_grow = to_write > can_write ? to_write - can_write : 0;
    size_t can_grow;

    যদি (!need_grow)
        ফেরত 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    যদি ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ধ্রুবক size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        ফেরত av_fifo_grow2(f, inc);
    }

    ফেরত AVERROR(ENOSPC);
}

স্থির পূর্ণসংখ্যা fifo_write_common(AVFifo *f, ধ্রুবক uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, শূন্য *opaque)
{
    size_t to_write = *nb_elems;
    size_t offset_w;
    পূর্ণসংখ্যা         ret = 0;

    ret = fifo_check_space(f, to_write);
    যদি (ret < 0)
        ফেরত ret;

    offset_w = f->offset_w;

    যখন (to_write > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->বাফার + offset_w * f->elem_আকার;

        যদি (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            যদি (ret < 0 || len == 0)
                বিরতি;
        } অন্যথা {
            memcpy(wptr, buf, len * f->elem_আকার);
            buf += len * f->elem_আকার;
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

    ফেরত ret;
}

পূর্ণসংখ্যা av_fifo_write(AVFifo *f, ধ্রুবক শূন্য *buf, size_t nb_elems)
{
    ফেরত fifo_write_common(f, buf, &nb_elems, ফাঁকা, ফাঁকা);
}

পূর্ণসংখ্যা av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          শূন্য *opaque, size_t *nb_elems)
{
    ফেরত fifo_write_common(f, ফাঁকা, nb_elems, read_cb, opaque);
}

স্থির পূর্ণসংখ্যা fifo_peek_common(ধ্রুবক AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t offset, AVFifoCB write_cb, শূন্য *opaque)
{
    size_t  to_read = *nb_elems;
    size_t offset_r = f->offset_r;
    size_t can_read = av_fifo_can_read(f);
    পূর্ণসংখ্যা         ret = 0;

    যদি (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        ফেরত AVERROR(EINVAL);
    }

    যদি (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    অন্যথা
        offset_r += offset;

    যখন (to_read > 0) {
        size_t    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->বাফার + offset_r * f->elem_আকার;

        যদি (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            যদি (ret < 0 || len == 0)
                বিরতি;
        } অন্যথা {
            memcpy(buf, rptr, len * f->elem_আকার);
            buf += len * f->elem_আকার;
        }
        offset_r += len;
        যদি (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    ফেরত ret;
}

পূর্ণসংখ্যা av_fifo_read(AVFifo *f, শূন্য *buf, size_t nb_elems)
{
    পূর্ণসংখ্যা ret = fifo_peek_common(f, buf, &nb_elems, 0, ফাঁকা, ফাঁকা);
    av_fifo_drain2(f, nb_elems);
    ফেরত ret;
}

পূর্ণসংখ্যা av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       শূন্য *opaque, size_t *nb_elems)
{
    পূর্ণসংখ্যা ret = fifo_peek_common(f, ফাঁকা, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    ফেরত ret;
}

পূর্ণসংখ্যা av_fifo_peek(ধ্রুবক AVFifo *f, শূন্য *buf, size_t nb_elems, size_t offset)
{
    ফেরত fifo_peek_common(f, buf, &nb_elems, offset, ফাঁকা, ফাঁকা);
}

পূর্ণসংখ্যা av_fifo_peek_to_cb(ধ্রুবক AVFifo *f, AVFifoCB write_cb, শূন্য *opaque,
                       size_t *nb_elems, size_t offset)
{
    ফেরত fifo_peek_common(f, ফাঁকা, nb_elems, offset, write_cb, opaque);
}

শূন্য av_fifo_drain2(AVFifo *f, size_t আকার_2)
{
    ধ্রুবক size_t cur_আকার = av_fifo_can_read(f);

    av_assert0(cur_আকার >= আকার_2);
    যদি (cur_আকার == আকার_2)
        f->is_empty = 1;

    যদি (f->offset_r >= f->nb_elems - আকার_2)
        f->offset_r -= f->nb_elems - আকার_2;
    অন্যথা
        f->offset_r += আকার_2;
}

শূন্য av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

শূন্য av_fifo_freep2(AVFifo **f)
{
    যদি (*f) {
        av_freep(&(*f)->বাফার);
        av_freep(f);
    }
}
