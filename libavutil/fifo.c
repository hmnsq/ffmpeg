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
#परिभाषय AUTO_GROW_DEFAULT_अष्टकानि (1024 * 1024)

संरचना AVFifo {
    uint8_t *बफर;

    size_t elem_आकार, nb_elems;
    size_t विस्थापनम्_r, विस्थापनम्_w;
    // distinguishes the ambiguous situation offset_r == offset_w
    पूर्णाङ्क    is_रिक्तानि;

    अचिह्नित पूर्णाङ्क flags;
    size_t       auto_grow_सीमा;
};

AVFifo *av_fifo_alloc2(size_t nb_elems, size_t elem_आकार,
                       अचिह्नित पूर्णाङ्क flags)
{
    AVFifo *f;
    शून्य *बफर = रिक्त;

    यदि (!elem_आकार)
        प्रत्यागम रिक्त;

    यदि (nb_elems) {
        बफर = av_realloc_array(रिक्त, nb_elems, elem_आकार);
        यदि (!बफर)
            प्रत्यागम रिक्त;
    }
    f = av_mallocz(परिमाण(*f));
    यदि (!f) {
        av_free(बफर);
        प्रत्यागम रिक्त;
    }
    f->बफर    = बफर;
    f->nb_elems  = nb_elems;
    f->elem_आकार = elem_आकार;
    f->is_रिक्तानि  = 1;

    f->flags           = flags;
    f->auto_grow_सीमा = FFMAX(AUTO_GROW_DEFAULT_अष्टकानि / elem_आकार, 1);

    प्रत्यागम f;
}

शून्य av_fifo_auto_grow_सीमा(AVFifo *f, size_t max_elems)
{
    f->auto_grow_सीमा = max_elems;
}

size_t av_fifo_elem_आकार(ध्रुव AVFifo *f)
{
    प्रत्यागम f->elem_आकार;
}

size_t av_fifo_can_read(ध्रुव AVFifo *f)
{
    यदि (f->विस्थापनम्_w <= f->विस्थापनम्_r && !f->is_रिक्तानि)
        प्रत्यागम f->nb_elems - f->विस्थापनम्_r + f->विस्थापनम्_w;
    प्रत्यागम f->विस्थापनम्_w - f->विस्थापनम्_r;
}

size_t av_fifo_can_write(ध्रुव AVFifo *f)
{
    प्रत्यागम f->nb_elems - av_fifo_can_read(f);
}

