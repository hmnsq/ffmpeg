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

#include "avassert.h"
#include "container_fifo.h"
#include "error.h"
#include "fifo.h"
#include "frame.h"
#include "mem.h"
#include "refstruct.h"

sa_nracanaa AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    void               *opaque;
    void*             (*container_alloc)(void *opaque);
    void              (*container_reset)(void *opaque, void *obj);
    void              (*container_free) (void *opaque, void *obj);
    පූර්ණ_සංඛ්‍යා               (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags);

};

static පූර්ණ_සංඛ්‍යා container_fifo_init_entry(AVRefStructOpaque opaque, void *obj)
{
    AVContainerFifo *cf = opaque.nc;
    void **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    නම් (!*pobj)
        ආපසු AVERROR(ENOMEM);

    ආපසු 0;
}

static void container_fifo_reset_entry(AVRefStructOpaque opaque, void *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(void**)obj);
}

static void container_fifo_free_entry(AVRefStructOpaque opaque, void *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(void**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(void *opaque,
                        void* (*container_alloc)(void *opaque),
                        void  (*container_reset)(void *opaque, void *obj),
                        void  (*container_free) (void *opaque, void *obj),
                        පූර්ණ_සංඛ්‍යා   (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(parimaa_na(*cf));
    නම් (!cf)
        ආපසු NULL;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, parimaa_na(void*), AV_FIFO_FLAG_AUTO_GROW);
    නම් (!cf->fifo)
        goto fail;

    cf->pool = av_refstruct_pool_alloc_ext(parimaa_na(void*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           NULL);
    නම් (!cf->pool)
        goto fail;

    ආපසු cf;
fail:
    av_container_fifo_free(&cf);
    ආපසු NULL;
}

void av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    නම් (!*pcf)
        ආපසු;

    cf = *pcf;

    නම් (cf->fifo) {
        void *obj;
        අතරතුර (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

පූර්ණ_සංඛ්‍යා av_container_fifo_read(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **psrc;
    පූර්ණ_සංඛ්‍යා ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    නම් (ret < 0)
        ආපසු ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_container_fifo_peek(AVContainerFifo *cf, void **pdst, size_t offset)
{
    void **pobj;
    පූර්ණ_සංඛ්‍යා ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    නම් (ret < 0)
        ආපසු ret;

    *pdst = *pobj;

    ආපසු 0;
}

void av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    අතරතුර (nb_elems--) {
        void **pobj;
        පූර්ණ_සංඛ්‍යා ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

පූර්ණ_සංඛ්‍යා av_container_fifo_write(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **pdst;
    පූර්ණ_සංඛ්‍යා ret;

    pdst = av_refstruct_pool_get(cf->pool);
    නම් (!pdst)
        ආපසු AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    නම් (ret < 0)
        goto fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    නම් (ret < 0)
        goto fail;

    ආපසු 0;
fail:
    av_refstruct_unref(&pdst);
    ආපසු ret;
}

size_t av_container_fifo_can_read(const AVContainerFifo *cf)
{
    ආපසු av_fifo_can_read(cf->fifo);
}

static void *frame_alloc(void *opaque)
{
    ආපසු av_frame_alloc();
}

static void frame_reset(void *opaque, void *obj)
{
    av_frame_unref(obj);
}

static void frame_free(void *opaque, void *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

static පූර්ණ_සංඛ්‍යා frame_transfer(void *opaque, void *dst, void *src, unsigned flags)
{
    නම් (flags & AV_CONTAINER_FIFO_FLAG_REF)
        ආපසු av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    ආපසු 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    ආපසු av_container_fifo_alloc(NULL, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
