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

#ifndef AVUTIL_HWCONTEXT_INTERNAL_H
#define AVUTIL_HWCONTEXT_INTERNAL_H

#অন্তর্ভাৱ <stddef.h>

#অন্তর্ভাৱ "buffer.h"
#অন্তর্ভাৱ "hwcontext.h"
#অন্তর্ভাৱ "thread.h"
#অন্তর্ভাৱ "frame.h"
#অন্তর্ভাৱ "pixfmt.h"

প্রকারনির্দেশ সংরচনা HWContextType {
    গণনা AVHWDeviceType type;
    ধ্রুৱ ৱর্ণ         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ধ্রুৱ গণনা AVPixelFormat *pix_fmts;

    /**
     * size of the public hardware-specific context,
     * i.e. AVHWDeviceContext.hwctx
     */
    size_t             device_hwctx_size;

    /**
     * Size of the hardware-specific device configuration.
     * (Used to query hwframe constraints.)
     */
    size_t             device_hwconfig_size;

    /**
     * size of the public frame pool hardware-specific context,
     * i.e. AVHWFramesContext.hwctx
     */
    size_t             frames_hwctx_size;

    পূর্ণাঙ্ক              (*device_create)(AVHWDeviceContext *ctx, ধ্রুৱ ৱর্ণ *device,
                                      AVDictionary *opts, পূর্ণাঙ্ক flags);
    পূর্ণাঙ্ক              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, পূর্ণাঙ্ক flags);

    পূর্ণাঙ্ক              (*device_init)(AVHWDeviceContext *ctx);
    শূন্য             (*device_uninit)(AVHWDeviceContext *ctx);

    পূর্ণাঙ্ক              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               ধ্রুৱ শূন্য *hwconfig,
                                               AVHWFramesConstraints *constraints);

    পূর্ণাঙ্ক              (*frames_init)(AVHWFramesContext *ctx);
    শূন্য             (*frames_uninit)(AVHWFramesContext *ctx);

    পূর্ণাঙ্ক              (*frames_get_buffer)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_buffer_alloc)(শূন্য *device_ref, size_t size);
    পূর্ণাঙ্ক              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             গণনা AVHWFrameTransferDirection dir,
                                             গণনা AVPixelFormat **formats);
    পূর্ণাঙ্ক              (*transfer_data_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ধ্রুৱ AVFrame *src);
    পূর্ণাঙ্ক              (*transfer_data_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ধ্রুৱ AVFrame *src);

    পূর্ণাঙ্ক              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               ধ্রুৱ AVFrame *src, পূর্ণাঙ্ক flags);
    পূর্ণাঙ্ক              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ধ্রুৱ AVFrame *src, পূর্ণাঙ্ক flags);

    পূর্ণাঙ্ক              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, পূর্ণাঙ্ক flags);
    পূর্ণাঙ্ক              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, পূর্ণাঙ্ক flags);
} HWContextType;

প্রকারনির্দেশ সংরচনা FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    ধ্রুৱ HWContextType *hw_type;

    AVBufferPool *pool_internal;

    /**
     * Buffers of transfer_pool_size bytes for av_hwframe_get_transfer_buffer(),
     * both guarded by transfer_pool_lock.
     */
    AVBufferPool *transfer_pool;
    size_t        transfer_pool_size;
    AVMutex       transfer_pool_lock;

    /**
     * For a derived context, a reference to the original frames
     * context it was derived from.
     */
    AVBufferRef *source_frames;
    /**
     * Flags to apply to the mapping from the source to the derived
     * frame context when trying to allocate in the derived context.
     */
    পূর্ণাঙ্ক source_allocation_map_flags;
} FFHWFramesContext;

স্থির অন্তঃস্থ FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    ঘূৰাই (FFHWFramesContext*)ctx;
}

প্রকারনির্দেশ সংরচনা HWMapDescriptor {
    /**
     * A reference to the original source of the mapping.
     */
    AVFrame *source;
    /**
     * A reference to the hardware frames context in which this
     * mapping was made.  May be the same as source->hw_frames_ctx,
     * but need not be.
     */
    AVBufferRef *hw_frames_ctx;
    /**
     * Unmap function.
     */
    শূন্য (*unmap)(AVHWFramesContext *ctx,
                  সংরচনা HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    শূন্য          *priv;
} HWMapDescriptor;

পূর্ণাঙ্ক ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ধ্রুৱ AVFrame *src,
                          শূন্য (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          শূন্য *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
পূর্ণাঙ্ক ff_hwframe_map_replace(AVFrame *dst, ধ্রুৱ AVFrame *src);

বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_cuda;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_d3d11va;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_d3d12va;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_drm;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_dxva2;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_opencl;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_qsv;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_vaapi;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_vdpau;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_videotoolbox;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_mediacodec;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_vulkan;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_amf;
বাহ্য ধ্রুৱ HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
