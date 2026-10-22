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

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "container_fifo.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "fifo.h"
#അന്തര്ഭാവ "frame.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "refstruct.h"

ഘടന AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    ശൂന്യം               *opaque;
    ശൂന്യം*             (*container_alloc)(ശൂന്യം *opaque);
    ശൂന്യം              (*container_reset)(ശൂന്യം *opaque, ശൂന്യം *obj);
    ശൂന്യം              (*container_free) (ശൂന്യം *opaque, ശൂന്യം *obj);
    പൂർണ്ണസംഖ്യ               (*fifo_transfer)  (ശൂന്യം *opaque, ശൂന്യം *dst, ശൂന്യം *src, unsigned flags);

};

സ്ഥിതം പൂർണ്ണസംഖ്യ container_fifo_init_entry(AVRefStructOpaque opaque, ശൂന്യം *obj)
{
    AVContainerFifo *cf = opaque.nc;
    ശൂന്യം **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    എങ്കിൽ (!*pobj)
        തിരികെ AVERROR(ENOMEM);

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം container_fifo_reset_entry(AVRefStructOpaque opaque, ശൂന്യം *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(ശൂന്യം**)obj);
}

സ്ഥിതം ശൂന്യം container_fifo_free_entry(AVRefStructOpaque opaque, ശൂന്യം *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(ശൂന്യം**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(ശൂന്യം *opaque,
                        ശൂന്യം* (*container_alloc)(ശൂന്യം *opaque),
                        ശൂന്യം  (*container_reset)(ശൂന്യം *opaque, ശൂന്യം *obj),
                        ശൂന്യം  (*container_free) (ശൂന്യം *opaque, ശൂന്യം *obj),
                        പൂർണ്ണസംഖ്യ   (*fifo_transfer)  (ശൂന്യം *opaque, ശൂന്യം *dst, ശൂന്യം *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(വലുപ്പം(*cf));
    എങ്കിൽ (!cf)
        തിരികെ ശൂന്യ;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, വലുപ്പം(ശൂന്യം*), AV_FIFO_FLAG_AUTO_GROW);
    എങ്കിൽ (!cf->fifo)
        പോകുക fail;

    cf->pool = av_refstruct_pool_alloc_ext(വലുപ്പം(ശൂന്യം*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           ശൂന്യ);
    എങ്കിൽ (!cf->pool)
        പോകുക fail;

    തിരികെ cf;
fail:
    av_container_fifo_free(&cf);
    തിരികെ ശൂന്യ;
}

ശൂന്യം av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    എങ്കിൽ (!*pcf)
        തിരികെ;

    cf = *pcf;

    എങ്കിൽ (cf->fifo) {
        ശൂന്യം *obj;
        ആകുമ്പോൾ (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

പൂർണ്ണസംഖ്യ av_container_fifo_read(AVContainerFifo *cf, ശൂന്യം *obj, unsigned flags)
{
    ശൂന്യം **psrc;
    പൂർണ്ണസംഖ്യ ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_container_fifo_peek(AVContainerFifo *cf, ശൂന്യം **pdst, size_t offset)
{
    ശൂന്യം **pobj;
    പൂർണ്ണസംഖ്യ ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    *pdst = *pobj;

    തിരികെ 0;
}

ശൂന്യം av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    ആകുമ്പോൾ (nb_elems--) {
        ശൂന്യം **pobj;
        പൂർണ്ണസംഖ്യ ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

പൂർണ്ണസംഖ്യ av_container_fifo_write(AVContainerFifo *cf, ശൂന്യം *obj, unsigned flags)
{
    ശൂന്യം **pdst;
    പൂർണ്ണസംഖ്യ ret;

    pdst = av_refstruct_pool_get(cf->pool);
    എങ്കിൽ (!pdst)
        തിരികെ AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    തിരികെ 0;
fail:
    av_refstruct_unref(&pdst);
    തിരികെ ret;
}

size_t av_container_fifo_can_read(സ്ഥിരം AVContainerFifo *cf)
{
    തിരികെ av_fifo_can_read(cf->fifo);
}

സ്ഥിതം ശൂന്യം *frame_alloc(ശൂന്യം *opaque)
{
    തിരികെ av_frame_alloc();
}

സ്ഥിതം ശൂന്യം frame_reset(ശൂന്യം *opaque, ശൂന്യം *obj)
{
    av_frame_unref(obj);
}

സ്ഥിതം ശൂന്യം frame_free(ശൂന്യം *opaque, ശൂന്യം *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ frame_transfer(ശൂന്യം *opaque, ശൂന്യം *dst, ശൂന്യം *src, unsigned flags)
{
    എങ്കിൽ (flags & AV_CONTAINER_FIFO_FLAG_REF)
        തിരികെ av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    തിരികെ 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    തിരികെ av_container_fifo_alloc(ശൂന്യ, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
