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

#నిర్వచితం_కాకపోతే AVUTIL_HWCONTEXT_అంతర్గత_H
#నిర్వచించు AVUTIL_HWCONTEXT_అంతర్గత_H

#అన్తర్భావ <stddef.h>

#అన్తర్భావ "buffer.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "thread.h"
#అన్తర్భావ "frame.h"
#అన్తర్భావ "pixfmt.h"

రకనిర్వచనం నిర్మాణం HWContextType {
    గణన AVHWDeviceType type;
    స్థిరరాశి అక్షరం         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    స్థిరరాశి గణన AVPixelFormat *pix_fmts;

    /**
     * size of the public hardware-specific context,
     * i.e. AVHWDeviceContext.hwctx
     */
    size_t             device_hwctx_కొలత;

    /**
     * Size of the hardware-specific device configuration.
     * (Used to query hwframe constraints.)
     */
    size_t             device_hwconfig_కొలత;

    /**
     * size of the public frame pool hardware-specific context,
     * i.e. AVHWFramesContext.hwctx
     */
    size_t             చట్రాలు_hwctx_కొలత;

    పూర్ణాంకం              (*device_create)(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                                      AVDictionary *opts, పూర్ణాంకం flags);
    పూర్ణాంకం              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, పూర్ణాంకం flags);

    పూర్ణాంకం              (*device_init)(AVHWDeviceContext *ctx);
    శూన్య             (*device_uninit)(AVHWDeviceContext *ctx);

    పూర్ణాంకం              (*చట్రాలు_get_constraints)(AVHWDeviceContext *ctx,
                                               స్థిరరాశి శూన్య *hwconfig,
                                               AVHWFramesConstraints *constraints);

    పూర్ణాంకం              (*చట్రాలు_init)(AVHWFramesContext *ctx);
    శూన్య             (*చట్రాలు_uninit)(AVHWFramesContext *ctx);

    పూర్ణాంకం              (*చట్రాలు_get_బఫరు)(AVHWFramesContext *ctx, AVFrame *చట్రం);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_బఫరు_alloc)(శూన్య *device_ref, size_t కొలత);
    పూర్ణాంకం              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             గణన AVHWFrameTransferDirection dir,
                                             గణన AVPixelFormat **formats);
    పూర్ణాంకం              (*transfer_దత్తాంశం_గమ్యం)(AVHWFramesContext *ctx, AVFrame *dst,
                                         స్థిరరాశి AVFrame *src);
    పూర్ణాంకం              (*transfer_దత్తాంశం_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           స్థిరరాశి AVFrame *src);

    పూర్ణాంకం              (*map_గమ్యం)(AVHWFramesContext *ctx, AVFrame *dst,
                               స్థిరరాశి AVFrame *src, పూర్ణాంకం flags);
    పూర్ణాంకం              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 స్థిరరాశి AVFrame *src, పూర్ణాంకం flags);

    పూర్ణాంకం              (*చట్రాలు_derive_గమ్యం)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, పూర్ణాంకం flags);
    పూర్ణాంకం              (*చట్రాలు_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, పూర్ణాంకం flags);
} HWContextType;

రకనిర్వచనం నిర్మాణం FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    స్థిరరాశి HWContextType *hw_type;

    AVBufferPool *pool_అంతర్గత;

    /**
     * Buffers of transfer_pool_size bytes for av_hwframe_get_transfer_buffer(),
     * both guarded by transfer_pool_lock.
     */
    AVBufferPool *transfer_pool;
    size_t        transfer_pool_కొలత;
    AVMutex       transfer_pool_తాళం;

    /**
     * For a derived context, a reference to the original frames
     * context it was derived from.
     */
    AVBufferRef *ఆధారం_చట్రాలు;
    /**
     * Flags to apply to the mapping from the source to the derived
     * frame context when trying to allocate in the derived context.
     */
    పూర్ణాంకం ఆధారం_కేటాయింపు_map_flags;
} FFHWFramesContext;

స్థిర అంతఃవరుస FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    తిరిగి (FFHWFramesContext*)ctx;
}

రకనిర్వచనం నిర్మాణం HWMapDescriptor {
    /**
     * A reference to the original source of the mapping.
     */
    AVFrame *ఆధారం;
    /**
     * A reference to the hardware frames context in which this
     * mapping was made.  May be the same as source->hw_frames_ctx,
     * but need not be.
     */
    AVBufferRef *hw_చట్రాలు_ctx;
    /**
     * Unmap function.
     */
    శూన్య (*unmap)(AVHWFramesContext *ctx,
                  నిర్మాణం HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    శూన్య          *priv;
} HWMapDescriptor;

పూర్ణాంకం ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, స్థిరరాశి AVFrame *src,
                          శూన్య (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          శూన్య *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
పూర్ణాంకం ff_hwframe_map_replace(AVFrame *dst, స్థిరరాశి AVFrame *src);

బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_cuda;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_d3d11va;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_d3d12va;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_drm;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_dxva2;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_opencl;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_qsv;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_vaapi;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_vdpau;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_videotoolbox;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_mediacodec;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_vulkan;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_amf;
బాహ్య స్థిరరాశి HWContextType ff_hwcontext_type_oh;

#అయితే_ముగింపు /* AVUTIL_HWCONTEXT_INTERNAL_H */
