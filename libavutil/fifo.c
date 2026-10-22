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

#समावेश <stdint.h>
#समावेश <string.h>

#समावेश "avassert.h"
#समावेश "error.h"
#समावेश "fifo.h"
#समावेश "macros.h"
#समावेश "mem.h"

// by default the FIFO can be auto-grown to 1MB
#घोषणा AUTO_GROW_DEFAULT_BYTES (1024 * 1024)

काष्ठा AVFifo {
    uint8_t *बफर;

    माप_प्रकार elem_आकार, nb_elems;
    माप_प्रकार offset_r, offset_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    पूर्णांक    is_empty;

    अचिन्हित पूर्णांक flags;
    माप_प्रकार       auto_grow_limit;
};

AVFifo *av_fifo_alloc2(माप_प्रकार nb_elems, माप_प्रकार elem_आकार,
                       अचिन्हित पूर्णांक flags)
{
    AVFifo *f;
    व्योम *बफर = शून्य;

    अगर (!elem_आकार)
        वापस शून्य;

    अगर (nb_elems) {
        बफर = av_realloc_array(शून्य, nb_elems, elem_आकार);
        अगर (!बफर)
            वापस शून्य;
    }
    f = av_mallocz(माप(*f));
    अगर (!f) {
        av_free(बफर);
        वापस शून्य;
    }
    f->बफर    = बफर;
    f->nb_elems  = nb_elems;
    f->elem_आकार = elem_आकार;
    f->is_empty  = 1;

    f->flags           = flags;
    f->auto_grow_limit = FFMAX(AUTO_GROW_DEFAULT_BYTES / elem_आकार, 1);

    वापस f;
}

व्योम av_fifo_auto_grow_limit(AVFifo *f, माप_प्रकार max_elems)
{
    f->auto_grow_limit = max_elems;
}

माप_प्रकार av_fifo_elem_आकार(स्थिर AVFifo *f)
{
    वापस f->elem_आकार;
}

माप_प्रकार av_fifo_can_read(स्थिर AVFifo *f)
{
    अगर (f->offset_w <= f->offset_r && !f->is_empty)
        वापस f->nb_elems - f->offset_r + f->offset_w;
    वापस f->offset_w - f->offset_r;
}

माप_प्रकार av_fifo_can_write(स्थिर AVFifo *f)
{
    वापस f->nb_elems - av_fifo_can_read(f);
}

पूर्णांक av_fifo_grow2(AVFifo *f, माप_प्रकार inc)
{
    uint8_t *tmp;

    अगर (inc > SIZE_MAX - f->nb_elems)
        वापस AVERROR(EINVAL);

    tmp = av_realloc_array(f->बफर, f->nb_elems + inc, f->elem_आकार);
    अगर (!tmp)
        वापस AVERROR(ENOMEM);
    f->बफर = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    अगर (f->offset_w <= f->offset_r && !f->is_empty) {
        स्थिर माप_प्रकार copy = FFMIN(inc, f->offset_w);
        स_नकल(tmp + f->nb_elems * f->elem_आकार, tmp, copy * f->elem_आकार);
        अगर (copy < f->offset_w) {
            स_हटाओ(tmp, tmp + copy * f->elem_आकार,
                    (f->offset_w - copy) * f->elem_आकार);
            f->offset_w -= copy;
        } अन्यथा
            f->offset_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    वापस 0;
}

अटल पूर्णांक fifo_check_space(AVFifo *f, माप_प्रकार to_write)
{
    स्थिर माप_प्रकार can_write = av_fifo_can_write(f);
    स्थिर माप_प्रकार need_grow = to_write > can_write ? to_write - can_write : 0;
    माप_प्रकार can_grow;

    अगर (!need_grow)
        वापस 0;

    can_grow = f->auto_grow_limit > f->nb_elems ?
               f->auto_grow_limit - f->nb_elems : 0;
    अगर ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        स्थिर माप_प्रकार inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        वापस av_fifo_grow2(f, inc);
    }

    वापस AVERROR(ENOSPC);
}

