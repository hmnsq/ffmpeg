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

#شامل "avassert.h"
#شامل "container_fifo.h"
#شامل "error.h"
#شامل "fifo.h"
#شامل "frame.h"
#شامل "mem.h"
#شامل "refstruct.h"

ساخت AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    خالی               *opaque;
    خالی*             (*container_alloc)(خالی *opaque);
    خالی              (*container_reset)(خالی *opaque, خالی *obj);
    خالی              (*container_free) (خالی *opaque, خالی *obj);
    صحیح               (*fifo_transfer)  (خالی *opaque, خالی *dst, خالی *src, غیرعلامتی flags);

};

ساکن صحیح container_fifo_init_اندراج(AVRefStructOpaque opaque, خالی *obj)
{
    AVContainerFifo *cf = opaque.nc;
    خالی **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    اگر (!*pobj)
        واپس AVERROR(ENOMEM);

    واپس 0;
}

ساکن خالی container_fifo_reset_اندراج(AVRefStructOpaque opaque, خالی *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(خالی**)obj);
}

ساکن خالی container_fifo_free_اندراج(AVRefStructOpaque opaque, خالی *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(خالی**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(خالی *opaque,
                        خالی* (*container_alloc)(خالی *opaque),
                        خالی  (*container_reset)(خالی *opaque, خالی *obj),
                        خالی  (*container_free) (خالی *opaque, خالی *obj),
                        صحیح   (*fifo_transfer)  (خالی *opaque, خالی *dst, خالی *src, غیرعلامتی flags),
                        غیرعلامتی flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(حجم(*cf));
    اگر (!cf)
        واپس تہی;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, حجم(خالی*), AV_FIFO_FLAG_AUTO_GROW);
    اگر (!cf->fifo)
        جاؤ fail;

    cf->pool = av_refstruct_pool_alloc_ext(حجم(خالی*), 0, cf,
                                           container_fifo_init_اندراج,
                                           container_fifo_reset_اندراج,
                                           container_fifo_free_اندراج,
                                           تہی);
    اگر (!cf->pool)
        جاؤ fail;

    واپس cf;
fail:
    av_container_fifo_free(&cf);
    واپس تہی;
}

خالی av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    اگر (!*pcf)
        واپس;

    cf = *pcf;

    اگر (cf->fifo) {
        خالی *obj;
        جب (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

صحیح av_container_fifo_read(AVContainerFifo *cf, خالی *obj, غیرعلامتی flags)
{
    خالی **psrc;
    صحیح ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    اگر (ret < 0)
        واپس ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    واپس ret;
}

صحیح av_container_fifo_peek(AVContainerFifo *cf, خالی **pdst, size_t انحراف)
{
    خالی **pobj;
    صحیح ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, انحراف);
    اگر (ret < 0)
        واپس ret;

    *pdst = *pobj;

    واپس 0;
}

خالی av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    جب (nb_elems--) {
        خالی **pobj;
        صحیح ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

صحیح av_container_fifo_write(AVContainerFifo *cf, خالی *obj, غیرعلامتی flags)
{
    خالی **pdst;
    صحیح ret;

    pdst = av_refstruct_pool_get(cf->pool);
    اگر (!pdst)
        واپس AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    اگر (ret < 0)
        جاؤ fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    اگر (ret < 0)
        جاؤ fail;

    واپس 0;
fail:
    av_refstruct_unref(&pdst);
    واپس ret;
}

size_t av_container_fifo_can_read(ثابت AVContainerFifo *cf)
{
    واپس av_fifo_can_read(cf->fifo);
}

ساکن خالی *چوکھٹا_alloc(خالی *opaque)
{
    واپس av_چوکھٹا_alloc();
}

ساکن خالی چوکھٹا_reset(خالی *opaque, خالی *obj)
{
    av_چوکھٹا_unref(obj);
}

ساکن خالی چوکھٹا_free(خالی *opaque, خالی *obj)
{
    AVFrame *چوکھٹا = obj;
    av_چوکھٹا_free(&چوکھٹا);
}

ساکن صحیح چوکھٹا_transfer(خالی *opaque, خالی *dst, خالی *src, غیرعلامتی flags)
{
    اگر (flags & AV_CONTAINER_FIFO_FLAG_REF)
        واپس av_چوکھٹا_ref(dst, src);

    av_چوکھٹا_move_ref(dst, src);
    واپس 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(غیرعلامتی flags)
{
    واپس av_container_fifo_alloc(تہی, چوکھٹا_alloc, چوکھٹا_reset, چوکھٹا_free,
                                   چوکھٹا_transfer, 0);
}
