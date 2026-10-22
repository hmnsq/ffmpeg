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

#شامل "config.h"

#شامل <fcntl.h>
#شامل <sys/mman.h>
#شامل <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#اگر HAVE_LINUX_DMA_BUF_H
#شامل <linux/dma-buf.h>
#شامل <sys/ioctl.h>
#endif

#شامل <drm.h>
#شامل <xf86drm.h>

#شامل "avassert.h"
#شامل "hwcontext.h"
#شامل "hwcontext_drm.h"
#شامل "hwcontext_internal.h"
#شامل "imgutils.h"
#شامل "mem.h"


ایستا تهی drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

ایستا صحیح drm_device_create(AVHWDeviceContext *hwdev, ثابت نویسه *device,
                             AVDictionary *opts, صحیح flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    اگر (hwctx->fd < 0)
        بازگشت AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    اگر (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        بازگشت AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->آزاد = &drm_device_free;

    بازگشت 0;
}

ایستا صحیح drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_اول;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    بازگشت 0;
}

تعریفنوع ساختار DRMMapping {
    // Address and length of each mmap()ed region.
    صحیح nb_regions;
    صحیح sync_flags;
    صحیح object[AV_DRM_MAX_PLANES];
    تهی *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

ایستا تهی drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    برای (صحیح i = 0; i < map->nb_regions; i++) {
#اگر HAVE_LINUX_DMA_BUF_H
        ساختار dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

ایستا صحیح drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    ثابت AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#اگر HAVE_LINUX_DMA_BUF_H
    ساختار dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    صحیح err, i, p, plane;
    صحیح mmap_prot;
    تهی *addr;

    map = av_mallocz(اندازه(*map));
    اگر (!map)
        بازگشت AVERROR(ENOMEM);

    mmap_prot = 0;
    اگر (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    اگر (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#اگر HAVE_LINUX_DMA_BUF_H
    اگر (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    اگر (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    برای (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(پوچ, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        اگر (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            برو fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#اگر HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    برای (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];
        برای (p = 0; p < layer->nb_planes; p++) {
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
    اگر (err < 0)
        برو fail;

    بازگشت 0;

fail:
    برای (i = 0; i < desc->nb_objects; i++) {
        اگر (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    بازگشت err;
}

ایستا صحیح drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    شمارش AVHWFrameTransferDirection dir,
                                    شمارش AVPixelFormat **formats)
{
    شمارش AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, اندازه(*pix_fmts));
    اگر (!pix_fmts)
        بازگشت AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    بازگشت 0;
}

ایستا صحیح drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (dst->width > hwfc->width || dst->height > hwfc->height)
        بازگشت AVERROR(EINVAL);

    map = av_frame_alloc();
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    اگر (err)
        برو fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    اگر (err)
        برو fail;

    err = 0;
fail:
    av_frame_free(&map);
    بازگشت err;
}

ایستا صحیح drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (src->width > hwfc->width || src->height > hwfc->height)
        بازگشت AVERROR(EINVAL);

    map = av_frame_alloc();
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    اگر (err)
        برو fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    اگر (err)
        برو fail;

    err = 0;
fail:
    av_frame_free(&map);
    بازگشت err;
}

ایستا صحیح drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ثابت AVFrame *src, صحیح flags)
{
    صحیح err;

    اگر (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    وگرنه اگر (hwfc->sw_format != dst->format)
        بازگشت AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    اگر (err)
        بازگشت err;

    err = av_frame_copy_props(dst, src);
    اگر (err)
        بازگشت err;

    بازگشت 0;
}

ثابت HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = اندازه(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ثابت شمارش AVPixelFormat[]) {
        AV_PIX_FMT_DRM_اول,
        AV_PIX_FMT_NONE
    },
};