अटल पूर्णांक fifo_write_common(AVFifo *f, स्थिर uint8_t *buf, माप_प्रकार *nb_elems,
                             AVFifoCB read_cb, व्योम *opaque)
{
    माप_प्रकार to_write = *nb_elems;
    माप_प्रकार offset_w;
    पूर्णांक         ret = 0;

    ret = fifo_check_space(f, to_write);
    अगर (ret < 0)
        वापस ret;

    offset_w = f->offset_w;

    जबतक (to_write > 0) {
        माप_प्रकार    len = FFMIN(f->nb_elems - offset_w, to_write);
        uint8_t *wptr = f->बफर + offset_w * f->elem_आकार;

        अगर (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            अगर (ret < 0 || len == 0)
                अवरोध;
        } अन्यथा {
            स_नकल(wptr, buf, len * f->elem_आकार);
            buf += len * f->elem_आकार;
        }
        offset_w += len;
        अगर (offset_w >= f->nb_elems)
            offset_w = 0;
        to_write -= len;
    }
    f->offset_w = offset_w;

    अगर (*nb_elems != to_write)
        f->is_empty = 0;
    *nb_elems -= to_write;

    वापस ret;
}

पूर्णांक av_fifo_write(AVFifo *f, स्थिर व्योम *buf, माप_प्रकार nb_elems)
{
    वापस fifo_write_common(f, buf, &nb_elems, शून्य, शून्य);
}

पूर्णांक av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          व्योम *opaque, माप_प्रकार *nb_elems)
{
    वापस fifo_write_common(f, शून्य, nb_elems, read_cb, opaque);
}

अटल पूर्णांक fifo_peek_common(स्थिर AVFifo *f, uint8_t *buf, माप_प्रकार *nb_elems,
                            माप_प्रकार offset, AVFifoCB write_cb, व्योम *opaque)
{
    माप_प्रकार  to_read = *nb_elems;
    माप_प्रकार offset_r = f->offset_r;
    माप_प्रकार can_read = av_fifo_can_read(f);
    पूर्णांक         ret = 0;

    अगर (offset > can_read || to_read > can_read - offset) {
        *nb_elems = 0;
        वापस AVERROR(EINVAL);
    }

    अगर (offset_r >= f->nb_elems - offset)
        offset_r -= f->nb_elems - offset;
    अन्यथा
        offset_r += offset;

    जबतक (to_read > 0) {
        माप_प्रकार    len = FFMIN(f->nb_elems - offset_r, to_read);
        uint8_t *rptr = f->बफर + offset_r * f->elem_आकार;

        अगर (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            अगर (ret < 0 || len == 0)
                अवरोध;
        } अन्यथा {
            स_नकल(buf, rptr, len * f->elem_आकार);
            buf += len * f->elem_आकार;
        }
        offset_r += len;
        अगर (offset_r >= f->nb_elems)
            offset_r = 0;
        to_read -= len;
    }

    *nb_elems -= to_read;

    वापस ret;
}

पूर्णांक av_fifo_read(AVFifo *f, व्योम *buf, माप_प्रकार nb_elems)
{
    पूर्णांक ret = fifo_peek_common(f, buf, &nb_elems, 0, शून्य, शून्य);
    av_fifo_drain2(f, nb_elems);
    वापस ret;
}

पूर्णांक av_fifo_read_to_cb(AVFifo *f, AVFifoCB write_cb,
                       व्योम *opaque, माप_प्रकार *nb_elems)
{
    पूर्णांक ret = fifo_peek_common(f, शून्य, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    वापस ret;
}

पूर्णांक av_fifo_peek(स्थिर AVFifo *f, व्योम *buf, माप_प्रकार nb_elems, माप_प्रकार offset)
{
    वापस fifo_peek_common(f, buf, &nb_elems, offset, शून्य, शून्य);
}

पूर्णांक av_fifo_peek_to_cb(स्थिर AVFifo *f, AVFifoCB write_cb, व्योम *opaque,
                       माप_प्रकार *nb_elems, माप_प्रकार offset)
{
    वापस fifo_peek_common(f, शून्य, nb_elems, offset, write_cb, opaque);
}

व्योम av_fifo_drain2(AVFifo *f, माप_प्रकार आकार)
{
    स्थिर माप_प्रकार cur_आकार = av_fifo_can_read(f);

    av_assert0(cur_आकार >= आकार);
    अगर (cur_आकार == आकार)
        f->is_empty = 1;

    अगर (f->offset_r >= f->nb_elems - आकार)
        f->offset_r -= f->nb_elems - आकार;
    अन्यथा
        f->offset_r += आकार;
}

व्योम av_fifo_reset2(AVFifo *f)
{
    f->offset_r = f->offset_w = 0;
    f->is_empty = 1;
}

व्योम av_fifo_freep2(AVFifo **f)
{
    अगर (*f) {
        av_freep(&(*f)->बफर);
        av_freep(f);
    }
}
