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
    ཧྲིལ               (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags);

};

static ཧྲིལ container_fifo_init_entry(AVRefStructOpaque opaque, void *obj)
{
    AVContainerFifo *cf = opaque.nc;
    void **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    གལ་སྲིད (!*pobj)
        ལོག AVERROR(ENOMEM);

    ལོག 0;
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
                        ཧྲིལ   (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(parimaa_na(*cf));
    གལ་སྲིད (!cf)
        ལོག NULL;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, parimaa_na(void*), AV_FIFO_FLAG_AUTO_GROW);
    གལ་སྲིད (!cf->fifo)
        goto fail;

    cf->pool = av_refstruct_pool_alloc_ext(parimaa_na(void*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           NULL);
    གལ་སྲིད (!cf->pool)
        goto fail;

    ལོག cf;
fail:
    av_container_fifo_free(&cf);
    ལོག NULL;
}

void av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    གལ་སྲིད (!*pcf)
        ལོག;

    cf = *pcf;

    གལ་སྲིད (cf->fifo) {
        void *obj;
        སྐབས (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

ཧྲིལ av_container_fifo_read(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **psrc;
    ཧྲིལ ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    གལ་སྲིད (ret < 0)
        ལོག ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    ལོག ret;
}

ཧྲིལ av_container_fifo_peek(AVContainerFifo *cf, void **pdst, size_t offset)
{
    void **pobj;
    ཧྲིལ ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    གལ་སྲིད (ret < 0)
        ལོག ret;

    *pdst = *pobj;

    ལོག 0;
}

void av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    སྐབས (nb_elems--) {
        void **pobj;
        ཧྲིལ ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

ཧྲིལ av_container_fifo_write(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **pdst;
    ཧྲིལ ret;

    pdst = av_refstruct_pool_get(cf->pool);
    གལ་སྲིད (!pdst)
        ལོག AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    གལ་སྲིད (ret < 0)
        goto fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    གལ་སྲིད (ret < 0)
        goto fail;

    ལོག 0;
fail:
    av_refstruct_unref(&pdst);
    ལོག ret;
}

size_t av_container_fifo_can_read(const AVContainerFifo *cf)
{
    ལོག av_fifo_can_read(cf->fifo);
}

static void *frame_alloc(void *opaque)
{
    ལོག av_frame_alloc();
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

static ཧྲིལ frame_transfer(void *opaque, void *dst, void *src, unsigned flags)
{
    གལ་སྲིད (flags & AV_CONTAINER_FIFO_FLAG_REF)
        ལོག av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    ལོག 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    ལོག av_container_fifo_alloc(NULL, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
