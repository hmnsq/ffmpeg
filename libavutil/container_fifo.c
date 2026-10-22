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

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "container_fifo.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "fifo.h"
#અન્તર્ભાવ "frame.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "refstruct.h"

સંરચના AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    શૂન્ય               *opaque;
    શૂન્ય*             (*container_alloc)(શૂન્ય *opaque);
    શૂન્ય              (*container_reset)(શૂન્ય *opaque, શૂન્ય *obj);
    શૂન્ય              (*container_free) (શૂન્ય *opaque, શૂન્ય *obj);
    પૂર્ણાંક               (*fifo_transfer)  (શૂન્ય *opaque, શૂન્ય *dst, શૂન્ય *src, unsigned flags);

};

સ્થિર પૂર્ણાંક container_fifo_init_entry(AVRefStructOpaque opaque, શૂન્ય *obj)
{
    AVContainerFifo *cf = opaque.nc;
    શૂન્ય **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    જો (!*pobj)
        પાછા AVERROR(ENOMEM);

    પાછા 0;
}

સ્થિર શૂન્ય container_fifo_reset_entry(AVRefStructOpaque opaque, શૂન્ય *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(શૂન્ય**)obj);
}

સ્થિર શૂન્ય container_fifo_free_entry(AVRefStructOpaque opaque, શૂન્ય *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(શૂન્ય**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(શૂન્ય *opaque,
                        શૂન્ય* (*container_alloc)(શૂન્ય *opaque),
                        શૂન્ય  (*container_reset)(શૂન્ય *opaque, શૂન્ય *obj),
                        શૂન્ય  (*container_free) (શૂન્ય *opaque, શૂન્ય *obj),
                        પૂર્ણાંક   (*fifo_transfer)  (શૂન્ય *opaque, શૂન્ય *dst, શૂન્ય *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(કદ(*cf));
    જો (!cf)
        પાછા ખાલી;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, કદ(શૂન્ય*), AV_FIFO_FLAG_AUTO_GROW);
    જો (!cf->fifo)
        જાઓ fail;

    cf->pool = av_refstruct_pool_alloc_ext(કદ(શૂન્ય*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           ખાલી);
    જો (!cf->pool)
        જાઓ fail;

    પાછા cf;
fail:
    av_container_fifo_free(&cf);
    પાછા ખાલી;
}

શૂન્ય av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    જો (!*pcf)
        પાછા;

    cf = *pcf;

    જો (cf->fifo) {
        શૂન્ય *obj;
        જ્યારે (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

પૂર્ણાંક av_container_fifo_read(AVContainerFifo *cf, શૂન્ય *obj, unsigned flags)
{
    શૂન્ય **psrc;
    પૂર્ણાંક ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    જો (ret < 0)
        પાછા ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    પાછા ret;
}

પૂર્ણાંક av_container_fifo_peek(AVContainerFifo *cf, શૂન્ય **pdst, size_t offset)
{
    શૂન્ય **pobj;
    પૂર્ણાંક ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    જો (ret < 0)
        પાછા ret;

    *pdst = *pobj;

    પાછા 0;
}

શૂન્ય av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    જ્યારે (nb_elems--) {
        શૂન્ય **pobj;
        પૂર્ણાંક ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

પૂર્ણાંક av_container_fifo_write(AVContainerFifo *cf, શૂન્ય *obj, unsigned flags)
{
    શૂન્ય **pdst;
    પૂર્ણાંક ret;

    pdst = av_refstruct_pool_get(cf->pool);
    જો (!pdst)
        પાછા AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    જો (ret < 0)
        જાઓ fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    જો (ret < 0)
        જાઓ fail;

    પાછા 0;
fail:
    av_refstruct_unref(&pdst);
    પાછા ret;
}

size_t av_container_fifo_can_read(અચલ AVContainerFifo *cf)
{
    પાછા av_fifo_can_read(cf->fifo);
}

સ્થિર શૂન્ય *frame_alloc(શૂન્ય *opaque)
{
    પાછા av_frame_alloc();
}

સ્થિર શૂન્ય frame_reset(શૂન્ય *opaque, શૂન્ય *obj)
{
    av_frame_unref(obj);
}

સ્થિર શૂન્ય frame_free(શૂન્ય *opaque, શૂન્ય *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

સ્થિર પૂર્ણાંક frame_transfer(શૂન્ય *opaque, શૂન્ય *dst, શૂન્ય *src, unsigned flags)
{
    જો (flags & AV_CONTAINER_FIFO_FLAG_REF)
        પાછા av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    પાછા 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    પાછા av_container_fifo_alloc(ખાલી, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
