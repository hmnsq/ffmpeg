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

#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "buffer.h"
#അന്തര്ഭാവ "pixfmt.h"
#അന്തര്ഭാവ "pixdesc.h"
#അന്തര്ഭാവ "imgutils.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_amf.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "hwcontext_amf_internal.h"

#അന്തര്ഭാവ "libavutil/thread.h"
#അന്തര്ഭാവ "libavutil/avassert.h"

#അന്തര്ഭാവ <AMF/core/Surface.h>
#അന്തര്ഭാവ <AMF/core/Trace.h>

#എങ്കിൽ CONFIG_VULKAN
#അന്തര്ഭാവ "hwcontext_vulkan.h"
#endif
#എങ്കിൽ CONFIG_D3D11VA
#അന്തര്ഭാവ "libavutil/hwcontext_d3d11va.h"
#endif
#എങ്കിൽ CONFIG_D3D12VA
#അന്തര്ഭാവ "libavutil/hwcontext_d3d12va.h"
#endif
#എങ്കിൽ CONFIG_DXVA2
#define COBJMACROS
#അന്തര്ഭാവ "libavutil/hwcontext_dxva2.h"
#endif
#ifdef _WIN32
#അന്തര്ഭാവ "compat/w32dlfcn.h"
#അല്ലെങ്കിൽ
#അന്തര്ഭാവ <dlfcn.h>
#endif
#define FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

സ്ഥിതം ശൂന്യം amf_lock_default(ശൂന്യം *opaque)
{
    ff_mutex_lock((AVMutex*)opaque);
}

സ്ഥിതം ശൂന്യം amf_unlock_default(ശൂന്യം *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

തരനിർവചനം ഘടന AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    ശൂന്യം               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

സ്ഥിതം ശൂന്യം AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    സ്ഥിരം wchar_t *scope, സ്ഥിരം wchar_t *message)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, message); // \n is provided from AMF
}

സ്ഥിതം ശൂന്യം AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

സ്ഥിതം AmfTraceWriter * amf_writer_alloc(ശൂന്യം  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(വലുപ്പം(AmfTraceWriter));
    എങ്കിൽ (!writer)
        തിരികെ ശൂന്യ;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    തിരികെ writer;
}

സ്ഥിതം ശൂന്യം amf_writer_free(ശൂന്യം  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
തരനിർവചനം ഘടന {
    ശൂന്യം *dummy;
} AMFFramesContext;

തരനിർവചനം ഘടന AVAMFFormatMap {
    എണ്ണൽ AVPixelFormat       av_format;
    എണ്ണൽ AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

സ്ഥിരം FormatMap format_map[] =
{
    { AV_PIX_FMT_NONE,          AMF_SURFACE_UNKNOWN },
    { AV_PIX_FMT_NV12,          AMF_SURFACE_NV12 },
    { AV_PIX_FMT_BGR0,          AMF_SURFACE_BGRA },
    { AV_PIX_FMT_RGB0,          AMF_SURFACE_RGBA },
    { AV_PIX_FMT_BGRA,          AMF_SURFACE_BGRA },
    { AV_PIX_FMT_ARGB,          AMF_SURFACE_ARGB },
    { AV_PIX_FMT_RGBA,          AMF_SURFACE_RGBA },
    { AV_PIX_FMT_GRAY8,         AMF_SURFACE_GRAY8 },
    { AV_PIX_FMT_YUV420P,       AMF_SURFACE_YUV420P },
    { AV_PIX_FMT_YUYV422,       AMF_SURFACE_YUY2 },
    { AV_PIX_FMT_P010,          AMF_SURFACE_P010 },
    { AV_PIX_FMT_X2BGR10,       AMF_SURFACE_R10G10B10A2 },
    { AV_PIX_FMT_RGBAF16,       AMF_SURFACE_RGBA_F16},
};

എണ്ണൽ AMF_SURFACE_FORMAT av_av_to_amf_format(എണ്ണൽ AVPixelFormat fmt)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < amf_countof(format_map); i++) {
        എങ്കിൽ (format_map[i].av_format == fmt) {
            തിരികെ format_map[i].amf_format;
        }
    }
    തിരികെ AMF_SURFACE_UNKNOWN;
}

