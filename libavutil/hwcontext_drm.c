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

#अन्तर्भाव "config.h"

#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <sys/mman.h>
#अन्तर्भाव <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#यदि HAVE_LINUX_DMA_BUF_H
#अन्तर्भाव <linux/dma-buf.h>
#अन्तर्भाव <sys/ioctl.h>
#endif

#अन्तर्भाव <drm.h>
#अन्तर्भाव <xf86drm.h>

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_drm.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "mem.h"


स्थिर शून्य drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

स्थिर पूर्णाङ्क drm_device_create(AVHWDeviceContext *hwdev, ध्रुव वर्ण *device,
                             AVDictionary *opts, पूर्णाङ्क flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    यदि (hwctx->fd < 0)
        प्रत्यागम AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    यदि (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        प्रत्यागम AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->मुक्त = &drm_device_free;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_अभाज्य;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    प्रत्यागम 0;
}

प्रकारनिर्देश संरचना DRMMapping {
    // Address and length of each mmap()ed region.
    पूर्णाङ्क nb_regions;
    पूर्णाङ्क sync_flags;
    पूर्णाङ्क object[AV_DRM_MAX_PLANES];
    शून्य *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

स्थिर शून्य drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    प्रति (पूर्णाङ्क i = 0; i < map->nb_regions; i++) {
#यदि HAVE_LINUX_DMA_BUF_H
        संरचना dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

स्थिर पूर्णाङ्क drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    ध्रुव AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#यदि HAVE_LINUX_DMA_BUF_H
    संरचना dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    पूर्णाङ्क err, i, p, plane;
    पूर्णाङ्क mmap_prot;
    शून्य *addr;

    map = av_mallocz(परिमाण(*map));
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);

    mmap_prot = 0;
    यदि (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    यदि (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#यदि HAVE_LINUX_DMA_BUF_H
    यदि (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    यदि (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    प्रति (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(रिक्त, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        यदि (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            गच्छ fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#यदि HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    प्रति (i = 0; i < desc->nb_layers; i++) {
        ध्रुव AVDRMLayerDescriptor *layer = &desc->layers[i];
        प्रति (p = 0; p < layer->nb_planes; p++) {
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
    यदि (err < 0)
        गच्छ fail;

    प्रत्यागम 0;

fail:
    प्रति (i = 0; i < desc->nb_objects; i++) {
        यदि (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    गणना AVHWFrameTransferDirection dir,
                                    गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, परिमाण(*pix_fmts));
    यदि (!pix_fmts)
        प्रत्यागम AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ध्रुव AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    यदि (dst->width > hwfc->width || dst->height > hwfc->height)
        प्रत्यागम AVERROR(EINVAL);

    map = av_frame_alloc();
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    यदि (err)
        गच्छ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    यदि (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, ध्रुव AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    यदि (src->width > hwfc->width || src->height > hwfc->height)
        प्रत्यागम AVERROR(EINVAL);

    map = av_frame_alloc();
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    यदि (err)
        गच्छ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    यदि (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err;

    यदि (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    अन्यथा यदि (hwfc->sw_format != dst->format)
        प्रत्यागम AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    यदि (err)
        प्रत्यागम err;

    err = av_frame_copy_props(dst, src);
    यदि (err)
        प्रत्यागम err;

    प्रत्यागम 0;
}

ध्रुव HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = परिमाण(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]) {
        AV_PIX_FMT_DRM_अभाज्य,
        AV_PIX_FMT_NONE
    },
};
