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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "fifo.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"

// by default the FIFO can be auto-grown to 1MB
#నిర్వచించు AUTO_GROW_DEFAULT_బైట్లు (1024 * 1024)

నిర్మాణం AVFifo {
    uint8_t *బఫరు;

    size_t elem_కొలత, nb_elems;
    size_t స్థానభ్రంశం_r, స్థానభ్రంశం_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    పూర్ణాంకం    is_ఖాళీలు;

    గుర్తులేని పూర్ణాంకం flags;
    size_t       auto_grow_హద్దు;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_కొలత,
                       గుర్తులేని పూర్ణాంకం flags)
{
    AVFifo *f;
    శూన్య *బఫరు = ఖాళీ;

    ఒకవేళ (!elem_కొలత)
        తిరిగి ఖాళీ;

    ఒకవేళ (nb_elems) {
        బఫరు = av_realloc_array(ఖాళీ, nb_elems, elem_కొలత);
        ఒకవేళ (!బఫరు)
            తిరిగి ఖాళీ;
    }
    f = av_mallocz(పరిమాణం(*f));
    ఒకవేళ (!f) {
        av_free(బఫరు);
        తిరిగి ఖాళీ;
    }
    f->బఫరు    = బఫరు;
    f->nb_elems  = nb_elems;
    f->elem_కొలత = elem_కొలత;
    f->is_ఖాళీలు  = 1;

    f->flags           = flags;
    f->auto_grow_హద్దు = FFMAX(AUTO_GROW_DEFAULT_బైట్లు / elem_కొలత, 1);

    తిరిగి f;
}

శూన్య av_fifo_auto_grow_హద్దు(AVFifo *f, size_t max_elems)
{
    f->auto_grow_హద్దు = max_elems;
}

size_t av_fifo_elem_కొలత(స్థిరరాశి AVFifo *f)
{
    తిరిగి f->elem_కొలత;
}

size_t av_fifo_can_read(స్థిరరాశి AVFifo *f)
{
    ఒకవేళ (f->స్థానభ్రంశం_w <= f->స్థానభ్రంశం_r && !f->is_ఖాళీలు)
        తిరిగి f->nb_elems - f->స్థానభ్రంశం_r + f->స్థానభ్రంశం_w;
    తిరిగి f->స్థానభ్రంశం_w - f->స్థానభ్రంశం_r;
}

size_t av_fifo_can_write(స్థిరరాశి AVFifo *f)
{
    తిరిగి f->nb_elems - av_fifo_can_read(f);
}

పూర్ణాంకం av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    ఒకవేళ (inc > SIZE_MAX - f->nb_elems)
        తిరిగి AVERROR(EINVAL);

    tmp = av_realloc_array(f->బఫరు, f->nb_elems + inc, f->elem_కొలత);
    ఒకవేళ (!tmp)
        తిరిగి AVERROR(ENOMEM);
    f->బఫరు = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    ఒకవేళ (f->స్థానభ్రంశం_w <= f->స్థానభ్రంశం_r && !f->is_ఖాళీలు) {
        స్థిరరాశి size_t copy = FFMIN(inc, f->స్థానభ్రంశం_w);
        జ్ఞాపకం_నకలు(tmp + f->nb_elems * f->elem_కొలత, tmp, copy * f->elem_కొలత);
        ఒకవేళ (copy < f->స్థానభ్రంశం_w) {
            memmove(tmp, tmp + copy * f->elem_కొలత,
                    (f->స్థానభ్రంశం_w - copy) * f->elem_కొలత);
            f->స్థానభ్రంశం_w -= copy;
        } లేకపోతే
            f->స్థానభ్రంశం_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం fifo_check_space(AVFifo *f, size_t గమ్యం_write)
{
    స్థిరరాశి size_t can_write = av_fifo_can_write(f);
    స్థిరరాశి size_t need_grow = గమ్యం_write > can_write ? గమ్యం_write - can_write : 0;
    size_t can_grow;

    ఒకవేళ (!need_grow)
        తిరిగి 0;

    can_grow = f->auto_grow_హద్దు > f->nb_elems ?
               f->auto_grow_హద్దు - f->nb_elems : 0;
    ఒకవేళ ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        స్థిరరాశి size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        తిరిగి av_fifo_grow2(f, inc);
    }

    తిరిగి AVERROR(ENOSPC);
}

స్థిర పూర్ణాంకం fifo_write_common(AVFifo *f, స్థిరరాశి uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, శూన్య *opaque)
{
    size_t గమ్యం_write = *nb_elems;
    size_t స్థానభ్రంశం_w;
    పూర్ణాంకం         ret = 0;

    ret = fifo_check_space(f, గమ్యం_write);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    స్థానభ్రంశం_w = f->స్థానభ్రంశం_w;

    అయితే (గమ్యం_write > 0) {
        size_t    len = FFMIN(f->nb_elems - స్థానభ్రంశం_w, గమ్యం_write);
        uint8_t *wptr = f->బఫరు + స్థానభ్రంశం_w * f->elem_కొలత;

        ఒకవేళ (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            ఒకవేళ (ret < 0 || len == 0)
                ఆపు;
        } లేకపోతే {
            జ్ఞాపకం_నకలు(wptr, buf, len * f->elem_కొలత);
            buf += len * f->elem_కొలత;
        }
        స్థానభ్రంశం_w += len;
        ఒకవేళ (స్థానభ్రంశం_w >= f->nb_elems)
            స్థానభ్రంశం_w = 0;
        గమ్యం_write -= len;
    }
    f->స్థానభ్రంశం_w = స్థానభ్రంశం_w;

    ఒకవేళ (*nb_elems != గమ్యం_write)
        f->is_ఖాళీలు = 0;
    *nb_elems -= గమ్యం_write;

    తిరిగి ret;
}

