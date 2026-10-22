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

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "container_fifo.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "fifo.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "refstruct.h"

ರಚನೆ AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    ಶೂನ್ಯ               *opaque;
    ಶೂನ್ಯ*             (*container_alloc)(ಶೂನ್ಯ *opaque);
    ಶೂನ್ಯ              (*container_reset)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ              (*container_free) (ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj);
    ಪೂರ್ಣಾಂಕ               (*fifo_transfer)  (ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *dst, ಶೂನ್ಯ *src, ಚಿಹ್ನೆರಹಿತ flags);

};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ container_fifo_init_ನಮೂದು(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    ಶೂನ್ಯ **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    ಆದರೆ (!*pobj)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ container_fifo_reset_ನಮೂದು(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(ಶೂನ್ಯ**)obj);
}

ಸ್ಥಿರ ಶೂನ್ಯ container_fifo_free_ನಮೂದು(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(ಶೂನ್ಯ**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(ಶೂನ್ಯ *opaque,
                        ಶೂನ್ಯ* (*container_alloc)(ಶೂನ್ಯ *opaque),
                        ಶೂನ್ಯ  (*container_reset)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj),
                        ಶೂನ್ಯ  (*container_free) (ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj),
                        ಪೂರ್ಣಾಂಕ   (*fifo_transfer)  (ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *dst, ಶೂನ್ಯ *src, ಚಿಹ್ನೆರಹಿತ flags),
                        ಚಿಹ್ನೆರಹಿತ flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(ಗಾತ್ರ(*cf));
    ಆದರೆ (!cf)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, ಗಾತ್ರ(ಶೂನ್ಯ*), AV_FIFO_FLAG_AUTO_GROW);
    ಆದರೆ (!cf->fifo)
        ಹೋಗು fail;

    cf->pool = av_refstruct_pool_alloc_ext(ಗಾತ್ರ(ಶೂನ್ಯ*), 0, cf,
                                           container_fifo_init_ನಮೂದು,
                                           container_fifo_reset_ನಮೂದು,
                                           container_fifo_free_ನಮೂದು,
                                           ಖಾಲಿ);
    ಆದರೆ (!cf->pool)
        ಹೋಗು fail;

    ಹಿಂತಿರುಗಿ cf;
fail:
    av_container_fifo_free(&cf);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಶೂನ್ಯ av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    ಆದರೆ (!*pcf)
        ಹಿಂತಿರುಗಿ;

    cf = *pcf;

    ಆದರೆ (cf->fifo) {
        ಶೂನ್ಯ *obj;
        ಆಗ (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

ಪೂರ್ಣಾಂಕ av_container_fifo_read(AVContainerFifo *cf, ಶೂನ್ಯ *obj, ಚಿಹ್ನೆರಹಿತ flags)
{
    ಶೂನ್ಯ **psrc;
    ಪೂರ್ಣಾಂಕ ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_container_fifo_peek(AVContainerFifo *cf, ಶೂನ್ಯ **pdst, size_t ಸ್ಥಾನಾಂತರ)
{
    ಶೂನ್ಯ **pobj;
    ಪೂರ್ಣಾಂಕ ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, ಸ್ಥಾನಾಂತರ);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    *pdst = *pobj;

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    ಆಗ (nb_elems--) {
        ಶೂನ್ಯ **pobj;
        ಪೂರ್ಣಾಂಕ ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

ಪೂರ್ಣಾಂಕ av_container_fifo_write(AVContainerFifo *cf, ಶೂನ್ಯ *obj, ಚಿಹ್ನೆರಹಿತ flags)
{
    ಶೂನ್ಯ **pdst;
    ಪೂರ್ಣಾಂಕ ret;

    pdst = av_refstruct_pool_get(cf->pool);
    ಆದರೆ (!pdst)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ಹಿಂತಿರುಗಿ 0;
fail:
    av_refstruct_unref(&pdst);
    ಹಿಂತಿರುಗಿ ret;
}

size_t av_container_fifo_can_read(ಸ್ಥಿರಾಂಕ AVContainerFifo *cf)
{
    ಹಿಂತಿರುಗಿ av_fifo_can_read(cf->fifo);
}

ಸ್ಥಿರ ಶೂನ್ಯ *ಚೌಕಟ್ಟು_alloc(ಶೂನ್ಯ *opaque)
{
    ಹಿಂತಿರುಗಿ av_ಚೌಕಟ್ಟು_alloc();
}

ಸ್ಥಿರ ಶೂನ್ಯ ಚೌಕಟ್ಟು_reset(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj)
{
    av_ಚೌಕಟ್ಟು_unref(obj);
}

ಸ್ಥಿರ ಶೂನ್ಯ ಚೌಕಟ್ಟು_free(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj)
{
    AVFrame *ಚೌಕಟ್ಟು = obj;
    av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_transfer(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *dst, ಶೂನ್ಯ *src, ಚಿಹ್ನೆರಹಿತ flags)
{
    ಆದರೆ (flags & AV_CONTAINER_FIFO_FLAG_REF)
        ಹಿಂತಿರುಗಿ av_ಚೌಕಟ್ಟು_ref(dst, src);

    av_ಚೌಕಟ್ಟು_move_ref(dst, src);
    ಹಿಂತಿರುಗಿ 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(ಚಿಹ್ನೆರಹಿತ flags)
{
    ಹಿಂತಿರುಗಿ av_container_fifo_alloc(ಖಾಲಿ, ಚೌಕಟ್ಟು_alloc, ಚೌಕಟ್ಟು_reset, ಚೌಕಟ್ಟು_free,
                                   ಚೌಕಟ್ಟು_transfer, 0);
}
