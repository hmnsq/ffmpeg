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

#அந்தர்பாவ <stddef.h>

#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "thread.h"
#அந்தர்பாவ "frame.h"
#அந்தர்பாவ "pixfmt.h"

வகைவரை கட்டமைப்பு HWContextType {
    எண்ணிக்கை AVHWDeviceType type;
    மாறிலி எழுத்து         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    மாறிலி எண்ணிக்கை AVPixelFormat *pix_fmts;

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

    முழு              (*device_create)(AVHWDeviceContext *ctx, மாறிலி எழுத்து *device,
                                      AVDictionary *opts, முழு flags);
    முழு              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, முழு flags);

    முழு              (*device_init)(AVHWDeviceContext *ctx);
    வெறுமை             (*device_uninit)(AVHWDeviceContext *ctx);

    முழு              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               மாறிலி வெறுமை *hwconfig,
                                               AVHWFramesConstraints *constraints);

    முழு              (*frames_init)(AVHWFramesContext *ctx);
    வெறுமை             (*frames_uninit)(AVHWFramesContext *ctx);

    முழு              (*frames_get_buffer)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_buffer_alloc)(வெறுமை *device_ref, size_t size);
    முழு              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             எண்ணிக்கை AVHWFrameTransferDirection dir,
                                             எண்ணிக்கை AVPixelFormat **formats);
    முழு              (*transfer_data_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         மாறிலி AVFrame *src);
    முழு              (*transfer_data_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           மாறிலி AVFrame *src);

    முழு              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               மாறிலி AVFrame *src, முழு flags);
    முழு              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 மாறிலி AVFrame *src, முழு flags);

    முழு              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, முழு flags);
    முழு              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, முழு flags);
} HWContextType;

வகைவரை கட்டமைப்பு FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    மாறிலி HWContextType *hw_type;

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
    முழு source_allocation_map_flags;
} FFHWFramesContext;

நிலையான உள்வரி FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    திரும்பு (FFHWFramesContext*)ctx;
}

வகைவரை கட்டமைப்பு HWMapDescriptor {
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
    வெறுமை (*unmap)(AVHWFramesContext *ctx,
                  கட்டமைப்பு HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    வெறுமை          *priv;
} HWMapDescriptor;

முழு ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, மாறிலி AVFrame *src,
                          வெறுமை (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          வெறுமை *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
முழு ff_hwframe_map_replace(AVFrame *dst, மாறிலி AVFrame *src);

வெளி மாறிலி HWContextType ff_hwcontext_type_cuda;
வெளி மாறிலி HWContextType ff_hwcontext_type_d3d11va;
வெளி மாறிலி HWContextType ff_hwcontext_type_d3d12va;
வெளி மாறிலி HWContextType ff_hwcontext_type_drm;
வெளி மாறிலி HWContextType ff_hwcontext_type_dxva2;
வெளி மாறிலி HWContextType ff_hwcontext_type_opencl;
வெளி மாறிலி HWContextType ff_hwcontext_type_qsv;
வெளி மாறிலி HWContextType ff_hwcontext_type_vaapi;
வெளி மாறிலி HWContextType ff_hwcontext_type_vdpau;
வெளி மாறிலி HWContextType ff_hwcontext_type_videotoolbox;
வெளி மாறிலி HWContextType ff_hwcontext_type_mediacodec;
வெளி மாறிலி HWContextType ff_hwcontext_type_vulkan;
வெளி மாறிலி HWContextType ff_hwcontext_type_amf;
வெளி மாறிலி HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
