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

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "container_fifo.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "fifo.h"
#అన్తర్భావ "frame.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "refstruct.h"

నిర్మాణం AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    శూన్య               *opaque;
    శూన్య*             (*container_alloc)(శూన్య *opaque);
    శూన్య              (*container_reset)(శూన్య *opaque, శూన్య *obj);
    శూన్య              (*container_free) (శూన్య *opaque, శూన్య *obj);
    పూర్ణాంకం               (*fifo_transfer)  (శూన్య *opaque, శూన్య *dst, శూన్య *src, గుర్తులేని flags);

};

స్థిర పూర్ణాంకం container_fifo_init_నమోదు(AVRefStructOpaque opaque, శూన్య *obj)
{
    AVContainerFifo *cf = opaque.nc;
    శూన్య **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    ఒకవేళ (!*pobj)
        తిరిగి AVERROR(ENOMEM);

    తిరిగి 0;
}

స్థిర శూన్య container_fifo_reset_నమోదు(AVRefStructOpaque opaque, శూన్య *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(శూన్య**)obj);
}

స్థిర శూన్య container_fifo_free_నమోదు(AVRefStructOpaque opaque, శూన్య *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(శూన్య**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(శూన్య *opaque,
                        శూన్య* (*container_alloc)(శూన్య *opaque),
                        శూన్య  (*container_reset)(శూన్య *opaque, శూన్య *obj),
                        శూన్య  (*container_free) (శూన్య *opaque, శూన్య *obj),
                        పూర్ణాంకం   (*fifo_transfer)  (శూన్య *opaque, శూన్య *dst, శూన్య *src, గుర్తులేని flags),
                        గుర్తులేని flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(పరిమాణం(*cf));
    ఒకవేళ (!cf)
        తిరిగి ఖాళీ;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, పరిమాణం(శూన్య*), AV_FIFO_FLAG_AUTO_GROW);
    ఒకవేళ (!cf->fifo)
        వెళ్ళు fail;

    cf->pool = av_refstruct_pool_alloc_ext(పరిమాణం(శూన్య*), 0, cf,
                                           container_fifo_init_నమోదు,
                                           container_fifo_reset_నమోదు,
                                           container_fifo_free_నమోదు,
                                           ఖాళీ);
    ఒకవేళ (!cf->pool)
        వెళ్ళు fail;

    తిరిగి cf;
fail:
    av_container_fifo_free(&cf);
    తిరిగి ఖాళీ;
}

శూన్య av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    ఒకవేళ (!*pcf)
        తిరిగి;

    cf = *pcf;

    ఒకవేళ (cf->fifo) {
        శూన్య *obj;
        అయితే (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

పూర్ణాంకం av_container_fifo_read(AVContainerFifo *cf, శూన్య *obj, గుర్తులేని flags)
{
    శూన్య **psrc;
    పూర్ణాంకం ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    తిరిగి ret;
}

పూర్ణాంకం av_container_fifo_peek(AVContainerFifo *cf, శూన్య **pdst, size_t స్థానభ్రంశం)
{
    శూన్య **pobj;
    పూర్ణాంకం ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, స్థానభ్రంశం);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    *pdst = *pobj;

    తిరిగి 0;
}

శూన్య av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    అయితే (nb_elems--) {
        శూన్య **pobj;
        పూర్ణాంకం ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

పూర్ణాంకం av_container_fifo_write(AVContainerFifo *cf, శూన్య *obj, గుర్తులేని flags)
{
    శూన్య **pdst;
    పూర్ణాంకం ret;

    pdst = av_refstruct_pool_get(cf->pool);
    ఒకవేళ (!pdst)
        తిరిగి AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    తిరిగి 0;
fail:
    av_refstruct_unref(&pdst);
    తిరిగి ret;
}

size_t av_container_fifo_can_read(స్థిరరాశి AVContainerFifo *cf)
{
    తిరిగి av_fifo_can_read(cf->fifo);
}

స్థిర శూన్య *చట్రం_alloc(శూన్య *opaque)
{
    తిరిగి av_చట్రం_alloc();
}

స్థిర శూన్య చట్రం_reset(శూన్య *opaque, శూన్య *obj)
{
    av_చట్రం_unref(obj);
}

స్థిర శూన్య చట్రం_free(శూన్య *opaque, శూన్య *obj)
{
    AVFrame *చట్రం = obj;
    av_చట్రం_free(&చట్రం);
}

స్థిర పూర్ణాంకం చట్రం_transfer(శూన్య *opaque, శూన్య *dst, శూన్య *src, గుర్తులేని flags)
{
    ఒకవేళ (flags & AV_CONTAINER_FIFO_FLAG_REF)
        తిరిగి av_చట్రం_ref(dst, src);

    av_చట్రం_move_ref(dst, src);
    తిరిగి 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(గుర్తులేని flags)
{
    తిరిగి av_container_fifo_alloc(ఖాళీ, చట్రం_alloc, చట్రం_reset, చట్రం_free,
                                   చట్రం_transfer, 0);
}
