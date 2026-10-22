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

#समावेश "avassert.h"
#समावेश "container_fifo.h"
#समावेश "error.h"
#समावेश "fifo.h"
#समावेश "frame.h"
#समावेश "mem.h"
#समावेश "refstruct.h"

काष्ठा AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    व्योम               *opaque;
    व्योम*             (*container_alloc)(व्योम *opaque);
    व्योम              (*container_reset)(व्योम *opaque, व्योम *obj);
    व्योम              (*container_free) (व्योम *opaque, व्योम *obj);
    पूर्णांक               (*fifo_transfer)  (व्योम *opaque, व्योम *dst, व्योम *src, अचिन्हित flags);

};

अटल पूर्णांक container_fifo_init_entry(AVRefStructOpaque opaque, व्योम *obj)
{
    AVContainerFifo *cf = opaque.nc;
    व्योम **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    अगर (!*pobj)
        वापस AVERROR(ENOMEM);

    वापस 0;
}

अटल व्योम container_fifo_reset_entry(AVRefStructOpaque opaque, व्योम *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(व्योम**)obj);
}

अटल व्योम container_fifo_free_entry(AVRefStructOpaque opaque, व्योम *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(व्योम**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(व्योम *opaque,
                        व्योम* (*container_alloc)(व्योम *opaque),
                        व्योम  (*container_reset)(व्योम *opaque, व्योम *obj),
                        व्योम  (*container_free) (व्योम *opaque, व्योम *obj),
                        पूर्णांक   (*fifo_transfer)  (व्योम *opaque, व्योम *dst, व्योम *src, अचिन्हित flags),
                        अचिन्हित flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(माप(*cf));
    अगर (!cf)
        वापस शून्य;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, माप(व्योम*), AV_FIFO_FLAG_AUTO_GROW);
    अगर (!cf->fifo)
        जाओ fail;

    cf->pool = av_refstruct_pool_alloc_ext(माप(व्योम*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           शून्य);
    अगर (!cf->pool)
        जाओ fail;

    वापस cf;
fail:
    av_container_fifo_free(&cf);
    वापस शून्य;
}

व्योम av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    अगर (!*pcf)
        वापस;

    cf = *pcf;

    अगर (cf->fifo) {
        व्योम *obj;
        जबतक (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

पूर्णांक av_container_fifo_read(AVContainerFifo *cf, व्योम *obj, अचिन्हित flags)
{
    व्योम **psrc;
    पूर्णांक ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    अगर (ret < 0)
        वापस ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    वापस ret;
}

पूर्णांक av_container_fifo_peek(AVContainerFifo *cf, व्योम **pdst, माप_प्रकार offset)
{
    व्योम **pobj;
    पूर्णांक ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    अगर (ret < 0)
        वापस ret;

    *pdst = *pobj;

    वापस 0;
}

व्योम av_container_fifo_drain(AVContainerFifo *cf, माप_प्रकार nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    जबतक (nb_elems--) {
        व्योम **pobj;
        पूर्णांक ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

पूर्णांक av_container_fifo_write(AVContainerFifo *cf, व्योम *obj, अचिन्हित flags)
{
    व्योम **pdst;
    पूर्णांक ret;

    pdst = av_refstruct_pool_get(cf->pool);
    अगर (!pdst)
        वापस AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    अगर (ret < 0)
        जाओ fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    अगर (ret < 0)
        जाओ fail;

    वापस 0;
fail:
    av_refstruct_unref(&pdst);
    वापस ret;
}

माप_प्रकार av_container_fifo_can_read(स्थिर AVContainerFifo *cf)
{
    वापस av_fifo_can_read(cf->fifo);
}

अटल व्योम *frame_alloc(व्योम *opaque)
{
    वापस av_frame_alloc();
}

अटल व्योम frame_reset(व्योम *opaque, व्योम *obj)
{
    av_frame_unref(obj);
}

अटल व्योम frame_free(व्योम *opaque, व्योम *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

अटल पूर्णांक frame_transfer(व्योम *opaque, व्योम *dst, व्योम *src, अचिन्हित flags)
{
    अगर (flags & AV_CONTAINER_FIFO_FLAG_REF)
        वापस av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    वापस 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(अचिन्हित flags)
{
    वापस av_container_fifo_alloc(शून्य, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
