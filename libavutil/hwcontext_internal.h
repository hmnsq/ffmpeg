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

#અન્તર્ભાવ <stddef.h>

#અન્તર્ભાવ "buffer.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "thread.h"
#અન્તર્ભાવ "frame.h"
#અન્તર્ભાવ "pixfmt.h"

પ્રકારવ્યાખ્યા સંરચના HWContextType {
    ગણના AVHWDeviceType type;
    અચલ અક્ષર         *name;

    /**
     * An array of pixel formats supported by the AVHWFramesContext instances
     * Terminated by AV_PIX_FMT_NONE.
     */
    અચલ ગણના AVPixelFormat *pix_fmts;

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

    પૂર્ણાંક              (*device_create)(AVHWDeviceContext *ctx, અચલ અક્ષર *device,
                                      AVDictionary *opts, પૂર્ણાંક flags);
    પૂર્ણાંક              (*device_derive)(AVHWDeviceContext *dst_ctx,
                                      AVHWDeviceContext *src_ctx,
                                      AVDictionary *opts, પૂર્ણાંક flags);

    પૂર્ણાંક              (*device_init)(AVHWDeviceContext *ctx);
    શૂન્ય             (*device_uninit)(AVHWDeviceContext *ctx);

    પૂર્ણાંક              (*frames_get_constraints)(AVHWDeviceContext *ctx,
                                               અચલ શૂન્ય *hwconfig,
                                               AVHWFramesConstraints *constraints);

    પૂર્ણાંક              (*frames_init)(AVHWFramesContext *ctx);
    શૂન્ય             (*frames_uninit)(AVHWFramesContext *ctx);

    પૂર્ણાંક              (*frames_get_buffer)(AVHWFramesContext *ctx, AVFrame *frame);

    /**
     * Allocate a buffer of size bytes for av_hwframe_get_transfer_buffer(),
     * av_buffer_alloc() is used if this is not set or returns NULL.
     *
     * @param device_ref the AVBufferRef of the AVHWDeviceContext
     */
    AVBufferRef     *(*transfer_buffer_alloc)(શૂન્ય *device_ref, size_t size);
    પૂર્ણાંક              (*transfer_get_formats)(AVHWFramesContext *ctx,
                                             ગણના AVHWFrameTransferDirection dir,
                                             ગણના AVPixelFormat **formats);
    પૂર્ણાંક              (*transfer_data_to)(AVHWFramesContext *ctx, AVFrame *dst,
                                         અચલ AVFrame *src);
    પૂર્ણાંક              (*transfer_data_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                           અચલ AVFrame *src);

    પૂર્ણાંક              (*map_to)(AVHWFramesContext *ctx, AVFrame *dst,
                               અચલ AVFrame *src, પૂર્ણાંક flags);
    પૂર્ણાંક              (*map_from)(AVHWFramesContext *ctx, AVFrame *dst,
                                 અચલ AVFrame *src, પૂર્ણાંક flags);

    પૂર્ણાંક              (*frames_derive_to)(AVHWFramesContext *dst_ctx,
                                         AVHWFramesContext *src_ctx, પૂર્ણાંક flags);
    પૂર્ણાંક              (*frames_derive_from)(AVHWFramesContext *dst_ctx,
                                           AVHWFramesContext *src_ctx, પૂર્ણાંક flags);
} HWContextType;

પ્રકારવ્યાખ્યા સંરચના FFHWFramesContext {
    /**
     * The public AVHWFramesContext. See hwcontext.h for it.
     */
    AVHWFramesContext p;

    અચલ HWContextType *hw_type;

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
    પૂર્ણાંક source_allocation_map_flags;
} FFHWFramesContext;

સ્થિર અંતઃરેખ FFHWFramesContext *ffhwframesctx(AVHWFramesContext *ctx)
{
    પાછા (FFHWFramesContext*)ctx;
}

પ્રકારવ્યાખ્યા સંરચના HWMapDescriptor {
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
    શૂન્ય (*unmap)(AVHWFramesContext *ctx,
                  સંરચના HWMapDescriptor *hwmap);
    /**
     * Hardware-specific private data associated with the mapping.
     */
    શૂન્ય          *priv;
} HWMapDescriptor;

પૂર્ણાંક ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, અચલ AVFrame *src,
                          શૂન્ય (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          શૂન્ય *priv);

/**
 * Replace the current hwmap of dst with the one from src, used for indirect
 * mappings like VAAPI->(DRM)->OpenCL/Vulkan where a direct interop is missing
 */
પૂર્ણાંક ff_hwframe_map_replace(AVFrame *dst, અચલ AVFrame *src);

બાહ્ય અચલ HWContextType ff_hwcontext_type_cuda;
બાહ્ય અચલ HWContextType ff_hwcontext_type_d3d11va;
બાહ્ય અચલ HWContextType ff_hwcontext_type_d3d12va;
બાહ્ય અચલ HWContextType ff_hwcontext_type_drm;
બાહ્ય અચલ HWContextType ff_hwcontext_type_dxva2;
બાહ્ય અચલ HWContextType ff_hwcontext_type_opencl;
બાહ્ય અચલ HWContextType ff_hwcontext_type_qsv;
બાહ્ય અચલ HWContextType ff_hwcontext_type_vaapi;
બાહ્ય અચલ HWContextType ff_hwcontext_type_vdpau;
બાહ્ય અચલ HWContextType ff_hwcontext_type_videotoolbox;
બાહ્ય અચલ HWContextType ff_hwcontext_type_mediacodec;
બાહ્ય અચલ HWContextType ff_hwcontext_type_vulkan;
બાહ્ય અચલ HWContextType ff_hwcontext_type_amf;
બાહ્ય અચલ HWContextType ff_hwcontext_type_oh;

#endif /* AVUTIL_HWCONTEXT_INTERNAL_H */
