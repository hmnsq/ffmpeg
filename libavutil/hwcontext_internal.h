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

#अन्तर्भाव <stddef.h>

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "thread.h"
#अन्तर्भाव "frame.h"
#अन्तर्भाव "pixfmt.h"

प्रकारनिर्देश संरचना HWContextType {
    गणना AVHWDeviceType type;
    ध्रुव वर्ण         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    ध्रुव गणना AVPixelFormat *pix_fmts;

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

    पूर्णाङ्क              (*device_create)(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                                      AVDictionary *opts, पूर्णाङ्क flags);
    पूर्णाङ्क              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, पूर्णाङ्क flags);

    पूर्णाङ्क              (*device_init)(AVHWDeviceContext *ctx);
    शून्य             (*device_uninit)(AVHWDeviceContext *ctx);

    पूर्णाङ्क              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               ध्रुव शून्य *hwconfig,
                                               AVHWFramesConstraints *constraints);

    पूर्णाङ्क              (*frames_init)(AVHWFramesContext *ctx);
    शून्य             (*frames_uninit)(AVHWFramesContext *ctx);

    पूर्णाङ्क              (*frames_get_buffer)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_buffer_alloc)(शून्य *device_ref, size_t size);
    पूर्णाङ्क              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             गणना AVHWFrameTransferDirection dir,
                                             गणना AVPixelFormat **formats);
    पूर्णाङ्क              (*transfer_data_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         ध्रुव AVFrame *src);
    पूर्णाङ्क              (*transfer_data_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           ध्रुव AVFrame *src);

    पूर्णाङ्क              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               ध्रुव AVFrame *src, पूर्णाङ्क flags);
    पूर्णाङ्क              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 ध्रुव AVFrame *src, पूर्णाङ्क flags);

    पूर्णाङ्क              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, पूर्णाङ्क flags);
    पूर्णाङ्क              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, पूर्णाङ्क flags);
} HWContextType;

प्रकारनिर्देश संरचना FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    ध्रुव HWContextType *hw_type;

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
    पूर्णाङ्क source_allocation_map_flags;
} FFHWFramesContext;

स्थिर अन्तःस्थ FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    प्रत्यागम (FFHWFramesContext*)ctx;
}

प्रकारनिर्देश संरचना HWMapDescriptor {
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
    शून्य (*unmap)(AVHWFramesContext *ctx,
                  संरचना HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    शून्य          *priv;
} HWMapDescriptor;

पूर्णाङ्क ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ध्रुव AVFrame *src,
                          शून्य (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          शून्य *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
पूर्णाङ्क ff_hwframe_map_replace(AVFrame *dst, ध्रुव AVFrame *src);

बाह्य ध्रुव HWContextType ff_hwcontext_type_cuda;
बाह्य ध्रुव HWContextType ff_hwcontext_type_d3d11va;
बाह्य ध्रुव HWContextType ff_hwcontext_type_d3d12va;
बाह्य ध्रुव HWContextType ff_hwcontext_type_drm;
बाह्य ध्रुव HWContextType ff_hwcontext_type_dxva2;
बाह्य ध्रुव HWContextType ff_hwcontext_type_opencl;
बाह्य ध्रुव HWContextType ff_hwcontext_type_qsv;
बाह्य ध्रुव HWContextType ff_hwcontext_type_vaapi;
बाह्य ध्रुव HWContextType ff_hwcontext_type_vdpau;
बाह्य ध्रुव HWContextType ff_hwcontext_type_videotoolbox;
बाह्य ध्रुव HWContextType ff_hwcontext_type_mediacodec;
बाह्य ध्रुव HWContextType ff_hwcontext_type_vulkan;
बाह्य ध्रुव HWContextType ff_hwcontext_type_amf;
बाह्य ध्रुव HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
