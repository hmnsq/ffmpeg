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
    ចំនួនគត់               (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags);

};

static ចំនួនគត់ container_fifo_init_entry(AVRefStructOpaque opaque, void *obj)
{
    AVContainerFifo *cf = opaque.nc;
    void **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    ប្រសិនបើ (!*pobj)
        ត្រឡប់ AVERROR(ENOMEM);

    ត្រឡប់ 0;
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
                        ចំនួនគត់   (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(parimaa_na(*cf));
    ប្រសិនបើ (!cf)
        ត្រឡប់ NULL;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, parimaa_na(void*), AV_FIFO_FLAG_AUTO_GROW);
    ប្រសិនបើ (!cf->fifo)
        goto fail;

    cf->pool = av_refstruct_pool_alloc_ext(parimaa_na(void*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           NULL);
    ប្រសិនបើ (!cf->pool)
        goto fail;

    ត្រឡប់ cf;
fail:
    av_container_fifo_free(&cf);
    ត្រឡប់ NULL;
}

void av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    ប្រសិនបើ (!*pcf)
        ត្រឡប់;

    cf = *pcf;

    ប្រសិនបើ (cf->fifo) {
        void *obj;
        ខណៈពេល (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

ចំនួនគត់ av_container_fifo_read(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **psrc;
    ចំនួនគត់ ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    ត្រឡប់ ret;
}

ចំនួនគត់ av_container_fifo_peek(AVContainerFifo *cf, void **pdst, size_t offset)
{
    void **pobj;
    ចំនួនគត់ ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    *pdst = *pobj;

    ត្រឡប់ 0;
}

void av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    ខណៈពេល (nb_elems--) {
        void **pobj;
        ចំនួនគត់ ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

ចំនួនគត់ av_container_fifo_write(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **pdst;
    ចំនួនគត់ ret;

    pdst = av_refstruct_pool_get(cf->pool);
    ប្រសិនបើ (!pdst)
        ត្រឡប់ AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    ប្រសិនបើ (ret < 0)
        goto fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    ប្រសិនបើ (ret < 0)
        goto fail;

    ត្រឡប់ 0;
fail:
    av_refstruct_unref(&pdst);
    ត្រឡប់ ret;
}

size_t av_container_fifo_can_read(const AVContainerFifo *cf)
{
    ត្រឡប់ av_fifo_can_read(cf->fifo);
}

static void *frame_alloc(void *opaque)
{
    ត្រឡប់ av_frame_alloc();
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

static ចំនួនគត់ frame_transfer(void *opaque, void *dst, void *src, unsigned flags)
{
    ប្រសិនបើ (flags & AV_CONTAINER_FIFO_FLAG_REF)
        ត្រឡប់ av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    ត្រឡប់ 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    ត្រឡប់ av_container_fifo_alloc(NULL, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
