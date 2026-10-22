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

#அந்தர்பாவ "config.h"

#அந்தர்பாவ <fcntl.h>
#அந்தர்பாவ <sys/mman.h>
#அந்தர்பாவ <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#எனில் HAVE_LINUX_DMA_BUF_H
#அந்தர்பாவ <linux/dma-buf.h>
#அந்தர்பாவ <sys/ioctl.h>
#endif

#அந்தர்பாவ <drm.h>
#அந்தர்பாவ <xf86drm.h>

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_drm.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "imgutils.h"
#அந்தர்பாவ "mem.h"


நிலையான வெறுமை drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

நிலையான முழு drm_device_create(AVHWDeviceContext *hwdev, மாறிலி எழுத்து *device,
                             AVDictionary *opts, முழு flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    எனில் (hwctx->fd < 0)
        திரும்பு AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    எனில் (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        திரும்பு AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->விடுவி = &drm_device_free;

    திரும்பு 0;
}

நிலையான முழு drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    எனில் (!frame->buf[0])
        திரும்பு AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_பகாஎண்;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    திரும்பு 0;
}

வகைவரை கட்டமைப்பு DRMMapping {
    // Address and length of each mmap()ed region.
    முழு nb_regions;
    முழு sync_flags;
    முழு object[AV_DRM_MAX_PLANES];
    வெறுமை *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

நிலையான வெறுமை drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    க்கு (முழு i = 0; i < map->nb_regions; i++) {
#எனில் HAVE_LINUX_DMA_BUF_H
        கட்டமைப்பு dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

நிலையான முழு drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, மாறிலி AVFrame *src, முழு flags)
{
    மாறிலி AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#எனில் HAVE_LINUX_DMA_BUF_H
    கட்டமைப்பு dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    முழு err, i, p, plane;
    முழு mmap_prot;
    வெறுமை *addr;

    map = av_mallocz(அளவு(*map));
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);

    mmap_prot = 0;
    எனில் (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    எனில் (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#எனில் HAVE_LINUX_DMA_BUF_H
    எனில் (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    எனில் (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    க்கு (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(வெற்று, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        எனில் (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            செல் fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#எனில் HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    க்கு (i = 0; i < desc->nb_layers; i++) {
        மாறிலி AVDRMLayerDescriptor *layer = &desc->layers[i];
        க்கு (p = 0; p < layer->nb_planes; p++) {
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
    எனில் (err < 0)
        செல் fail;

    திரும்பு 0;

fail:
    க்கு (i = 0; i < desc->nb_objects; i++) {
        எனில் (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    திரும்பு err;
}

நிலையான முழு drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    எண்ணிக்கை AVHWFrameTransferDirection dir,
                                    எண்ணிக்கை AVPixelFormat **formats)
{
    எண்ணிக்கை AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, அளவு(*pix_fmts));
    எனில் (!pix_fmts)
        திரும்பு AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    திரும்பு 0;
}

நிலையான முழு drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, மாறிலி AVFrame *src)
{
    AVFrame *map;
    முழு err;

    எனில் (dst->width > hwfc->width || dst->height > hwfc->height)
        திரும்பு AVERROR(EINVAL);

    map = av_frame_alloc();
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    எனில் (err)
        செல் fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    எனில் (err)
        செல் fail;

    err = 0;
fail:
    av_frame_free(&map);
    திரும்பு err;
}

நிலையான முழு drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, மாறிலி AVFrame *src)
{
    AVFrame *map;
    முழு err;

    எனில் (src->width > hwfc->width || src->height > hwfc->height)
        திரும்பு AVERROR(EINVAL);

    map = av_frame_alloc();
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    எனில் (err)
        செல் fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    எனில் (err)
        செல் fail;

    err = 0;
fail:
    av_frame_free(&map);
    திரும்பு err;
}

நிலையான முழு drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        மாறிலி AVFrame *src, முழு flags)
{
    முழு err;

    எனில் (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    இல்லையெனில் எனில் (hwfc->sw_format != dst->format)
        திரும்பு AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    எனில் (err)
        திரும்பு err;

    err = av_frame_copy_props(dst, src);
    எனில் (err)
        திரும்பு err;

    திரும்பு 0;
}

மாறிலி HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = அளவு(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (மாறிலி எண்ணிக்கை AVPixelFormat[]) {
        AV_PIX_FMT_DRM_பகாஎண்,
        AV_PIX_FMT_NONE
    },
};
