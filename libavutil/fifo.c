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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "fifo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

// by default the FIFO can be auto-grown to 1MB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AUTO_GROW_DEFAULT_ਬਾਈਟਾਂ (1024 * 1024)

ਬਣਤਰ AVFifo {
    uint8_t *ਬਫਰ;

    size_t elem_ਮਾਪ, nb_elems;
    size_t ਵਿੱਥ_r, ਵਿੱਥ_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    ਪੂਰਨ    is_ਖਾਲੀ_ਥਾਵਾਂ;

    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flags;
    size_t       auto_grow_ਹੱਦਬੰਦੀ;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_ਮਾਪ,
                       ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flags)
{
    AVFifo *f;
    ਖਾਲੀ *ਬਫਰ = ਨਿਰਾ;

    ਜੇ (!elem_ਮਾਪ)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (nb_elems) {
        ਬਫਰ = av_realloc_array(ਨਿਰਾ, nb_elems, elem_ਮਾਪ);
        ਜੇ (!ਬਫਰ)
            ਵਾਪਸ ਨਿਰਾ;
    }
    f = av_mallocz(ਆਕਾਰ(*f));
    ਜੇ (!f) {
        av_free(ਬਫਰ);
        ਵਾਪਸ ਨਿਰਾ;
    }
    f->ਬਫਰ    = ਬਫਰ;
    f->nb_elems  = nb_elems;
    f->elem_ਮਾਪ = elem_ਮਾਪ;
    f->is_ਖਾਲੀ_ਥਾਵਾਂ  = 1;

    f->flags           = flags;
    f->auto_grow_ਹੱਦਬੰਦੀ = FFMAX(AUTO_GROW_DEFAULT_ਬਾਈਟਾਂ / elem_ਮਾਪ, 1);

    ਵਾਪਸ f;
}

ਖਾਲੀ av_fifo_auto_grow_ਹੱਦਬੰਦੀ(AVFifo *f, size_t max_elems)
{
    f->auto_grow_ਹੱਦਬੰਦੀ = max_elems;
}

size_t av_fifo_elem_ਮਾਪ(ਅਚਲ AVFifo *f)
{
    ਵਾਪਸ f->elem_ਮਾਪ;
}

size_t av_fifo_can_read(ਅਚਲ AVFifo *f)
{
    ਜੇ (f->ਵਿੱਥ_w <= f->ਵਿੱਥ_r && !f->is_ਖਾਲੀ_ਥਾਵਾਂ)
        ਵਾਪਸ f->nb_elems - f->ਵਿੱਥ_r + f->ਵਿੱਥ_w;
    ਵਾਪਸ f->ਵਿੱਥ_w - f->ਵਿੱਥ_r;
}

size_t av_fifo_can_write(ਅਚਲ AVFifo *f)
{
    ਵਾਪਸ f->nb_elems - av_fifo_can_read(f);
}

ਪੂਰਨ av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    ਜੇ (inc > SIZE_MAX - f->nb_elems)
        ਵਾਪਸ AVERROR(EINVAL);

    tmp = av_realloc_array(f->ਬਫਰ, f->nb_elems + inc, f->elem_ਮਾਪ);
    ਜੇ (!tmp)
        ਵਾਪਸ AVERROR(ENOMEM);
    f->ਬਫਰ = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    ਜੇ (f->ਵਿੱਥ_w <= f->ਵਿੱਥ_r && !f->is_ਖਾਲੀ_ਥਾਵਾਂ) {
        ਅਚਲ size_t copy = FFMIN(inc, f->ਵਿੱਥ_w);
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(tmp + f->nb_elems * f->elem_ਮਾਪ, tmp, copy * f->elem_ਮਾਪ);
        ਜੇ (copy < f->ਵਿੱਥ_w) {
            memmove(tmp, tmp + copy * f->elem_ਮਾਪ,
                    (f->ਵਿੱਥ_w - copy) * f->elem_ਮਾਪ);
            f->ਵਿੱਥ_w -= copy;
        } ਨਹੀਂਤਾਂ
            f->ਵਿੱਥ_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ fifo_check_space(AVFifo *f, size_t ਮੰਜ਼ਿਲ_write)
{
    ਅਚਲ size_t can_write = av_fifo_can_write(f);
    ਅਚਲ size_t need_grow = ਮੰਜ਼ਿਲ_write > can_write ? ਮੰਜ਼ਿਲ_write - can_write : 0;
    size_t can_grow;

    ਜੇ (!need_grow)
        ਵਾਪਸ 0;

    can_grow = f->auto_grow_ਹੱਦਬੰਦੀ > f->nb_elems ?
               f->auto_grow_ਹੱਦਬੰਦੀ - f->nb_elems : 0;
    ਜੇ ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ਅਚਲ size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        ਵਾਪਸ av_fifo_grow2(f, inc);
    }

    ਵਾਪਸ AVERROR(ENOSPC);
}

