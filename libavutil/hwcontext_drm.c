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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ <fcntl.h>
#ଅନ୍ତର୍ଭାଵ <sys/mman.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#ଯଦି HAVE_LINUX_DMA_BUF_H
#ଅନ୍ତର୍ଭାଵ <linux/dma-buf.h>
#ଅନ୍ତର୍ଭାଵ <sys/ioctl.h>
#endif

#ଅନ୍ତର୍ଭାଵ <drm.h>
#ଅନ୍ତର୍ଭାଵ <xf86drm.h>

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_drm.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "imgutils.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"


ସ୍ଥିର ଶୂନ୍ୟ drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_device_create(AVHWDeviceContext *hwdev, ଅଚଳ ଅକ୍ଷର *device,
                             AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    ଯଦି (hwctx->fd < 0)
        ଫେରନ୍ତୁ AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    ଯଦି (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->ମୁକ୍ତ = &drm_device_free;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_ମୌଳିକ;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    ଫେରନ୍ତୁ 0;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା DRMMapping {
    // Address and length of each mmap()ed region.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_regions;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sync_flags;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା object[AV_DRM_MAX_PLANES];
    ଶୂନ୍ୟ *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

ସ୍ଥିର ଶୂନ୍ୟ drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < map->nb_regions; i++) {
#ଯଦି HAVE_LINUX_DMA_BUF_H
        ସଂରଚନା dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#ଯଦି HAVE_LINUX_DMA_BUF_H
    ସଂରଚନା dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, p, plane;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା mmap_prot;
    ଶୂନ୍ୟ *addr;

    map = av_mallocz(ଆକାର(*map));
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    mmap_prot = 0;
    ଯଦି (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    ଯଦି (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#ଯଦି HAVE_LINUX_DMA_BUF_H
    ଯଦି (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    ଯଦି (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    ପାଇଁ (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(ଖାଲି, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        ଯଦି (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            ଯାଅ fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#ଯଦି HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    ପାଇଁ (i = 0; i < desc->nb_layers; i++) {
        ଅଚଳ AVDRMLayerDescriptor *layer = &desc->layers[i];
        ପାଇଁ (p = 0; p < layer->nb_planes; p++) {
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
    ଯଦି (err < 0)
        ଯାଅ fail;

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (i = 0; i < desc->nb_objects; i++) {
        ଯଦି (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    ଗଣନା AVHWFrameTransferDirection dir,
                                    ଗଣନା AVPixelFormat **formats)
{
    ଗଣନା AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, ଆକାର(*pix_fmts));
    ଯଦି (!pix_fmts)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ଅଚଳ AVFrame *src)
{
    AVFrame *map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (dst->width > hwfc->width || dst->height > hwfc->height)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    map = av_frame_alloc();
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ଯଦି (err)
        ଯାଅ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    ଯଦି (err)
        ଯାଅ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, ଅଚଳ AVFrame *src)
{
    AVFrame *map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (src->width > hwfc->width || src->height > hwfc->height)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    map = av_frame_alloc();
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    ଯଦି (err)
        ଯାଅ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    ଯଦି (err)
        ଯାଅ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ଅନ୍ୟଥା ଯଦି (hwfc->sw_format != dst->format)
        ଫେରନ୍ତୁ AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    err = av_frame_copy_props(dst, src);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    ଫେରନ୍ତୁ 0;
}

ଅଚଳ HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = ଆକାର(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ଅଚଳ ଗଣନା AVPixelFormat[]) {
        AV_PIX_FMT_DRM_ମୌଳିକ,
        AV_PIX_FMT_NONE
    },
};
