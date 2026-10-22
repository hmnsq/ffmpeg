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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_HWCONTEXT_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_HWCONTEXT_ਅੰਦਰੂਨੀ_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HWContextType {
    ਗਿਣਤੀ AVHWDeviceType type;
    ਅਚਲ ਅੱਖਰ         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ਅਚਲ ਗਿਣਤੀ AVPixelFormat *pix_fmts;

    /**
     * size of the public hardware-specific context,
     * i.e. AVHWDeviceContext.hwctx
     */
    size_t             device_hwctx_ਮਾਪ;

    /**
     * Size of the hardware-specific device configuration.
     * (Used to query hwframe constraints.)
     */
    size_t             device_hwconfig_ਮਾਪ;

    /**
     * size of the public frame pool hardware-specific context,
     * i.e. AVHWFramesContext.hwctx
     */
    size_t             ਚੌਖਟੇ_hwctx_ਮਾਪ;

    ਪੂਰਨ              (*device_create)(AVHWDeviceContext *ctx, ਅਚਲ ਅੱਖਰ *device,
                                      AVDictionary *opts, ਪੂਰਨ flags);
    ਪੂਰਨ              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, ਪੂਰਨ flags);

    ਪੂਰਨ              (*device_init)(AVHWDeviceContext *ctx);
    ਖਾਲੀ             (*device_uninit)(AVHWDeviceContext *ctx);

    ਪੂਰਨ              (*ਚੌਖਟੇ_get_constraints)(AVHWDeviceContext *ctx,
                                               ਅਚਲ ਖਾਲੀ *hwconfig,
                                               AVHWFramesConstraints *constraints);

    ਪੂਰਨ              (*ਚੌਖਟੇ_init)(AVHWFramesContext *ctx);
    ਖਾਲੀ             (*ਚੌਖਟੇ_uninit)(AVHWFramesContext *ctx);

    ਪੂਰਨ              (*ਚੌਖਟੇ_get_ਬਫਰ)(AVHWFramesContext *ctx, AVFrame *ਚੌਖਟਾ);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_ਬਫਰ_alloc)(ਖਾਲੀ *device_ref, size_t ਮਾਪ);
    ਪੂਰਨ              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                             ਗਿਣਤੀ AVPixelFormat **formats);
    ਪੂਰਨ              (*transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ਅਚਲ AVFrame *src);
    ਪੂਰਨ              (*transfer_ਅੰਕੜੇ_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ਅਚਲ AVFrame *src);

    ਪੂਰਨ              (*map_ਮੰਜ਼ਿਲ)(AVHWFramesContext *ctx, AVFrame *dst,
                               ਅਚਲ AVFrame *src, ਪੂਰਨ flags);
    ਪੂਰਨ              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ਅਚਲ AVFrame *src, ਪੂਰਨ flags);

    ਪੂਰਨ              (*ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, ਪੂਰਨ flags);
    ਪੂਰਨ              (*ਚੌਖਟੇ_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, ਪੂਰਨ flags);
} HWContextType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    ਅਚਲ HWContextType *hw_type;

    AVBufferPool *pool_ਅੰਦਰੂਨੀ;

    /**
     * Buffers of transfer_pool_size bytes for av_hwframe_get_transfer_buffer(),
     * both guarded by transfer_pool_lock.
     */
    AVBufferPool *transfer_pool;
    size_t        transfer_pool_ਮਾਪ;
    AVMutex       transfer_pool_ਤਾਲਾ;

    /**
     * For a derived context, a reference to the original frames
     * context it was derived from.
     */
    AVBufferRef *ਸਰੋਤ_ਚੌਖਟੇ;
    /**
     * Flags to apply to the mapping from the source to the derived
     * frame context when trying to allocate in the derived context.
     */
    ਪੂਰਨ ਸਰੋਤ_ਵੰਡ_map_flags;
} FFHWFramesContext;

ਸਥਿਰ ਸਤਰਅੰਦਰ FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    ਵਾਪਸ (FFHWFramesContext*)ctx;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HWMapDescriptor {
    /**
     * A reference to the original source of the mapping.
     */
    AVFrame *ਸਰੋਤ;
    /**
     * A reference to the hardware frames context in which this
     * mapping was made.  May be the same as source->hw_frames_ctx,
     * but need not be.
     */
    AVBufferRef *hw_ਚੌਖਟੇ_ctx;
    /**
     * Unmap function.
     */
    ਖਾਲੀ (*unmap)(AVHWFramesContext *ctx,
                  ਬਣਤਰ HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    ਖਾਲੀ          *priv;
} HWMapDescriptor;

ਪੂਰਨ ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ਅਚਲ AVFrame *src,
                          ਖਾਲੀ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          ਖਾਲੀ *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
ਪੂਰਨ ff_hwframe_map_replace(AVFrame *dst, ਅਚਲ AVFrame *src);

ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_cuda;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_d3d11va;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_d3d12va;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_drm;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_dxva2;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_opencl;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_qsv;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_vaapi;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_vdpau;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_videotoolbox;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_mediacodec;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_vulkan;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_amf;
ਬਾਹਰੀ ਅਚਲ HWContextType ff_hwcontext_type_oh;

#ਜੇ_ਅੰਤ /* AVUTIL_HWCONTEXT_INTERNAL_H */
