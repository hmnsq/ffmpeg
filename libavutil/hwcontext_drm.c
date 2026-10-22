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

#ضمن "config.h"

#ضمن <fcntl.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#إذا HAVE_LINUX_DMA_BUF_H
#ضمن <linux/dma-buf.h>
#ضمن <sys/ioctl.h>
#پایان_اگر

#ضمن <drm.h>
#ضمن <xf86drm.h>

#ضمن "avassert.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_drm.h"
#ضمن "hwcontext_internal.h"
#ضمن "imgutils.h"
#ضمن "mem.h"


ساكن فراغ drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

ساكن صحيح drm_device_create(AVHWDeviceContext *hwdev, ثابت حرف *device,
                             AVDictionary *opts, صحيح flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drm_نسخه_Ptr نسخه;

    hwctx->fd = open(device, O_RDWR);
    إذا (hwctx->fd < 0)
        أرجع AVERROR(errno);

    نسخه = drm_Get_نسخه(hwctx->fd);
    إذا (!نسخه) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        أرجع AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, نسخه->name,
           نسخه->نسخه_major, نسخه->نسخه_minor,
           نسخه->نسخه_patchlevel);

    drm_Free_نسخه(نسخه);

    hwdev->حرر = &drm_device_free;

    أرجع 0;
}

ساكن صحيح drm_get_میانگیر(AVHWFramesContext *hwfc, AVFrame *قاب)
{
    قاب->buf[0] = av_میانگیر_pool_get(hwfc->pool);
    إذا (!قاب->buf[0])
        أرجع AVERROR(ENOMEM);

    قاب->داده[0] = (uint8_t*)قاب->buf[0]->داده;

    قاب->format = AV_PIX_FMT_DRM_اول;
    قاب->عرض  = hwfc->عرض;
    قاب->ارتفاع = hwfc->ارتفاع;

    أرجع 0;
}

تعريفنوع بنية DRMMapping {
    // Address and length of each mmap()ed region.
    صحيح nb_regions;
    صحيح sync_flags;
    صحيح object[AV_DRM_MAX_PLANES];
    فراغ *آدرس[AV_DRM_MAX_PLANES];
    size_t درازی[AV_DRM_MAX_PLANES];
} DRMMapping;

ساكن فراغ drm_unmap_قاب(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    لكل (صحيح i = 0; i < map->nb_regions; i++) {
#إذا HAVE_LINUX_DMA_BUF_H
        بنية dma_buf_sync sync = { .flags = DMA_BUF_SYNC_انتها | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#پایان_اگر
        munmap(map->آدرس[i], map->درازی[i]);
    }

    av_free(map);
}

ساكن صحيح drm_map_قاب(AVHWFramesContext *hwfc,
                         AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    ثابت AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->داده[0];
#إذا HAVE_LINUX_DMA_BUF_H
    بنية dma_buf_sync sync_شروع = { 0 };
#پایان_اگر
    DRMMapping *map;
    صحيح err, i, p, plane;
    صحيح mmap_prot;
    فراغ *addr;

    map = av_mallocz(حجم(*map));
    إذا (!map)
        أرجع AVERROR(ENOMEM);

    mmap_prot = 0;
    إذا (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    إذا (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#إذا HAVE_LINUX_DMA_BUF_H
    إذا (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    إذا (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_شروع.flags = DMA_BUF_SYNC_شروع | map->sync_flags;
#پایان_اگر

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    لكل (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(عدم, desc->objects[i].اندازه, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        إذا (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            اذهب fail;
        }

        map->آدرس[i] = addr;
        map->درازی[i]  = desc->objects[i].اندازه;
        map->object[i] = desc->objects[i].fd;

#إذا HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_شروع);
#پایان_اگر
    }
    map->nb_regions = i;

    plane = 0;
    لكل (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];
        لكل (p = 0; p < layer->nb_planes; p++) {
            dst->داده[plane] =
                (uint8_t*)map->آدرس[layer->planes[p].object_شاخص] +
                                       layer->planes[p].جابه_جایی;
            dst->linesize[plane] =     layer->planes[p].pitch;
            ++plane;
        }
    }
    av_assert0(plane <= AV_DRM_MAX_PLANES);

    dst->عرض  = src->عرض;
    dst->ارتفاع = src->ارتفاع;

    err = ff_hwframe_map_create(src->hw_قابها_ctx, dst, src,
                                &drm_unmap_قاب, map);
    إذا (err < 0)
        اذهب fail;

    أرجع 0;

fail:
    لكل (i = 0; i < desc->nb_objects; i++) {
        إذا (map->آدرس[i])
            munmap(map->آدرس[i], map->درازی[i]);
    }
    av_free(map);
    أرجع err;
}

ساكن صحيح drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    تعداد AVHWFrameTransferDirection dir,
                                    تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, حجم(*pix_fmts));
    إذا (!pix_fmts)
        أرجع AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    أرجع 0;
}

ساكن صحيح drm_transfer_داده_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    إذا (dst->عرض > hwfc->عرض || dst->ارتفاع > hwfc->ارتفاع)
        أرجع AVERROR(EINVAL);

    map = av_قاب_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_قاب(hwfc, map, src, AV_HWFRAME_MAP_READ);
    إذا (err)
        اذهب fail;

    map->عرض  = dst->عرض;
    map->ارتفاع = dst->ارتفاع;

    err = av_قاب_copy(dst, map);
    إذا (err)
        اذهب fail;

    err = 0;
fail:
    av_قاب_free(&map);
    أرجع err;
}

ساكن صحيح drm_transfer_داده_مقصد(AVHWFramesContext *hwfc,
                                AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    إذا (src->عرض > hwfc->عرض || src->ارتفاع > hwfc->ارتفاع)
        أرجع AVERROR(EINVAL);

    map = av_قاب_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_قاب(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    إذا (err)
        اذهب fail;

    map->عرض  = src->عرض;
    map->ارتفاع = src->ارتفاع;

    err = av_قاب_copy(map, src);
    إذا (err)
        اذهب fail;

    err = 0;
fail:
    av_قاب_free(&map);
    أرجع err;
}

ساكن صحيح drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ثابت AVFrame *src, صحيح flags)
{
    صحيح err;

    إذا (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    وإلا إذا (hwfc->sw_format != dst->format)
        أرجع AVERROR(ENOSYS);

    err = drm_map_قاب(hwfc, dst, src, flags);
    إذا (err)
        أرجع err;

    err = av_قاب_copy_props(dst, src);
    إذا (err)
        أرجع err;

    أرجع 0;
}

ثابت HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_اندازه      = حجم(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .قابها_get_میانگیر      = &drm_get_میانگیر,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_داده_مقصد       = &drm_transfer_داده_مقصد,
    .transfer_داده_from     = &drm_transfer_داده_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]) {
        AV_PIX_FMT_DRM_اول,
        AV_PIX_FMT_NONE
    },
};
