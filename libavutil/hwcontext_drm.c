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

#অন্তর্ভাব "config.h"

#অন্তর্ভাব <fcntl.h>
#অন্তর্ভাব <sys/mman.h>
#অন্তর্ভাব <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#যদি HAVE_LINUX_DMA_BUF_H
#অন্তর্ভাব <linux/dma-buf.h>
#অন্তর্ভাব <sys/ioctl.h>
#endif

#অন্তর্ভাব <drm.h>
#অন্তর্ভাব <xf86drm.h>

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_drm.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "imgutils.h"
#অন্তর্ভাব "mem.h"


স্থির শূন্য drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

স্থির পূর্ণসংখ্যা drm_device_create(AVHWDeviceContext *hwdev, ধ্রুবক অক্ষর *device,
                             AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    যদি (hwctx->fd < 0)
        ফেরত AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    যদি (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        ফেরত AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->মুক্ত = &drm_device_free;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা drm_get_বাফার(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_বাফার_pool_get(hwfc->pool);
    যদি (!frame->buf[0])
        ফেরত AVERROR(ENOMEM);

    frame->তথ্য[0] = (uint8_t*)frame->buf[0]->তথ্য;

    frame->format = AV_PIX_FMT_DRM_মৌলিক;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    ফেরত 0;
}

প্রকারলেখ কাঠামো DRMMapping {
    // Address and length of each mmap()ed region.
    পূর্ণসংখ্যা nb_regions;
    পূর্ণসংখ্যা sync_flags;
    পূর্ণসংখ্যা object[AV_DRM_MAX_PLANES];
    শূন্য *address[AV_DRM_MAX_PLANES];
    size_t দৈর্ঘ্য[AV_DRM_MAX_PLANES];
} DRMMapping;

স্থির শূন্য drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    জন্য (পূর্ণসংখ্যা i = 0; i < map->nb_regions; i++) {
#যদি HAVE_LINUX_DMA_BUF_H
        কাঠামো dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->দৈর্ঘ্য[i]);
    }

    av_free(map);
}

স্থির পূর্ণসংখ্যা drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    ধ্রুবক AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->তথ্য[0];
#যদি HAVE_LINUX_DMA_BUF_H
    কাঠামো dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    পূর্ণসংখ্যা err, i, p, plane;
    পূর্ণসংখ্যা mmap_prot;
    শূন্য *addr;

    map = av_mallocz(আকার(*map));
    যদি (!map)
        ফেরত AVERROR(ENOMEM);

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
    জন্য (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(ফাঁকা, desc->objects[i].আকার_2, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        যদি (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            যাও fail;
        }

        map->address[i] = addr;
        map->দৈর্ঘ্য[i]  = desc->objects[i].আকার_2;
        map->object[i] = desc->objects[i].fd;

#যদি HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    জন্য (i = 0; i < desc->nb_layers; i++) {
        ধ্রুবক AVDRMLayerDescriptor *layer = &desc->layers[i];
        জন্য (p = 0; p < layer->nb_planes; p++) {
            dst->তথ্য[plane] =
                (uint8_t*)map->address[layer->planes[p].object_সূচক] +
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
        যাও fail;

    ফেরত 0;

fail:
    জন্য (i = 0; i < desc->nb_objects; i++) {
        যদি (map->address[i])
            munmap(map->address[i], map->দৈর্ঘ্য[i]);
    }
    av_free(map);
    ফেরত err;
}

স্থির পূর্ণসংখ্যা drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    গণনা AVHWFrameTransferDirection dir,
                                    গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, আকার(*pix_fmts));
    যদি (!pix_fmts)
        ফেরত AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা drm_transfer_তথ্য_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ধ্রুবক AVFrame *src)
{
    AVFrame *map;
    পূর্ণসংখ্যা err;

    যদি (dst->width > hwfc->width || dst->height > hwfc->height)
        ফেরত AVERROR(EINVAL);

    map = av_frame_alloc();
    যদি (!map)
        ফেরত AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    যদি (err)
        যাও fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    যদি (err)
        যাও fail;

    err = 0;
fail:
    av_frame_free(&map);
    ফেরত err;
}

স্থির পূর্ণসংখ্যা drm_transfer_তথ্য_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, ধ্রুবক AVFrame *src)
{
    AVFrame *map;
    পূর্ণসংখ্যা err;

    যদি (src->width > hwfc->width || src->height > hwfc->height)
        ফেরত AVERROR(EINVAL);

    map = av_frame_alloc();
    যদি (!map)
        ফেরত AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    যদি (err)
        যাও fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    যদি (err)
        যাও fail;

    err = 0;
fail:
    av_frame_free(&map);
    ফেরত err;
}

স্থির পূর্ণসংখ্যা drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    পূর্ণসংখ্যা err;

    যদি (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    অন্যথা যদি (hwfc->sw_format != dst->format)
        ফেরত AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    যদি (err)
        ফেরত err;

    err = av_frame_copy_props(dst, src);
    যদি (err)
        ফেরত err;

    ফেরত 0;
}

ধ্রুবক HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_আকার      = আকার(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_বাফার      = &drm_get_বাফার,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_তথ্য_to       = &drm_transfer_তথ্য_to,
    .transfer_তথ্য_from     = &drm_transfer_তথ্য_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ধ্রুবক গণনা AVPixelFormat[]) {
        AV_PIX_FMT_DRM_মৌলিক,
        AV_PIX_FMT_NONE
    },
};
