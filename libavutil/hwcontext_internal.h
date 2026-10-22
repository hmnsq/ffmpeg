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

#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "thread.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ HWContextType {
    ಗಣನಾ AVHWDeviceType type;
    ಧ್ರುವ ವರ್ಣ         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ಧ್ರುವ ಗಣನಾ AVPixelFormat *pix_fmts;

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

    ಪೂರ್ಣಾಙ್ಕ              (*device_create)(AVHWDeviceContext *ctx, ಧ್ರುವ ವರ್ಣ *device,
                                      AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags);
    ಪೂರ್ಣಾಙ್ಕ              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags);

    ಪೂರ್ಣಾಙ್ಕ              (*device_init)(AVHWDeviceContext *ctx);
    ಶೂನ್ಯ             (*device_uninit)(AVHWDeviceContext *ctx);

    ಪೂರ್ಣಾಙ್ಕ              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               ಧ್ರುವ ಶೂನ್ಯ *hwconfig,
                                               AVHWFramesConstraints *constraints);

    ಪೂರ್ಣಾಙ್ಕ              (*frames_init)(AVHWFramesContext *ctx);
    ಶೂನ್ಯ             (*frames_uninit)(AVHWFramesContext *ctx);

    ಪೂರ್ಣಾಙ್ಕ              (*frames_get_buffer)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_buffer_alloc)(ಶೂನ್ಯ *device_ref, size_t size);
    ಪೂರ್ಣಾಙ್ಕ              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             ಗಣನಾ AVHWFrameTransferDirection dir,
                                             ಗಣನಾ AVPixelFormat **formats);
    ಪೂರ್ಣಾಙ್ಕ              (*transfer_data_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ಧ್ರುವ AVFrame *src);
    ಪೂರ್ಣಾಙ್ಕ              (*transfer_data_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ಧ್ರುವ AVFrame *src);

    ಪೂರ್ಣಾಙ್ಕ              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags);
    ಪೂರ್ಣಾಙ್ಕ              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags);

    ಪೂರ್ಣಾಙ್ಕ              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಙ್ಕ flags);
    ಪೂರ್ಣಾಙ್ಕ              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಙ್ಕ flags);
} HWContextType;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    ಧ್ರುವ HWContextType *hw_type;

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
    ಪೂರ್ಣಾಙ್ಕ source_allocation_map_flags;
} FFHWFramesContext;

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    ಪ್ರತ್ಯಾಗಮ (FFHWFramesContext*)ctx;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ HWMapDescriptor {
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
    ಶೂನ್ಯ (*unmap)(AVHWFramesContext *ctx,
                  ಸಂರಚನಾ HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    ಶೂನ್ಯ          *priv;
} HWMapDescriptor;

ಪೂರ್ಣಾಙ್ಕ ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ಧ್ರುವ AVFrame *src,
                          ಶೂನ್ಯ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          ಶೂನ್ಯ *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
ಪೂರ್ಣಾಙ್ಕ ff_hwframe_map_replace(AVFrame *dst, ಧ್ರುವ AVFrame *src);

ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_cuda;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_d3d11va;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_d3d12va;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_drm;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_dxva2;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_opencl;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_qsv;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_vaapi;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_vdpau;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_videotoolbox;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_mediacodec;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_vulkan;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_amf;
ಬಾಹ್ಯ ಧ್ರುವ HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