ਸਥਿਰ ਪੂਰਨ fifo_write_common(AVFifo *f, ਅਚਲ uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, ਖਾਲੀ *opaque)
{
    size_t ਮੰਜ਼ਿਲ_write = *nb_elems;
    size_t ਵਿੱਥ_w;
    ਪੂਰਨ         ret = 0;

    ret = fifo_check_space(f, ਮੰਜ਼ਿਲ_write);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਵਿੱਥ_w = f->ਵਿੱਥ_w;

    ਜਦੋਂ (ਮੰਜ਼ਿਲ_write > 0) {
        size_t    len = FFMIN(f->nb_elems - ਵਿੱਥ_w, ਮੰਜ਼ਿਲ_write);
        uint8_t *wptr = f->ਬਫਰ + ਵਿੱਥ_w * f->elem_ਮਾਪ;

        ਜੇ (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            ਜੇ (ret < 0 || len == 0)
                ਰੋਕੋ;
        } ਨਹੀਂਤਾਂ {
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(wptr, buf, len * f->elem_ਮਾਪ);
            buf += len * f->elem_ਮਾਪ;
        }
        ਵਿੱਥ_w += len;
        ਜੇ (ਵਿੱਥ_w >= f->nb_elems)
            ਵਿੱਥ_w = 0;
        ਮੰਜ਼ਿਲ_write -= len;
    }
    f->ਵਿੱਥ_w = ਵਿੱਥ_w;

    ਜੇ (*nb_elems != ਮੰਜ਼ਿਲ_write)
        f->is_ਖਾਲੀ_ਥਾਵਾਂ = 0;
    *nb_elems -= ਮੰਜ਼ਿਲ_write;

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_fifo_write(AVFifo *f, ਅਚਲ ਖਾਲੀ *buf, size_t nb_elems)
{
    ਵਾਪਸ fifo_write_common(f, buf, &nb_elems, ਨਿਰਾ, ਨਿਰਾ);
}

ਪੂਰਨ av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          ਖਾਲੀ *opaque, size_t *nb_elems)
{
    ਵਾਪਸ fifo_write_common(f, ਨਿਰਾ, nb_elems, read_cb, opaque);
}

ਸਥਿਰ ਪੂਰਨ fifo_peek_common(ਅਚਲ AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t ਵਿੱਥ, AVFifoCB write_cb, ਖਾਲੀ *opaque)
{
    size_t  ਮੰਜ਼ਿਲ_read = *nb_elems;
    size_t ਵਿੱਥ_r = f->ਵਿੱਥ_r;
    size_t can_read = av_fifo_can_read(f);
    ਪੂਰਨ         ret = 0;

    ਜੇ (ਵਿੱਥ > can_read || ਮੰਜ਼ਿਲ_read > can_read - ਵਿੱਥ) {
        *nb_elems = 0;
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ (ਵਿੱਥ_r >= f->nb_elems - ਵਿੱਥ)
        ਵਿੱਥ_r -= f->nb_elems - ਵਿੱਥ;
    ਨਹੀਂਤਾਂ
        ਵਿੱਥ_r += ਵਿੱਥ;

    ਜਦੋਂ (ਮੰਜ਼ਿਲ_read > 0) {
        size_t    len = FFMIN(f->nb_elems - ਵਿੱਥ_r, ਮੰਜ਼ਿਲ_read);
        uint8_t *rptr = f->ਬਫਰ + ਵਿੱਥ_r * f->elem_ਮਾਪ;

        ਜੇ (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            ਜੇ (ret < 0 || len == 0)
                ਰੋਕੋ;
        } ਨਹੀਂਤਾਂ {
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(buf, rptr, len * f->elem_ਮਾਪ);
            buf += len * f->elem_ਮਾਪ;
        }
        ਵਿੱਥ_r += len;
        ਜੇ (ਵਿੱਥ_r >= f->nb_elems)
            ਵਿੱਥ_r = 0;
        ਮੰਜ਼ਿਲ_read -= len;
    }

    *nb_elems -= ਮੰਜ਼ਿਲ_read;

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_fifo_read(AVFifo *f, ਖਾਲੀ *buf, size_t nb_elems)
{
    ਪੂਰਨ ret = fifo_peek_common(f, buf, &nb_elems, 0, ਨਿਰਾ, ਨਿਰਾ);
    av_fifo_drain2(f, nb_elems);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_fifo_read_ਮੰਜ਼ਿਲ_cb(AVFifo *f, AVFifoCB write_cb,
                       ਖਾਲੀ *opaque, size_t *nb_elems)
{
    ਪੂਰਨ ret = fifo_peek_common(f, ਨਿਰਾ, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_fifo_peek(ਅਚਲ AVFifo *f, ਖਾਲੀ *buf, size_t nb_elems, size_t ਵਿੱਥ)
{
    ਵਾਪਸ fifo_peek_common(f, buf, &nb_elems, ਵਿੱਥ, ਨਿਰਾ, ਨਿਰਾ);
}

ਪੂਰਨ av_fifo_peek_ਮੰਜ਼ਿਲ_cb(ਅਚਲ AVFifo *f, AVFifoCB write_cb, ਖਾਲੀ *opaque,
                       size_t *nb_elems, size_t ਵਿੱਥ)
{
    ਵਾਪਸ fifo_peek_common(f, ਨਿਰਾ, nb_elems, ਵਿੱਥ, write_cb, opaque);
}

ਖਾਲੀ av_fifo_drain2(AVFifo *f, size_t ਮਾਪ)
{
    ਅਚਲ size_t cur_ਮਾਪ = av_fifo_can_read(f);

    av_assert0(cur_ਮਾਪ >= ਮਾਪ);
    ਜੇ (cur_ਮਾਪ == ਮਾਪ)
        f->is_ਖਾਲੀ_ਥਾਵਾਂ = 1;

    ਜੇ (f->ਵਿੱਥ_r >= f->nb_elems - ਮਾਪ)
        f->ਵਿੱਥ_r -= f->nb_elems - ਮਾਪ;
    ਨਹੀਂਤਾਂ
        f->ਵਿੱਥ_r += ਮਾਪ;
}

ਖਾਲੀ av_fifo_reset2(AVFifo *f)
{
    f->ਵਿੱਥ_r = f->ਵਿੱਥ_w = 0;
    f->is_ਖਾਲੀ_ਥਾਵਾਂ = 1;
}

ਖਾਲੀ av_fifo_freep2(AVFifo **f)
{
    ਜੇ (*f) {
        av_freep(&(*f)->ਬਫਰ);
        av_freep(f);
    }
}
