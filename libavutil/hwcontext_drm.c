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

#అన్తర్భావ "config.h"

#అన్తర్భావ <fcntl.h>
#అన్తర్భావ <sys/mman.h>
#అన్తర్భావ <unistd.h>

/* This was introduced in version 4.6. And may not exist all without an
 * optional package. So to prevent a hard dependency on needing the Linux
 * kernel headers to compile, make this optional. */
#ఒకవేళ HAVE_LINUX_DMA_BUF_H
#అన్తర్భావ <linux/dma-buf.h>
#అన్తర్భావ <sys/ioctl.h>
#అయితే_ముగింపు

#అన్తర్భావ <drm.h>
#అన్తర్భావ <xf86drm.h>

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_drm.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "mem.h"


స్థిర శూన్య drm_device_free(AVHWDeviceContext *hwdev)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;

    close(hwctx->fd);
}

స్థిర పూర్ణాంకం drm_device_create(AVHWDeviceContext *hwdev, స్థిరరాశి అక్షరం *device,
                             AVDictionary *opts, పూర్ణాంకం flags)
{
    AVDRMDeviceContext *hwctx = hwdev->hwctx;
    drm_సంస్కరణ_Ptr సంస్కరణ;

    hwctx->fd = open(device, O_RDWR);
    ఒకవేళ (hwctx->fd < 0)
        తిరిగి AVERROR(errno);

    సంస్కరణ = drm_Get_సంస్కరణ(hwctx->fd);
    ఒకవేళ (!సంస్కరణ) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get version information "
               "from %s: probably not a DRM device?\n", device);
        close(hwctx->fd);
        తిరిగి AVERROR(EINVAL);
    }

    av_log(hwdev, AV_LOG_VERBOSE, "Opened DRM device %s: driver %s "
           "version %d.%d.%d.\n", device, సంస్కరణ->name,
           సంస్కరణ->సంస్కరణ_major, సంస్కరణ->సంస్కరణ_minor,
           సంస్కరణ->సంస్కరణ_patchlevel);

    drm_Free_సంస్కరణ(సంస్కరణ);

    hwdev->విడుదల = &drm_device_free;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం drm_get_బఫరు(AVHWFramesContext *hwfc, AVFrame *చట్రం)
{
    చట్రం->buf[0] = av_బఫరు_pool_get(hwfc->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    చట్రం->దత్తాంశం[0] = (uint8_t*)చట్రం->buf[0]->దత్తాంశం;

    చట్రం->format = AV_PIX_FMT_DRM_ప్రధానసంఖ్య;
    చట్రం->వెడల్పు  = hwfc->వెడల్పు;
    చట్రం->ఎత్తు = hwfc->ఎత్తు;

    తిరిగి 0;
}

రకనిర్వచనం నిర్మాణం DRMMapping {
    // Address and length of each mmap()ed region.
    పూర్ణాంకం nb_regions;
    పూర్ణాంకం sync_flags;
    పూర్ణాంకం object[AV_DRM_MAX_PLANES];
    శూన్య *చిరునామా[AV_DRM_MAX_PLANES];
    size_t నిడివి[AV_DRM_MAX_PLANES];
} DRMMapping;

స్థిర శూన్య drm_unmap_చట్రం(AVHWFramesContext *hwfc,
                            HWMapDescriptor *hwmap)
{
    DRMMapping *map = hwmap->priv;

    కొరకు (పూర్ణాంకం i = 0; i < map->nb_regions; i++) {
#ఒకవేళ HAVE_LINUX_DMA_BUF_H
        నిర్మాణం dma_buf_sync sync = { .flags = DMA_BUF_SYNC_చివర | map->sync_flags };
        ioctl(map->object[i], DMA_BUF_IOCTL_SYNC, &sync);
#అయితే_ముగింపు
        munmap(map->చిరునామా[i], map->నిడివి[i]);
    }

    av_free(map);
}

స్థిర పూర్ణాంకం drm_map_చట్రం(AVHWFramesContext *hwfc,
                         AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    స్థిరరాశి AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->దత్తాంశం[0];
#ఒకవేళ HAVE_LINUX_DMA_BUF_H
    నిర్మాణం dma_buf_sync sync_ప్రారంభం = { 0 };
#అయితే_ముగింపు
    DRMMapping *map;
    పూర్ణాంకం err, i, p, plane;
    పూర్ణాంకం mmap_prot;
    శూన్య *addr;

    map = av_mallocz(పరిమాణం(*map));
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);

    mmap_prot = 0;
    ఒకవేళ (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    ఒకవేళ (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

#ఒకవేళ HAVE_LINUX_DMA_BUF_H
    ఒకవేళ (flags & AV_HWFRAME_MAP_READ)
        map->sync_flags |= DMA_BUF_SYNC_READ;
    ఒకవేళ (flags & AV_HWFRAME_MAP_WRITE)
        map->sync_flags |= DMA_BUF_SYNC_WRITE;
    sync_ప్రారంభం.flags = DMA_BUF_SYNC_ప్రారంభం | map->sync_flags;
#అయితే_ముగింపు

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    కొరకు (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(ఖాళీ, desc->objects[i].కొలత, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        ఒకవేళ (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            వెళ్ళు fail;
        }

        map->చిరునామా[i] = addr;
        map->నిడివి[i]  = desc->objects[i].కొలత;
        map->object[i] = desc->objects[i].fd;

#ఒకవేళ HAVE_LINUX_DMA_BUF_H
        /* We're not checking for errors here because the kernel may not
         * support the ioctl, in which case its okay to carry on */
        ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_SYNC, &sync_ప్రారంభం);
#అయితే_ముగింపు
    }
    map->nb_regions = i;

    plane = 0;
    కొరకు (i = 0; i < desc->nb_layers; i++) {
        స్థిరరాశి AVDRMLayerDescriptor *layer = &desc->layers[i];
        కొరకు (p = 0; p < layer->nb_planes; p++) {
            dst->దత్తాంశం[plane] =
                (uint8_t*)map->చిరునామా[layer->planes[p].object_సూచీ] +
                                       layer->planes[p].స్థానభ్రంశం;
            dst->linesize[plane] =     layer->planes[p].pitch;
            ++plane;
        }
    }
    av_assert0(plane <= AV_DRM_MAX_PLANES);

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    err = ff_hwframe_map_create(src->hw_చట్రాలు_ctx, dst, src,
                                &drm_unmap_చట్రం, map);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    తిరిగి 0;

fail:
    కొరకు (i = 0; i < desc->nb_objects; i++) {
        ఒకవేళ (map->చిరునామా[i])
            munmap(map->చిరునామా[i], map->నిడివి[i]);
    }
    av_free(map);
    తిరిగి err;
}

స్థిర పూర్ణాంకం drm_transfer_get_formats(AVHWFramesContext *ctx,
                                    గణన AVHWFrameTransferDirection dir,
                                    గణన AVPixelFormat **formats)
{
    గణన AVPixelFormat *pix_fmts;

    pix_fmts = av_malloc_array(2, పరిమాణం(*pix_fmts));
    ఒకవేళ (!pix_fmts)
        తిరిగి AVERROR(ENOMEM);

    pix_fmts[0] = ctx->sw_format;
    pix_fmts[1] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం drm_transfer_దత్తాంశం_from(AVHWFramesContext *hwfc,
                                  AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    AVFrame *map;
    పూర్ణాంకం err;

    ఒకవేళ (dst->వెడల్పు > hwfc->వెడల్పు || dst->ఎత్తు > hwfc->ఎత్తు)
        తిరిగి AVERROR(EINVAL);

    map = av_చట్రం_alloc();
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    map->format = dst->format;

    err = drm_map_చట్రం(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ఒకవేళ (err)
        వెళ్ళు fail;

    map->వెడల్పు  = dst->వెడల్పు;
    map->ఎత్తు = dst->ఎత్తు;

    err = av_చట్రం_copy(dst, map);
    ఒకవేళ (err)
        వెళ్ళు fail;

    err = 0;
fail:
    av_చట్రం_free(&map);
    తిరిగి err;
}

స్థిర పూర్ణాంకం drm_transfer_దత్తాంశం_గమ్యం(AVHWFramesContext *hwfc,
                                AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    AVFrame *map;
    పూర్ణాంకం err;

    ఒకవేళ (src->వెడల్పు > hwfc->వెడల్పు || src->ఎత్తు > hwfc->ఎత్తు)
        తిరిగి AVERROR(EINVAL);

    map = av_చట్రం_alloc();
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    map->format = src->format;

    err = drm_map_చట్రం(hwfc, map, dst, AV_HWFRAME_MAP_WRITE |
                                        AV_HWFRAME_MAP_OVERWRITE);
    ఒకవేళ (err)
        వెళ్ళు fail;

    map->వెడల్పు  = src->వెడల్పు;
    map->ఎత్తు = src->ఎత్తు;

    err = av_చట్రం_copy(map, src);
    ఒకవేళ (err)
        వెళ్ళు fail;

    err = 0;
fail:
    av_చట్రం_free(&map);
    తిరిగి err;
}

స్థిర పూర్ణాంకం drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    పూర్ణాంకం err;

    ఒకవేళ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    లేకపోతే ఒకవేళ (hwfc->sw_format != dst->format)
        తిరిగి AVERROR(ENOSYS);

    err = drm_map_చట్రం(hwfc, dst, src, flags);
    ఒకవేళ (err)
        తిరిగి err;

    err = av_చట్రం_copy_props(dst, src);
    ఒకవేళ (err)
        తిరిగి err;

    తిరిగి 0;
}

స్థిరరాశి HWContextType ff_hwcontext_type_drm = {
    .type                   = AV_HWDEVICE_TYPE_DRM,
    .name                   = "DRM",

    .device_hwctx_కొలత      = పరిమాణం(AVDRMDeviceContext),

    .device_create          = &drm_device_create,

    .చట్రాలు_get_బఫరు      = &drm_get_బఫరు,

    .transfer_get_formats   = &drm_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం       = &drm_transfer_దత్తాంశం_గమ్యం,
    .transfer_దత్తాంశం_from     = &drm_transfer_దత్తాంశం_from,
    .map_from               = &drm_map_from,

    .pix_fmts = (స్థిరరాశి గణన AVPixelFormat[]) {
        AV_PIX_FMT_DRM_ప్రధానసంఖ్య,
        AV_PIX_FMT_NONE
    },
};
