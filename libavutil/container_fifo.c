/*
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

#ضمن "avassert.h"
#ضمن "container_fifo.h"
#ضمن "error.h"
#ضمن "fifo.h"
#ضمن "frame.h"
#ضمن "mem.h"
#ضمن "refstruct.h"

بنية AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    فراغ               *opaque;
    فراغ*             (*container_alloc)(فراغ *opaque);
    فراغ              (*container_reset)(فراغ *opaque, فراغ *obj);
    فراغ              (*container_free) (فراغ *opaque, فراغ *obj);
    صحيح               (*fifo_transfer)  (فراغ *opaque, فراغ *dst, فراغ *src, unsigned flags);

};

ساكن صحيح container_fifo_init_entry(AVRefStructOpaque opaque, فراغ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    فراغ **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    إذا (!*pobj)
        إرجاع AVERROR(ENOMEM);

    إرجاع 0;
}

ساكن فراغ container_fifo_reset_entry(AVRefStructOpaque opaque, فراغ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(فراغ**)obj);
}

ساكن فراغ container_fifo_free_entry(AVRefStructOpaque opaque, فراغ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(فراغ**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(فراغ *opaque,
                        فراغ* (*container_alloc)(فراغ *opaque),
                        فراغ  (*container_reset)(فراغ *opaque, فراغ *obj),
                        فراغ  (*container_free) (فراغ *opaque, فراغ *obj),
                        صحيح   (*fifo_transfer)  (فراغ *opaque, فراغ *dst, فراغ *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(حجم(*cf));
    إذا (!cf)
        إرجاع عدم;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, حجم(فراغ*), AV_FIFO_FLAG_AUTO_GROW);
    إذا (!cf->fifo)
        اذهب fail;

    cf->pool = av_refstruct_pool_alloc_ext(حجم(فراغ*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           عدم);
    إذا (!cf->pool)
        اذهب fail;

    إرجاع cf;
fail:
    av_container_fifo_free(&cf);
    إرجاع عدم;
}

فراغ av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    إذا (!*pcf)
        إرجاع;

    cf = *pcf;

    إذا (cf->fifo) {
        فراغ *obj;
        بينما (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

صحيح av_container_fifo_read(AVContainerFifo *cf, فراغ *obj, unsigned flags)
{
    فراغ **psrc;
    صحيح ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    إذا (ret < 0)
        إرجاع ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    إرجاع ret;
}

صحيح av_container_fifo_peek(AVContainerFifo *cf, فراغ **pdst, size_t offset)
{
    فراغ **pobj;
    صحيح ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    إذا (ret < 0)
        إرجاع ret;

    *pdst = *pobj;

    إرجاع 0;
}

فراغ av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    بينما (nb_elems--) {
        فراغ **pobj;
        صحيح ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

صحيح av_container_fifo_write(AVContainerFifo *cf, فراغ *obj, unsigned flags)
{
    فراغ **pdst;
    صحيح ret;

    pdst = av_refstruct_pool_get(cf->pool);
    إذا (!pdst)
        إرجاع AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    إذا (ret < 0)
        اذهب fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    إذا (ret < 0)
        اذهب fail;

    إرجاع 0;
fail:
    av_refstruct_unref(&pdst);
    إرجاع ret;
}

size_t av_container_fifo_can_read(ثابت AVContainerFifo *cf)
{
    إرجاع av_fifo_can_read(cf->fifo);
}

ساكن فراغ *frame_alloc(فراغ *opaque)
{
    إرجاع av_frame_alloc();
}

ساكن فراغ frame_reset(فراغ *opaque, فراغ *obj)
{
    av_frame_unref(obj);
}

ساكن فراغ frame_free(فراغ *opaque, فراغ *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

ساكن صحيح frame_transfer(فراغ *opaque, فراغ *dst, فراغ *src, unsigned flags)
{
    إذا (flags & AV_CONTAINER_FIFO_FLAG_REF)
        إرجاع av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    إرجاع 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    إرجاع av_container_fifo_alloc(عدم, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
