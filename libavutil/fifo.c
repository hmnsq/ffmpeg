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
#وصف_ڪريو AUTO_GROW_DEFAULT_بائيٽون (1024 * 1024)

بنية AVFifo {
    uint8_t *بفر;

    size_t elem_سائيز, nb_elems;
    size_t وٿي_r, وٿي_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    صحيح    is_خالي_جايون;

    بنانشان صحيح flags;
    size_t       auto_grow_حد_بندي;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_سائيز,
                       بنانشان صحيح flags)
{
    AVFifo *f;
    فراغ *بفر = عدم;

    إذا (!elem_سائيز)
        أرجع عدم;

    إذا (nb_elems) {
        بفر = av_realloc_array(عدم, nb_elems, elem_سائيز);
        إذا (!بفر)
            أرجع عدم;
    }
    f = av_mallocz(حجم(*f));
    إذا (!f) {
        av_free(بفر);
        أرجع عدم;
    }
    f->بفر    = بفر;
    f->nb_elems  = nb_elems;
    f->elem_سائيز = elem_سائيز;
    f->is_خالي_جايون  = 1;

    f->flags           = flags;
    f->auto_grow_حد_بندي = FFMAX(AUTO_GROW_DEFAULT_بائيٽون / elem_سائيز, 1);

    أرجع f;
}

فراغ av_fifo_auto_grow_حد_بندي(AVFifo *f, size_t max_elems)
{
    f->auto_grow_حد_بندي = max_elems;
}

size_t av_fifo_elem_سائيز(ثابت AVFifo *f)
{
    أرجع f->elem_سائيز;
}

size_t av_fifo_can_read(ثابت AVFifo *f)
{
    إذا (f->وٿي_w <= f->وٿي_r && !f->is_خالي_جايون)
        أرجع f->nb_elems - f->وٿي_r + f->وٿي_w;
    أرجع f->وٿي_w - f->وٿي_r;
}

size_t av_fifo_can_write(ثابت AVFifo *f)
{
    أرجع f->nb_elems - av_fifo_can_read(f);
}

صحيح av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    إذا (inc > SIZE_MAX - f->nb_elems)
        أرجع AVERROR(EINVAL);

    tmp = av_realloc_array(f->بفر, f->nb_elems + inc, f->elem_سائيز);
    إذا (!tmp)
        أرجع AVERROR(ENOMEM);
    f->بفر = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    إذا (f->وٿي_w <= f->وٿي_r && !f->is_خالي_جايون) {
        ثابت size_t copy = FFMIN(inc, f->وٿي_w);
        يادگيري_نقل(tmp + f->nb_elems * f->elem_سائيز, tmp, copy * f->elem_سائيز);
        إذا (copy < f->وٿي_w) {
            memmove(tmp, tmp + copy * f->elem_سائيز,
                    (f->وٿي_w - copy) * f->elem_سائيز);
            f->وٿي_w -= copy;
        } وإلا
            f->وٿي_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    أرجع 0;
}

ساكن صحيح fifo_check_space(AVFifo *f, size_t منزل_write)
{
    ثابت size_t can_write = av_fifo_can_write(f);
    ثابت size_t need_grow = منزل_write > can_write ? منزل_write - can_write : 0;
    size_t can_grow;

    إذا (!need_grow)
        أرجع 0;

    can_grow = f->auto_grow_حد_بندي > f->nb_elems ?
               f->auto_grow_حد_بندي - f->nb_elems : 0;
    إذا ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ثابت size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        أرجع av_fifo_grow2(f, inc);
    }

    أرجع AVERROR(ENOSPC);
}

