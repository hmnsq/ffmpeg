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

ಸಂರಚನಾ AVContainerFifo {
    AVFifo             *fifo;
    AVRefStructPool    *pool;

    ಶೂನ್ಯ               *opaque;
    ಶೂನ್ಯ*             (*container_alloc)(ಶೂನ್ಯ *opaque);
    ಶೂನ್ಯ              (*container_reset)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ              (*container_free) (ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj);
    ಪೂರ್ಣಾಙ್ಕ               (*fifo_transfer)  (ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *dst, ಶೂನ್ಯ *src, unsigned flags);

};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ container_fifo_init_entry(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    ಶೂನ್ಯ **pobj = obj;

    *pobj = cf->container_alloc(cf->opaque);
    ಯದಿ (!*pobj)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ container_fifo_reset_entry(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_reset(cf->opaque, *(ಶೂನ್ಯ**)obj);
}

ಸ್ಥಿರ ಶೂನ್ಯ container_fifo_free_entry(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    AVContainerFifo *cf = opaque.nc;
    cf->container_free(cf->opaque, *(ಶೂನ್ಯ**)obj);
}

AVContainerFifo*
av_container_fifo_alloc(ಶೂನ್ಯ *opaque,
                        ಶೂನ್ಯ* (*container_alloc)(ಶೂನ್ಯ *opaque),
                        ಶೂನ್ಯ  (*container_reset)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj),
                        ಶೂನ್ಯ  (*container_free) (ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj),
                        ಪೂರ್ಣಾಙ್ಕ   (*fifo_transfer)  (ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *dst, ಶೂನ್ಯ *src, unsigned flags),
                        unsigned flags)
{
    AVContainerFifo *cf;

    cf = av_mallocz(ಪರಿಮಾಣ(*cf));
    ಯದಿ (!cf)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    cf->opaque          = opaque;
    cf->container_alloc = container_alloc;
    cf->container_reset = container_reset;
    cf->container_free  = container_free;
    cf->fifo_transfer   = fifo_transfer;

    cf->fifo = av_fifo_alloc2(1, ಪರಿಮಾಣ(ಶೂನ್ಯ*), AV_FIFO_FLAG_AUTO_GROW);
    ಯದಿ (!cf->fifo)
        ಗಚ್ಛ fail;

    cf->pool = av_refstruct_pool_alloc_ext(ಪರಿಮಾಣ(ಶೂನ್ಯ*), 0, cf,
                                           container_fifo_init_entry,
                                           container_fifo_reset_entry,
                                           container_fifo_free_entry,
                                           ರಿಕ್ತ);
    ಯದಿ (!cf->pool)
        ಗಚ್ಛ fail;

    ಪ್ರತ್ಯಾಗಮ cf;
fail:
    av_container_fifo_free(&cf);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಶೂನ್ಯ av_container_fifo_free(AVContainerFifo **pcf)
{
    AVContainerFifo *cf;

    ಯದಿ (!*pcf)
        ಪ್ರತ್ಯಾಗಮ;

    cf = *pcf;

    ಯದಿ (cf->fifo) {
        ಶೂನ್ಯ *obj;
        ಯಾವತ್ (av_fifo_read(cf->fifo, &obj, 1) >= 0)
            av_refstruct_unref(&obj);
        av_fifo_freep2(&cf->fifo);
    }

    av_refstruct_pool_uninit(&cf->pool);

    av_freep(pcf);
}

ಪೂರ್ಣಾಙ್ಕ av_container_fifo_read(AVContainerFifo *cf, ಶೂನ್ಯ *obj, unsigned flags)
{
    ಶೂನ್ಯ **psrc;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ret = av_fifo_read(cf->fifo, &psrc, 1);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ret = cf->fifo_transfer(cf->opaque, obj, *psrc, flags);
    av_refstruct_unref(&psrc);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_container_fifo_peek(AVContainerFifo *cf, ಶೂನ್ಯ **pdst, size_t offset)
{
    ಶೂನ್ಯ **pobj;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ret = av_fifo_peek(cf->fifo, &pobj, 1, offset);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    *pdst = *pobj;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_container_fifo_drain(AVContainerFifo *cf, size_t nb_elems)
{
    av_assert0(nb_elems <= av_fifo_can_read(cf->fifo));
    ಯಾವತ್ (nb_elems--) {
        ಶೂನ್ಯ **pobj;
        ಪೂರ್ಣಾಙ್ಕ ret = av_fifo_read(cf->fifo, &pobj, 1);
        av_assert0(ret >= 0);
        av_refstruct_unref(&pobj);
    }
}

ಪೂರ್ಣಾಙ್ಕ av_container_fifo_write(AVContainerFifo *cf, ಶೂನ್ಯ *obj, unsigned flags)
{
    ಶೂನ್ಯ **pdst;
    ಪೂರ್ಣಾಙ್ಕ ret;

    pdst = av_refstruct_pool_get(cf->pool);
    ಯದಿ (!pdst)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ret = cf->fifo_transfer(cf->opaque, *pdst, obj, flags);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    ret = av_fifo_write(cf->fifo, &pdst, 1);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತ್ಯಾಗಮ 0;
fail:
    av_refstruct_unref(&pdst);
    ಪ್ರತ್ಯಾಗಮ ret;
}

size_t av_container_fifo_can_read(ಧ್ರುವ AVContainerFifo *cf)
{
    ಪ್ರತ್ಯಾಗಮ av_fifo_can_read(cf->fifo);
}

ಸ್ಥಿರ ಶೂನ್ಯ *frame_alloc(ಶೂನ್ಯ *opaque)
{
    ಪ್ರತ್ಯಾಗಮ av_frame_alloc();
}

ಸ್ಥಿರ ಶೂನ್ಯ frame_reset(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj)
{
    av_frame_unref(obj);
}

ಸ್ಥಿರ ಶೂನ್ಯ frame_free(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *obj)
{
    AVFrame *frame = obj;
    av_frame_free(&frame);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ frame_transfer(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *dst, ಶೂನ್ಯ *src, unsigned flags)
{
    ಯದಿ (flags & AV_CONTAINER_FIFO_FLAG_REF)
        ಪ್ರತ್ಯಾಗಮ av_frame_ref(dst, src);

    av_frame_move_ref(dst, src);
    ಪ್ರತ್ಯಾಗಮ 0;
}

AVContainerFifo *av_container_fifo_alloc_avframe(unsigned flags)
{
    ಪ್ರತ್ಯಾಗಮ av_container_fifo_alloc(ರಿಕ್ತ, frame_alloc, frame_reset, frame_free,
                                   frame_transfer, 0);
}
