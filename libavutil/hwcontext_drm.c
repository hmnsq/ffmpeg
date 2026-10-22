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
#නම් HAVE_LINUX_DMA_BUF_H
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

static පූර්ණ_සංඛ්‍යා drm_device_create(AVHWDeviceContext *hwdev, const var_na *device,
                             AVDictionary *opts, පූර්ණ_සංඛ්‍යා flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    නම් (hwctx->fd < 0)
        ආපසු AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    නම් (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        ආපසු AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->free = &drm_device_free;

    ආපසු 0;
}

static පූර්ණ_සංඛ්‍යා drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    නම් (!frame->buf[0])
        ආපසු AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_PRIME;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    ආපසු 0;
}

typedef sa_nracanaa DRMMapping {
    // Address and length of each mmap()ed region.
    පූර්ණ_සංඛ්‍යා nb_regions;
    පූර්ණ_සංඛ්‍යා sync_flags;
    පූර්ණ_සංඛ්‍යා object[AV_DRM_MAX_PLANES];
    void *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

static void drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < map->nb_regions; i++) {
#නම් HAVE_LINUX_DMA_BUF_H
        sa_nracanaa dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

static පූර්ණ_සංඛ්‍යා drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, const AVFrame *src, පූර්ණ_සංඛ්‍යා flags)
{
    const AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#නම් HAVE_LINUX_DMA_BUF_H
    sa_nracanaa dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    පූර්ණ_සංඛ්‍යා err, i, p, plane;
    පූර්ණ_සංඛ්‍යා mmap_prot;
    void *addr;

    map = av_mallocz(parimaa_na(*map));
    නම් (!map)
        ආපසු AVERROR(ENOMEM);

    mmap_prot = 0;
    නම් (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    නම් (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#නම් HAVE_LINUX_DMA_BUF_H
    නම් (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    නම් (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    සඳහා (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(NULL, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        නම් (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            goto fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#නම් HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    සඳහා (i = 0; i < desc->nb_layers; i++) {
        const AVDRMLayerDescriptor *layer = &desc->layers[i];
        සඳහා (p = 0; p < layer->nb_planes; p++) {
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
    නම් (err < 0)
        goto fail;

    ආපසු 0;

fail:
    සඳහා (i = 0; i < desc->nb_objects; i++) {
        නම් (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    ආපසු err;
}

static පූර්ණ_සංඛ්‍යා drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    ga_nanaa AVHWFrameTransferDirection dir,
                                    ga_nanaa AVPixelFormat **formats)
{
    ga_nanaa AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, parimaa_na(*pix_fmts));
    නම් (!pix_fmts)
        ආපසු AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ආපසු 0;
}

static පූර්ණ_සංඛ්‍යා drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    පූර්ණ_සංඛ්‍යා err;

    නම් (dst->width > hwfc->width || dst->height > hwfc->height)
        ආපසු AVERROR(EINVAL);

    map = av_frame_alloc();
    නම් (!map)
        ආපසු AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    නම් (err)
        goto fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    නම් (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    ආපසු err;
}

static පූර්ණ_සංඛ්‍යා drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    පූර්ණ_සංඛ්‍යා err;

    නම් (src->width > hwfc->width || src->height > hwfc->height)
        ආපසු AVERROR(EINVAL);

    map = av_frame_alloc();
    නම් (!map)
        ආපසු AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    නම් (err)
        goto fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    නම් (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    ආපසු err;
}

static පූර්ණ_සංඛ්‍යා drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        const AVFrame *src, පූර්ණ_සංඛ්‍යා flags)
{
    පූර්ණ_සංඛ්‍යා err;

    නම් (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    නැතහොත් නම් (hwfc->sw_format != dst->format)
        ආපසු AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    නම් (err)
        ආපසු err;

    err = av_frame_copy_props(dst, src);
    නම් (err)
        ආපසු err;

    ආපසු 0;
}

const HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = parimaa_na(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (const ga_nanaa AVPixelFormat[]) {
        AV_PIX_FMT_DRM_PRIME,
        AV_PIX_FMT_NONE
    },
};
