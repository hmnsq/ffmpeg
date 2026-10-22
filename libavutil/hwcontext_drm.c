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

#समावेश "config.h"

#समावेश <fcntl.h>
#समावेश <sys/mman.h>
#समावेश <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#अगर HAVE_LINUX_DMA_BUF_H
#समावेश <linux/dma-buf.h>
#समावेश <sys/ioctl.h>
#पूर्ण_अगर

#समावेश <drm.h>
#समावेश <xf86drm.h>

#समावेश "avassert.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_drm.h"
#समावेश "hwcontext_internal.h"
#समावेश "imgutils.h"
#समावेश "mem.h"


अटल व्योम drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    बंद(hwctx->fd);
}

अटल पूर्णांक drm_device_create(AVHWDeviceContext *hwdev, स्थिर अक्षर *device,
                             AVDictionary *opts, पूर्णांक flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = खोलो(device, O_RDWR);
    अगर (hwctx->fd < 0)
        वापस AVERROR(त्रुटि_सं);

    version = drmGetVersion(hwctx->fd);
    अगर (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        बंद(hwctx->fd);
        वापस AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->मुक्त = &drm_device_free;

    वापस 0;
}

अटल पूर्णांक drm_get_बफर(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(hwfc->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    frame->तथ्य[0] = (uint8_t*)frame->buf[0]->तथ्य;

    frame->format = AV_PIX_FMT_DRM_अभाज्य;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    वापस 0;
}

प्रकार काष्ठा DRMMapping {
    // Address and length of each mmap()ed region.
    पूर्णांक nb_regions;
    पूर्णांक sync_flags;
    पूर्णांक object[AV_DRM_MAX_PLANES];
    व्योम *address[AV_DRM_MAX_PLANES];
    माप_प्रकार लंबाई[AV_DRM_MAX_PLANES];
} DRMMapping;

अटल व्योम drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    क्रम (पूर्णांक i = 0; i < map->nb_regions; i++) {
#अगर HAVE_LINUX_DMA_BUF_H
        काष्ठा dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#पूर्ण_अगर
        munmap(map->address[i], map->लंबाई[i]);
    }

    av_free(map);
}

अटल पूर्णांक drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    स्थिर AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->तथ्य[0];
#अगर HAVE_LINUX_DMA_BUF_H
    काष्ठा dma_buf_sync sync_start = { 0 };
#पूर्ण_अगर
    DRMMapping *map;
    पूर्णांक err, i, p, plane;
    पूर्णांक mmap_prot;
    व्योम *addr;

    map = av_mallocz(माप(*map));
    अगर (!map)
        वापस AVERROR(ENOMEM);

    mmap_prot = 0;
    अगर (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    अगर (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#अगर HAVE_LINUX_DMA_BUF_H
    अगर (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    अगर (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#पूर्ण_अगर

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    क्रम (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(शून्य, desc->objects[i].आकार, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        अगर (addr == MAP_FAILED) {
            err = AVERROR(त्रुटि_सं);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, त्रुटि_सं);
            जाओ fail;
        }

        map->address[i] = addr;
        map->लंबाई[i]  = desc->objects[i].आकार;
        map->object[i] = desc->objects[i].fd;

#अगर HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#पूर्ण_अगर
    }
    map->nb_regions = i;

    plane = 0;
    क्रम (i = 0; i < desc->nb_layers; i++) {
        स्थिर AVDRMLayerDescriptor *layer = &desc->layers[i];
        क्रम (p = 0; p < layer->nb_planes; p++) {
            dst->तथ्य[plane] =
                (uint8_t*)map->address[layer->planes[p].object_सूचकांक] +
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
    अगर (err < 0)
        जाओ fail;

    वापस 0;

fail:
    क्रम (i = 0; i < desc->nb_objects; i++) {
        अगर (map->address[i])
            munmap(map->address[i], map->लंबाई[i]);
    }
    av_free(map);
    वापस err;
}

अटल पूर्णांक drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    क्रमागत AVHWFrameTransferDirection dir,
                                    क्रमागत AVPixelFormat **formats)
{
    क्रमागत AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, माप(*pix_fmts));
    अगर (!pix_fmts)
        वापस AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    वापस 0;
}

अटल पूर्णांक drm_transfer_तथ्य_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, स्थिर AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    अगर (dst->width > hwfc->width || dst->height > hwfc->height)
        वापस AVERROR(EINVAL);

    map = av_frame_alloc();
    अगर (!map)
        वापस AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    अगर (err)
        जाओ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    अगर (err)
        जाओ fail;

    err = 0;
fail:
    av_frame_free(&map);
    वापस err;
}

अटल पूर्णांक drm_transfer_तथ्य_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, स्थिर AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    अगर (src->width > hwfc->width || src->height > hwfc->height)
        वापस AVERROR(EINVAL);

    map = av_frame_alloc();
    अगर (!map)
        वापस AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    अगर (err)
        जाओ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    अगर (err)
        जाओ fail;

    err = 0;
fail:
    av_frame_free(&map);
    वापस err;
}

अटल पूर्णांक drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        स्थिर AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err;

    अगर (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    अन्यथा अगर (hwfc->sw_format != dst->format)
        वापस AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    अगर (err)
        वापस err;

    err = av_frame_copy_props(dst, src);
    अगर (err)
        वापस err;

    वापस 0;
}

स्थिर HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_आकार      = माप(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_बफर      = &drm_get_बफर,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_तथ्य_to       = &drm_transfer_तथ्य_to,
    .transfer_तथ्य_from     = &drm_transfer_तथ्य_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (स्थिर क्रमागत AVPixelFormat[]) {
        AV_PIX_FMT_DRM_अभाज्य,
        AV_PIX_FMT_NONE
    },
};