పూర్ణాంకం av_fifo_write(AVFifo *f, స్థిరరాశి శూన్య *buf, size_t nb_elems)
{
    తిరిగి fifo_write_common(f, buf, &nb_elems, ఖాళీ, ఖాళీ);
}

పూర్ణాంకం av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          శూన్య *opaque, size_t *nb_elems)
{
    తిరిగి fifo_write_common(f, ఖాళీ, nb_elems, read_cb, opaque);
}

స్థిర పూర్ణాంకం fifo_peek_common(స్థిరరాశి AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t స్థానభ్రంశం, AVFifoCB write_cb, శూన్య *opaque)
{
    size_t  గమ్యం_read = *nb_elems;
    size_t స్థానభ్రంశం_r = f->స్థానభ్రంశం_r;
    size_t can_read = av_fifo_can_read(f);
    పూర్ణాంకం         ret = 0;

    ఒకవేళ (స్థానభ్రంశం > can_read || గమ్యం_read > can_read - స్థానభ్రంశం) {
        *nb_elems = 0;
        తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ (స్థానభ్రంశం_r >= f->nb_elems - స్థానభ్రంశం)
        స్థానభ్రంశం_r -= f->nb_elems - స్థానభ్రంశం;
    లేకపోతే
        స్థానభ్రంశం_r += స్థానభ్రంశం;

    అయితే (గమ్యం_read > 0) {
        size_t    len = FFMIN(f->nb_elems - స్థానభ్రంశం_r, గమ్యం_read);
        uint8_t *rptr = f->బఫరు + స్థానభ్రంశం_r * f->elem_కొలత;

        ఒకవేళ (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            ఒకవేళ (ret < 0 || len == 0)
                ఆపు;
        } లేకపోతే {
            జ్ఞాపకం_నకలు(buf, rptr, len * f->elem_కొలత);
            buf += len * f->elem_కొలత;
        }
        స్థానభ్రంశం_r += len;
        ఒకవేళ (స్థానభ్రంశం_r >= f->nb_elems)
            స్థానభ్రంశం_r = 0;
        గమ్యం_read -= len;
    }

    *nb_elems -= గమ్యం_read;

    తిరిగి ret;
}

పూర్ణాంకం av_fifo_read(AVFifo *f, శూన్య *buf, size_t nb_elems)
{
    పూర్ణాంకం ret = fifo_peek_common(f, buf, &nb_elems, 0, ఖాళీ, ఖాళీ);
    av_fifo_drain2(f, nb_elems);
    తిరిగి ret;
}

పూర్ణాంకం av_fifo_read_గమ్యం_cb(AVFifo *f, AVFifoCB write_cb,
                       శూన్య *opaque, size_t *nb_elems)
{
    పూర్ణాంకం ret = fifo_peek_common(f, ఖాళీ, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    తిరిగి ret;
}

పూర్ణాంకం av_fifo_peek(స్థిరరాశి AVFifo *f, శూన్య *buf, size_t nb_elems, size_t స్థానభ్రంశం)
{
    తిరిగి fifo_peek_common(f, buf, &nb_elems, స్థానభ్రంశం, ఖాళీ, ఖాళీ);
}

పూర్ణాంకం av_fifo_peek_గమ్యం_cb(స్థిరరాశి AVFifo *f, AVFifoCB write_cb, శూన్య *opaque,
                       size_t *nb_elems, size_t స్థానభ్రంశం)
{
    తిరిగి fifo_peek_common(f, ఖాళీ, nb_elems, స్థానభ్రంశం, write_cb, opaque);
}

శూన్య av_fifo_drain2(AVFifo *f, size_t కొలత)
{
    స్థిరరాశి size_t cur_కొలత = av_fifo_can_read(f);

    av_assert0(cur_కొలత >= కొలత);
    ఒకవేళ (cur_కొలత == కొలత)
        f->is_ఖాళీలు = 1;

    ఒకవేళ (f->స్థానభ్రంశం_r >= f->nb_elems - కొలత)
        f->స్థానభ్రంశం_r -= f->nb_elems - కొలత;
    లేకపోతే
        f->స్థానభ్రంశం_r += కొలత;
}

శూన్య av_fifo_reset2(AVFifo *f)
{
    f->స్థానభ్రంశం_r = f->స్థానభ్రంశం_w = 0;
    f->is_ఖాళీలు = 1;
}

శూన్య av_fifo_freep2(AVFifo **f)
{
    ఒకవేళ (*f) {
        av_freep(&(*f)->బఫరు);
        av_freep(f);
    }
}