എണ്ണൽ AVPixelFormat av_amf_to_av_format(എണ്ണൽ AMF_SURFACE_FORMAT fmt)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < amf_countof(format_map); i++) {
        എങ്കിൽ (format_map[i].amf_format == fmt) {
            തിരികെ format_map[i].av_format;
        }
    }
    തിരികെ AV_PIX_FMT_NONE;
}

എണ്ണൽ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(എണ്ണൽ AVColorRange color_range, എണ്ണൽ AVColorSpace color_space)
{
    തിരഞ്ഞെടുപ്പ് (color_space) {
    അവസ്ഥ AVCOL_SPC_SMPTE170M:
        എങ്കിൽ (color_range == AVCOL_RANGE_JPEG) {
            തിരികെ AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_601;
        } അല്ലെങ്കിൽ {
            തിരികെ AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        നിർത്തുക;
    അവസ്ഥ AVCOL_SPC_BT709:
        എങ്കിൽ (color_range == AVCOL_RANGE_JPEG) {
            തിരികെ AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_709;
        } അല്ലെങ്കിൽ {
            തിരികെ AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        നിർത്തുക;
    അവസ്ഥ AVCOL_SPC_BT2020_NCL:
    അവസ്ഥ AVCOL_SPC_BT2020_CL:
        എങ്കിൽ (color_range == AVCOL_RANGE_JPEG) {
            തിരികെ AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_2020;
        } അല്ലെങ്കിൽ {
            തിരികെ AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
        തിരികെ AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

പൂർണ്ണസംഖ്യ av_amf_display_mastering_meta_to_hdrmeta(സ്ഥിരം AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    എങ്കിൽ (!display_meta || !hdrmeta)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (display_meta->has_luminance) {
        സ്ഥിരം unsigned പൂർണ്ണസംഖ്യ luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    എങ്കിൽ (display_meta->has_primaries) {
        സ്ഥിരം unsigned പൂർണ്ണസംഖ്യ chroma_den = 50000;
        hdrmeta->redPrimary[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[0][0])), chroma_den);
        hdrmeta->redPrimary[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[0][1])), chroma_den);
        hdrmeta->greenPrimary[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[1][0])), chroma_den);
        hdrmeta->greenPrimary[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[1][1])), chroma_den);
        hdrmeta->bluePrimary[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[2][0])), chroma_den);
        hdrmeta->bluePrimary[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[2][1])), chroma_den);
        hdrmeta->whitePoint[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_point[0])), chroma_den);
        hdrmeta->whitePoint[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_point[1])), chroma_den);
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_amf_light_metadata_to_hdrmeta(സ്ഥിരം AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    എങ്കിൽ (!light_meta || !hdrmeta)
        തിരികെ AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->maxFrameAverageLightLevel = (amf_uint16)light_meta->MaxFALL;

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_amf_extract_hdr_metadata(സ്ഥിരം AVFrame *frame, AMFHDRMetadata *hdrmeta)
{
    AVFrameSideData *sidedata;
    AVContentLightMetadata *content_light = ശൂന്യ;
    AVMasteringDisplayMetadata *mastering_display = ശൂന്യ;

    എങ്കിൽ (!frame || !hdrmeta)
        തിരികെ AVERROR(EINVAL);

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_MASTERING_DISPLAY_METADATA);
    എങ്കിൽ (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->data;
        എങ്കിൽ (av_amf_display_mastering_meta_to_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = ശൂന്യ;
    }

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_CONTENT_LIGHT_LEVEL);
    എങ്കിൽ (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->data;
        എങ്കിൽ (av_amf_light_metadata_to_hdrmeta(content_light, hdrmeta) != 0)
            content_light = ശൂന്യ;
    }

    എങ്കിൽ (!mastering_display && !content_light)
        തിരികെ AVERROR(ENODATA);

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_amf_attach_hdr_metadata(AVFrame *frame, സ്ഥിരം AMFHDRMetadata *hdrmeta) {
    എങ്കിൽ (!hdrmeta || !frame)
        തിരികെ AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_data(frame);
    സ്ഥിരം പൂർണ്ണസംഖ്യ chroma_den = 50000;
    സ്ഥിരം പൂർണ്ണസംഖ്യ luma_den = 10000;

    എങ്കിൽ (!mastering)
      തിരികെ AVERROR(ENOMEM);

    mastering->display_primaries[0][0] =
        av_make_q(hdrmeta->redPrimary[0], chroma_den);
    mastering->display_primaries[0][1] =
        av_make_q(hdrmeta->redPrimary[1], chroma_den);

    mastering->display_primaries[1][0] =
        av_make_q(hdrmeta->greenPrimary[0], chroma_den);
    mastering->display_primaries[1][1] =
        av_make_q(hdrmeta->greenPrimary[1], chroma_den);

    mastering->display_primaries[2][0] =
        av_make_q(hdrmeta->bluePrimary[0], chroma_den);
    mastering->display_primaries[2][1] =
        av_make_q(hdrmeta->bluePrimary[1], chroma_den);

    mastering->white_point[0] = av_make_q(hdrmeta->whitePoint[0], chroma_den);
    mastering->white_point[1] = av_make_q(hdrmeta->whitePoint[1], chroma_den);

    mastering->max_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);
    mastering->min_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);

    mastering->has_luminance = 1;
    mastering->has_primaries = 1;
    എങ്കിൽ (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_data(frame);

      എങ്കിൽ (!light)
        തിരികെ AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->maxFrameAverageLightLevel;
    }

    തിരികെ 0;
}

