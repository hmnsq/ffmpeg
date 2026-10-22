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

#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ <fcntl.h>
#અન્તર્ભાવ <sys/mman.h>
#અન્તર્ભાવ <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#જો HAVE_LINUX_DMA_BUF_H
#અન્તર્ભાવ <linux/dma-buf.h>
#અન્તર્ભાવ <sys/ioctl.h>
#endif

#અન્તર્ભાવ <drm.h>
#અન્તર્ભાવ <xf86drm.h>

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_drm.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "imgutils.h"
#અન્તર્ભાવ "mem.h"


સ્થિર શૂન્ય drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

સ્થિર પૂર્ણાંક drm_device_create(AVHWDeviceContext *hwdev, અચલ અક્ષર *device,
                             AVDictionary *opts, પૂર્ણાંક flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    જો (hwctx->fd < 0)
        પાછા AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    જો (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        પાછા AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->મુક્ત = &drm_device_free;

    પાછા 0;
}

સ્થિર પૂર્ણાંક drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    જો (!frame->buf[0])
        પાછા AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_અવિભાજ્ય;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    પાછા 0;
}

પ્રકારવ્યાખ્યા સંરચના DRMMapping {
    // Address and length of each mmap()ed region.
    પૂર્ણાંક nb_regions;
    પૂર્ણાંક sync_flags;
    પૂર્ણાંક object[AV_DRM_MAX_PLANES];
    શૂન્ય *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

સ્થિર શૂન્ય drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    માટે (પૂર્ણાંક i = 0; i < map->nb_regions; i++) {
#જો HAVE_LINUX_DMA_BUF_H
        સંરચના dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

સ્થિર પૂર્ણાંક drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, અચલ AVFrame *src, પૂર્ણાંક flags)
{
    અચલ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#જો HAVE_LINUX_DMA_BUF_H
    સંરચના dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    પૂર્ણાંક err, i, p, plane;
    પૂર્ણાંક mmap_prot;
    શૂન્ય *addr;

    map = av_mallocz(કદ(*map));
    જો (!map)
        પાછા AVERROR(ENOMEM);

    mmap_prot = 0;
    જો (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    જો (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#જો HAVE_LINUX_DMA_BUF_H
    જો (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    જો (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    માટે (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(ખાલી, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        જો (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            જાઓ fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#જો HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    માટે (i = 0; i < desc->nb_layers; i++) {
        અચલ AVDRMLayerDescriptor *layer = &desc->layers[i];
        માટે (p = 0; p < layer->nb_planes; p++) {
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
    જો (err < 0)
        જાઓ fail;

    પાછા 0;

fail:
    માટે (i = 0; i < desc->nb_objects; i++) {
        જો (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    પાછા err;
}

સ્થિર પૂર્ણાંક drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    ગણના AVHWFrameTransferDirection dir,
                                    ગણના AVPixelFormat **formats)
{
    ગણના AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, કદ(*pix_fmts));
    જો (!pix_fmts)
        પાછા AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    પાછા 0;
}

સ્થિર પૂર્ણાંક drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, અચલ AVFrame *src)
{
    AVFrame *map;
    પૂર્ણાંક err;

    જો (dst->width > hwfc->width || dst->height > hwfc->height)
        પાછા AVERROR(EINVAL);

    map = av_frame_alloc();
    જો (!map)
        પાછા AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    જો (err)
        જાઓ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    જો (err)
        જાઓ fail;

    err = 0;
fail:
    av_frame_free(&map);
    પાછા err;
}

સ્થિર પૂર્ણાંક drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, અચલ AVFrame *src)
{
    AVFrame *map;
    પૂર્ણાંક err;

    જો (src->width > hwfc->width || src->height > hwfc->height)
        પાછા AVERROR(EINVAL);

    map = av_frame_alloc();
    જો (!map)
        પાછા AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    જો (err)
        જાઓ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    જો (err)
        જાઓ fail;

    err = 0;
fail:
    av_frame_free(&map);
    પાછા err;
}

સ્થિર પૂર્ણાંક drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        અચલ AVFrame *src, પૂર્ણાંક flags)
{
    પૂર્ણાંક err;

    જો (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    નહીંતર જો (hwfc->sw_format != dst->format)
        પાછા AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    જો (err)
        પાછા err;

    err = av_frame_copy_props(dst, src);
    જો (err)
        પાછા err;

    પાછા 0;
}

અચલ HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = કદ(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (અચલ ગણના AVPixelFormat[]) {
        AV_PIX_FMT_DRM_અવિભાજ્ય,
        AV_PIX_FMT_NONE
    },
};
