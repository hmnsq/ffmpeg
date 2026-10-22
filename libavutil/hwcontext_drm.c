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
#ಯದಿ HAVE_LINUX_DMA_BUF_H
#ಅನ್ತರ್ಭಾವ <linux/dma-buf.h>
#ಅನ್ತರ್ಭಾವ <sys/ioctl.h>
#endif

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

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ drm_device_create(AVHWDeviceContext *hwdev, ಧ್ರುವ ವರ್ಣ *device,
                             AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    ಯದಿ (hwctx->fd < 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    ಯದಿ (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->ಮುಕ್ತ = &drm_device_free;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ DRMMapping {
    // Address and length of each mmap()ed region.
    ಪೂರ್ಣಾಙ್ಕ nb_regions;
    ಪೂರ್ಣಾಙ್ಕ sync_flags;
    ಪೂರ್ಣಾಙ್ಕ object[AV_DRM_MAX_PLANES];
    ಶೂನ್ಯ *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

ಸ್ಥಿರ ಶೂನ್ಯ drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < map->nb_regions; i++) {
#ಯದಿ HAVE_LINUX_DMA_BUF_H
        ಸಂರಚನಾ dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#ಯದಿ HAVE_LINUX_DMA_BUF_H
    ಸಂರಚನಾ dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    ಪೂರ್ಣಾಙ್ಕ err, i, p, plane;
    ಪೂರ್ಣಾಙ್ಕ mmap_prot;
    ಶೂನ್ಯ *addr;

    map = av_mallocz(ಪರಿಮಾಣ(*map));
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    mmap_prot = 0;
    ಯದಿ (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    ಯದಿ (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#ಯದಿ HAVE_LINUX_DMA_BUF_H
    ಯದಿ (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    ಯದಿ (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    ಪ್ರತಿ (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(ರಿಕ್ತ, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        ಯದಿ (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            ಗಚ್ಛ fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#ಯದಿ HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    ಪ್ರತಿ (i = 0; i < desc->nb_layers; i++) {
        ಧ್ರುವ AVDRMLayerDescriptor *layer = &desc->layers[i];
        ಪ್ರತಿ (p = 0; p < layer->nb_planes; p++) {
            dst->data[plane] =
                (uint8_t*)map->address[layer->planes[p].object_index] +
                                       layer->planes[p].offset;
            dst->linesize[plane] =     layer->planes[p].pitch;
            ++plane;
        }
    }
    av_assert0(plane <= AV_DRM_MAX_PLANES);

    dst->width  = src->width;
    dst->height = src->height;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &drm_unmap_frame, map);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (i = 0; i < desc->nb_objects; i++) {
        ಯದಿ (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    ಗಣನಾ AVHWFrameTransferDirection dir,
                                    ಗಣನಾ AVPixelFormat **formats)
{
    ಗಣನಾ AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, ಪರಿಮಾಣ(*pix_fmts));
    ಯದಿ (!pix_fmts)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (dst->width > hwfc->width || dst->height > hwfc->height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    map = av_frame_alloc();
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (src->width > hwfc->width || src->height > hwfc->height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    map = av_frame_alloc();
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ಅನ್ಯಥಾ ಯದಿ (hwfc->sw_format != dst->format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    err = av_frame_copy_props(dst, src);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಧ್ರುವ HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = ಪರಿಮಾಣ(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]) {
        AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ,
        AV_PIX_FMT_NONE
    },
};