സ്ഥിതം സ്ഥിരം എണ്ണൽ AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#എങ്കിൽ CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#endif
#എങ്കിൽ CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#endif
#എങ്കിൽ CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#endif
};

സ്ഥിതം സ്ഥിരം എണ്ണൽ AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

സ്ഥിതം പൂർണ്ണസംഖ്യ amf_frames_get_constraints(AVHWDeviceContext *ctx,
                                       സ്ഥിരം ശൂന്യം *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    പൂർണ്ണസംഖ്യ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    വലുപ്പം(*constraints->valid_sw_formats));
    എങ്കിൽ (!constraints->valid_sw_formats)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, വലുപ്പം(*constraints->valid_hw_formats));
    എങ്കിൽ (!constraints->valid_hw_formats)
        തിരികെ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം amf_dummy_free(ശൂന്യം *opaque, uint8_t *data)
{

}

സ്ഥിതം AVBufferRef *amf_pool_alloc(ശൂന്യം *opaque, size_t size)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_buffer_create(ശൂന്യ, 0, amf_dummy_free, hwfc, AV_BUFFER_FLAG_READONLY);
    എങ്കിൽ (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        തിരികെ ശൂന്യ;
    }
    തിരികെ buf;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ amf_frames_init(AVHWFramesContext *ctx)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        എങ്കിൽ (ctx->sw_format == supported_formats[i])
            നിർത്തുക;
    }
    എങ്കിൽ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        തിരികെ AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(വലുപ്പം(AMFSurface), ctx,
                                 &amf_pool_alloc, ശൂന്യ);

    തിരികെ 0;
}


