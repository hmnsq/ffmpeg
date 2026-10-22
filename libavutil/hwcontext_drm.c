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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/mman.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#ਜੇ HAVE_LINUX_DMA_BUF_H
#ਅਨ੍ਤਰ੍ਭਾਵ <linux/dma-buf.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/ioctl.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <drm.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xf86drm.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_drm.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"


ਸਥਿਰ ਖਾਲੀ drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

ਸਥਿਰ ਪੂਰਨ drm_device_create(AVHWDeviceContext *hwdev, ਅਚਲ ਅੱਖਰ *device,
                             AVDictionary *opts, ਪੂਰਨ flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drm_ਸੰਸਕਰਣ_Ptr ਸੰਸਕਰਣ;

    hwctx->fd = open(device, O_RDWR);
    ਜੇ (hwctx->fd < 0)
        ਵਾਪਸ AVERROR(errno);

    ਸੰਸਕਰਣ = drm_Get_ਸੰਸਕਰਣ(hwctx->fd);
    ਜੇ (!ਸੰਸਕਰਣ) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, ਸੰਸਕਰਣ->name,
           ਸੰਸਕਰਣ->ਸੰਸਕਰਣ_major, ਸੰਸਕਰਣ->ਸੰਸਕਰਣ_minor,
           ਸੰਸਕਰਣ->ਸੰਸਕਰਣ_patchlevel);

    drm_Free_ਸੰਸਕਰਣ(ਸੰਸਕਰਣ);

    hwdev->ਮੁਕਤ = &drm_device_free;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ drm_get_ਬਫਰ(AVHWFramesContext *hwfc, AVFrame *ਚੌਖਟਾ)
{
    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(hwfc->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    ਚੌਖਟਾ->ਅੰਕੜੇ[0] = (uint8_t*)ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;

    ਚੌਖਟਾ->format = AV_PIX_FMT_DRM_ਅਭਾਜ;
    ਚੌਖਟਾ->ਚੌੜਾਈ  = hwfc->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ = hwfc->ਉਚਾਈ;

    ਵਾਪਸ 0;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DRMMapping {
    // Address and length of each mmap()ed region.
    ਪੂਰਨ nb_regions;
    ਪੂਰਨ sync_flags;
    ਪੂਰਨ object[AV_DRM_MAX_PLANES];
    ਖਾਲੀ *ਪਤਾ[AV_DRM_MAX_PLANES];
    size_t ਲੰਮਾਈ[AV_DRM_MAX_PLANES];
} DRMMapping;

ਸਥਿਰ ਖਾਲੀ drm_unmap_ਚੌਖਟਾ(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    ਲਈ (ਪੂਰਨ i = 0; i < map->nb_regions; i++) {
#ਜੇ HAVE_LINUX_DMA_BUF_H
        ਬਣਤਰ dma_buf_sync sync = { .flags = DMA_BUF_SYNC_ਸਿਰਾ | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#ਜੇ_ਅੰਤ
        munmap(map->ਪਤਾ[i], map->ਲੰਮਾਈ[i]);
    }

    av_free(map);
}

ਸਥਿਰ ਪੂਰਨ drm_map_ਚੌਖਟਾ(AVHWFramesContext *hwfc,
                         AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    ਅਚਲ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->ਅੰਕੜੇ[0];
#ਜੇ HAVE_LINUX_DMA_BUF_H
    ਬਣਤਰ dma_buf_sync sync_ਸ਼ੁਰੂ = { 0 };
#ਜੇ_ਅੰਤ
    DRMMapping *map;
    ਪੂਰਨ err, i, p, plane;
    ਪੂਰਨ mmap_prot;
    ਖਾਲੀ *addr;

    map = av_mallocz(ਆਕਾਰ(*map));
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(ENOMEM);

    mmap_prot = 0;
    ਜੇ (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    ਜੇ (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#ਜੇ HAVE_LINUX_DMA_BUF_H
    ਜੇ (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    ਜੇ (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_ਸ਼ੁਰੂ.flags = DMA_BUF_SYNC_ਸ਼ੁਰੂ | map->sync_flags;
#ਜੇ_ਅੰਤ

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    ਲਈ (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(ਨਿਰਾ, desc->objects[i].ਮਾਪ, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        ਜੇ (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            ਜਾਓ fail;
        }

        map->ਪਤਾ[i] = addr;
        map->ਲੰਮਾਈ[i]  = desc->objects[i].ਮਾਪ;
        map->object[i] = desc->objects[i].fd;

#ਜੇ HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_ਸ਼ੁਰੂ);
#ਜੇ_ਅੰਤ
    }
    map->nb_regions = i;

    plane = 0;
    ਲਈ (i = 0; i < desc->nb_layers; i++) {
        ਅਚਲ AVDRMLayerDescriptor *layer = &desc->layers[i];
        ਲਈ (p = 0; p < layer->nb_planes; p++) {
            dst->ਅੰਕੜੇ[plane] =
                (uint8_t*)map->ਪਤਾ[layer->planes[p].object_ਸੂਚਕਾਂਕ] +
                                       layer->planes[p].ਵਿੱਥ;
            dst->linesize[plane] =     layer->planes[p].pitch;
            ++plane;
        }
    }
    av_assert0(plane <= AV_DRM_MAX_PLANES);

    dst->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;

    err = ff_hwframe_map_create(src->hw_ਚੌਖਟੇ_ctx, dst, src,
                                &drm_unmap_ਚੌਖਟਾ, map);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    ਵਾਪਸ 0;

fail:
    ਲਈ (i = 0; i < desc->nb_objects; i++) {
        ਜੇ (map->ਪਤਾ[i])
            munmap(map->ਪਤਾ[i], map->ਲੰਮਾਈ[i]);
    }
    av_free(map);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                    ਗਿਣਤੀ AVPixelFormat **formats)
{
    ਗਿਣਤੀ AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, ਆਕਾਰ(*pix_fmts));
    ਜੇ (!pix_fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ drm_transfer_ਅੰਕੜੇ_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ਅਚਲ AVFrame *src)
{
    AVFrame *map;
    ਪੂਰਨ err;

    ਜੇ (dst->ਚੌੜਾਈ > hwfc->ਚੌੜਾਈ || dst->ਉਚਾਈ > hwfc->ਉਚਾਈ)
        ਵਾਪਸ AVERROR(EINVAL);

    map = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_ਚੌਖਟਾ(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ਜੇ (err)
        ਜਾਓ fail;

    map->ਚੌੜਾਈ  = dst->ਚੌੜਾਈ;
    map->ਉਚਾਈ = dst->ਉਚਾਈ;

    err = av_ਚੌਖਟਾ_copy(dst, map);
    ਜੇ (err)
        ਜਾਓ fail;

    err = 0;
fail:
    av_ਚੌਖਟਾ_free(&map);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ drm_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(AVHWFramesContext *hwfc,
                                AVFrame *dst, ਅਚਲ AVFrame *src)
{
    AVFrame *map;
    ਪੂਰਨ err;

    ਜੇ (src->ਚੌੜਾਈ > hwfc->ਚੌੜਾਈ || src->ਉਚਾਈ > hwfc->ਉਚਾਈ)
        ਵਾਪਸ AVERROR(EINVAL);

    map = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_ਚੌਖਟਾ(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    ਜੇ (err)
        ਜਾਓ fail;

    map->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    map->ਉਚਾਈ = src->ਉਚਾਈ;

    err = av_ਚੌਖਟਾ_copy(map, src);
    ਜੇ (err)
        ਜਾਓ fail;

    err = 0;
fail:
    av_ਚੌਖਟਾ_free(&map);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    ਪੂਰਨ err;

    ਜੇ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ਨਹੀਂਤਾਂ ਜੇ (hwfc->sw_format != dst->format)
        ਵਾਪਸ AVERROR(ENOSYS);

    err = drm_map_ਚੌਖਟਾ(hwfc, dst, src, flags);
    ਜੇ (err)
        ਵਾਪਸ err;

    err = av_ਚੌਖਟਾ_copy_props(dst, src);
    ਜੇ (err)
        ਵਾਪਸ err;

    ਵਾਪਸ 0;
}

ਅਚਲ HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_ਮਾਪ      = ਆਕਾਰ(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .ਚੌਖਟੇ_get_ਬਫਰ      = &drm_get_ਬਫਰ,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ       = &drm_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ,
    .transfer_ਅੰਕੜੇ_from     = &drm_transfer_ਅੰਕੜੇ_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]) {
        AV_PIX_FMT_DRM_ਅਭਾਜ,
        AV_PIX_FMT_NONE
    },
};
