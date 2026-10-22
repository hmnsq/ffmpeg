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
#اگر_ختم

#شامل <drm.h>
#شامل <xf86drm.h>

#شامل "avassert.h"
#شامل "hwcontext.h"
#شامل "hwcontext_drm.h"
#شامل "hwcontext_internal.h"
#شامل "imgutils.h"
#شامل "mem.h"


ساکن خالی drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

ساکن صحیح drm_device_create(AVHWDeviceContext *hwdev, ثابت حرف *device,
                             AVDictionary *opts, صحیح flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drm_نسخہ_Ptr نسخہ;

    hwctx->fd = open(device, O_RDWR);
    اگر (hwctx->fd < 0)
        واپس AVERROR(errno);

    نسخہ = drm_Get_نسخہ(hwctx->fd);
    اگر (!نسخہ) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        واپس AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, نسخہ->name,
           نسخہ->نسخہ_major, نسخہ->نسخہ_minor,
           نسخہ->نسخہ_patchlevel);

    drm_Free_نسخہ(نسخہ);

    hwdev->آزاد = &drm_device_free;

    واپس 0;
}

ساکن صحیح drm_get_بفر(AVHWFramesContext *hwfc, AVFrame *چوکھٹا)
{
    چوکھٹا->buf[0] = av_بفر_pool_get(hwfc->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    چوکھٹا->ڈیٹا[0] = (uint8_t*)چوکھٹا->buf[0]->ڈیٹا;

    چوکھٹا->format = AV_PIX_FMT_DRM_مفرد;
    چوکھٹا->چوڑائی  = hwfc->چوڑائی;
    چوکھٹا->اونچائی = hwfc->اونچائی;

    واپس 0;
}

قسمتعریف ساخت DRMMapping {
    // Address and length of each mmap()ed region.
    صحیح nb_regions;
    صحیح sync_flags;
    صحیح object[AV_DRM_MAX_PLANES];
    خالی *پتہ[AV_DRM_MAX_PLANES];
    size_t لمبائی[AV_DRM_MAX_PLANES];
} DRMMapping;

ساکن خالی drm_unmap_چوکھٹا(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    برائے (صحیح i = 0; i < map->nb_regions; i++) {
#اگر HAVE_LINUX_DMA_BUF_H
        ساخت dma_buf_sync sync = { .flags = DMA_BUF_SYNC_انتہا | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#اگر_ختم
        munmap(map->پتہ[i], map->لمبائی[i]);
    }

    av_free(map);
}

ساکن صحیح drm_map_چوکھٹا(AVHWFramesContext *hwfc,
                         AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    ثابت AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->ڈیٹا[0];
#اگر HAVE_LINUX_DMA_BUF_H
    ساخت dma_buf_sync sync_آغاز = { 0 };
#اگر_ختم
    DRMMapping *map;
    صحیح err, i, p, plane;
    صحیح mmap_prot;
    خالی *addr;

    map = av_mallocz(حجم(*map));
    اگر (!map)
        واپس AVERROR(ENOMEM);

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
    sync_آغاز.flags = DMA_BUF_SYNC_آغاز | map->sync_flags;
#اگر_ختم

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    برائے (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(تہی, desc->objects[i].سائز, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        اگر (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            جاؤ fail;
        }

        map->پتہ[i] = addr;
        map->لمبائی[i]  = desc->objects[i].سائز;
        map->object[i] = desc->objects[i].fd;

#اگر HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_آغاز);
#اگر_ختم
    }
    map->nb_regions = i;

    plane = 0;
    برائے (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];
        برائے (p = 0; p < layer->nb_planes; p++) {
            dst->ڈیٹا[plane] =
                (uint8_t*)map->پتہ[layer->planes[p].object_اشاریہ] +
                                       layer->planes[p].انحراف;
            dst->linesize[plane] =     layer->planes[p].pitch;
            ++plane;
        }
    }
    av_assert0(plane <= AV_DRM_MAX_PLANES);

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx, dst, src,
                                &drm_unmap_چوکھٹا, map);
    اگر (err < 0)
        جاؤ fail;

    واپس 0;

fail:
    برائے (i = 0; i < desc->nb_objects; i++) {
        اگر (map->پتہ[i])
            munmap(map->پتہ[i], map->لمبائی[i]);
    }
    av_free(map);
    واپس err;
}

ساکن صحیح drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    شمار AVHWFrameTransferDirection dir,
                                    شمار AVPixelFormat **formats)
{
    شمار AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, حجم(*pix_fmts));
    اگر (!pix_fmts)
        واپس AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    واپس 0;
}

ساکن صحیح drm_transfer_ڈیٹا_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (dst->چوڑائی > hwfc->چوڑائی || dst->اونچائی > hwfc->اونچائی)
        واپس AVERROR(EINVAL);

    map = av_چوکھٹا_alloc();
    اگر (!map)
        واپس AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_چوکھٹا(hwfc, map, src, AV_HWFRAME_MAP_READ);
    اگر (err)
        جاؤ fail;

    map->چوڑائی  = dst->چوڑائی;
    map->اونچائی = dst->اونچائی;

    err = av_چوکھٹا_copy(dst, map);
    اگر (err)
        جاؤ fail;

    err = 0;
fail:
    av_چوکھٹا_free(&map);
    واپس err;
}

ساکن صحیح drm_transfer_ڈیٹا_مقصد(AVHWFramesContext *hwfc,
                                AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (src->چوڑائی > hwfc->چوڑائی || src->اونچائی > hwfc->اونچائی)
        واپس AVERROR(EINVAL);

    map = av_چوکھٹا_alloc();
    اگر (!map)
        واپس AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_چوکھٹا(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    اگر (err)
        جاؤ fail;

    map->چوڑائی  = src->چوڑائی;
    map->اونچائی = src->اونچائی;

    err = av_چوکھٹا_copy(map, src);
    اگر (err)
        جاؤ fail;

    err = 0;
fail:
    av_چوکھٹا_free(&map);
    واپس err;
}

ساکن صحیح drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        ثابت AVFrame *src, صحیح flags)
{
    صحیح err;

    اگر (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ورنہ اگر (hwfc->sw_format != dst->format)
        واپس AVERROR(ENOSYS);

    err = drm_map_چوکھٹا(hwfc, dst, src, flags);
    اگر (err)
        واپس err;

    err = av_چوکھٹا_copy_props(dst, src);
    اگر (err)
        واپس err;

    واپس 0;
}

ثابت HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_سائز      = حجم(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .چوکھٹے_get_بفر      = &drm_get_بفر,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_ڈیٹا_مقصد       = &drm_transfer_ڈیٹا_مقصد,
    .transfer_ڈیٹا_from     = &drm_transfer_ڈیٹا_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (ثابت شمار AVPixelFormat[]) {
        AV_PIX_FMT_DRM_مفرد,
        AV_PIX_FMT_NONE
    },
};
