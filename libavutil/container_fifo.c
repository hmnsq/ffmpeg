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
    цео               (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags);

};

static цео container_fifo_init_entry(AVRefStructOpaque opaque, void *obj)
{
    AVContainerFifo *cf = opaque.nc;
    void **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    ако (!*pobj)
        врати AVERROR(ENOMEM);

    врати 0;
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
                        цео   (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(sizeof(*cf));
    ако (!cf)
        врати NULL;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, sizeof(void*), AV_FIFO_FLAG_AUTO_GROW);
    ако (!cf->fifo)
        goto fail;

    cf->pool = av_refstruct_pool_alloc_ext(sizeof(void*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           NULL);
    ако (!cf->pool)
        goto fail;

    врати cf;
fail:
    av_container_fifo_free(&cf);
    врати NULL;
}

void av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    ако (!*pcf)
        врати;

    cf = *pcf;

    ако (cf->fifo) {
        void *obj;
        док (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

цео av_container_fifo_read(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **psrc;
    цео ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    ако (ret < 0)
        врати ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    врати ret;
}

цео av_container_fifo_peek(AVContainerFifo *cf, void **pdst, size_t offset)
{
    void **pobj;
    цео ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    ако (ret < 0)
        врати ret;

    *pdst = *pobj;

    врати 0;
}

void av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    док (nb_elems--) {
        void **pobj;
        цео ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

цео av_container_fifo_write(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **pdst;
    цео ret;

    pdst = av_refstruct_pool_get(cf->pool);
    ако (!pdst)
        врати AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    ако (ret < 0)
        goto fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    ако (ret < 0)
        goto fail;

    врати 0;
fail:
    av_refstruct_unref(&pdst);
    врати ret;
}

size_t av_container_fifo_can_read(const AVContainerFifo *cf)
{
    врати av_fifo_can_read(cf->fifo);
}

static void *frame_alloc(void *opaque)
{
    врати av_frame_alloc();
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

static цео frame_transfer(void *opaque, void *dst, void *src, unsigned flags)
{
    ако (flags & AV_CONTAINER_FIFO_FLAG_REF)
        врати av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    врати 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    врати av_container_fifo_alloc(NULL, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
