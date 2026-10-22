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

#ଅନ୍ତର୍ଭାଵ <stddef.h>

#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "thread.h"
#ଅନ୍ତର୍ଭାଵ "frame.h"
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା HWContextType {
    ଗଣନା AVHWDeviceType type;
    ଅଚଳ ଅକ୍ଷର         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ଅଚଳ ଗଣନା AVPixelFormat *pix_fmts;

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

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*device_create)(AVHWDeviceContext *ctx, ଅଚଳ ଅକ୍ଷର *device,
                                      AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*device_init)(AVHWDeviceContext *ctx);
    ଶୂନ୍ୟ             (*device_uninit)(AVHWDeviceContext *ctx);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               ଅଚଳ ଶୂନ୍ୟ *hwconfig,
                                               AVHWFramesConstraints *constraints);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*frames_init)(AVHWFramesContext *ctx);
    ଶୂନ୍ୟ             (*frames_uninit)(AVHWFramesContext *ctx);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*frames_get_buffer)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_buffer_alloc)(ଶୂନ୍ୟ *device_ref, size_t size);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             ଗଣନା AVHWFrameTransferDirection dir,
                                             ଗଣନା AVPixelFormat **formats);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*transfer_data_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ଅଚଳ AVFrame *src);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*transfer_data_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ଅଚଳ AVFrame *src);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags);
} HWContextType;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    ଅଚଳ HWContextType *hw_type;

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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା source_allocation_map_flags;
} FFHWFramesContext;

ସ୍ଥିର ଧାଡ଼ିଭିତରେ FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    ଫେରନ୍ତୁ (FFHWFramesContext*)ctx;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା HWMapDescriptor {
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
    ଶୂନ୍ୟ (*unmap)(AVHWFramesContext *ctx,
                  ସଂରଚନା HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    ଶୂନ୍ୟ          *priv;
} HWMapDescriptor;

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ଅଚଳ AVFrame *src,
                          ଶୂନ୍ୟ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          ଶୂନ୍ୟ *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_hwframe_map_replace(AVFrame *dst, ଅଚଳ AVFrame *src);

ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_cuda;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_d3d11va;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_d3d12va;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_drm;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_dxva2;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_opencl;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_qsv;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_vaapi;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_vdpau;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_videotoolbox;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_mediacodec;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_vulkan;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_amf;
ବାହ୍ୟ ଅଚଳ HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
