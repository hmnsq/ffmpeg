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

#اگر_غیر_تعریف_شدہ AVUTIL_HWCONTEXT_اندرونی_H
#تعریف_کرو AVUTIL_HWCONTEXT_اندرونی_H

#شامل <stddef.h>

#شامل "buffer.h"
#شامل "hwcontext.h"
#شامل "thread.h"
#شامل "frame.h"
#شامل "pixfmt.h"

قسمتعریف ساخت HWContextType {
    شمار AVHWDeviceType type;
    ثابت حرف         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ثابت شمار AVPixelFormat *pix_fmts;

    /**
     * size of the public hardware-specific context,
     * i.e. AVHWDeviceContext.hwctx
     */
    size_t             device_hwctx_سائز;

    /**
     * Size of the hardware-specific device configuration.
     * (Used to query hwframe constraints.)
     */
    size_t             device_hwconfig_سائز;

    /**
     * size of the public frame pool hardware-specific context,
     * i.e. AVHWFramesContext.hwctx
     */
    size_t             چوکھٹے_hwctx_سائز;

    صحیح              (*device_create)(AVHWDeviceContext *ctx, ثابت حرف *device,
                                      AVDictionary *opts, صحیح flags);
    صحیح              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, صحیح flags);

    صحیح              (*device_init)(AVHWDeviceContext *ctx);
    خالی             (*device_uninit)(AVHWDeviceContext *ctx);

    صحیح              (*چوکھٹے_get_constraints)(AVHWDeviceContext *ctx,
                                               ثابت خالی *hwconfig,
                                               AVHWFramesConstraints *constraints);

    صحیح              (*چوکھٹے_init)(AVHWFramesContext *ctx);
    خالی             (*چوکھٹے_uninit)(AVHWFramesContext *ctx);

    صحیح              (*چوکھٹے_get_بفر)(AVHWFramesContext *ctx, AVFrame *چوکھٹا);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_بفر_alloc)(خالی *device_ref, size_t سائز);
    صحیح              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             شمار AVHWFrameTransferDirection dir,
                                             شمار AVPixelFormat **formats);
    صحیح              (*transfer_ڈیٹا_مقصد)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ثابت AVFrame *src);
    صحیح              (*transfer_ڈیٹا_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ثابت AVFrame *src);

    صحیح              (*map_مقصد)(AVHWFramesContext *ctx, AVFrame *dst,
                               ثابت AVFrame *src, صحیح flags);
    صحیح              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src, صحیح flags);

    صحیح              (*چوکھٹے_derive_مقصد)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, صحیح flags);
    صحیح              (*چوکھٹے_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, صحیح flags);
} HWContextType;

قسمتعریف ساخت FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    ثابت HWContextType *hw_type;

    AVBufferPool *pool_اندرونی;

    /**
     * Buffers of transfer_pool_size bytes for av_hwframe_get_transfer_buffer(),
     * both guarded by transfer_pool_lock.
     */
    AVBufferPool *transfer_pool;
    size_t        transfer_pool_سائز;
    AVMutex       transfer_pool_تالا;

    /**
     * For a derived context, a reference to the original frames
     * context it was derived from.
     */
    AVBufferRef *ماخذ_چوکھٹے;
    /**
     * Flags to apply to the mapping from the source to the derived
     * frame context when trying to allocate in the derived context.
     */
    صحیح ماخذ_تخصیص_map_flags;
} FFHWFramesContext;

ساکن اندرونی FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    واپس (FFHWFramesContext*)ctx;
}

قسمتعریف ساخت HWMapDescriptor {
    /**
     * A reference to the original source of the mapping.
     */
    AVFrame *ماخذ;
    /**
     * A reference to the hardware frames context in which this
     * mapping was made.  May be the same as source->hw_frames_ctx,
     * but need not be.
     */
    AVBufferRef *hw_چوکھٹے_ctx;
    /**
     * Unmap function.
     */
    خالی (*unmap)(AVHWFramesContext *ctx,
                  ساخت HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    خالی          *priv;
} HWMapDescriptor;

صحیح ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ثابت AVFrame *src,
                          خالی (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          خالی *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
صحیح ff_hwframe_map_replace(AVFrame *dst, ثابت AVFrame *src);

خارجی ثابت HWContextType ff_hwcontext_type_cuda;
خارجی ثابت HWContextType ff_hwcontext_type_d3d11va;
خارجی ثابت HWContextType ff_hwcontext_type_d3d12va;
خارجی ثابت HWContextType ff_hwcontext_type_drm;
خارجی ثابت HWContextType ff_hwcontext_type_dxva2;
خارجی ثابت HWContextType ff_hwcontext_type_opencl;
خارجی ثابت HWContextType ff_hwcontext_type_qsv;
خارجی ثابت HWContextType ff_hwcontext_type_vaapi;
خارجی ثابت HWContextType ff_hwcontext_type_vdpau;
خارجی ثابت HWContextType ff_hwcontext_type_videotoolbox;
خارجی ثابت HWContextType ff_hwcontext_type_mediacodec;
خارجی ثابت HWContextType ff_hwcontext_type_vulkan;
خارجی ثابت HWContextType ff_hwcontext_type_amf;
خارجی ثابت HWContextType ff_hwcontext_type_oh;

#اگر_ختم /* AVUTIL_HWCONTEXT_INTERNAL_H */
