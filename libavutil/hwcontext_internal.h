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

#ضمن <stddef.h>

#ضمن "buffer.h"
#ضمن "hwcontext.h"
#ضمن "thread.h"
#ضمن "frame.h"
#ضمن "pixfmt.h"

تعريفنوع بنية HWContextType {
    تعداد AVHWDeviceType type;
    ثابت حرف         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ثابت تعداد AVPixelFormat *pix_fmts;

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

    صحيح              (*device_create)(AVHWDeviceContext *ctx, ثابت حرف *device,
                                      AVDictionary *opts, صحيح flags);
    صحيح              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, صحيح flags);

    صحيح              (*device_init)(AVHWDeviceContext *ctx);
    فراغ             (*device_uninit)(AVHWDeviceContext *ctx);

    صحيح              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               ثابت فراغ *hwconfig,
                                               AVHWFramesConstraints *constraints);

    صحيح              (*frames_init)(AVHWFramesContext *ctx);
    فراغ             (*frames_uninit)(AVHWFramesContext *ctx);

    صحيح              (*frames_get_buffer)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_buffer_alloc)(فراغ *device_ref, size_t size);
    صحيح              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             تعداد AVHWFrameTransferDirection dir,
                                             تعداد AVPixelFormat **formats);
    صحيح              (*transfer_data_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ثابت AVFrame *src);
    صحيح              (*transfer_data_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ثابت AVFrame *src);

    صحيح              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               ثابت AVFrame *src, صحيح flags);
    صحيح              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src, صحيح flags);

    صحيح              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, صحيح flags);
    صحيح              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, صحيح flags);
} HWContextType;

تعريفنوع بنية FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    ثابت HWContextType *hw_type;

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
    صحيح source_allocation_map_flags;
} FFHWFramesContext;

ساكن مضمن FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    إرجاع (FFHWFramesContext*)ctx;
}

تعريفنوع بنية HWMapDescriptor {
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
    فراغ (*unmap)(AVHWFramesContext *ctx,
                  بنية HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    فراغ          *priv;
} HWMapDescriptor;

صحيح ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ثابت AVFrame *src,
                          فراغ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          فراغ *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
صحيح ff_hwframe_map_replace(AVFrame *dst, ثابت AVFrame *src);

خارجي ثابت HWContextType ff_hwcontext_type_cuda;
خارجي ثابت HWContextType ff_hwcontext_type_d3d11va;
خارجي ثابت HWContextType ff_hwcontext_type_d3d12va;
خارجي ثابت HWContextType ff_hwcontext_type_drm;
خارجي ثابت HWContextType ff_hwcontext_type_dxva2;
خارجي ثابت HWContextType ff_hwcontext_type_opencl;
خارجي ثابت HWContextType ff_hwcontext_type_qsv;
خارجي ثابت HWContextType ff_hwcontext_type_vaapi;
خارجي ثابت HWContextType ff_hwcontext_type_vdpau;
خارجي ثابت HWContextType ff_hwcontext_type_videotoolbox;
خارجي ثابت HWContextType ff_hwcontext_type_mediacodec;
خارجي ثابت HWContextType ff_hwcontext_type_vulkan;
خارجي ثابت HWContextType ff_hwcontext_type_amf;
خارجي ثابت HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
