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

#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_amf.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_amf_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/thread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avassert.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <AMF/core/Surface.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <AMF/core/Trace.h>

#ਜੇ CONFIG_VULKAN
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_vulkan.h"
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hwcontext_d3d11va.h"
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D12VA
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hwcontext_d3d12va.h"
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COBJMACROS
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hwcontext_dxva2.h"
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
#ਅਨ੍ਤਰ੍ਭਾਵ "compat/w32dlfcn.h"
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ <dlfcn.h>
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

ਸਥਿਰ ਖਾਲੀ amf_ਤਾਲਾ_default(ਖਾਲੀ *opaque)
{
    ff_mutex_ਤਾਲਾ((AVMutex*)opaque);
}

ਸਥਿਰ ਖਾਲੀ amf_unlock_default(ਖਾਲੀ *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    ਖਾਲੀ               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

ਸਥਿਰ ਖਾਲੀ AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    ਅਚਲ wchar_t *scope, ਅਚਲ wchar_t *ਸੁਨੇਹਾ_2)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, ਸੁਨੇਹਾ_2); // \n is provided from AMF
}

ਸਥਿਰ ਖਾਲੀ AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

ਸਥਿਰ AmfTraceWriter * amf_writer_alloc(ਖਾਲੀ  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(ਆਕਾਰ(AmfTraceWriter));
    ਜੇ (!writer)
        ਵਾਪਸ ਨਿਰਾ;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    ਵਾਪਸ writer;
}

ਸਥਿਰ ਖਾਲੀ amf_writer_free(ਖਾਲੀ  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    ਖਾਲੀ *dummy;
} AMFFramesContext;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVAMFFormatMap {
    ਗਿਣਤੀ AVPixelFormat       av_format;
    ਗਿਣਤੀ AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

ਅਚਲ FormatMap format_map[] =
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

ਗਿਣਤੀ AMF_SURFACE_FORMAT av_av_ਮੰਜ਼ਿਲ_amf_format(ਗਿਣਤੀ AVPixelFormat fmt)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < amf_countof(format_map); i++) {
        ਜੇ (format_map[i].av_format == fmt) {
            ਵਾਪਸ format_map[i].amf_format;
        }
    }
    ਵਾਪਸ AMF_SURFACE_UNKNOWN;
}

ਗਿਣਤੀ AVPixelFormat av_amf_ਮੰਜ਼ਿਲ_av_format(ਗਿਣਤੀ AMF_SURFACE_FORMAT fmt)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < amf_countof(format_map); i++) {
        ਜੇ (format_map[i].amf_format == fmt) {
            ਵਾਪਸ format_map[i].av_format;
        }
    }
    ਵਾਪਸ AV_PIX_FMT_NONE;
}

