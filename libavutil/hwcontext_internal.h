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

#അന്തര്ഭാവ <stddef.h>

#അന്തര്ഭാവ "buffer.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "thread.h"
#അന്തര്ഭാവ "frame.h"
#അന്തര്ഭാവ "pixfmt.h"

തരനിർവചനം ഘടന HWContextType {
    എണ്ണൽ AVHWDeviceType type;
    സ്ഥിരം അക്ഷരം         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    സ്ഥിരം എണ്ണൽ AVPixelFormat *pix_fmts;

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

    പൂർണ്ണസംഖ്യ              (*device_create)(AVHWDeviceContext *ctx, സ്ഥിരം അക്ഷരം *device,
                                      AVDictionary *opts, പൂർണ്ണസംഖ്യ flags);
    പൂർണ്ണസംഖ്യ              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, പൂർണ്ണസംഖ്യ flags);

    പൂർണ്ണസംഖ്യ              (*device_init)(AVHWDeviceContext *ctx);
    ശൂന്യം             (*device_uninit)(AVHWDeviceContext *ctx);

    പൂർണ്ണസംഖ്യ              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               സ്ഥിരം ശൂന്യം *hwconfig,
                                               AVHWFramesConstraints *constraints);

    പൂർണ്ണസംഖ്യ              (*frames_init)(AVHWFramesContext *ctx);
    ശൂന്യം             (*frames_uninit)(AVHWFramesContext *ctx);

    പൂർണ്ണസംഖ്യ              (*frames_get_buffer)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_buffer_alloc)(ശൂന്യം *device_ref, size_t size);
    പൂർണ്ണസംഖ്യ              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             എണ്ണൽ AVHWFrameTransferDirection dir,
                                             എണ്ണൽ AVPixelFormat **formats);
    പൂർണ്ണസംഖ്യ              (*transfer_data_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         സ്ഥിരം AVFrame *src);
    പൂർണ്ണസംഖ്യ              (*transfer_data_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           സ്ഥിരം AVFrame *src);

    പൂർണ്ണസംഖ്യ              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags);
    പൂർണ്ണസംഖ്യ              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags);

    പൂർണ്ണസംഖ്യ              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, പൂർണ്ണസംഖ്യ flags);
    പൂർണ്ണസംഖ്യ              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, പൂർണ്ണസംഖ്യ flags);
} HWContextType;

തരനിർവചനം ഘടന FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    സ്ഥിരം HWContextType *hw_type;

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
    പൂർണ്ണസംഖ്യ source_allocation_map_flags;
} FFHWFramesContext;

സ്ഥിതം വരിയിൽ FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    തിരികെ (FFHWFramesContext*)ctx;
}

തരനിർവചനം ഘടന HWMapDescriptor {
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
    ശൂന്യം (*unmap)(AVHWFramesContext *ctx,
                  ഘടന HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    ശൂന്യം          *priv;
} HWMapDescriptor;

പൂർണ്ണസംഖ്യ ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, സ്ഥിരം AVFrame *src,
                          ശൂന്യം (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          ശൂന്യം *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
പൂർണ്ണസംഖ്യ ff_hwframe_map_replace(AVFrame *dst, സ്ഥിരം AVFrame *src);

ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_cuda;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_d3d11va;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_d3d12va;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_drm;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_dxva2;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_opencl;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_qsv;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_vaapi;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_vdpau;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_videotoolbox;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_mediacodec;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_vulkan;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_amf;
ബാഹ്യ സ്ഥിരം HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