ساكن صحيح fifo_write_common(AVFifo *f, ثابت uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, فراغ *opaque)
{
    size_t منزل_write = *nb_elems;
    size_t وٿي_w;
    صحيح         ret = 0;

    ret = fifo_check_space(f, منزل_write);
    إذا (ret < 0)
        أرجع ret;

    وٿي_w = f->وٿي_w;

    طالما (منزل_write > 0) {
        size_t    len = FFMIN(f->nb_elems - وٿي_w, منزل_write);
        uint8_t *wptr = f->بفر + وٿي_w * f->elem_سائيز;

        إذا (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            إذا (ret < 0 || len == 0)
                اكسر;
        } وإلا {
            يادگيري_نقل(wptr, buf, len * f->elem_سائيز);
            buf += len * f->elem_سائيز;
        }
        وٿي_w += len;
        إذا (وٿي_w >= f->nb_elems)
            وٿي_w = 0;
        منزل_write -= len;
    }
    f->وٿي_w = وٿي_w;

    إذا (*nb_elems != منزل_write)
        f->is_خالي_جايون = 0;
    *nb_elems -= منزل_write;

    أرجع ret;
}

صحيح av_fifo_write(AVFifo *f, ثابت فراغ *buf, size_t nb_elems)
{
    أرجع fifo_write_common(f, buf, &nb_elems, عدم, عدم);
}

صحيح av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          فراغ *opaque, size_t *nb_elems)
{
    أرجع fifo_write_common(f, عدم, nb_elems, read_cb, opaque);
}

ساكن صحيح fifo_peek_common(ثابت AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t وٿي, AVFifoCB write_cb, فراغ *opaque)
{
    size_t  منزل_read = *nb_elems;
    size_t وٿي_r = f->وٿي_r;
    size_t can_read = av_fifo_can_read(f);
    صحيح         ret = 0;

    إذا (وٿي > can_read || منزل_read > can_read - وٿي) {
        *nb_elems = 0;
        أرجع AVERROR(EINVAL);
    }

    إذا (وٿي_r >= f->nb_elems - وٿي)
        وٿي_r -= f->nb_elems - وٿي;
    وإلا
        وٿي_r += وٿي;

    طالما (منزل_read > 0) {
        size_t    len = FFMIN(f->nb_elems - وٿي_r, منزل_read);
        uint8_t *rptr = f->بفر + وٿي_r * f->elem_سائيز;

        إذا (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            إذا (ret < 0 || len == 0)
                اكسر;
        } وإلا {
            يادگيري_نقل(buf, rptr, len * f->elem_سائيز);
            buf += len * f->elem_سائيز;
        }
        وٿي_r += len;
        إذا (وٿي_r >= f->nb_elems)
            وٿي_r = 0;
        منزل_read -= len;
    }

    *nb_elems -= منزل_read;

    أرجع ret;
}

صحيح av_fifo_read(AVFifo *f, فراغ *buf, size_t nb_elems)
{
    صحيح ret = fifo_peek_common(f, buf, &nb_elems, 0, عدم, عدم);
    av_fifo_drain2(f, nb_elems);
    أرجع ret;
}

صحيح av_fifo_read_منزل_cb(AVFifo *f, AVFifoCB write_cb,
                       فراغ *opaque, size_t *nb_elems)
{
    صحيح ret = fifo_peek_common(f, عدم, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    أرجع ret;
}

صحيح av_fifo_peek(ثابت AVFifo *f, فراغ *buf, size_t nb_elems, size_t وٿي)
{
    أرجع fifo_peek_common(f, buf, &nb_elems, وٿي, عدم, عدم);
}

صحيح av_fifo_peek_منزل_cb(ثابت AVFifo *f, AVFifoCB write_cb, فراغ *opaque,
                       size_t *nb_elems, size_t وٿي)
{
    أرجع fifo_peek_common(f, عدم, nb_elems, وٿي, write_cb, opaque);
}

فراغ av_fifo_drain2(AVFifo *f, size_t سائيز)
{
    ثابت size_t cur_سائيز = av_fifo_can_read(f);

    av_assert0(cur_سائيز >= سائيز);
    إذا (cur_سائيز == سائيز)
        f->is_خالي_جايون = 1;

    إذا (f->وٿي_r >= f->nb_elems - سائيز)
        f->وٿي_r -= f->nb_elems - سائيز;
    وإلا
        f->وٿي_r += سائيز;
}

فراغ av_fifo_reset2(AVFifo *f)
{
    f->وٿي_r = f->وٿي_w = 0;
    f->is_خالي_جايون = 1;
}

فراغ av_fifo_freep2(AVFifo **f)
{
    إذا (*f) {
        av_freep(&(*f)->بفر);
        av_freep(f);
    }
}
