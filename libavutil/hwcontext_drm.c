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

#include "config.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#якщо HAVE_LINUX_DMA_BUF_H
#include <linux/dma-buf.h>
#include <sys/ioctl.h>
#endif

#include <drm.h>
#include <xf86drm.h>

#include "avassert.h"
#include "hwcontext.h"
#include "hwcontext_drm.h"
#include "hwcontext_internal.h"
#include "imgutils.h"
#include "mem.h"


static void drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

static ціле drm_device_create(AVHWDeviceContext *hwdev, const char *device,
                             AVDictionary *opts, ціле flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    якщо (hwctx->fd < 0)
        повернути AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    якщо (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        повернути AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->free = &drm_device_free;

    повернути 0;
}

static ціле drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    якщо (!frame->buf[0])
        повернути AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_PRIME;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    повернути 0;
}

typedef struct DRMMapping {
    // Address and length of each mmap()ed region.
    ціле nb_regions;
    ціле sync_flags;
    ціле object[AV_DRM_MAX_PLANES];
    void *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

static void drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    для (ціле i = 0; i < map->nb_regions; i++) {
#якщо HAVE_LINUX_DMA_BUF_H
        struct dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

static ціле drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, const AVFrame *src, ціле flags)
{
    const AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#якщо HAVE_LINUX_DMA_BUF_H
    struct dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    ціле err, i, p, plane;
    ціле mmap_prot;
    void *addr;

    map = av_mallocz(sizeof(*map));
    якщо (!map)
        повернути AVERROR(ENOMEM);

    mmap_prot = 0;
    якщо (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    якщо (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#якщо HAVE_LINUX_DMA_BUF_H
    якщо (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    якщо (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    для (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(NULL, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        якщо (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            goto fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#якщо HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    для (i = 0; i < desc->nb_layers; i++) {
        const AVDRMLayerDescriptor *layer = &desc->layers[i];
        для (p = 0; p < layer->nb_planes; p++) {
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
    якщо (err < 0)
        goto fail;

    повернути 0;

fail:
    для (i = 0; i < desc->nb_objects; i++) {
        якщо (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    повернути err;
}

static ціле drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    enum AVHWFrameTransferDirection dir,
                                    enum AVPixelFormat **formats)
{
    enum AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, sizeof(*pix_fmts));
    якщо (!pix_fmts)
        повернути AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    повернути 0;
}

static ціле drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    ціле err;

    якщо (dst->width > hwfc->width || dst->height > hwfc->height)
        повернути AVERROR(EINVAL);

    map = av_frame_alloc();
    якщо (!map)
        повернути AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    якщо (err)
        goto fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    якщо (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    повернути err;
}

static ціле drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    ціле err;

    якщо (src->width > hwfc->width || src->height > hwfc->height)
        повернути AVERROR(EINVAL);

    map = av_frame_alloc();
    якщо (!map)
        повернути AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    якщо (err)
        goto fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    якщо (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    повернути err;
}

static ціле drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        const AVFrame *src, ціле flags)
{
    ціле err;

    якщо (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    інакше якщо (hwfc->sw_format != dst->format)
        повернути AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    якщо (err)
        повернути err;

    err = av_frame_copy_props(dst, src);
    якщо (err)
        повернути err;

    повернути 0;
}

const HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = sizeof(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (const enum AVPixelFormat[]) {
        AV_PIX_FMT_DRM_PRIME,
        AV_PIX_FMT_NONE
    },
};
