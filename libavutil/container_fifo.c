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

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "container_fifo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "fifo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "refstruct.h"

ਬਣਤਰ AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    ਖਾਲੀ               *opaque;
    ਖਾਲੀ*             (*container_alloc)(ਖਾਲੀ *opaque);
    ਖਾਲੀ              (*container_reset)(ਖਾਲੀ *opaque, ਖਾਲੀ *obj);
    ਖਾਲੀ              (*container_free) (ਖਾਲੀ *opaque, ਖਾਲੀ *obj);
    ਪੂਰਨ               (*fifo_transfer)  (ਖਾਲੀ *opaque, ਖਾਲੀ *dst, ਖਾਲੀ *src, ਬਿਨਾਨਿਸ਼ਾਨੀ flags);

};

ਸਥਿਰ ਪੂਰਨ container_fifo_init_ਇੰਦਰਾਜ(AVRefStructOpaque opaque, ਖਾਲੀ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    ਖਾਲੀ **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    ਜੇ (!*pobj)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ container_fifo_reset_ਇੰਦਰਾਜ(AVRefStructOpaque opaque, ਖਾਲੀ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(ਖਾਲੀ**)obj);
}

ਸਥਿਰ ਖਾਲੀ container_fifo_free_ਇੰਦਰਾਜ(AVRefStructOpaque opaque, ਖਾਲੀ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(ਖਾਲੀ**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(ਖਾਲੀ *opaque,
                        ਖਾਲੀ* (*container_alloc)(ਖਾਲੀ *opaque),
                        ਖਾਲੀ  (*container_reset)(ਖਾਲੀ *opaque, ਖਾਲੀ *obj),
                        ਖਾਲੀ  (*container_free) (ਖਾਲੀ *opaque, ਖਾਲੀ *obj),
                        ਪੂਰਨ   (*fifo_transfer)  (ਖਾਲੀ *opaque, ਖਾਲੀ *dst, ਖਾਲੀ *src, ਬਿਨਾਨਿਸ਼ਾਨੀ flags),
                        ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(ਆਕਾਰ(*cf));
    ਜੇ (!cf)
        ਵਾਪਸ ਨਿਰਾ;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, ਆਕਾਰ(ਖਾਲੀ*), AV_FIFO_FLAG_AUTO_GROW);
    ਜੇ (!cf->fifo)
        ਜਾਓ fail;

    cf->pool = av_refstruct_pool_alloc_ext(ਆਕਾਰ(ਖਾਲੀ*), 0, cf,
                                           container_fifo_init_ਇੰਦਰਾਜ,
                                           container_fifo_reset_ਇੰਦਰਾਜ,
                                           container_fifo_free_ਇੰਦਰਾਜ,
                                           ਨਿਰਾ);
    ਜੇ (!cf->pool)
        ਜਾਓ fail;

    ਵਾਪਸ cf;
fail:
    av_container_fifo_free(&cf);
    ਵਾਪਸ ਨਿਰਾ;
}

ਖਾਲੀ av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    ਜੇ (!*pcf)
        ਵਾਪਸ;

    cf = *pcf;

    ਜੇ (cf->fifo) {
        ਖਾਲੀ *obj;
        ਜਦੋਂ (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

ਪੂਰਨ av_container_fifo_read(AVContainerFifo *cf, ਖਾਲੀ *obj, ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
    ਖਾਲੀ **psrc;
    ਪੂਰਨ ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_container_fifo_peek(AVContainerFifo *cf, ਖਾਲੀ **pdst, size_t ਵਿੱਥ)
{
    ਖਾਲੀ **pobj;
    ਪੂਰਨ ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, ਵਿੱਥ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    *pdst = *pobj;

    ਵਾਪਸ 0;
}

ਖਾਲੀ av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    ਜਦੋਂ (nb_elems--) {
        ਖਾਲੀ **pobj;
        ਪੂਰਨ ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

ਪੂਰਨ av_container_fifo_write(AVContainerFifo *cf, ਖਾਲੀ *obj, ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
    ਖਾਲੀ **pdst;
    ਪੂਰਨ ret;

    pdst = av_refstruct_pool_get(cf->pool);
    ਜੇ (!pdst)
        ਵਾਪਸ AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ਵਾਪਸ 0;
fail:
    av_refstruct_unref(&pdst);
    ਵਾਪਸ ret;
}

size_t av_container_fifo_can_read(ਅਚਲ AVContainerFifo *cf)
{
    ਵਾਪਸ av_fifo_can_read(cf->fifo);
}

ਸਥਿਰ ਖਾਲੀ *ਚੌਖਟਾ_alloc(ਖਾਲੀ *opaque)
{
    ਵਾਪਸ av_ਚੌਖਟਾ_alloc();
}

ਸਥਿਰ ਖਾਲੀ ਚੌਖਟਾ_reset(ਖਾਲੀ *opaque, ਖਾਲੀ *obj)
{
    av_ਚੌਖਟਾ_unref(obj);
}

ਸਥਿਰ ਖਾਲੀ ਚੌਖਟਾ_free(ਖਾਲੀ *opaque, ਖਾਲੀ *obj)
{
    AVFrame *ਚੌਖਟਾ = obj;
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
}

ਸਥਿਰ ਪੂਰਨ ਚੌਖਟਾ_transfer(ਖਾਲੀ *opaque, ਖਾਲੀ *dst, ਖਾਲੀ *src, ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
    ਜੇ (flags & AV_CONTAINER_FIFO_FLAG_REF)
        ਵਾਪਸ av_ਚੌਖਟਾ_ref(dst, src);

    av_ਚੌਖਟਾ_move_ref(dst, src);
    ਵਾਪਸ 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
    ਵਾਪਸ av_container_fifo_alloc(ਨਿਰਾ, ਚੌਖਟਾ_alloc, ਚੌਖਟਾ_reset, ਚੌਖਟਾ_free,
                                   ਚੌਖਟਾ_transfer, 0);
}