സ്ഥിതം പൂർണ്ണസംഖ്യ amf_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    എങ്കിൽ (!frame->buf[0])
        തിരികെ AVERROR(ENOMEM);

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_AMF_SURFACE;
    frame->width   = ctx->width;
    frame->height  = ctx->height;
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     എണ്ണൽ AVHWFrameTransferDirection dir,
                                     എണ്ണൽ AVPixelFormat **formats)
{
    എണ്ണൽ AVPixelFormat *fmts;
    പൂർണ്ണസംഖ്യ i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), വലുപ്പം(*fmts));
    എങ്കിൽ (!fmts)
        തിരികെ AVERROR(ENOMEM);
    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം amf_free_amfsurface(ശൂന്യം *opaque, uint8_t *data)
{
    എങ്കിൽ(!!data){
        AMFSurface *surface = (AMFSurface*)(data);
        surface->pVtbl->Release(surface);
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ amf_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                 സ്ഥിരം AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->data[0];
    AMFPlane *plane;
    uint8_t  *dst_data[4];
    പൂർണ്ണസംഖ്യ       dst_linesize[4];
    പൂർണ്ണസംഖ്യ       planes;
    പൂർണ്ണസംഖ്യ       i;
    പൂർണ്ണസംഖ്യ       res;
    പൂർണ്ണസംഖ്യ w = FFMIN(dst->width,  src->width);
    പൂർണ്ണസംഖ്യ h = FFMIN(dst->height, src->height);

    എങ്കിൽ (dst->hw_frames_ctx->data != (uint8_t *)ctx || src->format != ctx->sw_format)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_to_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_MEMORY_HOST, format, dst->width, dst->height, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->data[0] = (uint8_t *)surface;
        dst->buf[1] = av_buffer_create((uint8_t *)surface, വലുപ്പം(surface),
                                            amf_free_amfsurface,
                                            ശൂന്യ,
                                            AV_BUFFER_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (പൂർണ്ണസംഖ്യ)surface->pVtbl->Get_Planes_എണ്ണം(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_data));

    വേണ്ടി (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_data[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_data, dst_linesize,
                   src->data, src->linesize, src->format,
                   w, h);

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ amf_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    സ്ഥിരം AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->data[0];
    AMFPlane *plane;
    uint8_t  *src_data[4];
    പൂർണ്ണസംഖ്യ       src_linesize[4];
    പൂർണ്ണസംഖ്യ       planes;
    പൂർണ്ണസംഖ്യ       i;
    പൂർണ്ണസംഖ്യ w = FFMIN(dst->width,  src->width);
    പൂർണ്ണസംഖ്യ h = FFMIN(dst->height, src->height);
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (src->hw_frames_ctx->data != (uint8_t *)ctx || dst->format != ctx->sw_format)
        തിരികെ AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_MEMORY_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (പൂർണ്ണസംഖ്യ)surface->pVtbl->Get_Planes_എണ്ണം(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_data));

    വേണ്ടി (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_data[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->data, dst->linesize,
                   src_data, src_linesize, dst->format,
                   w, h);
    തിരികെ 0;
}



സ്ഥിതം ശൂന്യം amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_RESULT          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    എങ്കിൽ (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = ശൂന്യ;
    }

    എങ്കിൽ (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    എങ്കിൽ (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    എങ്കിൽ(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = ശൂന്യ;
    }
    എങ്കിൽ (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    എങ്കിൽ (amf_ctx->lock_ctx == amf_lock_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->lock_ctx);
        av_freep(&amf_ctx->lock_ctx);
        amf_ctx->lock = ശൂന്യ;
        amf_ctx->unlock = ശൂന്യ;
    }

    amf_ctx->version = 0;
}

എണ്ണൽ AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ശൂന്യ;
    AMFGuid guid1 = IID_AMFContext1();
    ശൂന്യം * device = ശൂന്യ;

#ifdef _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = ശൂന്യ;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    സ്ഥിതം സ്ഥിരം AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    എങ്കിൽ (!amf_ctx)
        തിരികെ AMF_MEMORY_UNKNOWN;

#ifdef _WIN32
    എങ്കിൽ (AMF_IFACE_CALL(context, QueryInterface, &guid2, (ശൂന്യം**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        എങ്കിൽ (device)
            തിരികെ AMF_MEMORY_DX12;
    }

    എങ്കിൽ (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        തിരികെ AMF_MEMORY_DX11;

    എങ്കിൽ (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        തിരികെ AMF_MEMORY_DX9;
#endif

    എങ്കിൽ (AMF_IFACE_CALL(context, QueryInterface, &guid1, (ശൂന്യം**)&context1) != AMF_OK)
        തിരികെ AMF_MEMORY_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    എങ്കിൽ (device)
        തിരികെ AMF_MEMORY_VULKAN;

    തിരികെ AMF_MEMORY_UNKNOWN;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ശൂന്യ;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_RESULT res;

#ifdef _WIN32
    AMFContext2 *context2 = ശൂന്യ;
    സ്ഥിതം സ്ഥിരം AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    എങ്കിൽ (!amf_ctx->lock) {
        amf_ctx->lock_ctx = av_mallocz(വലുപ്പം(AVMutex));
        എങ്കിൽ (!amf_ctx->lock_ctx) {
            തിരികെ AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->lock_ctx, ശൂന്യ);
        amf_ctx->lock   = amf_lock_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    എങ്കിൽ (av_amf_get_memory_type(amf_ctx) != AMF_MEMORY_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        തിരികെ 0;
    }

#ifdef _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, ശൂന്യ, AMF_DX11_1);
    എങ്കിൽ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        തിരികെ 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (ശൂന്യം**)&context2);
    എങ്കിൽ (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, ശൂന്യ, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        എങ്കിൽ (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            തിരികെ 0;
        }
    } അല്ലെങ്കിൽ {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, ശൂന്യ);
    എങ്കിൽ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        തിരികെ 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#endif

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (ശൂന്യം**)&context1);
    എങ്കിൽ (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        തിരികെ AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, ശൂന്യ);
    AMF_IFACE_CALL(context1, Release);

    എങ്കിൽ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        അല്ലെങ്കിൽ
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        തിരികെ AVERROR(ENOSYS);
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ amf_load_library(AVAMFDeviceContext* amf_ctx,  ശൂന്യം* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQueryVersion_Fn version_fun;
    AMF_RESULT         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != ശൂന്യ,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != ശൂന്യ, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    version_fun = (AMFQueryVersion_Fn)dlsym(amf_ctx->library, AMF_QUERY_VERSION_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, version_fun != ശൂന്യ, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_VERSION_FUNCTION_NAME);

    amf_uint64 version;
    res = version_fun(&version);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_VERSION_FUNCTION_NAME, res);
    amf_ctx->version = version;
    res = init_fun(AMF_FULL_VERSION, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ amf_device_create(AVHWDeviceContext *device_ctx,
                              സ്ഥിരം അക്ഷരം *device,
                              AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    പൂർണ്ണസംഖ്യ ret;
    എങ്കിൽ ((ret = amf_load_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        എങ്കിൽ (ret == AMF_OK) {
            പൂർണ്ണസംഖ്യ level_ff = av_log_get_level();
            പൂർണ്ണസംഖ്യ level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            തിരഞ്ഞെടുപ്പ്(level_ff)
            {
            അവസ്ഥ AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                നിർത്തുക;
            അവസ്ഥ AV_LOG_PANIC:
            അവസ്ഥ AV_LOG_FATAL:
            അവസ്ഥ AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                നിർത്തുക;
            അവസ്ഥ AV_LOG_WARNING:
            അവസ്ഥ AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                നിർത്തുക;
            അവസ്ഥ AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                നിർത്തുക;
            അവസ്ഥ AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                നിർത്തുക;
            അവസ്ഥ AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                നിർത്തുക;
            }
            എങ്കിൽ(ctx->version == AMF_MAKE_FULL_VERSION(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
                level_amf = AMF_TRACE_WARNING;
            }

            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_CONSOLE, 0);
            trace->pVtbl->SetGlobalLevel(trace, level_amf);

            // connect AMF logger to av_log
            ctx->trace_writer = amf_writer_alloc(device_ctx);
            trace->pVtbl->RegisterWriter(trace, FFMPEG_AMF_WRITER_ID, (AMFTraceWriter*)ctx->trace_writer, 1);
            trace->pVtbl->SetWriterLevel(trace, FFMPEG_AMF_WRITER_ID, level_amf);
            trace->pVtbl->EnableWriter(trace, FFMPEG_AMF_WRITER_ID, enable_log);
            trace->pVtbl->SetWriterLevel(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, level_amf);
            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, enable_log);
        }


        ret = ctx->factory->pVtbl->CreateContext(ctx->factory, &ctx->context);
        എങ്കിൽ (ret == AMF_OK) {
            AMF_ASSIGN_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            തിരികെ 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    തിരികെ ret;
}

#എങ്കിൽ CONFIG_DXVA2
സ്ഥിതം പൂർണ്ണസംഖ്യ amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = child_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_RESULT          res;
    പൂർണ്ണസംഖ്യ ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    എങ്കിൽ (FAILED(hr)) {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        തിരികെ AVERROR_EXTERNAL;
    }

    hr = IDirect3DDeviceManager9_LockDevice(hwctx->devmgr, device_handle, &device, FALSE);
    എങ്കിൽ (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } അല്ലെങ്കിൽ {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    എങ്കിൽ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        എങ്കിൽ (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        അല്ലെങ്കിൽ
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        തിരികെ AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    തിരികെ 0;
}
#endif

#എങ്കിൽ CONFIG_D3D11VA
സ്ഥിതം പൂർണ്ണസംഖ്യ amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AMF_RESULT res;
    AVD3D11VADeviceContext *hwctx = child_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    എങ്കിൽ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        എങ്കിൽ (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        അല്ലെങ്കിൽ
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        തിരികെ AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    തിരികെ 0;
}
#endif

#എങ്കിൽ CONFIG_D3D12VA
സ്ഥിതം പൂർണ്ണസംഖ്യ amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = child_device_ctx->hwctx;
    AMF_RESULT res;
    AMFContext2 *context2 = ശൂന്യ;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (ശൂന്യം**)&context2);
    AMF_RETURN_IF_FALSE(child_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    എങ്കിൽ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        എങ്കിൽ (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        അല്ലെങ്കിൽ
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        തിരികെ AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    തിരികെ 0;
}
#endif


സ്ഥിതം പൂർണ്ണസംഖ്യ amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *child_device_ctx, AVDictionary *opts,
                              പൂർണ്ണസംഖ്യ flags)
{
#എങ്കിൽ CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#endif
    പൂർണ്ണസംഖ്യ ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    എങ്കിൽ(ret < 0)
        തിരികെ ret;

    തിരഞ്ഞെടുപ്പ് (child_device_ctx->type) {
#എങ്കിൽ CONFIG_DXVA2
    അവസ്ഥ AV_HWDEVICE_TYPE_DXVA2:
        തിരികെ amf_init_from_dxva2_device(amf_ctx, child_device_ctx);
#endif
#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
        തിരികെ amf_init_from_d3d11_device(amf_ctx, child_device_ctx);
#endif
#എങ്കിൽ CONFIG_D3D12VA
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D12VA:
        തിരികെ amf_init_from_d3d12_device(amf_ctx, child_device_ctx);
#endif
    സ്ഥിരസ്ഥിതി:
        av_log(child_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(child_device_ctx->type));
        തിരികെ AVERROR(ENOSYS);
    }
}

സ്ഥിതം ശൂന്യം amf_unmap_frame(av_unused AVHWFramesContext *unused, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ amf_map_frame(AVHWFramesContext *device_ctx, AVFrame *dst, സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    AMFSurface *surface = (AMFSurface *)src->data[0];
    AMFSurface1 *surface1 = ശൂന്യ;
    size_t *linesizes = ശൂന്യ;
    uint8_t **map = ശൂന്യ;
    പൂർണ്ണസംഖ്യ amf_mem_flags = AMF_MEMORY_CPU_NONE;
    സ്ഥിരം AMFGuid guid = IID_AMFSurface1();
    AMF_RESULT res = AMF_FAIL;
    size_t plane_എണ്ണം = 0;
    പൂർണ്ണസംഖ്യ ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != ശൂന്യ, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (ശൂന്യം**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    എങ്കിൽ (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_MEMORY_CPU_READ;

    എങ്കിൽ (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_MEMORY_CPU_WRITE;

    plane_എണ്ണം = AMF_IFACE_CALL(surface, Get_Planes_എണ്ണം);
    linesizes = av_malloc_array(വലുപ്പം(size_t), plane_എണ്ണം);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(വലുപ്പം(uint8_t *), plane_എണ്ണം);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_to_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_എണ്ണം, linesizes, (ശൂന്യം**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &amf_unmap_frame, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->width  = src->width;
    dst->height = src->height;
    av_frame_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_buffer_unref(&dst->hw_frames_ctx);

    വേണ്ടി (പൂർണ്ണസംഖ്യ plane = 0; plane < plane_എണ്ണം; ++plane)
    {
        dst->data[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    എങ്കിൽ (map)
        av_free(map);

    എങ്കിൽ (linesizes)
        av_free(linesizes);

    എങ്കിൽ (ret < 0 && surface1 != ശൂന്യ)
        AMF_IFACE_CALL(surface1, Release);

    തിരികെ ret;
}

സ്ഥിരം HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_size    = വലുപ്പം(AVAMFDeviceContext),
    .frames_hwctx_size    = വലുപ്പം(AMFFramesContext),

    .device_create        = amf_device_create,
    .device_derive        = amf_device_derive,
    .device_init          = amf_device_init,
    .device_uninit        = amf_device_uninit,
    .frames_get_constraints = amf_frames_get_constraints,
    .frames_init          = amf_frames_init,
    .frames_get_buffer    = amf_get_buffer,
    .transfer_get_formats = amf_transfer_get_formats,
    .transfer_data_to     = amf_transfer_data_to,
    .transfer_data_from   = amf_transfer_data_from,
    .map_from             = amf_map_frame,

    .pix_fmts             = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
