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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_HWCONTEXT_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_HWCONTEXT_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "thread.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HWContextType {
    ಎಣಿಕೆ AVHWDeviceType type;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat *pix_fmts;

    /**
     * size of the public hardware-specific context,
     * i.e. AVHWDeviceContext.hwctx
     */
    size_t             device_hwctx_ಗಾತ್ರ;

    /**
     * Size of the hardware-specific device configuration.
     * (Used to query hwframe constraints.)
     */
    size_t             device_hwconfig_ಗಾತ್ರ;

    /**
     * size of the public frame pool hardware-specific context,
     * i.e. AVHWFramesContext.hwctx
     */
    size_t             ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ;

    ಪೂರ್ಣಾಂಕ              (*device_create)(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                                      AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags);
    ಪೂರ್ಣಾಂಕ              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags);

    ಪೂರ್ಣಾಂಕ              (*device_init)(AVHWDeviceContext *ctx);
    ಶೂನ್ಯ             (*device_uninit)(AVHWDeviceContext *ctx);

    ಪೂರ್ಣಾಂಕ              (*ಚೌಕಟ್ಟುಗಳು_get_constraints)(AVHWDeviceContext *ctx,
                                               ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                               AVHWFramesConstraints *constraints);

    ಪೂರ್ಣಾಂಕ              (*ಚೌಕಟ್ಟುಗಳು_init)(AVHWFramesContext *ctx);
    ಶೂನ್ಯ             (*ಚೌಕಟ್ಟುಗಳು_uninit)(AVHWFramesContext *ctx);

    ಪೂರ್ಣಾಂಕ              (*ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್)(AVHWFramesContext *ctx, AVFrame *ಚೌಕಟ್ಟು);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_ಬಫರ್_alloc)(ಶೂನ್ಯ *device_ref, size_t ಗಾತ್ರ_2);
    ಪೂರ್ಣಾಂಕ              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                             ಎಣಿಕೆ AVPixelFormat **formats);
    ಪೂರ್ಣಾಂಕ              (*transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ಸ್ಥಿರಾಂಕ AVFrame *src);
    ಪೂರ್ಣಾಂಕ              (*transfer_ದತ್ತಾಂಶ_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ಸ್ಥಿರಾಂಕ AVFrame *src);

    ಪೂರ್ಣಾಂಕ              (*map_ಗಮ್ಯ)(AVHWFramesContext *ctx, AVFrame *dst,
                               ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags);
    ಪೂರ್ಣಾಂಕ              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags);

    ಪೂರ್ಣಾಂಕ              (*ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಂಕ flags);
    ಪೂರ್ಣಾಂಕ              (*ಚೌಕಟ್ಟುಗಳು_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಂಕ flags);
} HWContextType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    ಸ್ಥಿರಾಂಕ HWContextType *hw_type;

    AVBufferPool *pool_ಆಂತರಿಕ;

    /**
     * Buffers of transfer_pool_size bytes for av_hwframe_get_transfer_buffer(),
     * both guarded by transfer_pool_lock.
     */
    AVBufferPool *transfer_pool;
    size_t        transfer_pool_ಗಾತ್ರ;
    AVMutex       transfer_pool_ಬೀಗ;

    /**
     * For a derived context, a reference to the original frames
     * context it was derived from.
     */
    AVBufferRef *ಮೂಲ_ಚೌಕಟ್ಟುಗಳು;
    /**
     * Flags to apply to the mapping from the source to the derived
     * frame context when trying to allocate in the derived context.
     */
    ಪೂರ್ಣಾಂಕ ಮೂಲ_ಹಂಚಿಕೆ_map_flags;
} FFHWFramesContext;

ಸ್ಥಿರ ಸಾಲೊಳಗೆ FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    ಹಿಂತಿರುಗಿ (FFHWFramesContext*)ctx;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HWMapDescriptor {
    /**
     * A reference to the original source of the mapping.
     */
    AVFrame *ಮೂಲ;
    /**
     * A reference to the hardware frames context in which this
     * mapping was made.  May be the same as source->hw_frames_ctx,
     * but need not be.
     */
    AVBufferRef *hw_ಚೌಕಟ್ಟುಗಳು_ctx;
    /**
     * Unmap function.
     */
    ಶೂನ್ಯ (*unmap)(AVHWFramesContext *ctx,
                  ರಚನೆ HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    ಶೂನ್ಯ          *priv;
} HWMapDescriptor;

ಪೂರ್ಣಾಂಕ ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src,
                          ಶೂನ್ಯ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          ಶೂನ್ಯ *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
ಪೂರ್ಣಾಂಕ ff_hwframe_map_replace(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src);

ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_cuda;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_d3d11va;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_d3d12va;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_drm;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_dxva2;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_opencl;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_qsv;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_vaapi;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_vdpau;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_videotoolbox;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_mediacodec;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_vulkan;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_amf;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_oh;

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_HWCONTEXT_INTERNAL_H */
