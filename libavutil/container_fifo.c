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
    puur_naa_nka               (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags);

};

static puur_naa_nka container_fifo_init_entry(AVRefStructOpaque opaque, void *obj)
{
    AVContainerFifo *cf = opaque.nc;
    void **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    ᬬᬾᬦ᭄ (!*pobj)
        ᬯᬮᬶ AVERROR(ENOMEM);

    ᬯᬮᬶ 0;
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
                        puur_naa_nka   (*fifo_transfer)  (void *opaque, void *dst, void *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(parimaa_na(*cf));
    ᬬᬾᬦ᭄ (!cf)
        ᬯᬮᬶ NULL;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, parimaa_na(void*), AV_FIFO_FLAG_AUTO_GROW);
    ᬬᬾᬦ᭄ (!cf->fifo)
        goto fail;

    cf->pool = av_refstruct_pool_alloc_ext(parimaa_na(void*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           NULL);
    ᬬᬾᬦ᭄ (!cf->pool)
        goto fail;

    ᬯᬮᬶ cf;
fail:
    av_container_fifo_free(&cf);
    ᬯᬮᬶ NULL;
}

void av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    ᬬᬾᬦ᭄ (!*pcf)
        ᬯᬮᬶ;

    cf = *pcf;

    ᬬᬾᬦ᭄ (cf->fifo) {
        void *obj;
        ᬲᭂᬤᭂᬮ (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

puur_naa_nka av_container_fifo_read(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **psrc;
    puur_naa_nka ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    ᬬᬾᬦ᭄ (ret < 0)
        ᬯᬮᬶ ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    ᬯᬮᬶ ret;
}

puur_naa_nka av_container_fifo_peek(AVContainerFifo *cf, void **pdst, size_t offset)
{
    void **pobj;
    puur_naa_nka ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    ᬬᬾᬦ᭄ (ret < 0)
        ᬯᬮᬶ ret;

    *pdst = *pobj;

    ᬯᬮᬶ 0;
}

void av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    ᬲᭂᬤᭂᬮ (nb_elems--) {
        void **pobj;
        puur_naa_nka ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

puur_naa_nka av_container_fifo_write(AVContainerFifo *cf, void *obj, unsigned flags)
{
    void **pdst;
    puur_naa_nka ret;

    pdst = av_refstruct_pool_get(cf->pool);
    ᬬᬾᬦ᭄ (!pdst)
        ᬯᬮᬶ AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    ᬬᬾᬦ᭄ (ret < 0)
        goto fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    ᬬᬾᬦ᭄ (ret < 0)
        goto fail;

    ᬯᬮᬶ 0;
fail:
    av_refstruct_unref(&pdst);
    ᬯᬮᬶ ret;
}

size_t av_container_fifo_can_read(const AVContainerFifo *cf)
{
    ᬯᬮᬶ av_fifo_can_read(cf->fifo);
}

static void *frame_alloc(void *opaque)
{
    ᬯᬮᬶ av_frame_alloc();
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

static puur_naa_nka frame_transfer(void *opaque, void *dst, void *src, unsigned flags)
{
    ᬬᬾᬦ᭄ (flags & AV_CONTAINER_FIFO_FLAG_REF)
        ᬯᬮᬶ av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    ᬯᬮᬶ 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    ᬯᬮᬶ av_container_fifo_alloc(NULL, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
