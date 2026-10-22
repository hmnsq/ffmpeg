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

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "container_fifo.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "fifo.h"
#அந்தர்பாவ "frame.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "refstruct.h"

கட்டமைப்பு AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    வெறுமை               *opaque;
    வெறுமை*             (*container_alloc)(வெறுமை *opaque);
    வெறுமை              (*container_reset)(வெறுமை *opaque, வெறுமை *obj);
    வெறுமை              (*container_free) (வெறுமை *opaque, வெறுமை *obj);
    முழு               (*fifo_transfer)  (வெறுமை *opaque, வெறுமை *dst, வெறுமை *src, unsigned flags);

};

நிலையான முழு container_fifo_init_entry(AVRefStructOpaque opaque, வெறுமை *obj)
{
    AVContainerFifo *cf = opaque.nc;
    வெறுமை **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    எனில் (!*pobj)
        திரும்பு AVERROR(ENOMEM);

    திரும்பு 0;
}

நிலையான வெறுமை container_fifo_reset_entry(AVRefStructOpaque opaque, வெறுமை *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(வெறுமை**)obj);
}

நிலையான வெறுமை container_fifo_free_entry(AVRefStructOpaque opaque, வெறுமை *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(வெறுமை**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(வெறுமை *opaque,
                        வெறுமை* (*container_alloc)(வெறுமை *opaque),
                        வெறுமை  (*container_reset)(வெறுமை *opaque, வெறுமை *obj),
                        வெறுமை  (*container_free) (வெறுமை *opaque, வெறுமை *obj),
                        முழு   (*fifo_transfer)  (வெறுமை *opaque, வெறுமை *dst, வெறுமை *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(அளவு(*cf));
    எனில் (!cf)
        திரும்பு வெற்று;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, அளவு(வெறுமை*), AV_FIFO_FLAG_AUTO_GROW);
    எனில் (!cf->fifo)
        செல் fail;

    cf->pool = av_refstruct_pool_alloc_ext(அளவு(வெறுமை*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           வெற்று);
    எனில் (!cf->pool)
        செல் fail;

    திரும்பு cf;
fail:
    av_container_fifo_free(&cf);
    திரும்பு வெற்று;
}

வெறுமை av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    எனில் (!*pcf)
        திரும்பு;

    cf = *pcf;

    எனில் (cf->fifo) {
        வெறுமை *obj;
        போது (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

முழு av_container_fifo_read(AVContainerFifo *cf, வெறுமை *obj, unsigned flags)
{
    வெறுமை **psrc;
    முழு ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    எனில் (ret < 0)
        திரும்பு ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    திரும்பு ret;
}

முழு av_container_fifo_peek(AVContainerFifo *cf, வெறுமை **pdst, size_t offset)
{
    வெறுமை **pobj;
    முழு ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    எனில் (ret < 0)
        திரும்பு ret;

    *pdst = *pobj;

    திரும்பு 0;
}

வெறுமை av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    போது (nb_elems--) {
        வெறுமை **pobj;
        முழு ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

முழு av_container_fifo_write(AVContainerFifo *cf, வெறுமை *obj, unsigned flags)
{
    வெறுமை **pdst;
    முழு ret;

    pdst = av_refstruct_pool_get(cf->pool);
    எனில் (!pdst)
        திரும்பு AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    எனில் (ret < 0)
        செல் fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    எனில் (ret < 0)
        செல் fail;

    திரும்பு 0;
fail:
    av_refstruct_unref(&pdst);
    திரும்பு ret;
}

size_t av_container_fifo_can_read(மாறிலி AVContainerFifo *cf)
{
    திரும்பு av_fifo_can_read(cf->fifo);
}

நிலையான வெறுமை *frame_alloc(வெறுமை *opaque)
{
    திரும்பு av_frame_alloc();
}

நிலையான வெறுமை frame_reset(வெறுமை *opaque, வெறுமை *obj)
{
    av_frame_unref(obj);
}

நிலையான வெறுமை frame_free(வெறுமை *opaque, வெறுமை *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

நிலையான முழு frame_transfer(வெறுமை *opaque, வெறுமை *dst, வெறுமை *src, unsigned flags)
{
    எனில் (flags & AV_CONTAINER_FIFO_FLAG_REF)
        திரும்பு av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    திரும்பு 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    திரும்பு av_container_fifo_alloc(வெற்று, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
