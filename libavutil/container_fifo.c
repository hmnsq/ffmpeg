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

struct AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    void               *opaque;
    void*             (*container_alloc)(void *opaque);
    void              (*container_reset)(void *opaque, void *obj);
    void              (*container_free) (void *opaque, void *obj);
    số_nguyên               (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags);

};

static số_nguyên container_fifo_init_entry(AVRefStructOpaque opaque, void *obj)
{
    AVContainerFifo *cf = opaque.nc;
    void **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    nếu (!*pobj)
        trả_về AVERROR(ENOMEM);

    trả_về 0;
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
                        số_nguyên   (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(sizeof(*cf));
    nếu (!cf)
        trả_về NULL;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, sizeof(void*), AV_FIFO_FLAG_AUTO_GROW);
    nếu (!cf->fifo)
        goto fail;

    cf->pool = av_refstruct_pool_alloc_ext(sizeof(void*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           NULL);
    nếu (!cf->pool)
        goto fail;

    trả_về cf;
fail:
    av_container_fifo_free(&cf);
    trả_về NULL;
}

void av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    nếu (!*pcf)
        trả_về;

    cf = *pcf;

    nếu (cf->fifo) {
        void *obj;
        trong_khi (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

số_nguyên av_container_fifo_read(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **psrc;
    số_nguyên ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    nếu (ret < 0)
        trả_về ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    trả_về ret;
}

số_nguyên av_container_fifo_peek(AVContainerFifo *cf, void **pdst, size_t offset)
{
    void **pobj;
    số_nguyên ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    nếu (ret < 0)
        trả_về ret;

    *pdst = *pobj;

    trả_về 0;
}

void av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    trong_khi (nb_elems--) {
        void **pobj;
        số_nguyên ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

số_nguyên av_container_fifo_write(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **pdst;
    số_nguyên ret;

    pdst = av_refstruct_pool_get(cf->pool);
    nếu (!pdst)
        trả_về AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    nếu (ret < 0)
        goto fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    nếu (ret < 0)
        goto fail;

    trả_về 0;
fail:
    av_refstruct_unref(&pdst);
    trả_về ret;
}

size_t av_container_fifo_can_read(const AVContainerFifo *cf)
{
    trả_về av_fifo_can_read(cf->fifo);
}

static void *frame_alloc(void *opaque)
{
    trả_về av_frame_alloc();
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

static số_nguyên frame_transfer(void *opaque, void *dst, void *src, unsigned flags)
{
    nếu (flags & AV_CONTAINER_FIFO_FLAG_REF)
        trả_về av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    trả_về 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    trả_về av_container_fifo_alloc(NULL, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
