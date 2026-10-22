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

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "container_fifo.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "fifo.h"
#अन्तर्भाव "frame.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "refstruct.h"

संरचना AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    शून्य               *opaque;
    शून्य*             (*container_alloc)(शून्य *opaque);
    शून्य              (*container_reset)(शून्य *opaque, शून्य *obj);
    शून्य              (*container_free) (शून्य *opaque, शून्य *obj);
    पूर्णाङ्क               (*fifo_transfer)  (शून्य *opaque, शून्य *dst, शून्य *src, अचिन्हित flags);

};

स्थिर पूर्णाङ्क container_fifo_init_entry(AVRefStructOpaque opaque, शून्य *obj)
{
    AVContainerFifo *cf = opaque.nc;
    शून्य **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    यदि (!*pobj)
        प्रत्यागम AVERROR(ENOMEM);

    प्रत्यागम 0;
}

स्थिर शून्य container_fifo_reset_entry(AVRefStructOpaque opaque, शून्य *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(शून्य**)obj);
}

स्थिर शून्य container_fifo_free_entry(AVRefStructOpaque opaque, शून्य *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(शून्य**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(शून्य *opaque,
                        शून्य* (*container_alloc)(शून्य *opaque),
                        शून्य  (*container_reset)(शून्य *opaque, शून्य *obj),
                        शून्य  (*container_free) (शून्य *opaque, शून्य *obj),
                        पूर्णाङ्क   (*fifo_transfer)  (शून्य *opaque, शून्य *dst, शून्य *src, अचिन्हित flags),
                        अचिन्हित flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(परिमाण(*cf));
    यदि (!cf)
        प्रत्यागम रिक्त;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, परिमाण(शून्य*), AV_FIFO_FLAG_AUTO_GROW);
    यदि (!cf->fifo)
        गच्छ fail;

    cf->pool = av_refstruct_pool_alloc_ext(परिमाण(शून्य*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           रिक्त);
    यदि (!cf->pool)
        गच्छ fail;

    प्रत्यागम cf;
fail:
    av_container_fifo_free(&cf);
    प्रत्यागम रिक्त;
}

शून्य av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    यदि (!*pcf)
        प्रत्यागम;

    cf = *pcf;

    यदि (cf->fifo) {
        शून्य *obj;
        यावत् (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

पूर्णाङ्क av_container_fifo_read(AVContainerFifo *cf, शून्य *obj, अचिन्हित flags)
{
    शून्य **psrc;
    पूर्णाङ्क ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    यदि (ret < 0)
        प्रत्यागम ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    प्रत्यागम ret;
}

पूर्णाङ्क av_container_fifo_peek(AVContainerFifo *cf, शून्य **pdst, माप_प्रकार offset)
{
    शून्य **pobj;
    पूर्णाङ्क ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    यदि (ret < 0)
        प्रत्यागम ret;

    *pdst = *pobj;

    प्रत्यागम 0;
}

शून्य av_container_fifo_drain(AVContainerFifo *cf, माप_प्रकार nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    यावत् (nb_elems--) {
        शून्य **pobj;
        पूर्णाङ्क ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

पूर्णाङ्क av_container_fifo_write(AVContainerFifo *cf, शून्य *obj, अचिन्हित flags)
{
    शून्य **pdst;
    पूर्णाङ्क ret;

    pdst = av_refstruct_pool_get(cf->pool);
    यदि (!pdst)
        प्रत्यागम AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    यदि (ret < 0)
        गच्छ fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    यदि (ret < 0)
        गच्छ fail;

    प्रत्यागम 0;
fail:
    av_refstruct_unref(&pdst);
    प्रत्यागम ret;
}

माप_प्रकार av_container_fifo_can_read(ध्रुव AVContainerFifo *cf)
{
    प्रत्यागम av_fifo_can_read(cf->fifo);
}

स्थिर शून्य *frame_alloc(शून्य *opaque)
{
    प्रत्यागम av_frame_alloc();
}

स्थिर शून्य frame_reset(शून्य *opaque, शून्य *obj)
{
    av_frame_unref(obj);
}

स्थिर शून्य frame_free(शून्य *opaque, शून्य *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

स्थिर पूर्णाङ्क frame_transfer(शून्य *opaque, शून्य *dst, शून्य *src, अचिन्हित flags)
{
    यदि (flags & AV_CONTAINER_FIFO_FLAG_REF)
        प्रत्यागम av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    प्रत्यागम 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(अचिन्हित flags)
{
    प्रत्यागम av_container_fifo_alloc(रिक्त, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
