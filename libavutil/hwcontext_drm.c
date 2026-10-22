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
#ܐܢ HAVE_LINUX_DMA_BUF_H
#ضمن <linux/dma-buf.h>
#ضمن <sys/ioctl.h>
#endif

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
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    ܐܢ (hwctx->fd < 0)
        ܦܢܐ AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    ܐܢ (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        ܦܢܐ AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->حرر = &drm_device_free;

    ܦܢܐ 0;
}

ساكن صحيح drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ܐܢ (!frame->buf[0])
        ܦܢܐ AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_PRIME;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    ܦܢܐ 0;
}

تعريفنوع بنية DRMMapping {
    // Address and length of each mmap()ed region.
    صحيح nb_regions;
    صحيح sync_flags;
    صحيح object[AV_DRM_MAX_PLANES];
    فراغ *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

ساكن فراغ drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    لكل (صحيح i = 0; i < map->nb_regions; i++) {
#ܐܢ HAVE_LINUX_DMA_BUF_H
        بنية dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

ساكن صحيح drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    ثابت AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#ܐܢ HAVE_LINUX_DMA_BUF_H
    بنية dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    صحيح err, i, p, plane;
    صحيح mmap_prot;
    فراغ *addr;

    map = av_mallocz(حجم(*map));
    ܐܢ (!map)
        ܦܢܐ AVERROR(ENOMEM);

    mmap_prot = 0;
    ܐܢ (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    ܐܢ (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#ܐܢ HAVE_LINUX_DMA_BUF_H
    ܐܢ (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    ܐܢ (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    لكل (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(عدم, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        ܐܢ (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            اذهب fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#ܐܢ HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    لكل (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];
        لكل (p = 0; p < layer->nb_planes; p++) {
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
    ܐܢ (err < 0)
        اذهب fail;

    ܦܢܐ 0;

fail:
    لكل (i = 0; i < desc->nb_objects; i++) {
        ܐܢ (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    ܦܢܐ err;
}

ساكن صحيح drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    تعداد AVHWFrameTransferDirection dir,
                                    تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, حجم(*pix_fmts));
    ܐܢ (!pix_fmts)
        ܦܢܐ AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ܦܢܐ 0;
}

ساكن صحيح drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    ܐܢ (dst->width > hwfc->width || dst->height > hwfc->height)
        ܦܢܐ AVERROR(EINVAL);

    map = av_frame_alloc();
    ܐܢ (!map)
        ܦܢܐ AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ܐܢ (err)
        اذهب fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    ܐܢ (err)
        اذهب fail;

    err = 0;
fail:
    av_frame_free(&map);
    ܦܢܐ err;
}

ساكن صحيح drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    ܐܢ (src->width > hwfc->width || src->height > hwfc->height)
        ܦܢܐ AVERROR(EINVAL);

    map = av_frame_alloc();
    ܐܢ (!map)
        ܦܢܐ AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    ܐܢ (err)
        اذهب fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    ܐܢ (err)
        اذهب fail;

    err = 0;
fail:
    av_frame_free(&map);
    ܦܢܐ err;
}

ساكن صحيح drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ثابت AVFrame *src, صحيح flags)
{
    صحيح err;

    ܐܢ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ܐܚܪܢܐ ܐܢ (hwfc->sw_format != dst->format)
        ܦܢܐ AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    ܐܢ (err)
        ܦܢܐ err;

    err = av_frame_copy_props(dst, src);
    ܐܢ (err)
        ܦܢܐ err;

    ܦܢܐ 0;
}

ثابت HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = حجم(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]) {
        AV_PIX_FMT_DRM_PRIME,
        AV_PIX_FMT_NONE
    },
};
