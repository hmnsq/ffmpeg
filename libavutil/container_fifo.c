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

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "container_fifo.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "fifo.h"
#ଅନ୍ତର୍ଭାଵ "frame.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "refstruct.h"

ସଂରଚନା AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    ଶୂନ୍ୟ               *opaque;
    ଶୂନ୍ୟ*             (*container_alloc)(ଶୂନ୍ୟ *opaque);
    ଶୂନ୍ୟ              (*container_reset)(ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *obj);
    ଶୂନ୍ୟ              (*container_free) (ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *obj);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା               (*fifo_transfer)  (ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *dst, ଶୂନ୍ୟ *src, unsigned flags);

};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା container_fifo_init_entry(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    ଶୂନ୍ୟ **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    ଯଦି (!*pobj)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ container_fifo_reset_entry(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(ଶୂନ୍ୟ**)obj);
}

ସ୍ଥିର ଶୂନ୍ୟ container_fifo_free_entry(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(ଶୂନ୍ୟ**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(ଶୂନ୍ୟ *opaque,
                        ଶୂନ୍ୟ* (*container_alloc)(ଶୂନ୍ୟ *opaque),
                        ଶୂନ୍ୟ  (*container_reset)(ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *obj),
                        ଶୂନ୍ୟ  (*container_free) (ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *obj),
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା   (*fifo_transfer)  (ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *dst, ଶୂନ୍ୟ *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(ଆକାର(*cf));
    ଯଦି (!cf)
        ଫେରନ୍ତୁ ଖାଲି;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, ଆକାର(ଶୂନ୍ୟ*), AV_FIFO_FLAG_AUTO_GROW);
    ଯଦି (!cf->fifo)
        ଯାଅ fail;

    cf->pool = av_refstruct_pool_alloc_ext(ଆକାର(ଶୂନ୍ୟ*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           ଖାଲି);
    ଯଦି (!cf->pool)
        ଯାଅ fail;

    ଫେରନ୍ତୁ cf;
fail:
    av_container_fifo_free(&cf);
    ଫେରନ୍ତୁ ଖାଲି;
}

ଶୂନ୍ୟ av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    ଯଦି (!*pcf)
        ଫେରନ୍ତୁ;

    cf = *pcf;

    ଯଦି (cf->fifo) {
        ଶୂନ୍ୟ *obj;
        ଯେତେବେଳେ (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_container_fifo_read(AVContainerFifo *cf, ଶୂନ୍ୟ *obj, unsigned flags)
{
    ଶୂନ୍ୟ **psrc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_container_fifo_peek(AVContainerFifo *cf, ଶୂନ୍ୟ **pdst, size_t offset)
{
    ଶୂନ୍ୟ **pobj;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    *pdst = *pobj;

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    ଯେତେବେଳେ (nb_elems--) {
        ଶୂନ୍ୟ **pobj;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_container_fifo_write(AVContainerFifo *cf, ଶୂନ୍ୟ *obj, unsigned flags)
{
    ଶୂନ୍ୟ **pdst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    pdst = av_refstruct_pool_get(cf->pool);
    ଯଦି (!pdst)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    ଫେରନ୍ତୁ 0;
fail:
    av_refstruct_unref(&pdst);
    ଫେରନ୍ତୁ ret;
}

size_t av_container_fifo_can_read(ଅଚଳ AVContainerFifo *cf)
{
    ଫେରନ୍ତୁ av_fifo_can_read(cf->fifo);
}

ସ୍ଥିର ଶୂନ୍ୟ *frame_alloc(ଶୂନ୍ୟ *opaque)
{
    ଫେରନ୍ତୁ av_frame_alloc();
}

ସ୍ଥିର ଶୂନ୍ୟ frame_reset(ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *obj)
{
    av_frame_unref(obj);
}

ସ୍ଥିର ଶୂନ୍ୟ frame_free(ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_transfer(ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *dst, ଶୂନ୍ୟ *src, unsigned flags)
{
    ଯଦି (flags & AV_CONTAINER_FIFO_FLAG_REF)
        ଫେରନ୍ତୁ av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    ଫେରନ୍ତୁ 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    ଫେରନ୍ତୁ av_container_fifo_alloc(ଖାଲି, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
