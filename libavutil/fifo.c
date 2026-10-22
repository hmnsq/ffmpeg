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

#شامل <stdint.h>
#شامل <string.h>

#شامل "avassert.h"
#شامل "error.h"
#شامل "fifo.h"
#شامل "macros.h"
#شامل "mem.h"

// by default the FIFO can be auto-grown to 1MB
#تعریف_کرو AUTO_GROW_DEFAULT_بائٹیں (1024 * 1024)

ساخت AVFifo {
    uint8_t *بفر;

    size_t elem_سائز, nb_elems;
    size_t انحراف_r, انحراف_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    صحیح    is_خالی_خانے;

    غیرعلامتی صحیح flags;
    size_t       auto_grow_حد_بندی;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_سائز,
                       غیرعلامتی صحیح flags)
{
    AVFifo *f;
    خالی *بفر = تہی;

    اگر (!elem_سائز)
        واپس تہی;

    اگر (nb_elems) {
        بفر = av_realloc_array(تہی, nb_elems, elem_سائز);
        اگر (!بفر)
            واپس تہی;
    }
    f = av_mallocz(حجم(*f));
    اگر (!f) {
        av_free(بفر);
        واپس تہی;
    }
    f->بفر    = بفر;
    f->nb_elems  = nb_elems;
    f->elem_سائز = elem_سائز;
    f->is_خالی_خانے  = 1;

    f->flags           = flags;
    f->auto_grow_حد_بندی = FFMAX(AUTO_GROW_DEFAULT_بائٹیں / elem_سائز, 1);

    واپس f;
}

خالی av_fifo_auto_grow_حد_بندی(AVFifo *f, size_t max_elems)
{
    f->auto_grow_حد_بندی = max_elems;
}

size_t av_fifo_elem_سائز(ثابت AVFifo *f)
{
    واپس f->elem_سائز;
}

size_t av_fifo_can_read(ثابت AVFifo *f)
{
    اگر (f->انحراف_w <= f->انحراف_r && !f->is_خالی_خانے)
        واپس f->nb_elems - f->انحراف_r + f->انحراف_w;
    واپس f->انحراف_w - f->انحراف_r;
}

size_t av_fifo_can_write(ثابت AVFifo *f)
{
    واپس f->nb_elems - av_fifo_can_read(f);
}

صحیح av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    اگر (inc > SIZE_MAX - f->nb_elems)
        واپس AVERROR(EINVAL);

    tmp = av_realloc_array(f->بفر, f->nb_elems + inc, f->elem_سائز);
    اگر (!tmp)
        واپس AVERROR(ENOMEM);
    f->بفر = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    اگر (f->انحراف_w <= f->انحراف_r && !f->is_خالی_خانے) {
        ثابت size_t copy = FFMIN(inc, f->انحراف_w);
        حافظہ_نقل(tmp + f->nb_elems * f->elem_سائز, tmp, copy * f->elem_سائز);
        اگر (copy < f->انحراف_w) {
            memmove(tmp, tmp + copy * f->elem_سائز,
                    (f->انحراف_w - copy) * f->elem_سائز);
            f->انحراف_w -= copy;
        } ورنہ
            f->انحراف_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    واپس 0;
}

ساکن صحیح fifo_check_space(AVFifo *f, size_t مقصد_write)
{
    ثابت size_t can_write = av_fifo_can_write(f);
    ثابت size_t need_grow = مقصد_write > can_write ? مقصد_write - can_write : 0;
    size_t can_grow;

    اگر (!need_grow)
        واپس 0;

    can_grow = f->auto_grow_حد_بندی > f->nb_elems ?
               f->auto_grow_حد_بندی - f->nb_elems : 0;
    اگر ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ثابت size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        واپس av_fifo_grow2(f, inc);
    }

    واپس AVERROR(ENOSPC);
}