पूर्णाङ्क av_fifo_grow2(AVFifo *f, size_t inc)
{
    uint8_t *tmp;

    यदि (inc > SIZE_MAX - f->nb_elems)
        प्रत्यागम AVERROR(EINVAL);

    tmp = av_realloc_array(f->बफर, f->nb_elems + inc, f->elem_आकार);
    यदि (!tmp)
        प्रत्यागम AVERROR(ENOMEM);
    f->बफर = tmp;

    // move the data from the beginning of the ring buffer
    // to the newly allocated space
    यदि (f->विस्थापनम्_w <= f->विस्थापनम्_r && !f->is_रिक्तानि) {
        ध्रुव size_t copy = FFMIN(inc, f->विस्थापनम्_w);
        स्मृतिं_प्रतिलिख(tmp + f->nb_elems * f->elem_आकार, tmp, copy * f->elem_आकार);
        यदि (copy < f->विस्थापनम्_w) {
            memmove(tmp, tmp + copy * f->elem_आकार,
                    (f->विस्थापनम्_w - copy) * f->elem_आकार);
            f->विस्थापनम्_w -= copy;
        } अन्यथा
            f->विस्थापनम्_w = copy == inc ? 0 : f->nb_elems + copy;
    }

    f->nb_elems += inc;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क fifo_check_space(AVFifo *f, size_t गन्तव्यम्_write)
{
    ध्रुव size_t can_write = av_fifo_can_write(f);
    ध्रुव size_t need_grow = गन्तव्यम्_write > can_write ? गन्तव्यम्_write - can_write : 0;
    size_t can_grow;

    यदि (!need_grow)
        प्रत्यागम 0;

    can_grow = f->auto_grow_सीमा > f->nb_elems ?
               f->auto_grow_सीमा - f->nb_elems : 0;
    यदि ((f->flags & AV_FIFO_FLAG_AUTO_GROW) && need_grow <= can_grow) {
        // allocate a bit more than necessary, if we can
        ध्रुव size_t inc = (need_grow < can_grow / 2 ) ? need_grow * 2 : can_grow;
        प्रत्यागम av_fifo_grow2(f, inc);
    }

    प्रत्यागम AVERROR(ENOSPC);
}

स्थिर पूर्णाङ्क fifo_write_common(AVFifo *f, ध्रुव uint8_t *buf, size_t *nb_elems,
                             AVFifoCB read_cb, शून्य *opaque)
{
    size_t गन्तव्यम्_write = *nb_elems;
    size_t विस्थापनम्_w;
    पूर्णाङ्क         ret = 0;

    ret = fifo_check_space(f, गन्तव्यम्_write);
    यदि (ret < 0)
        प्रत्यागम ret;

    विस्थापनम्_w = f->विस्थापनम्_w;

    यावत् (गन्तव्यम्_write > 0) {
        size_t    len = FFMIN(f->nb_elems - विस्थापनम्_w, गन्तव्यम्_write);
        uint8_t *wptr = f->बफर + विस्थापनम्_w * f->elem_आकार;

        यदि (read_cb) {
            ret = read_cb(opaque, wptr, &len);
            यदि (ret < 0 || len == 0)
                भङ्ग;
        } अन्यथा {
            स्मृतिं_प्रतिलिख(wptr, buf, len * f->elem_आकार);
            buf += len * f->elem_आकार;
        }
        विस्थापनम्_w += len;
        यदि (विस्थापनम्_w >= f->nb_elems)
            विस्थापनम्_w = 0;
        गन्तव्यम्_write -= len;
    }
    f->विस्थापनम्_w = विस्थापनम्_w;

    यदि (*nb_elems != गन्तव्यम्_write)
        f->is_रिक्तानि = 0;
    *nb_elems -= गन्तव्यम्_write;

    प्रत्यागम ret;
}

पूर्णाङ्क av_fifo_write(AVFifo *f, ध्रुव शून्य *buf, size_t nb_elems)
{
    प्रत्यागम fifo_write_common(f, buf, &nb_elems, रिक्त, रिक्त);
}

पूर्णाङ्क av_fifo_write_from_cb(AVFifo *f, AVFifoCB read_cb,
                          शून्य *opaque, size_t *nb_elems)
{
    प्रत्यागम fifo_write_common(f, रिक्त, nb_elems, read_cb, opaque);
}

स्थिर पूर्णाङ्क fifo_peek_common(ध्रुव AVFifo *f, uint8_t *buf, size_t *nb_elems,
                            size_t विस्थापनम्, AVFifoCB write_cb, शून्य *opaque)
{
    size_t  गन्तव्यम्_read = *nb_elems;
    size_t विस्थापनम्_r = f->विस्थापनम्_r;
    size_t can_read = av_fifo_can_read(f);
    पूर्णाङ्क         ret = 0;

    यदि (विस्थापनम् > can_read || गन्तव्यम्_read > can_read - विस्थापनम्) {
        *nb_elems = 0;
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि (विस्थापनम्_r >= f->nb_elems - विस्थापनम्)
        विस्थापनम्_r -= f->nb_elems - विस्थापनम्;
    अन्यथा
        विस्थापनम्_r += विस्थापनम्;

    यावत् (गन्तव्यम्_read > 0) {
        size_t    len = FFMIN(f->nb_elems - विस्थापनम्_r, गन्तव्यम्_read);
        uint8_t *rptr = f->बफर + विस्थापनम्_r * f->elem_आकार;

        यदि (write_cb) {
            ret = write_cb(opaque, rptr, &len);
            यदि (ret < 0 || len == 0)
                भङ्ग;
        } अन्यथा {
            स्मृतिं_प्रतिलिख(buf, rptr, len * f->elem_आकार);
            buf += len * f->elem_आकार;
        }
        विस्थापनम्_r += len;
        यदि (विस्थापनम्_r >= f->nb_elems)
            विस्थापनम्_r = 0;
        गन्तव्यम्_read -= len;
    }

    *nb_elems -= गन्तव्यम्_read;

    प्रत्यागम ret;
}

पूर्णाङ्क av_fifo_read(AVFifo *f, शून्य *buf, size_t nb_elems)
{
    पूर्णाङ्क ret = fifo_peek_common(f, buf, &nb_elems, 0, रिक्त, रिक्त);
    av_fifo_drain2(f, nb_elems);
    प्रत्यागम ret;
}

पूर्णाङ्क av_fifo_read_गन्तव्यम्_cb(AVFifo *f, AVFifoCB write_cb,
                       शून्य *opaque, size_t *nb_elems)
{
    पूर्णाङ्क ret = fifo_peek_common(f, रिक्त, nb_elems, 0, write_cb, opaque);
    av_fifo_drain2(f, *nb_elems);
    प्रत्यागम ret;
}

पूर्णाङ्क av_fifo_peek(ध्रुव AVFifo *f, शून्य *buf, size_t nb_elems, size_t विस्थापनम्)
{
    प्रत्यागम fifo_peek_common(f, buf, &nb_elems, विस्थापनम्, रिक्त, रिक्त);
}

पूर्णाङ्क av_fifo_peek_गन्तव्यम्_cb(ध्रुव AVFifo *f, AVFifoCB write_cb, शून्य *opaque,
                       size_t *nb_elems, size_t विस्थापनम्)
{
    प्रत्यागम fifo_peek_common(f, रिक्त, nb_elems, विस्थापनम्, write_cb, opaque);
}

शून्य av_fifo_drain2(AVFifo *f, size_t आकार)
{
    ध्रुव size_t cur_आकार = av_fifo_can_read(f);

    av_assert0(cur_आकार >= आकार);
    यदि (cur_आकार == आकार)
        f->is_रिक्तानि = 1;

    यदि (f->विस्थापनम्_r >= f->nb_elems - आकार)
        f->विस्थापनम्_r -= f->nb_elems - आकार;
    अन्यथा
        f->विस्थापनम्_r += आकार;
}

शून्य av_fifo_reset2(AVFifo *f)
{
    f->विस्थापनम्_r = f->विस्थापनम्_w = 0;
    f->is_रिक्तानि = 1;
}

शून्य av_fifo_freep2(AVFifo **f)
{
    यदि (*f) {
        av_freep(&(*f)->बफर);
        av_freep(f);
    }
}
