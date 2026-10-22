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

#അന്തര്ഭാവ "config.h"

#അന്തര്ഭാവ <fcntl.h>
#അന്തര്ഭാവ <sys/mman.h>
#അന്തര്ഭാവ <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#എങ്കിൽ HAVE_LINUX_DMA_BUF_H
#അന്തര്ഭാവ <linux/dma-buf.h>
#അന്തര്ഭാവ <sys/ioctl.h>
#endif

#അന്തര്ഭാവ <drm.h>
#അന്തര്ഭാവ <xf86drm.h>

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_drm.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "imgutils.h"
#അന്തര്ഭാവ "mem.h"


സ്ഥിതം ശൂന്യം drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ drm_device_create(AVHWDeviceContext *hwdev, സ്ഥിരം അക്ഷരം *device,
                             AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drmVersionPtr version;

    hwctx->fd = open(device, O_RDWR);
    എങ്കിൽ (hwctx->fd < 0)
        തിരികെ AVERROR(errno);

    version = drmGetVersion(hwctx->fd);
    എങ്കിൽ (!version) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        തിരികെ AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, version->name,
           version->version_major, version->version_minor,
           version->version_patchlevel);

    drmFreeVersion(version);

    hwdev->സ്വതന്ത്രം = &drm_device_free;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ drm_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    എങ്കിൽ (!frame->buf[0])
        തിരികെ AVERROR(ENOMEM);

    frame->data[0] = (uint8_t*)frame->buf[0]->data;

    frame->format = AV_PIX_FMT_DRM_അഭാജ്യം;
    frame->width  = hwfc->width;
    frame->height = hwfc->height;

    തിരികെ 0;
}

തരനിർവചനം ഘടന DRMMapping {
    // Address and length of each mmap()ed region.
    പൂർണ്ണസംഖ്യ nb_regions;
    പൂർണ്ണസംഖ്യ sync_flags;
    പൂർണ്ണസംഖ്യ object[AV_DRM_MAX_PLANES];
    ശൂന്യം *address[AV_DRM_MAX_PLANES];
    size_t length[AV_DRM_MAX_PLANES];
} DRMMapping;

സ്ഥിതം ശൂന്യം drm_unmap_frame(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < map->nb_regions; i++) {
#എങ്കിൽ HAVE_LINUX_DMA_BUF_H
        ഘടന dma_buf_sync sync = { .flags = DMA_BUF_SYNC_END | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#endif
        munmap(map->address[i], map->length[i]);
    }

    av_free(map);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
#എങ്കിൽ HAVE_LINUX_DMA_BUF_H
    ഘടന dma_buf_sync sync_start = { 0 };
#endif
    DRMMapping *map;
    പൂർണ്ണസംഖ്യ err, i, p, plane;
    പൂർണ്ണസംഖ്യ mmap_prot;
    ശൂന്യം *addr;

    map = av_mallocz(വലുപ്പം(*map));
    എങ്കിൽ (!map)
        തിരികെ AVERROR(ENOMEM);

    mmap_prot = 0;
    എങ്കിൽ (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    എങ്കിൽ (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#എങ്കിൽ HAVE_LINUX_DMA_BUF_H
    എങ്കിൽ (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    എങ്കിൽ (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_start.flags = DMA_BUF_SYNC_START | map->sync_flags;
#endif

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    വേണ്ടി (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(ശൂന്യ, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        എങ്കിൽ (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            പോകുക fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
        map->object[i] = desc->objects[i].fd;

#എങ്കിൽ HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_start);
#endif
    }
    map->nb_regions = i;

    plane = 0;
    വേണ്ടി (i = 0; i < desc->nb_layers; i++) {
        സ്ഥിരം AVDRMLayerDescriptor *layer = &desc->layers[i];
        വേണ്ടി (p = 0; p < layer->nb_planes; p++) {
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
    എങ്കിൽ (err < 0)
        പോകുക fail;

    തിരികെ 0;

fail:
    വേണ്ടി (i = 0; i < desc->nb_objects; i++) {
        എങ്കിൽ (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    എണ്ണൽ AVHWFrameTransferDirection dir,
                                    എണ്ണൽ AVPixelFormat **formats)
{
    എണ്ണൽ AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, വലുപ്പം(*pix_fmts));
    എങ്കിൽ (!pix_fmts)
        തിരികെ AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ drm_transfer_data_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    AVFrame *map;
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (dst->width > hwfc->width || dst->height > hwfc->height)
        തിരികെ AVERROR(EINVAL);

    map = av_frame_alloc();
    എങ്കിൽ (!map)
        തിരികെ AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    എങ്കിൽ (err)
        പോകുക fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    എങ്കിൽ (err)
        പോകുക fail;

    err = 0;
fail:
    av_frame_free(&map);
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ drm_transfer_data_to(AVHWFramesContext *hwfc,
                                AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    AVFrame *map;
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (src->width > hwfc->width || src->height > hwfc->height)
        തിരികെ AVERROR(EINVAL);

    map = av_frame_alloc();
    എങ്കിൽ (!map)
        തിരികെ AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    എങ്കിൽ (err)
        പോകുക fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    എങ്കിൽ (err)
        പോകുക fail;

    err = 0;
fail:
    av_frame_free(&map);
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    അല്ലെങ്കിൽ എങ്കിൽ (hwfc->sw_format != dst->format)
        തിരികെ AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    എങ്കിൽ (err)
        തിരികെ err;

    err = av_frame_copy_props(dst, src);
    എങ്കിൽ (err)
        തിരികെ err;

    തിരികെ 0;
}

സ്ഥിരം HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_size      = വലുപ്പം(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .frames_get_buffer      = &drm_get_buffer,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_data_to       = &drm_transfer_data_to,
    .transfer_data_from     = &drm_transfer_data_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]) {
        AV_PIX_FMT_DRM_അഭാജ്യം,
        AV_PIX_FMT_NONE
    },
};