ساکن صحیح fifo_write_common(AVFifo *f, ثابت uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, خالی *opaque)
{
    size_t مقصد_write = *nb_elems;
    size_t انحراف_w;
    صحیح         ret = 0;

    ret = fifo_check_space(f, مقصد_write);
    اگر (ret < 0)
        واپس ret;

    انحراف_w = f->انحراف_w;

    جب (مقصد_write > 0) {
        size_t    len = FFMIN(f->nb_elems - انحراف_w, مقصد_write);
        uint8_t *wptr = f->بفر + انحراف_w * f->elem_سائز;

        اگر (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            اگر (ret < 0 || len == 0)
                توڑو;
        } ورنہ {
            حافظہ_نقل(wptr, buf, len * f->elem_سائز);
            buf += len * f->elem_سائز;
        }
        انحراف_w += len;
        اگر (انحراف_w >= f->nb_elems)
            انحراف_w = 0;
        مقصد_write -= len;
    }
    f->انحراف_w = انحراف_w;

    اگر (*nb_elems != مقصد_write)
        f->is_خالی_خانے = 0;
    *nb_elems -= مقصد_write;

    واپس ret;
}

صحیح av_fifo_write(AVFifo *f, ثابت خالی *buf, size_t nb_elems)
{
    واپس fifo_write_common(f, buf, &nb_elems, تہی, تہی);
}

صحیح av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          خالی *opaque, size_t *nb_elems)
{
    واپس fifo_write_common(f, تہی, nb_elems, read_cb, opaque);
}

ساکن صحیح fifo_peek_common(ثابت AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t انحراف, AVFifoCB write_cb, خالی *opaque)
{
    size_t  مقصد_read = *nb_elems;
    size_t انحراف_r = f->انحراف_r;
    size_t can_read = av_fifo_can_read(f);
    صحیح         ret = 0;

    اگر (انحراف > can_read || مقصد_read > can_read - انحراف) {
        *nb_elems = 0;
        واپس AVERROR(EINVAL);
    }

    اگر (انحراف_r >= f->nb_elems - انحراف)
        انحراف_r -= f->nb_elems - انحراف;
    ورنہ
        انحراف_r += انحراف;

    جب (مقصد_read > 0) {
        size_t    len = FFMIN(f->nb_elems - انحراف_r, مقصد_read);
        uint8_t *rptr = f->بفر + انحراف_r * f->elem_سائز;

        اگر (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            اگر (ret < 0 || len == 0)
                توڑو;
        } ورنہ {
            حافظہ_نقل(buf, rptr, len * f->elem_سائز);
            buf += len * f->elem_سائز;
        }
        انحراف_r += len;
        اگر (انحراف_r >= f->nb_elems)
            انحراف_r = 0;
        مقصد_read -= len;
    }

    *nb_elems -= مقصد_read;

    واپس ret;
}

صحیح av_fifo_read(AVFifo *f, خالی *buf, size_t nb_elems)
{
    صحیح ret = fifo_peek_common(f, buf, &nb_elems, 0, تہی, تہی);
    av_fifo_drain2(f, nb_elems);
    واپس ret;
}

صحیح av_fifo_read_مقصد_cb(AVFifo *f, AVFifoCB write_cb,
                       خالی *opaque, size_t *nb_elems)
{
    صحیح ret = fifo_peek_common(f, تہی, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    واپس ret;
}

صحیح av_fifo_peek(ثابت AVFifo *f, خالی *buf, size_t nb_elems, size_t انحراف)
{
    واپس fifo_peek_common(f, buf, &nb_elems, انحراف, تہی, تہی);
}

صحیح av_fifo_peek_مقصد_cb(ثابت AVFifo *f, AVFifoCB write_cb, خالی *opaque,
                       size_t *nb_elems, size_t انحراف)
{
    واپس fifo_peek_common(f, تہی, nb_elems, انحراف, write_cb, opaque);
}

خالی av_fifo_drain2(AVFifo *f, size_t سائز)
{
    ثابت size_t cur_سائز = av_fifo_can_read(f);

    av_assert0(cur_سائز >= سائز);
    اگر (cur_سائز == سائز)
        f->is_خالی_خانے = 1;

    اگر (f->انحراف_r >= f->nb_elems - سائز)
        f->انحراف_r -= f->nb_elems - سائز;
    ورنہ
        f->انحراف_r += سائز;
}

خالی av_fifo_reset2(AVFifo *f)
{
    f->انحراف_r = f->انحراف_w = 0;
    f->is_خالی_خانے = 1;
}

خالی av_fifo_freep2(AVFifo **f)
{
    اگر (*f) {
        av_freep(&(*f)->بفر);
        av_freep(f);
    }
}
