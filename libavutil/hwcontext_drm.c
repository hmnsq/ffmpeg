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

#অন্তর্ভাৱ "config.h"

#অন্তর্ভাৱ <fcntl.h>
#অন্তর্ভাৱ <sys/mman.h>
#অন্তর্ভাৱ <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#যদি HAVE_LINUX_DMA_BUF_H
#অন্তর্ভাৱ <linux/dma-buf.h>
#অন্তর্ভাৱ <sys/ioctl.h>
#endif

#অন্তর্ভাৱ <drm.h>
#অন্তর্ভাৱ <xf86drm.h>

#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "hwcontext.h"
#অন্তর্ভাৱ "hwcontext_drm.h"
#অন্তর্ভাৱ "hwcontext_internal.h"
#অন্তর্ভাৱ "imgutils.h"
#অন্তর্ভাৱ "mem.h"


স্থির শূন্য drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

স্থির পূর্ণাঙ্ক drm_device_create(AVHWDeviceContext *hwdev, ধ্রুৱ ৱর্ণ *device,
                             AVDictionary *opts, পূর্ণাঙ্ক flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    যদি (hwctx->fd < 0)
        ঘূৰাই AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    যদি (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        ঘূৰাই AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->মুক্ত = &drm_device_free;

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    যদি (!frame->buf[0])
        ঘূৰাই AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_মৌলিক;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    ঘূৰাই 0;
}

প্রকারনির্দেশ সংরচনা DRMMapping {
    // Address and length of each mmap()ed region.
    পূর্ণাঙ্ক nb_regions;
    পূর্ণাঙ্ক sync_flags;
    পূর্ণাঙ্ক object[AV_DRM_MAX_PLANES];
    শূন্য *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

স্থির শূন্য drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    বাবে (পূর্ণাঙ্ক i = 0; i < map->nb_regions; i++) {
#যদি HAVE_LINUX_DMA_BUF_H
        সংরচনা dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

স্থির পূর্ণাঙ্ক drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, ধ্রুৱ AVFrame *src, পূর্ণাঙ্ক flags)
{
    ধ্রুৱ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#যদি HAVE_LINUX_DMA_BUF_H
    সংরচনা dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    পূর্ণাঙ্ক err, i, p, plane;
    পূর্ণাঙ্ক mmap_prot;
    শূন্য *addr;

    map = av_mallocz(পরিমাণ(*map));
    যদি (!map)
        ঘূৰাই AVERROR(ENOMEM);

    mmap_prot = 0;
    যদি (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    যদি (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#যদি HAVE_LINUX_DMA_BUF_H
    যদি (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    যদি (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    বাবে (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(রিক্ত, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        যদি (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            গচ্ছ fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#যদি HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    বাবে (i = 0; i < desc->nb_layers; i++) {
        ধ্রুৱ AVDRMLayerDescriptor *layer = &desc->layers[i];
        বাবে (p = 0; p < layer->nb_planes; p++) {
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
    যদি (err < 0)
        গচ্ছ fail;

    ঘূৰাই 0;

fail:
    বাবে (i = 0; i < desc->nb_objects; i++) {
        যদি (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    ঘূৰাই err;
}

স্থির পূর্ণাঙ্ক drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    গণনা AVHWFrameTransferDirection dir,
                                    গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, পরিমাণ(*pix_fmts));
    যদি (!pix_fmts)
        ঘূৰাই AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ধ্রুৱ AVFrame *src)
{
    AVFrame *map;
    পূর্ণাঙ্ক err;

    যদি (dst->width > hwfc->width || dst->height > hwfc->height)
        ঘূৰাই AVERROR(EINVAL);

    map = av_frame_alloc();
    যদি (!map)
        ঘূৰাই AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    যদি (err)
        গচ্ছ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    যদি (err)
        গচ্ছ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ঘূৰাই err;
}

স্থির পূর্ণাঙ্ক drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, ধ্রুৱ AVFrame *src)
{
    AVFrame *map;
    পূর্ণাঙ্ক err;

    যদি (src->width > hwfc->width || src->height > hwfc->height)
        ঘূৰাই AVERROR(EINVAL);

    map = av_frame_alloc();
    যদি (!map)
        ঘূৰাই AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    যদি (err)
        গচ্ছ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    যদি (err)
        গচ্ছ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ঘূৰাই err;
}

স্থির পূর্ণাঙ্ক drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ধ্রুৱ AVFrame *src, পূর্ণাঙ্ক flags)
{
    পূর্ণাঙ্ক err;

    যদি (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    অন্যথা যদি (hwfc->sw_format != dst->format)
        ঘূৰাই AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    যদি (err)
        ঘূৰাই err;

    err = av_frame_copy_props(dst, src);
    যদি (err)
        ঘূৰাই err;

    ঘূৰাই 0;
}

ধ্রুৱ HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = পরিমাণ(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ধ্রুৱ গণনা AVPixelFormat[]) {
        AV_PIX_FMT_DRM_মৌলিক,
        AV_PIX_FMT_NONE
    },
};
