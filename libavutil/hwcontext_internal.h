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

#شامل <stddef.h>

#شامل "buffer.h"
#شامل "hwcontext.h"
#شامل "thread.h"
#شامل "frame.h"
#شامل "pixfmt.h"

تعریفنوع ساختار HWContextType {
    شمارش AVHWDeviceType type;
    ثابت نویسه         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ثابت شمارش AVPixelFormat *pix_fmts;

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

    صحیح              (*device_create)(AVHWDeviceContext *ctx, ثابت نویسه *device,
                                      AVDictionary *opts, صحیح flags);
    صحیح              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, صحیح flags);

    صحیح              (*device_init)(AVHWDeviceContext *ctx);
    تهی             (*device_uninit)(AVHWDeviceContext *ctx);

    صحیح              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               ثابت تهی *hwconfig,
                                               AVHWFramesConstraints *constraints);

    صحیح              (*frames_init)(AVHWFramesContext *ctx);
    تهی             (*frames_uninit)(AVHWFramesContext *ctx);

    صحیح              (*frames_get_buffer)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_buffer_alloc)(تهی *device_ref, size_t size);
    صحیح              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             شمارش AVHWFrameTransferDirection dir,
                                             شمارش AVPixelFormat **formats);
    صحیح              (*transfer_data_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ثابت AVFrame *src);
    صحیح              (*transfer_data_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ثابت AVFrame *src);

    صحیح              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               ثابت AVFrame *src, صحیح flags);
    صحیح              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src, صحیح flags);

    صحیح              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, صحیح flags);
    صحیح              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, صحیح flags);
} HWContextType;

تعریفنوع ساختار FFHWFramesContext {
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
    صحیح source_allocation_map_flags;
} FFHWFramesContext;

ایستا درونخطی FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    بازگشت (FFHWFramesContext*)ctx;
}

تعریفنوع ساختار HWMapDescriptor {
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
    تهی (*unmap)(AVHWFramesContext *ctx,
                  ساختار HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    تهی          *priv;
} HWMapDescriptor;

صحیح ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ثابت AVFrame *src,
                          تهی (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          تهی *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
صحیح ff_hwframe_map_replace(AVFrame *dst, ثابت AVFrame *src);

بیرونی ثابت HWContextType ff_hwcontext_type_cuda;
بیرونی ثابت HWContextType ff_hwcontext_type_d3d11va;
بیرونی ثابت HWContextType ff_hwcontext_type_d3d12va;
بیرونی ثابت HWContextType ff_hwcontext_type_drm;
بیرونی ثابت HWContextType ff_hwcontext_type_dxva2;
بیرونی ثابت HWContextType ff_hwcontext_type_opencl;
بیرونی ثابت HWContextType ff_hwcontext_type_qsv;
بیرونی ثابت HWContextType ff_hwcontext_type_vaapi;
بیرونی ثابت HWContextType ff_hwcontext_type_vdpau;
بیرونی ثابت HWContextType ff_hwcontext_type_videotoolbox;
بیرونی ثابت HWContextType ff_hwcontext_type_mediacodec;
بیرونی ثابت HWContextType ff_hwcontext_type_vulkan;
بیرونی ثابت HWContextType ff_hwcontext_type_amf;
بیرونی ثابت HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
