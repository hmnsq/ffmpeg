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

#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_amf.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_amf_internal.h"

#ಅನ್ತರ್ಭಾವ "libavutil/thread.h"
#ಅನ್ತರ್ಭಾವ "libavutil/avassert.h"

#ಅನ್ತರ್ಭಾವ <AMF/core/Surface.h>
#ಅನ್ತರ್ಭಾವ <AMF/core/Trace.h>

#ಆದರೆ CONFIG_VULKAN
#ಅನ್ತರ್ಭಾವ "hwcontext_vulkan.h"
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
#ಅನ್ತರ್ಭಾವ "libavutil/hwcontext_d3d11va.h"
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D12VA
#ಅನ್ತರ್ಭಾವ "libavutil/hwcontext_d3d12va.h"
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS
#ಅನ್ತರ್ಭಾವ "libavutil/hwcontext_dxva2.h"
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
#ಅನ್ತರ್ಭಾವ "compat/w32dlfcn.h"
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ <dlfcn.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

ಸ್ಥಿರ ಶೂನ್ಯ amf_ಬೀಗ_default(ಶೂನ್ಯ *opaque)
{
    ff_mutex_ಬೀಗ((AVMutex*)opaque);
}

ಸ್ಥಿರ ಶೂನ್ಯ amf_unlock_default(ಶೂನ್ಯ *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    ಶೂನ್ಯ               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

ಸ್ಥಿರ ಶೂನ್ಯ AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    ಸ್ಥಿರಾಂಕ wchar_t *scope, ಸ್ಥಿರಾಂಕ wchar_t *ಸಂದೇಶ_2)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, ಸಂದೇಶ_2); // \n is provided from AMF
}

ಸ್ಥಿರ ಶೂನ್ಯ AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

ಸ್ಥಿರ AmfTraceWriter * amf_writer_alloc(ಶೂನ್ಯ  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(ಗಾತ್ರ(AmfTraceWriter));
    ಆದರೆ (!writer)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    ಹಿಂತಿರುಗಿ writer;
}

ಸ್ಥಿರ ಶೂನ್ಯ amf_writer_free(ಶೂನ್ಯ  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    ಶೂನ್ಯ *dummy;
} AMFFramesContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVAMFFormatMap {
    ಎಣಿಕೆ AVPixelFormat       av_format;
    ಎಣಿಕೆ AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

ಸ್ಥಿರಾಂಕ FormatMap format_map[] =
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

ಎಣಿಕೆ AMF_SURFACE_FORMAT av_av_ಗಮ್ಯ_amf_format(ಎಣಿಕೆ AVPixelFormat fmt)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < amf_countof(format_map); i++) {
        ಆದರೆ (format_map[i].av_format == fmt) {
            ಹಿಂತಿರುಗಿ format_map[i].amf_format;
        }
    }
    ಹಿಂತಿರುಗಿ AMF_SURFACE_UNKNOWN;
}

ಎಣಿಕೆ AVPixelFormat av_amf_ಗಮ್ಯ_av_format(ಎಣಿಕೆ AMF_SURFACE_FORMAT fmt)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < amf_countof(format_map); i++) {
        ಆದರೆ (format_map[i].amf_format == fmt) {
            ಹಿಂತಿರುಗಿ format_map[i].av_format;
        }
    }
    ಹಿಂತಿರುಗಿ AV_PIX_FMT_NONE;
}