ਗਿਣਤੀ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(ਗਿਣਤੀ AVColorRange color_range, ਗਿਣਤੀ AVColorSpace color_space)
{
    ਚੋਣ (color_space) {
    ਹਾਲਤ AVCOL_SPC_SMPTE170M:
        ਜੇ (color_range == AVCOL_RANGE_JPEG) {
            ਵਾਪਸ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ਭਰਿਆ_601;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        ਰੋਕੋ;
    ਹਾਲਤ AVCOL_SPC_BT709:
        ਜੇ (color_range == AVCOL_RANGE_JPEG) {
            ਵਾਪਸ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ਭਰਿਆ_709;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        ਰੋਕੋ;
    ਹਾਲਤ AVCOL_SPC_BT2020_NCL:
    ਹਾਲਤ AVCOL_SPC_BT2020_CL:
        ਜੇ (color_range == AVCOL_RANGE_JPEG) {
            ਵਾਪਸ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ਭਰਿਆ_2020;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        ਰੋਕੋ;

    ਮੂਲ:
        ਵਾਪਸ AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

ਪੂਰਨ av_amf_display_mastering_meta_ਮੰਜ਼ਿਲ_hdrmeta(ਅਚਲ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    ਜੇ (!display_meta || !hdrmeta)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (display_meta->has_luminance) {
        ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    ਜੇ (display_meta->has_primaries) {
        ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ chroma_den = 50000;
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
        hdrmeta->white_ਬਿੰਦੂ[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_ਬਿੰਦੂ_2[0])), chroma_den);
        hdrmeta->white_ਬਿੰਦੂ[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_ਬਿੰਦੂ_2[1])), chroma_den);
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_amf_light_metadata_ਮੰਜ਼ਿਲ_hdrmeta(ਅਚਲ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    ਜੇ (!light_meta || !hdrmeta)
        ਵਾਪਸ AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->max_ਚੌਖਟਾ_ਔਸਤਨ_Light_Level = (amf_uint16)light_meta->MaxFALL;

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_amf_ਕੱਢੋ_hdr_metadata(ਅਚਲ AVFrame *ਚੌਖਟਾ, AMFHDRMetadata *hdrmeta)
{
    AVFrame_Side_ਅੰਕੜੇ *sidedata;
    AVContentLightMetadata *content_light = ਨਿਰਾ;
    AVMasteringDisplayMetadata *mastering_display = ਨਿਰਾ;

    ਜੇ (!ਚੌਖਟਾ || !hdrmeta)
        ਵਾਪਸ AVERROR(EINVAL);

    sidedata = av_ਚੌਖਟਾ_get_side_ਅੰਕੜੇ(ਚੌਖਟਾ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_MASTERING_DISPLAY_METADATA);
    ਜੇ (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->ਅੰਕੜੇ;
        ਜੇ (av_amf_display_mastering_meta_ਮੰਜ਼ਿਲ_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = ਨਿਰਾ;
    }

    sidedata = av_ਚੌਖਟਾ_get_side_ਅੰਕੜੇ(ਚੌਖਟਾ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_CONTENT_LIGHT_LEVEL);
    ਜੇ (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->ਅੰਕੜੇ;
        ਜੇ (av_amf_light_metadata_ਮੰਜ਼ਿਲ_hdrmeta(content_light, hdrmeta) != 0)
            content_light = ਨਿਰਾ;
    }

    ਜੇ (!mastering_display && !content_light)
        ਵਾਪਸ AVERROR(ENODATA);

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_amf_attach_hdr_metadata(AVFrame *ਚੌਖਟਾ, ਅਚਲ AMFHDRMetadata *hdrmeta) {
    ਜੇ (!hdrmeta || !ਚੌਖਟਾ)
        ਵਾਪਸ AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
    ਅਚਲ ਪੂਰਨ chroma_den = 50000;
    ਅਚਲ ਪੂਰਨ luma_den = 10000;

    ਜੇ (!mastering)
      ਵਾਪਸ AVERROR(ENOMEM);

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

    mastering->white_ਬਿੰਦੂ_2[0] = av_make_q(hdrmeta->white_ਬਿੰਦੂ[0], chroma_den);
    mastering->white_ਬਿੰਦੂ_2[1] = av_make_q(hdrmeta->white_ਬਿੰਦੂ[1], chroma_den);

    mastering->max_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);
    mastering->min_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);

    mastering->has_luminance = 1;
    mastering->has_primaries = 1;
    ਜੇ (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);

      ਜੇ (!light)
        ਵਾਪਸ AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->max_ਚੌਖਟਾ_ਔਸਤਨ_Light_Level;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#ਜੇ CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#ਜੇ_ਅੰਤ
};

ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

ਸਥਿਰ ਪੂਰਨ amf_ਚੌਖਟੇ_get_constraints(AVHWDeviceContext *ctx,
                                       ਅਚਲ ਖਾਲੀ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ਪੂਰਨ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ਆਕਾਰ(*constraints->valid_sw_formats));
    ਜੇ (!constraints->valid_sw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ਆਕਾਰ(*constraints->valid_hw_formats));
    ਜੇ (!constraints->valid_hw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ amf_dummy_free(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{

}

ਸਥਿਰ AVBufferRef *amf_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_ਬਫਰ_create(ਨਿਰਾ, 0, amf_dummy_free, hwfc, AV_ਬਫਰ_FLAG_READONLY);
    ਜੇ (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ buf;
}

ਸਥਿਰ ਪੂਰਨ amf_ਚੌਖਟੇ_init(AVHWFramesContext *ctx)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ਜੇ (ctx->sw_format == supported_formats[i])
            ਰੋਕੋ;
    }
    ਜੇ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ =
            av_ਬਫਰ_pool_init2(ਆਕਾਰ(AMFSurface), ctx,
                                 &amf_pool_alloc, ਨਿਰਾ);

    ਵਾਪਸ 0;
}


ਸਥਿਰ ਪੂਰਨ amf_get_ਬਫਰ(AVHWFramesContext *ctx, AVFrame *ਚੌਖਟਾ)
{
    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(ctx->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    ਚੌਖਟਾ->ਅੰਕੜੇ[0] = ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;
    ਚੌਖਟਾ->format  = AV_PIX_FMT_AMF_SURFACE;
    ਚੌਖਟਾ->ਚੌੜਾਈ   = ctx->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ  = ctx->ਉਚਾਈ;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                     ਗਿਣਤੀ AVPixelFormat **formats)
{
    ਗਿਣਤੀ AVPixelFormat *fmts;
    ਪੂਰਨ i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);
    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ amf_free_amfsurface(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    ਜੇ(!!ਅੰਕੜੇ){
        AMFSurface *surface = (AMFSurface*)(ਅੰਕੜੇ);
        surface->pVtbl->Release(surface);
    }
}

ਸਥਿਰ ਪੂਰਨ amf_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(AVHWFramesContext *ctx, AVFrame *dst,
                                 ਅਚਲ AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->ਅੰਕੜੇ[0];
    AMFPlane *plane;
    uint8_t  *dst_ਅੰਕੜੇ[4];
    ਪੂਰਨ       dst_linesize[4];
    ਪੂਰਨ       planes;
    ਪੂਰਨ       i;
    ਪੂਰਨ       res;
    ਪੂਰਨ w = FFMIN(dst->ਚੌੜਾਈ,  src->ਚੌੜਾਈ);
    ਪੂਰਨ h = FFMIN(dst->ਉਚਾਈ, src->ਉਚਾਈ);

    ਜੇ (dst->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ != (uint8_t *)ctx || src->format != ctx->sw_format)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_ਮੰਜ਼ਿਲ_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_ਸਮ੍ਰਿਤੀ_HOST, format, dst->ਚੌੜਾਈ, dst->ਉਚਾਈ, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->ਅੰਕੜੇ[0] = (uint8_t *)surface;
        dst->buf[1] = av_ਬਫਰ_create((uint8_t *)surface, ਆਕਾਰ(surface),
                                            amf_free_amfsurface,
                                            ਨਿਰਾ,
                                            AV_ਬਫਰ_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (ਪੂਰਨ)surface->pVtbl->Get_Planes_ਗਿਣਤੀ(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_ਅੰਕੜੇ));

    ਲਈ (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_ਅੰਕੜੇ[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_ਅੰਕੜੇ, dst_linesize,
                   src->ਅੰਕੜੇ, src->linesize, src->format,
                   w, h);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ amf_transfer_ਅੰਕੜੇ_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ਅਚਲ AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->ਅੰਕੜੇ[0];
    AMFPlane *plane;
    uint8_t  *src_ਅੰਕੜੇ[4];
    ਪੂਰਨ       src_linesize[4];
    ਪੂਰਨ       planes;
    ਪੂਰਨ       i;
    ਪੂਰਨ w = FFMIN(dst->ਚੌੜਾਈ,  src->ਚੌੜਾਈ);
    ਪੂਰਨ h = FFMIN(dst->ਉਚਾਈ, src->ਉਚਾਈ);
    ਪੂਰਨ ret;

    ਜੇ (src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ != (uint8_t *)ctx || dst->format != ctx->sw_format)
        ਵਾਪਸ AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_ਸਮ੍ਰਿਤੀ_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (ਪੂਰਨ)surface->pVtbl->Get_Planes_ਗਿਣਤੀ(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_ਅੰਕੜੇ));

    ਲਈ (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_ਅੰਕੜੇ[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->ਅੰਕੜੇ, dst->linesize,
                   src_ਅੰਕੜੇ, src_linesize, dst->format,
                   w, h);
    ਵਾਪਸ 0;
}



ਸਥਿਰ ਖਾਲੀ amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_ਨਤੀਜਾ          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    ਜੇ (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = ਨਿਰਾ;
    }

    ਜੇ (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    ਜੇ (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    ਜੇ(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = ਨਿਰਾ;
    }
    ਜੇ (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    ਜੇ (amf_ctx->ਤਾਲਾ_ctx == amf_ਤਾਲਾ_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->ਤਾਲਾ_ctx);
        av_freep(&amf_ctx->ਤਾਲਾ_ctx);
        amf_ctx->ਤਾਲਾ = ਨਿਰਾ;
        amf_ctx->unlock = ਨਿਰਾ;
    }

    amf_ctx->ਸੰਸਕਰਣ = 0;
}

ਗਿਣਤੀ AMF_ਸਮ੍ਰਿਤੀ_TYPE av_amf_get_ਸਮ੍ਰਿਤੀ_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ਨਿਰਾ;
    AMFGuid guid1 = IID_AMFContext1();
    ਖਾਲੀ * device = ਨਿਰਾ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = ਨਿਰਾ;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    ਸਥਿਰ ਅਚਲ AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#ਜੇ_ਅੰਤ

    ਜੇ (!amf_ctx)
        ਵਾਪਸ AMF_ਸਮ੍ਰਿਤੀ_UNKNOWN;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    ਜੇ (AMF_IFACE_CALL(context, QueryInterface, &guid2, (ਖਾਲੀ**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        ਜੇ (device)
            ਵਾਪਸ AMF_ਸਮ੍ਰਿਤੀ_DX12;
    }

    ਜੇ (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        ਵਾਪਸ AMF_ਸਮ੍ਰਿਤੀ_DX11;

    ਜੇ (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        ਵਾਪਸ AMF_ਸਮ੍ਰਿਤੀ_DX9;
#ਜੇ_ਅੰਤ

    ਜੇ (AMF_IFACE_CALL(context, QueryInterface, &guid1, (ਖਾਲੀ**)&context1) != AMF_OK)
        ਵਾਪਸ AMF_ਸਮ੍ਰਿਤੀ_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    ਜੇ (device)
        ਵਾਪਸ AMF_ਸਮ੍ਰਿਤੀ_VULKAN;

    ਵਾਪਸ AMF_ਸਮ੍ਰਿਤੀ_UNKNOWN;
}

ਸਥਿਰ ਪੂਰਨ amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ਨਿਰਾ;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_ਨਤੀਜਾ res;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    AMFContext2 *context2 = ਨਿਰਾ;
    ਸਥਿਰ ਅਚਲ AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#ਜੇ_ਅੰਤ

    ਜੇ (!amf_ctx->ਤਾਲਾ) {
        amf_ctx->ਤਾਲਾ_ctx = av_mallocz(ਆਕਾਰ(AVMutex));
        ਜੇ (!amf_ctx->ਤਾਲਾ_ctx) {
            ਵਾਪਸ AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->ਤਾਲਾ_ctx, ਨਿਰਾ);
        amf_ctx->ਤਾਲਾ   = amf_ਤਾਲਾ_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    ਜੇ (av_amf_get_ਸਮ੍ਰਿਤੀ_type(amf_ctx) != AMF_ਸਮ੍ਰਿਤੀ_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        ਵਾਪਸ 0;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, ਨਿਰਾ, AMF_DX11_1);
    ਜੇ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        ਵਾਪਸ 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (ਖਾਲੀ**)&context2);
    ਜੇ (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, ਨਿਰਾ, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        ਜੇ (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            ਵਾਪਸ 0;
        }
    } ਨਹੀਂਤਾਂ {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, ਨਿਰਾ);
    ਜੇ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        ਵਾਪਸ 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#ਜੇ_ਅੰਤ

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (ਖਾਲੀ**)&context1);
    ਜੇ (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, ਨਿਰਾ);
    AMF_IFACE_CALL(context1, Release);

    ਜੇ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } ਨਹੀਂਤਾਂ {
        ਜੇ (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        ਨਹੀਂਤਾਂ
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ amf_ਲੱਦੋ_library(AVAMFDeviceContext* amf_ctx,  ਖਾਲੀ* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQuery_ਸੰਸਕਰਣ_Fn ਸੰਸਕਰਣ_fun;
    AMF_ਨਤੀਜਾ         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != ਨਿਰਾ,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != ਨਿਰਾ, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    ਸੰਸਕਰਣ_fun = (AMFQuery_ਸੰਸਕਰਣ_Fn)dlsym(amf_ctx->library, AMF_QUERY_ਸੰਸਕਰਣ_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, ਸੰਸਕਰਣ_fun != ਨਿਰਾ, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_ਸੰਸਕਰਣ_FUNCTION_NAME);

    amf_uint64 ਸੰਸਕਰਣ;
    res = ਸੰਸਕਰਣ_fun(&ਸੰਸਕਰਣ);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_ਸੰਸਕਰਣ_FUNCTION_NAME, res);
    amf_ctx->ਸੰਸਕਰਣ = ਸੰਸਕਰਣ;
    res = init_fun(AMF_ਭਰਿਆ_ਸੰਸਕਰਣ, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ amf_device_create(AVHWDeviceContext *device_ctx,
                              ਅਚਲ ਅੱਖਰ *device,
                              AVDictionary *opts, ਪੂਰਨ flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    ਪੂਰਨ ret;
    ਜੇ ((ret = amf_ਲੱਦੋ_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        ਜੇ (ret == AMF_OK) {
            ਪੂਰਨ level_ff = av_log_get_level();
            ਪੂਰਨ level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            ਚੋਣ(level_ff)
            {
            ਹਾਲਤ AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                ਰੋਕੋ;
            ਹਾਲਤ AV_LOG_PANIC:
            ਹਾਲਤ AV_LOG_FATAL:
            ਹਾਲਤ AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                ਰੋਕੋ;
            ਹਾਲਤ AV_LOG_WARNING:
            ਹਾਲਤ AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                ਰੋਕੋ;
            ਹਾਲਤ AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                ਰੋਕੋ;
            ਹਾਲਤ AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                ਰੋਕੋ;
            ਹਾਲਤ AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                ਰੋਕੋ;
            }
            ਜੇ(ctx->ਸੰਸਕਰਣ == AMF_MAKE_ਭਰਿਆ_ਸੰਸਕਰਣ(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
                level_amf = AMF_TRACE_WARNING;
            }

            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_CONSOLE, 0);
            trace->pVtbl->ਸੈੱਟ_Global_Level(trace, level_amf);

            // connect AMF logger to av_log
            ctx->trace_writer = amf_writer_alloc(device_ctx);
            trace->pVtbl->ਰਜਿਸਟਰ_Writer(trace, FFMPEG_AMF_WRITER_ID, (AMFTraceWriter*)ctx->trace_writer, 1);
            trace->pVtbl->ਸੈੱਟ_Writer_Level(trace, FFMPEG_AMF_WRITER_ID, level_amf);
            trace->pVtbl->EnableWriter(trace, FFMPEG_AMF_WRITER_ID, enable_log);
            trace->pVtbl->ਸੈੱਟ_Writer_Level(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, level_amf);
            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, enable_log);
        }


        ret = ctx->factory->pVtbl->CreateContext(ctx->factory, &ctx->context);
        ਜੇ (ret == AMF_OK) {
            AMF_ਸੌਂਪੋ_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            ਵਾਪਸ 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    ਵਾਪਸ ret;
}

#ਜੇ CONFIG_DXVA2
ਸਥਿਰ ਪੂਰਨ amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *ਬੱਚਾ_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = ਬੱਚਾ_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_ਨਤੀਜਾ          res;
    ਪੂਰਨ ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    ਜੇ (FAILED(hr)) {
        av_log(ਬੱਚਾ_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)hr);
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    hr = IDirect3_DDevice_Manager9_ਤਾਲਾ_Device(hwctx->devmgr, device_handle, &device, FALSE);
    ਜੇ (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } ਨਹੀਂਤਾਂ {
        av_log(ਬੱਚਾ_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    ਜੇ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ਜੇ (res == AMF_NOT_SUPPORTED)
            av_log(ਬੱਚਾ_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        ਨਹੀਂਤਾਂ
            av_log(ਬੱਚਾ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        ਵਾਪਸ AVERROR(ENODEV);
    }
    av_log(ਬੱਚਾ_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_D3D11VA
ਸਥਿਰ ਪੂਰਨ amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *ਬੱਚਾ_device_ctx)
{
    AMF_ਨਤੀਜਾ res;
    AVD3D11VADeviceContext *hwctx = ਬੱਚਾ_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    ਜੇ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ਜੇ (res == AMF_NOT_SUPPORTED)
            av_log(ਬੱਚਾ_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        ਨਹੀਂਤਾਂ
            av_log(ਬੱਚਾ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        ਵਾਪਸ AVERROR(ENODEV);
    }
    av_log(ਬੱਚਾ_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_D3D12VA
ਸਥਿਰ ਪੂਰਨ amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *ਬੱਚਾ_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = ਬੱਚਾ_device_ctx->hwctx;
    AMF_ਨਤੀਜਾ res;
    AMFContext2 *context2 = ਨਿਰਾ;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (ਖਾਲੀ**)&context2);
    AMF_RETURN_IF_FALSE(ਬੱਚਾ_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    ਜੇ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ਜੇ (res == AMF_NOT_SUPPORTED)
            av_log(ਬੱਚਾ_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        ਨਹੀਂਤਾਂ
            av_log(ਬੱਚਾ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        ਵਾਪਸ AVERROR(ENODEV);
    }
    av_log(ਬੱਚਾ_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ


ਸਥਿਰ ਪੂਰਨ amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *ਬੱਚਾ_device_ctx, AVDictionary *opts,
                              ਪੂਰਨ flags)
{
#ਜੇ CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#ਜੇ_ਅੰਤ
    ਪੂਰਨ ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    ਜੇ(ret < 0)
        ਵਾਪਸ ret;

    ਚੋਣ (ਬੱਚਾ_device_ctx->type) {
#ਜੇ CONFIG_DXVA2
    ਹਾਲਤ AV_HWDEVICE_TYPE_DXVA2:
        ਵਾਪਸ amf_init_from_dxva2_device(amf_ctx, ਬੱਚਾ_device_ctx);
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
        ਵਾਪਸ amf_init_from_d3d11_device(amf_ctx, ਬੱਚਾ_device_ctx);
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D12VA
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D12VA:
        ਵਾਪਸ amf_init_from_d3d12_device(amf_ctx, ਬੱਚਾ_device_ctx);
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        av_log(ਬੱਚਾ_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(ਬੱਚਾ_device_ctx->type));
        ਵਾਪਸ AVERROR(ENOSYS);
    }
}

ਸਥਿਰ ਖਾਲੀ amf_unmap_ਚੌਖਟਾ(av_ਅਣਵਰਤਿਆ AVHWFramesContext *ਅਣਵਰਤਿਆ, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

ਸਥਿਰ ਪੂਰਨ amf_map_ਚੌਖਟਾ(AVHWFramesContext *device_ctx, AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    AMFSurface *surface = (AMFSurface *)src->ਅੰਕੜੇ[0];
    AMFSurface1 *surface1 = ਨਿਰਾ;
    size_t *linesizes = ਨਿਰਾ;
    uint8_t **map = ਨਿਰਾ;
    ਪੂਰਨ amf_mem_flags = AMF_ਸਮ੍ਰਿਤੀ_CPU_NONE;
    ਅਚਲ AMFGuid guid = IID_AMFSurface1();
    AMF_ਨਤੀਜਾ res = AMF_FAIL;
    size_t plane_ਗਿਣਤੀ = 0;
    ਪੂਰਨ ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != ਨਿਰਾ, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (ਖਾਲੀ**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    ਜੇ (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_ਸਮ੍ਰਿਤੀ_CPU_READ;

    ਜੇ (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_ਸਮ੍ਰਿਤੀ_CPU_WRITE;

    plane_ਗਿਣਤੀ = AMF_IFACE_CALL(surface, Get_Planes_ਗਿਣਤੀ);
    linesizes = av_malloc_array(ਆਕਾਰ(size_t), plane_ਗਿਣਤੀ);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(ਆਕਾਰ(uint8_t *), plane_ਗਿਣਤੀ);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_ਮੰਜ਼ਿਲ_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_ਗਿਣਤੀ, linesizes, (ਖਾਲੀ**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_ਚੌਖਟੇ_ctx, dst, src, &amf_unmap_ਚੌਖਟਾ, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;
    av_ਚੌਖਟਾ_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_ਬਫਰ_unref(&dst->hw_ਚੌਖਟੇ_ctx);

    ਲਈ (ਪੂਰਨ plane = 0; plane < plane_ਗਿਣਤੀ; ++plane)
    {
        dst->ਅੰਕੜੇ[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    ਜੇ (map)
        av_free(map);

    ਜੇ (linesizes)
        av_free(linesizes);

    ਜੇ (ret < 0 && surface1 != ਨਿਰਾ)
        AMF_IFACE_CALL(surface1, Release);

    ਵਾਪਸ ret;
}

ਅਚਲ HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_ਮਾਪ    = ਆਕਾਰ(AVAMFDeviceContext),
    .ਚੌਖਟੇ_hwctx_ਮਾਪ    = ਆਕਾਰ(AMFFramesContext),

    .device_create        = amf_device_create,
    .device_derive        = amf_device_derive,
    .device_init          = amf_device_init,
    .device_uninit        = amf_device_uninit,
    .ਚੌਖਟੇ_get_constraints = amf_ਚੌਖਟੇ_get_constraints,
    .ਚੌਖਟੇ_init          = amf_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_get_ਬਫਰ    = amf_get_ਬਫਰ,
    .transfer_get_formats = amf_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ     = amf_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ,
    .transfer_ਅੰਕੜੇ_from   = amf_transfer_ਅੰਕੜੇ_from,
    .map_from             = amf_map_ਚੌਖਟਾ,

    .pix_fmts             = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
