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

ساختار AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    تهی               *opaque;
    تهی*             (*container_alloc)(تهی *opaque);
    تهی              (*container_reset)(تهی *opaque, تهی *obj);
    تهی              (*container_free) (تهی *opaque, تهی *obj);
    صحیح               (*fifo_transfer)  (تهی *opaque, تهی *dst, تهی *src, unsigned flags);

};

ایستا صحیح container_fifo_init_entry(AVRefStructOpaque opaque, تهی *obj)
{
    AVContainerFifo *cf = opaque.nc;
    تهی **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    اگر (!*pobj)
        بازگشت AVERROR(ENOMEM);

    بازگشت 0;
}

ایستا تهی container_fifo_reset_entry(AVRefStructOpaque opaque, تهی *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(تهی**)obj);
}

ایستا تهی container_fifo_free_entry(AVRefStructOpaque opaque, تهی *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(تهی**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(تهی *opaque,
                        تهی* (*container_alloc)(تهی *opaque),
                        تهی  (*container_reset)(تهی *opaque, تهی *obj),
                        تهی  (*container_free) (تهی *opaque, تهی *obj),
                        صحیح   (*fifo_transfer)  (تهی *opaque, تهی *dst, تهی *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(اندازه(*cf));
    اگر (!cf)
        بازگشت پوچ;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, اندازه(تهی*), AV_FIFO_FLAG_AUTO_GROW);
    اگر (!cf->fifo)
        برو fail;

    cf->pool = av_refstruct_pool_alloc_ext(اندازه(تهی*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           پوچ);
    اگر (!cf->pool)
        برو fail;

    بازگشت cf;
fail:
    av_container_fifo_free(&cf);
    بازگشت پوچ;
}

تهی av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    اگر (!*pcf)
        بازگشت;

    cf = *pcf;

    اگر (cf->fifo) {
        تهی *obj;
        وقتی (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

صحیح av_container_fifo_read(AVContainerFifo *cf, تهی *obj, unsigned flags)
{
    تهی **psrc;
    صحیح ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    اگر (ret < 0)
        بازگشت ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    بازگشت ret;
}

صحیح av_container_fifo_peek(AVContainerFifo *cf, تهی **pdst, size_t offset)
{
    تهی **pobj;
    صحیح ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    اگر (ret < 0)
        بازگشت ret;

    *pdst = *pobj;

    بازگشت 0;
}

تهی av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    وقتی (nb_elems--) {
        تهی **pobj;
        صحیح ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

صحیح av_container_fifo_write(AVContainerFifo *cf, تهی *obj, unsigned flags)
{
    تهی **pdst;
    صحیح ret;

    pdst = av_refstruct_pool_get(cf->pool);
    اگر (!pdst)
        بازگشت AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    اگر (ret < 0)
        برو fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    اگر (ret < 0)
        برو fail;

    بازگشت 0;
fail:
    av_refstruct_unref(&pdst);
    بازگشت ret;
}

size_t av_container_fifo_can_read(ثابت AVContainerFifo *cf)
{
    بازگشت av_fifo_can_read(cf->fifo);
}

ایستا تهی *frame_alloc(تهی *opaque)
{
    بازگشت av_frame_alloc();
}

ایستا تهی frame_reset(تهی *opaque, تهی *obj)
{
    av_frame_unref(obj);
}

ایستا تهی frame_free(تهی *opaque, تهی *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

ایستا صحیح frame_transfer(تهی *opaque, تهی *dst, تهی *src, unsigned flags)
{
    اگر (flags & AV_CONTAINER_FIFO_FLAG_REF)
        بازگشت av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    بازگشت 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    بازگشت av_container_fifo_alloc(پوچ, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