ಎಣಿಕೆ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(ಎಣಿಕೆ AVColorRange color_range, ಎಣಿಕೆ AVColorSpace color_space)
{
    ಆಯ್ಕೆ (color_space) {
    ಸ್ಥಿತಿ AVCOL_SPC_SMPTE170M:
        ಆದರೆ (color_range == AVCOL_RANGE_JPEG) {
            ಹಿಂತಿರುಗಿ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ತುಂಬಿದ_601;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AVCOL_SPC_BT709:
        ಆದರೆ (color_range == AVCOL_RANGE_JPEG) {
            ಹಿಂತಿರುಗಿ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ತುಂಬಿದ_709;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AVCOL_SPC_BT2020_NCL:
    ಸ್ಥಿತಿ AVCOL_SPC_BT2020_CL:
        ಆದರೆ (color_range == AVCOL_RANGE_JPEG) {
            ಹಿಂತಿರುಗಿ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ತುಂಬಿದ_2020;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

ಪೂರ್ಣಾಂಕ av_amf_display_mastering_meta_ಗಮ್ಯ_hdrmeta(ಸ್ಥಿರಾಂಕ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    ಆದರೆ (!display_meta || !hdrmeta)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (display_meta->has_luminance) {
        ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    ಆದರೆ (display_meta->has_primaries) {
        ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ chroma_den = 50000;
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
        hdrmeta->white_ಬಿಂದು[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_ಬಿಂದು_2[0])), chroma_den);
        hdrmeta->white_ಬಿಂದು[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_ಬಿಂದು_2[1])), chroma_den);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_amf_light_metadata_ಗಮ್ಯ_hdrmeta(ಸ್ಥಿರಾಂಕ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    ಆದರೆ (!light_meta || !hdrmeta)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->max_ಚೌಕಟ್ಟು_ಸರಾಸರಿ_ಮೌಲ್ಯ_Light_Level = (amf_uint16)light_meta->MaxFALL;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_amf_ಹೊರತೆಗೆ_hdr_metadata(ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು, AMFHDRMetadata *hdrmeta)
{
    AVFrame_Side_ದತ್ತಾಂಶ *sidedata;
    AVContentLightMetadata *content_light = ಖಾಲಿ;
    AVMasteringDisplayMetadata *mastering_display = ಖಾಲಿ;

    ಆದರೆ (!ಚೌಕಟ್ಟು || !hdrmeta)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    sidedata = av_ಚೌಕಟ್ಟು_get_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_MASTERING_DISPLAY_METADATA);
    ಆದರೆ (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->ದತ್ತಾಂಶ;
        ಆದರೆ (av_amf_display_mastering_meta_ಗಮ್ಯ_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = ಖಾಲಿ;
    }

    sidedata = av_ಚೌಕಟ್ಟು_get_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_CONTENT_LIGHT_LEVEL);
    ಆದರೆ (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->ದತ್ತಾಂಶ;
        ಆದರೆ (av_amf_light_metadata_ಗಮ್ಯ_hdrmeta(content_light, hdrmeta) != 0)
            content_light = ಖಾಲಿ;
    }

    ಆದರೆ (!mastering_display && !content_light)
        ಹಿಂತಿರುಗಿ AVERROR(ENODATA);

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_amf_attach_hdr_metadata(AVFrame *ಚೌಕಟ್ಟು, ಸ್ಥಿರಾಂಕ AMFHDRMetadata *hdrmeta) {
    ಆದರೆ (!hdrmeta || !ಚೌಕಟ್ಟು)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ chroma_den = 50000;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ luma_den = 10000;

    ಆದರೆ (!mastering)
      ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

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

    mastering->white_ಬಿಂದು_2[0] = av_make_q(hdrmeta->white_ಬಿಂದು[0], chroma_den);
    mastering->white_ಬಿಂದು_2[1] = av_make_q(hdrmeta->white_ಬಿಂದು[1], chroma_den);

    mastering->max_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);
    mastering->min_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);

    mastering->has_luminance = 1;
    mastering->has_primaries = 1;
    ಆದರೆ (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);

      ಆದರೆ (!light)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->max_ಚೌಕಟ್ಟು_ಸರಾಸರಿ_ಮೌಲ್ಯ_Light_Level;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#ಆದರೆ CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#ಆದರೆ_ಅಂತ್ಯ
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *ctx,
                                       ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ಪೂರ್ಣಾಂಕ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ಗಾತ್ರ(*constraints->valid_sw_formats));
    ಆದರೆ (!constraints->valid_sw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ಗಾತ್ರ(*constraints->valid_hw_formats));
    ಆದರೆ (!constraints->valid_hw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ amf_dummy_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{

}

ಸ್ಥಿರ AVBufferRef *amf_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_ಬಫರ್_create(ಖಾಲಿ, 0, amf_dummy_free, hwfc, AV_ಬಫರ್_FLAG_READONLY);
    ಆದರೆ (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ buf;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *ctx)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ಆದರೆ (ctx->sw_format == supported_formats[i])
            ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_ಆಂತರಿಕ =
            av_ಬಫರ್_pool_init2(ಗಾತ್ರ(AMFSurface), ctx,
                                 &amf_pool_alloc, ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ 0;
}


ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_get_ಬಫರ್(AVHWFramesContext *ctx, AVFrame *ಚೌಕಟ್ಟು)
{
    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(ctx->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] = ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;
    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_AMF_SURFACE;
    ಚೌಕಟ್ಟು->ಅಗಲ   = ctx->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = ctx->ಎತ್ತರ;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                     ಎಣಿಕೆ AVPixelFormat **formats)
{
    ಎಣಿಕೆ AVPixelFormat *fmts;
    ಪೂರ್ಣಾಂಕ i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ amf_free_amfsurface(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    ಆದರೆ(!!ದತ್ತಾಂಶ){
        AMFSurface *surface = (AMFSurface*)(ದತ್ತಾಂಶ);
        surface->pVtbl->Release(surface);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(AVHWFramesContext *ctx, AVFrame *dst,
                                 ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->ದತ್ತಾಂಶ[0];
    AMFPlane *plane;
    uint8_t  *dst_ದತ್ತಾಂಶ[4];
    ಪೂರ್ಣಾಂಕ       dst_linesize[4];
    ಪೂರ್ಣಾಂಕ       planes;
    ಪೂರ್ಣಾಂಕ       i;
    ಪೂರ್ಣಾಂಕ       res;
    ಪೂರ್ಣಾಂಕ w = FFMIN(dst->ಅಗಲ,  src->ಅಗಲ);
    ಪೂರ್ಣಾಂಕ h = FFMIN(dst->ಎತ್ತರ, src->ಎತ್ತರ);

    ಆದರೆ (dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ != (uint8_t *)ctx || src->format != ctx->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_ಗಮ್ಯ_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_ಸ್ಮರಣೆ_HOST, format, dst->ಅಗಲ, dst->ಎತ್ತರ, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->ದತ್ತಾಂಶ[0] = (uint8_t *)surface;
        dst->buf[1] = av_ಬಫರ್_create((uint8_t *)surface, ಗಾತ್ರ(surface),
                                            amf_free_amfsurface,
                                            ಖಾಲಿ,
                                            AV_ಬಫರ್_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (ಪೂರ್ಣಾಂಕ)surface->pVtbl->Get_Planes_ಎಣಿಕೆ(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_ದತ್ತಾಂಶ));

    ಗಾಗಿ (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_ದತ್ತಾಂಶ[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_ದತ್ತಾಂಶ, dst_linesize,
                   src->ದತ್ತಾಂಶ, src->linesize, src->format,
                   w, h);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_transfer_ದತ್ತಾಂಶ_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->ದತ್ತಾಂಶ[0];
    AMFPlane *plane;
    uint8_t  *src_ದತ್ತಾಂಶ[4];
    ಪೂರ್ಣಾಂಕ       src_linesize[4];
    ಪೂರ್ಣಾಂಕ       planes;
    ಪೂರ್ಣಾಂಕ       i;
    ಪೂರ್ಣಾಂಕ w = FFMIN(dst->ಅಗಲ,  src->ಅಗಲ);
    ಪೂರ್ಣಾಂಕ h = FFMIN(dst->ಎತ್ತರ, src->ಎತ್ತರ);
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ != (uint8_t *)ctx || dst->format != ctx->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_ಸ್ಮರಣೆ_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (ಪೂರ್ಣಾಂಕ)surface->pVtbl->Get_Planes_ಎಣಿಕೆ(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_ದತ್ತಾಂಶ));

    ಗಾಗಿ (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_ದತ್ತಾಂಶ[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->ದತ್ತಾಂಶ, dst->linesize,
                   src_ದತ್ತಾಂಶ, src_linesize, dst->format,
                   w, h);
    ಹಿಂತಿರುಗಿ 0;
}



ಸ್ಥಿರ ಶೂನ್ಯ amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_ಫಲಿತಾಂಶ          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    ಆದರೆ (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = ಖಾಲಿ;
    }

    ಆದರೆ (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    ಆದರೆ (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    ಆದರೆ(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = ಖಾಲಿ;
    }
    ಆದರೆ (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    ಆದರೆ (amf_ctx->ಬೀಗ_ctx == amf_ಬೀಗ_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->ಬೀಗ_ctx);
        av_freep(&amf_ctx->ಬೀಗ_ctx);
        amf_ctx->ಬೀಗ_2 = ಖಾಲಿ;
        amf_ctx->unlock = ಖಾಲಿ;
    }

    amf_ctx->ಆವೃತ್ತಿ = 0;
}

ಎಣಿಕೆ AMF_ಸ್ಮರಣೆ_TYPE av_amf_get_ಸ್ಮರಣೆ_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ಖಾಲಿ;
    AMFGuid guid1 = IID_AMFContext1();
    ಶೂನ್ಯ * device = ಖಾಲಿ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = ಖಾಲಿ;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!amf_ctx)
        ಹಿಂತಿರುಗಿ AMF_ಸ್ಮರಣೆ_UNKNOWN;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    ಆದರೆ (AMF_IFACE_CALL(context, QueryInterface, &guid2, (ಶೂನ್ಯ**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        ಆದರೆ (device)
            ಹಿಂತಿರುಗಿ AMF_ಸ್ಮರಣೆ_DX12;
    }

    ಆದರೆ (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        ಹಿಂತಿರುಗಿ AMF_ಸ್ಮರಣೆ_DX11;

    ಆದರೆ (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        ಹಿಂತಿರುಗಿ AMF_ಸ್ಮರಣೆ_DX9;
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (AMF_IFACE_CALL(context, QueryInterface, &guid1, (ಶೂನ್ಯ**)&context1) != AMF_OK)
        ಹಿಂತಿರುಗಿ AMF_ಸ್ಮರಣೆ_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    ಆದರೆ (device)
        ಹಿಂತಿರುಗಿ AMF_ಸ್ಮರಣೆ_VULKAN;

    ಹಿಂತಿರುಗಿ AMF_ಸ್ಮರಣೆ_UNKNOWN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ಖಾಲಿ;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_ಫಲಿತಾಂಶ res;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    AMFContext2 *context2 = ಖಾಲಿ;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!amf_ctx->ಬೀಗ_2) {
        amf_ctx->ಬೀಗ_ctx = av_mallocz(ಗಾತ್ರ(AVMutex));
        ಆದರೆ (!amf_ctx->ಬೀಗ_ctx) {
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->ಬೀಗ_ctx, ಖಾಲಿ);
        amf_ctx->ಬೀಗ_2   = amf_ಬೀಗ_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    ಆದರೆ (av_amf_get_ಸ್ಮರಣೆ_type(amf_ctx) != AMF_ಸ್ಮರಣೆ_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        ಹಿಂತಿರುಗಿ 0;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, ಖಾಲಿ, AMF_DX11_1);
    ಆದರೆ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        ಹಿಂತಿರುಗಿ 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (ಶೂನ್ಯ**)&context2);
    ಆದರೆ (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, ಖಾಲಿ, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        ಆದರೆ (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            ಹಿಂತಿರುಗಿ 0;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, ಖಾಲಿ);
    ಆದರೆ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        ಹಿಂತಿರುಗಿ 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#ಆದರೆ_ಅಂತ್ಯ

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (ಶೂನ್ಯ**)&context1);
    ಆದರೆ (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, ಖಾಲಿ);
    AMF_IFACE_CALL(context1, Release);

    ಆದರೆ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        ಇಲ್ಲದಿದ್ದರೆ
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_ತುಂಬು_library(AVAMFDeviceContext* amf_ctx,  ಶೂನ್ಯ* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQuery_ಆವೃತ್ತಿ_Fn ಆವೃತ್ತಿ_fun;
    AMF_ಫಲಿತಾಂಶ         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != ಖಾಲಿ,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != ಖಾಲಿ, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    ಆವೃತ್ತಿ_fun = (AMFQuery_ಆವೃತ್ತಿ_Fn)dlsym(amf_ctx->library, AMF_QUERY_ಆವೃತ್ತಿ_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, ಆವೃತ್ತಿ_fun != ಖಾಲಿ, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_ಆವೃತ್ತಿ_FUNCTION_NAME);

    amf_uint64 ಆವೃತ್ತಿ;
    res = ಆವೃತ್ತಿ_fun(&ಆವೃತ್ತಿ);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_ಆವೃತ್ತಿ_FUNCTION_NAME, res);
    amf_ctx->ಆವೃತ್ತಿ = ಆವೃತ್ತಿ;
    res = init_fun(AMF_ತುಂಬಿದ_ಆವೃತ್ತಿ, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_device_create(AVHWDeviceContext *device_ctx,
                              ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                              AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    ಪೂರ್ಣಾಂಕ ret;
    ಆದರೆ ((ret = amf_ತುಂಬು_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        ಆದರೆ (ret == AMF_OK) {
            ಪೂರ್ಣಾಂಕ level_ff = av_log_get_level();
            ಪೂರ್ಣಾಂಕ level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            ಆಯ್ಕೆ(level_ff)
            {
            ಸ್ಥಿತಿ AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_LOG_PANIC:
            ಸ್ಥಿತಿ AV_LOG_FATAL:
            ಸ್ಥಿತಿ AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_LOG_WARNING:
            ಸ್ಥಿತಿ AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                ನಿಲ್ಲಿಸು;
            }
            ಆದರೆ(ctx->ಆವೃತ್ತಿ == AMF_MAKE_ತುಂಬಿದ_ಆವೃತ್ತಿ(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
                level_amf = AMF_TRACE_WARNING;
            }

            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_CONSOLE, 0);
            trace->pVtbl->ಗಣ_Global_Level(trace, level_amf);

            // connect AMF logger to av_log
            ctx->trace_writer = amf_writer_alloc(device_ctx);
            trace->pVtbl->ರಿಜಿಸ್ಟರ್_Writer(trace, FFMPEG_AMF_WRITER_ID, (AMFTraceWriter*)ctx->trace_writer, 1);
            trace->pVtbl->ಗಣ_Writer_Level(trace, FFMPEG_AMF_WRITER_ID, level_amf);
            trace->pVtbl->EnableWriter(trace, FFMPEG_AMF_WRITER_ID, enable_log);
            trace->pVtbl->ಗಣ_Writer_Level(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, level_amf);
            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, enable_log);
        }


        ret = ctx->factory->pVtbl->CreateContext(ctx->factory, &ctx->context);
        ಆದರೆ (ret == AMF_OK) {
            AMF_ನಿಯೋಜಿಸು_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            ಹಿಂತಿರುಗಿ 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    ಹಿಂತಿರುಗಿ ret;
}

#ಆದರೆ CONFIG_DXVA2
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *ಮಗು_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = ಮಗು_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_ಫಲಿತಾಂಶ          res;
    ಪೂರ್ಣಾಂಕ ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    ಆದರೆ (FAILED(hr)) {
        av_log(ಮಗು_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)hr);
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    hr = IDirect3_DDevice_Manager9_ಬೀಗ_Device(hwctx->devmgr, device_handle, &device, FALSE);
    ಆದರೆ (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(ಮಗು_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    ಆದರೆ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ಆದರೆ (res == AMF_NOT_SUPPORTED)
            av_log(ಮಗು_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        ಇಲ್ಲದಿದ್ದರೆ
            av_log(ಮಗು_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        ಹಿಂತಿರುಗಿ AVERROR(ENODEV);
    }
    av_log(ಮಗು_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_D3D11VA
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *ಮಗು_device_ctx)
{
    AMF_ಫಲಿತಾಂಶ res;
    AVD3D11VADeviceContext *hwctx = ಮಗು_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    ಆದರೆ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ಆದರೆ (res == AMF_NOT_SUPPORTED)
            av_log(ಮಗು_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        ಇಲ್ಲದಿದ್ದರೆ
            av_log(ಮಗು_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        ಹಿಂತಿರುಗಿ AVERROR(ENODEV);
    }
    av_log(ಮಗು_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_D3D12VA
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *ಮಗು_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = ಮಗು_device_ctx->hwctx;
    AMF_ಫಲಿತಾಂಶ res;
    AMFContext2 *context2 = ಖಾಲಿ;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (ಶೂನ್ಯ**)&context2);
    AMF_RETURN_IF_FALSE(ಮಗು_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    ಆದರೆ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ಆದರೆ (res == AMF_NOT_SUPPORTED)
            av_log(ಮಗು_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        ಇಲ್ಲದಿದ್ದರೆ
            av_log(ಮಗು_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        ಹಿಂತಿರುಗಿ AVERROR(ENODEV);
    }
    av_log(ಮಗು_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ


ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *ಮಗು_device_ctx, AVDictionary *opts,
                              ಪೂರ್ಣಾಂಕ flags)
{
#ಆದರೆ CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    ಆದರೆ(ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆಯ್ಕೆ (ಮಗು_device_ctx->type) {
#ಆದರೆ CONFIG_DXVA2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DXVA2:
        ಹಿಂತಿರುಗಿ amf_init_from_dxva2_device(amf_ctx, ಮಗು_device_ctx);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
        ಹಿಂತಿರುಗಿ amf_init_from_d3d11_device(amf_ctx, ಮಗು_device_ctx);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D12VA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D12VA:
        ಹಿಂತಿರುಗಿ amf_init_from_d3d12_device(amf_ctx, ಮಗು_device_ctx);
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        av_log(ಮಗು_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(ಮಗು_device_ctx->type));
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ amf_unmap_ಚೌಕಟ್ಟು(av_ಬಳಸದ AVHWFramesContext *ಬಳಸದ, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ amf_map_ಚೌಕಟ್ಟು(AVHWFramesContext *device_ctx, AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AMFSurface *surface = (AMFSurface *)src->ದತ್ತಾಂಶ[0];
    AMFSurface1 *surface1 = ಖಾಲಿ;
    size_t *linesizes = ಖಾಲಿ;
    uint8_t **map = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ amf_mem_flags = AMF_ಸ್ಮರಣೆ_CPU_NONE;
    ಸ್ಥಿರಾಂಕ AMFGuid guid = IID_AMFSurface1();
    AMF_ಫಲಿತಾಂಶ res = AMF_FAIL;
    size_t plane_ಎಣಿಕೆ = 0;
    ಪೂರ್ಣಾಂಕ ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != ಖಾಲಿ, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (ಶೂನ್ಯ**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    ಆದರೆ (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_ಸ್ಮರಣೆ_CPU_READ;

    ಆದರೆ (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_ಸ್ಮರಣೆ_CPU_WRITE;

    plane_ಎಣಿಕೆ = AMF_IFACE_CALL(surface, Get_Planes_ಎಣಿಕೆ);
    linesizes = av_malloc_array(ಗಾತ್ರ(size_t), plane_ಎಣಿಕೆ);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(ಗಾತ್ರ(uint8_t *), plane_ಎಣಿಕೆ);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_ಗಮ್ಯ_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_ಎಣಿಕೆ, linesizes, (ಶೂನ್ಯ**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src, &amf_unmap_ಚೌಕಟ್ಟು, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;
    av_ಚೌಕಟ್ಟು_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_ಬಫರ್_unref(&dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ plane = 0; plane < plane_ಎಣಿಕೆ; ++plane)
    {
        dst->ದತ್ತಾಂಶ[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    ಆದರೆ (map)
        av_free(map);

    ಆದರೆ (linesizes)
        av_free(linesizes);

    ಆದರೆ (ret < 0 && surface1 != ಖಾಲಿ)
        AMF_IFACE_CALL(surface1, Release);

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(AVAMFDeviceContext),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(AMFFramesContext),

    .device_create        = amf_device_create,
    .device_derive        = amf_device_derive,
    .device_init          = amf_device_init,
    .device_uninit        = amf_device_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_constraints = amf_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_init          = amf_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್    = amf_get_ಬಫರ್,
    .transfer_get_formats = amf_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ     = amf_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ,
    .transfer_ದತ್ತಾಂಶ_from   = amf_transfer_ದತ್ತಾಂಶ_from,
    .map_from             = amf_map_ಚೌಕಟ್ಟು,

    .pix_fmts             = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
