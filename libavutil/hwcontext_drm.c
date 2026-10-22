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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#ಆದರೆ HAVE_LINUX_DMA_BUF_H
#ಅನ್ತರ್ಭಾವ <linux/dma-buf.h>
#ಅನ್ತರ್ಭಾವ <sys/ioctl.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <drm.h>
#ಅನ್ತರ್ಭಾವ <xf86drm.h>

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_drm.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "mem.h"


ಸ್ಥಿರ ಶೂನ್ಯ drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ drm_device_create(AVHWDeviceContext *hwdev, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                             AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drm_ಆವೃತ್ತಿ_Ptr ಆವೃತ್ತಿ;

    hwctx->fd = open(device, O_RDWR);
    ಆದರೆ (hwctx->fd < 0)
        ಹಿಂತಿರುಗಿ AVERROR(errno);

    ಆವೃತ್ತಿ = drm_Get_ಆವೃತ್ತಿ(hwctx->fd);
    ಆದರೆ (!ಆವೃತ್ತಿ) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, ಆವೃತ್ತಿ->name,
           ಆವೃತ್ತಿ->ಆವೃತ್ತಿ_major, ಆವೃತ್ತಿ->ಆವೃತ್ತಿ_minor,
           ಆವೃತ್ತಿ->ಆವೃತ್ತಿ_patchlevel);

    drm_Free_ಆವೃತ್ತಿ(ಆವೃತ್ತಿ);

    hwdev->ಬಿಡುಗಡೆ = &drm_device_free;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ drm_get_ಬಫರ್(AVHWFramesContext *hwfc, AVFrame *ಚೌಕಟ್ಟು)
{
    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(hwfc->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] = (uint8_t*)ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;

    ಚೌಕಟ್ಟು->format = AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ;
    ಚೌಕಟ್ಟು->ಅಗಲ  = hwfc->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ = hwfc->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DRMMapping {
    // Address and length of each mmap()ed region.
    ಪೂರ್ಣಾಂಕ nb_regions;
    ಪೂರ್ಣಾಂಕ sync_flags;
    ಪೂರ್ಣಾಂಕ object[AV_DRM_MAX_PLANES];
    ಶೂನ್ಯ *ವಿಳಾಸ[AV_DRM_MAX_PLANES];
    size_t ಉದ್ದಳತೆ[AV_DRM_MAX_PLANES];
} DRMMapping;

ಸ್ಥಿರ ಶೂನ್ಯ drm_unmap_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < map->nb_regions; i++) {
#ಆದರೆ HAVE_LINUX_DMA_BUF_H
        ರಚನೆ dma_buf_sync sync = { .flags = DMA_BUF_SYNC_ಕೊನೆ | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#ಆದರೆ_ಅಂತ್ಯ
        munmap(map->ವಿಳಾಸ[i], map->ಉದ್ದಳತೆ[i]);
    }

    av_free(map);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ drm_map_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc,
                         AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->ದತ್ತಾಂಶ[0];
#ಆದರೆ HAVE_LINUX_DMA_BUF_H
    ರಚನೆ dma_buf_sync sync_ಆರಂಭ = { 0 };
#ಆದರೆ_ಅಂತ್ಯ
    DRMMapping *map;
    ಪೂರ್ಣಾಂಕ err, i, p, plane;
    ಪೂರ್ಣಾಂಕ mmap_prot;
    ಶೂನ್ಯ *addr;

    map = av_mallocz(ಗಾತ್ರ(*map));
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    mmap_prot = 0;
    ಆದರೆ (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    ಆದರೆ (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#ಆದರೆ HAVE_LINUX_DMA_BUF_H
    ಆದರೆ (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    ಆದರೆ (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_ಆರಂಭ.flags = DMA_BUF_SYNC_ಆರಂಭ | map->sync_flags;
#ಆದರೆ_ಅಂತ್ಯ

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    ಗಾಗಿ (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(ಖಾಲಿ, desc->objects[i].ಗಾತ್ರ_2, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        ಆದರೆ (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            ಹೋಗು fail;
        }

        map->ವಿಳಾಸ[i] = addr;
        map->ಉದ್ದಳತೆ[i]  = desc->objects[i].ಗಾತ್ರ_2;
        map->object[i] = desc->objects[i].fd;

#ಆದರೆ HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_ಆರಂಭ);
#ಆದರೆ_ಅಂತ್ಯ
    }
    map->nb_regions = i;

    plane = 0;
    ಗಾಗಿ (i = 0; i < desc->nb_layers; i++) {
        ಸ್ಥಿರಾಂಕ AVDRMLayerDescriptor *layer = &desc->layers[i];
        ಗಾಗಿ (p = 0; p < layer->nb_planes; p++) {
            dst->ದತ್ತಾಂಶ[plane] =
                (uint8_t*)map->ವಿಳಾಸ[layer->planes[p].object_ಸೂಚ್ಯಂಕ] +
                                       layer->planes[p].ಸ್ಥಾನಾಂತರ;
            dst->linesize[plane] =     layer->planes[p].pitch;
            ++plane;
        }
    }
    av_assert0(plane <= AV_DRM_MAX_PLANES);

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    err = ff_hwframe_map_create(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &drm_unmap_ಚೌಕಟ್ಟು, map);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (i = 0; i < desc->nb_objects; i++) {
        ಆದರೆ (map->ವಿಳಾಸ[i])
            munmap(map->ವಿಳಾಸ[i], map->ಉದ್ದಳತೆ[i]);
    }
    av_free(map);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                    ಎಣಿಕೆ AVPixelFormat **formats)
{
    ಎಣಿಕೆ AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, ಗಾತ್ರ(*pix_fmts));
    ಆದರೆ (!pix_fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ drm_transfer_ದತ್ತಾಂಶ_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (dst->ಅಗಲ > hwfc->ಅಗಲ || dst->ಎತ್ತರ > hwfc->ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    map = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_ಚೌಕಟ್ಟು(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ಆದರೆ (err)
        ಹೋಗು fail;

    map->ಅಗಲ  = dst->ಅಗಲ;
    map->ಎತ್ತರ = dst->ಎತ್ತರ;

    err = av_ಚೌಕಟ್ಟು_copy(dst, map);
    ಆದರೆ (err)
        ಹೋಗು fail;

    err = 0;
fail:
    av_ಚೌಕಟ್ಟು_free(&map);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ drm_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(AVHWFramesContext *hwfc,
                                AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (src->ಅಗಲ > hwfc->ಅಗಲ || src->ಎತ್ತರ > hwfc->ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    map = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_ಚೌಕಟ್ಟು(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    ಆದರೆ (err)
        ಹೋಗು fail;

    map->ಅಗಲ  = src->ಅಗಲ;
    map->ಎತ್ತರ = src->ಎತ್ತರ;

    err = av_ಚೌಕಟ್ಟು_copy(map, src);
    ಆದರೆ (err)
        ಹೋಗು fail;

    err = 0;
fail:
    av_ಚೌಕಟ್ಟು_free(&map);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (hwfc->sw_format != dst->format)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

    err = drm_map_ಚೌಕಟ್ಟು(hwfc, dst, src, flags);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    err = av_ಚೌಕಟ್ಟು_copy_props(dst, src);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್      = &drm_get_ಬಫರ್,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ       = &drm_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ,
    .transfer_ದತ್ತಾಂಶ_from     = &drm_transfer_ದತ್ತಾಂಶ_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]) {
        AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ,
        AV_PIX_FMT_NONE
    },
};
