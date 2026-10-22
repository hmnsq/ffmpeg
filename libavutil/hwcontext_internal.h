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

#অন্তর্ভাব <stddef.h>

#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "thread.h"
#অন্তর্ভাব "frame.h"
#অন্তর্ভাব "pixfmt.h"

প্রকারলেখ কাঠামো HWContextType {
    গণনা AVHWDeviceType type;
    ধ্রুবক অক্ষর         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ধ্রুবক গণনা AVPixelFormat *pix_fmts;

    /**
     * size of the public hardware-specific context,
     * i.e. AVHWDeviceContext.hwctx
     */
    size_t             device_hwctx_আকার;

    /**
     * Size of the hardware-specific device configuration.
     * (Used to query hwframe constraints.)
     */
    size_t             device_hwconfig_আকার;

    /**
     * size of the public frame pool hardware-specific context,
     * i.e. AVHWFramesContext.hwctx
     */
    size_t             frames_hwctx_আকার;

    পূর্ণসংখ্যা              (*device_create)(AVHWDeviceContext *ctx, ধ্রুবক অক্ষর *device,
                                      AVDictionary *opts, পূর্ণসংখ্যা flags);
    পূর্ণসংখ্যা              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, পূর্ণসংখ্যা flags);

    পূর্ণসংখ্যা              (*device_init)(AVHWDeviceContext *ctx);
    শূন্য             (*device_uninit)(AVHWDeviceContext *ctx);

    পূর্ণসংখ্যা              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               ধ্রুবক শূন্য *hwconfig,
                                               AVHWFramesConstraints *constraints);

    পূর্ণসংখ্যা              (*frames_init)(AVHWFramesContext *ctx);
    শূন্য             (*frames_uninit)(AVHWFramesContext *ctx);

    পূর্ণসংখ্যা              (*frames_get_বাফার)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_বাফার_alloc)(শূন্য *device_ref, size_t আকার_2);
    পূর্ণসংখ্যা              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             গণনা AVHWFrameTransferDirection dir,
                                             গণনা AVPixelFormat **formats);
    পূর্ণসংখ্যা              (*transfer_তথ্য_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ধ্রুবক AVFrame *src);
    পূর্ণসংখ্যা              (*transfer_তথ্য_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ধ্রুবক AVFrame *src);

    পূর্ণসংখ্যা              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags);
    পূর্ণসংখ্যা              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags);

    পূর্ণসংখ্যা              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, পূর্ণসংখ্যা flags);
    পূর্ণসংখ্যা              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, পূর্ণসংখ্যা flags);
} HWContextType;

প্রকারলেখ কাঠামো FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    ধ্রুবক HWContextType *hw_type;

    AVBufferPool *pool_internal;

    /**
     * Buffers of transfer_pool_size bytes for av_hwframe_get_transfer_buffer(),
     * both guarded by transfer_pool_lock.
     */
    AVBufferPool *transfer_pool;
    size_t        transfer_pool_আকার;
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
    পূর্ণসংখ্যা source_allocation_map_flags;
} FFHWFramesContext;

স্থির অন্তঃরেখ FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    ফেরত (FFHWFramesContext*)ctx;
}

প্রকারলেখ কাঠামো HWMapDescriptor {
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
                  কাঠামো HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    শূন্য          *priv;
} HWMapDescriptor;

পূর্ণসংখ্যা ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ধ্রুবক AVFrame *src,
                          শূন্য (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          শূন্য *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
পূর্ণসংখ্যা ff_hwframe_map_replace(AVFrame *dst, ধ্রুবক AVFrame *src);

বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_cuda;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_d3d11va;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_d3d12va;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_drm;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_dxva2;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_opencl;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_qsv;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_vaapi;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_vdpau;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_videotoolbox;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_mediacodec;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_vulkan;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_amf;
বাহ্যিক ধ্রুবক HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
