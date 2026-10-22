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

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "container_fifo.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "fifo.h"
#অন্তর্ভাব "frame.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "refstruct.h"

কাঠামো AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    শূন্য               *opaque;
    শূন্য*             (*container_alloc)(শূন্য *opaque);
    শূন্য              (*container_reset)(শূন্য *opaque, শূন্য *obj);
    শূন্য              (*container_free) (শূন্য *opaque, শূন্য *obj);
    পূর্ণসংখ্যা               (*fifo_transfer)  (শূন্য *opaque, শূন্য *dst, শূন্য *src, unsigned flags);

};

স্থির পূর্ণসংখ্যা container_fifo_init_entry(AVRefStructOpaque opaque, শূন্য *obj)
{
    AVContainerFifo *cf = opaque.nc;
    শূন্য **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    যদি (!*pobj)
        ফেরত AVERROR(ENOMEM);

    ফেরত 0;
}

স্থির শূন্য container_fifo_reset_entry(AVRefStructOpaque opaque, শূন্য *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(শূন্য**)obj);
}

স্থির শূন্য container_fifo_free_entry(AVRefStructOpaque opaque, শূন্য *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(শূন্য**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(শূন্য *opaque,
                        শূন্য* (*container_alloc)(শূন্য *opaque),
                        শূন্য  (*container_reset)(শূন্য *opaque, শূন্য *obj),
                        শূন্য  (*container_free) (শূন্য *opaque, শূন্য *obj),
                        পূর্ণসংখ্যা   (*fifo_transfer)  (শূন্য *opaque, শূন্য *dst, শূন্য *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(আকার(*cf));
    যদি (!cf)
        ফেরত ফাঁকা;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, আকার(শূন্য*), AV_FIFO_FLAG_AUTO_GROW);
    যদি (!cf->fifo)
        যাও fail;

    cf->pool = av_refstruct_pool_alloc_ext(আকার(শূন্য*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           ফাঁকা);
    যদি (!cf->pool)
        যাও fail;

    ফেরত cf;
fail:
    av_container_fifo_free(&cf);
    ফেরত ফাঁকা;
}

শূন্য av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    যদি (!*pcf)
        ফেরত;

    cf = *pcf;

    যদি (cf->fifo) {
        শূন্য *obj;
        যখন (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

পূর্ণসংখ্যা av_container_fifo_read(AVContainerFifo *cf, শূন্য *obj, unsigned flags)
{
    শূন্য **psrc;
    পূর্ণসংখ্যা ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    যদি (ret < 0)
        ফেরত ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    ফেরত ret;
}

পূর্ণসংখ্যা av_container_fifo_peek(AVContainerFifo *cf, শূন্য **pdst, size_t offset)
{
    শূন্য **pobj;
    পূর্ণসংখ্যা ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    যদি (ret < 0)
        ফেরত ret;

    *pdst = *pobj;

    ফেরত 0;
}

শূন্য av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    যখন (nb_elems--) {
        শূন্য **pobj;
        পূর্ণসংখ্যা ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

পূর্ণসংখ্যা av_container_fifo_write(AVContainerFifo *cf, শূন্য *obj, unsigned flags)
{
    শূন্য **pdst;
    পূর্ণসংখ্যা ret;

    pdst = av_refstruct_pool_get(cf->pool);
    যদি (!pdst)
        ফেরত AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    যদি (ret < 0)
        যাও fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    যদি (ret < 0)
        যাও fail;

    ফেরত 0;
fail:
    av_refstruct_unref(&pdst);
    ফেরত ret;
}

size_t av_container_fifo_can_read(ধ্রুবক AVContainerFifo *cf)
{
    ফেরত av_fifo_can_read(cf->fifo);
}

স্থির শূন্য *frame_alloc(শূন্য *opaque)
{
    ফেরত av_frame_alloc();
}

স্থির শূন্য frame_reset(শূন্য *opaque, শূন্য *obj)
{
    av_frame_unref(obj);
}

স্থির শূন্য frame_free(শূন্য *opaque, শূন্য *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

স্থির পূর্ণসংখ্যা frame_transfer(শূন্য *opaque, শূন্য *dst, শূন্য *src, unsigned flags)
{
    যদি (flags & AV_CONTAINER_FIFO_FLAG_REF)
        ফেরত av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    ফেরত 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    ফেরত av_container_fifo_alloc(ফাঁকা, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
